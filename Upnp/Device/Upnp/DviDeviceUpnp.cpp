#include <DviDeviceUpnp.h>
#include <DviDevice.h>
#include <OhNetTypes.h>
#include <Buffer.h>
#include <Stack.h>
#include <DviStack.h>
#include <NetworkInterfaceList.h>
#include <Discovery.h>
#include <OsWrapper.h>
#include <Maths.h>
#include <Printer.h>
#include <Ascii.h>
#include <DviServerUpnp.h>
#include <Ssdp.h>
#include <Converter.h>
#include <Parser.h>
#include <MimeTypes.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// DviDeviceUpnp

const Brn DviDeviceUpnp::kProtocolName("Upnp");
const Brn DviDeviceUpnp::kDeviceXmlName("device.xml");
const Brn DviDeviceUpnp::kServiceXmlName("service.xml");
const Brn DviDeviceUpnp::kControlUrlTail("control");
const Brn DviDeviceUpnp::kEventUrlTail("event");

DviDeviceUpnp::DviDeviceUpnp(DviDevice& aDevice)
    : iDevice(aDevice)
    , iLock("DMUP")
    , iSuppressScheduledEvents(false)
{
    iLock.Wait();
    iServer = &DviStack::ServerUpnp();
    NetworkInterfaceList& nifList = Stack::NetworkInterfaceList();
    Functor functor = MakeFunctor(*this, &DviDeviceUpnp::SubnetListChanged);
    iSubnetChangeListenerId = nifList.AddSubnetChangeListener(functor);
    std::vector<NetworkInterface*>* subnetList = nifList.CreateSubnetList();
    for (TUint i=0; i<subnetList->size(); i++) {
        NetworkInterface* subnet = (*subnetList)[i];
        AddInterface(*subnet);
    }
    NetworkInterfaceList::DestroySubnetList(subnetList);
    iAliveTimer = new Timer(MakeFunctor(*this, &DviDeviceUpnp::SendAliveNotifications));
    iLock.Signal();
}

DviDeviceUpnp::~DviDeviceUpnp()
{
    delete iAliveTimer;
    iLock.Wait();
    Stack::NetworkInterfaceList().RemoveSubnetChangeListener(iSubnetChangeListenerId);
    for (TUint i=0; i<iInterfaces.size(); i++) {
        delete iInterfaces[i];
    }
    iSuppressScheduledEvents = true;
    iLock.Signal();
    for (TUint i=0; i<iMsgSchedulers.size(); i++) {
        delete iMsgSchedulers[i];
    }
}

Brn DviDeviceUpnp::Domain() const
{
    const TChar* ptr;
    GetAttribute("Domain", &ptr);
    Brn domain(ptr);
    return domain;
}

Brn DviDeviceUpnp::Type() const
{
    const TChar* ptr;
    GetAttribute("Type", &ptr);
    Brn type(ptr);
    return type;
}

TUint DviDeviceUpnp::Version() const
{
    const TChar* ptr;
    GetAttribute("Version", &ptr);
    Brn verBuf(ptr);
    return Ascii::Uint(verBuf);
}

void DviDeviceUpnp::MsgSchedulerComplete(DeviceMsgScheduler* aScheduler)
{
    iLock.Wait();
    // FIXME: iSuppressScheduledEvents hack
    // I've added iSuppressScheduledEvents to fix the race condition
    // where the destructor is attempting to delete the schedulers at
    // the same time as the schedulers are still running and can call
    // this method to try to delete themselves. I consider it a hack
    // and I would recommend that we review this code and try to fix
    // it in a cleaner manner. --AW
    bool shouldDelete = false;
    if (!iSuppressScheduledEvents)
    {
        shouldDelete = true;
        for (TUint i=0; i<iMsgSchedulers.size(); i++) {
            DeviceMsgScheduler* scheduler = iMsgSchedulers[i];
            if (scheduler == aScheduler) {
                iMsgSchedulers.erase(iMsgSchedulers.begin() + i);
                break;
            }
        }
    }
    iLock.Signal();
    // If iSuppressScheduledEvents was set while we held the lock, we
    // are not responsible here for deleting the scheduler - that will be
    // taken care of in our destructor. If iSuppressScheduledEvents *was*
    // set, we have now removed the scheduler from the list and so we know
    // that it is safe for us to delete it here.
    if (shouldDelete)
    {
        delete aScheduler;
    }
}

void DviDeviceUpnp::AddInterface(const NetworkInterface& aNif)
{
    TIpAddress addr = aNif.Address();
    Bwh uriBase;
    TUint port = iServer->Port(addr);
    DviDevice* root = (iDevice.IsRoot()? &iDevice : iDevice.Root());
    root->GetUriBase(uriBase, addr, port, *this);
    DviDeviceUpnp::Nif* nif = new DviDeviceUpnp::Nif(*this, iDevice, aNif, uriBase, port);
    iInterfaces.push_back(nif);
}

void DviDeviceUpnp::SubnetListChanged()
{
    // !!!! untested
    if (!iDevice.Enabled()) {
        return;
    }

    TBool update = false;
	std::vector<Nif*> pendingDelete;
    iLock.Wait();
    NetworkInterfaceList& interfaceList = Stack::NetworkInterfaceList();
    std::vector<NetworkInterface*>* subnetList = interfaceList.CreateSubnetList();
    const std::vector<NetworkInterface*>& nifList = interfaceList.List();
    TUint i = 0;
    iMsgSchedulers.clear();
    // remove listeners whose interface is no longer available
    while (i<iInterfaces.size()) {
        if (FindInterface(iInterfaces[i]->Interface(), nifList) != -1) {
			i++;
		}
		else {
			iInterfaces[i]->SetPendingDelete();
			pendingDelete.push_back(iInterfaces[i]);
            iInterfaces.erase(iInterfaces.begin() + i);
        }
    }

	
	for (i=0; i<iInterfaces.size(); i++) {
        if (FindInterface(iInterfaces[i]->Interface(), nifList) == -1) {
            delete iInterfaces[i];
            iInterfaces.erase(iInterfaces.begin() + i);
        }
    }
    // add listeners for new subnets
    for (i=0; i<subnetList->size(); i++) {
        NetworkInterface* subnet = (*subnetList)[i];
        if (FindListenerForSubnet(subnet->Subnet()) == -1) {
            AddInterface(*subnet);
            update = true;
        }
    }

	if (update) {
		// halt any ssdp broadcasts/responses that are currently in progress
		// (in case they're for a subnet that's no longer valid)
		// they'll be advertised again by the SendUpdateNotifications() call below
		for (i=0; i<iMsgSchedulers.size(); i++) {
			iMsgSchedulers[i]->Stop();
		}
	}

    iLock.Signal();
    NetworkInterfaceList::DestroySubnetList(subnetList);
	for (i=0; i<pendingDelete.size(); i++) {
		delete pendingDelete[i];
	}

    if (update) {
        SendUpdateNotifications();
    }
}

TInt DviDeviceUpnp::FindInterface(TIpAddress aInterface, const std::vector<NetworkInterface*>& aNifList)
{
    for (TUint i=0; i<aNifList.size(); i++) {
        if (aNifList[i]->Address() == aInterface) {
            return i;
        }
    }
    return -1;
}

TInt DviDeviceUpnp::FindListenerForSubnet(TIpAddress aSubnet)
{
    for (TUint i=0; i<iInterfaces.size(); i++) {
        if (iInterfaces[i]->Subnet() == aSubnet) {
            return i;
        }
    }
    return -1;
}

TInt DviDeviceUpnp::FindListenerForInterface(TIpAddress aInterface)
{
    for (TUint i=0; i<iInterfaces.size(); i++) {
        if (iInterfaces[i]->Interface() == aInterface) {
            return i;
        }
    }
    return -1;
}

void DviDeviceUpnp::WriteResource(const Brx& aUriTail, TIpAddress aInterface, std::vector<char*>& aLanguageList, IResourceWriter& aResourceWriter)
{
    AutoMutex a(iLock);
    if (aUriTail == kDeviceXmlName) {
        Brh xml;
        Brn xmlBuf;
        const TInt index = FindListenerForInterface(aInterface);
        if (index == -1) {
            return;
        }
        if (iDevice.IsRoot()) {
            const Brx& cachedXml = iInterfaces[index]->DeviceXml();
            if (cachedXml.Bytes() > 0) {
                xmlBuf.Set(cachedXml);
            }
        }
        if (xmlBuf.Bytes() == 0) {
            GetDeviceXml(xml, aInterface);
            if (iDevice.IsRoot()) {
                iInterfaces[index]->SetDeviceXml(xml);
                xmlBuf.Set(iInterfaces[index]->DeviceXml());
            }
            else {
                xmlBuf.Set(xml);
            }
        }
        aResourceWriter.WriteResourceBegin(xmlBuf.Bytes(), kOhNetMimeTypeXml);
        aResourceWriter.WriteResource(xmlBuf.Ptr(), xmlBuf.Bytes());
        aResourceWriter.WriteResourceEnd();
    }
    else {
        Parser parser(aUriTail);
        Brn buf = parser.Next('/');
        Brn rem = parser.Remaining();
        if (buf == DviDevice::kResourceDir) {
            IResourceManager* resMgr = iDevice.ResourceManager();
            if (resMgr != NULL) {
                resMgr->WriteResource(rem, aInterface, aLanguageList, aResourceWriter);
            }
        }
        else if (rem == kServiceXmlName) {
            DviService* service = NULL;
            const TUint count = iDevice.ServiceCount();
            for (TUint i=0; i<count; i++) {
                DviService& s = iDevice.Service(i);
                if (s.ServiceType().PathUpnp() == buf) {
                    service = &s;
                    break;
                }
            }
            if (service == NULL) {
                THROW(ReaderError);
            }
            WriteServiceXml(*service, aResourceWriter);
        }
    }
}

const Brx& DviDeviceUpnp::ProtocolName() const
{
    return kProtocolName;
}

void DviDeviceUpnp::Enable()
{
    iLock.Wait();
    
    // check we have at least the basic attributes requried for advertisement
    ASSERT(Domain().Bytes() > 0);
    ASSERT(Type().Bytes() > 0);
    ASSERT(Version() > 0);
    
    for (TUint i=0; i<iInterfaces.size(); i++) {
        DviDeviceUpnp::Nif* nif = iInterfaces[i];
        Bwh uriBase;
        DviDevice* root = (iDevice.IsRoot()? &iDevice : iDevice.Root());
        nif->UpdateServerPort(*iServer);
        root->GetUriBase(uriBase, nif->Interface(), nif->ServerPort(), *this);
        nif->UpdateUriBase(uriBase);
        nif->ClearDeviceXml();
        if (iDevice.ResourceManager() != NULL) {
            const TChar* name = NULL;
            GetAttribute("FriendlyName", &name);
            nif->BonjourRegister(name);
            GetAttribute("MdnsHostName", &name);
            if (name != NULL) {
                DviStack::MdnsProvider()->MdnsSetHostName(name);
                Bwh redirectedPath(iDevice.Udn().Bytes() + kProtocolName.Bytes() + iDevice.kResourceDir.Bytes() + 4);
                redirectedPath.Append('/');
                redirectedPath.Append(iDevice.Udn());
                redirectedPath.Append('/');
                redirectedPath.Append(kProtocolName);
                redirectedPath.Append('/');
                redirectedPath.Append(iDevice.kResourceDir);
                redirectedPath.Append('/');
                DviStack::ServerUpnp().Redirect(Brn("/"), redirectedPath);
            }
        }
    }
    iLock.Signal();
    SendAliveNotifications();
}

void DviDeviceUpnp::Disable(Functor& aComplete)
{
    iLock.Wait();
    iDisableComplete = aComplete;
    TUint i;
    for (i=0; i<iMsgSchedulers.size(); i++) {
        iMsgSchedulers[i]->Stop();
    }
    iSubnetDisableCount = (TUint)iInterfaces.size();
    Functor functor = MakeFunctor(*this, &DviDeviceUpnp::SubnetDisabled);
    for (i=0; i<iSubnetDisableCount; i++) {
        Bwh uri;
        GetUriDeviceXml(uri, iInterfaces[i]->UriBase());
        iMsgSchedulers.push_back(new DeviceMsgSchedulerNotifyByeBye(iDevice, *this, iInterfaces[i]->Interface(),
                                                                    uri, iDevice.ConfigId(), functor));
    }
    for (TUint i=0; i<iInterfaces.size(); i++) {
        iInterfaces[i]->BonjourDeregister();
    }
    const TChar* name = NULL;
    GetAttribute("MdnsHostName", &name);
    if (name != NULL) {
        DviStack::MdnsProvider()->MdnsSetHostName("");
    }

    iLock.Signal();
}

void DviDeviceUpnp::GetAttribute(const TChar* aKey, const TChar** aValue) const
{
    *aValue = iAttributeMap.Get(aKey);
}

void DviDeviceUpnp::SetAttribute(const TChar* aKey, const TChar* aValue)
{
    if (strcmp(aKey, "TestUpdate") == 0) {
        SendUpdateNotifications();
        return;
    }
    if (strcmp(aKey, "MdnsHostName") == 0) {
        ASSERT(iDevice.ResourceManager() != NULL);
        ASSERT(DviStack::MdnsProvider() != NULL);
    }

    iAttributeMap.Set(aKey, aValue);
}

void DviDeviceUpnp::SetCustomData(const TChar* aTag, void* aData)
{
    Brn tag(aTag);
    if (tag == Brn("Server")) {
        iServer = reinterpret_cast<DviServerUpnp*>(aData);
    }
}

void DviDeviceUpnp::SubnetDisabled()
{
    iLock.Wait();
    ASSERT(iSubnetDisableCount != 0);
    TBool signal = (--iSubnetDisableCount == 0);
    iLock.Signal();
    if (signal) {
        iDisableComplete();
    }
}

void DviDeviceUpnp::SubnetUpdated()
{
    iLock.Wait();
    ASSERT(iUpdateCount != 0);
    TBool signal = (--iUpdateCount == 0);
    iLock.Signal();
    if (signal) {
        DviStack::UpdateBootId();
        SendAliveNotifications();
    }
}

void DviDeviceUpnp::SendAliveNotifications()
{
    if(!iDevice.Enabled()) {
        return;
    }
    iLock.Wait();
    for (TUint i=0; i<iInterfaces.size(); i++) {
        Bwh uri;
        GetUriDeviceXml(uri, iInterfaces[i]->UriBase());
        iMsgSchedulers.push_back(new DeviceMsgSchedulerNotifyAlive(iDevice, *this, iInterfaces[i]->Interface(),
                                                                   uri, iDevice.ConfigId()));
    }
    TUint maxUpdateTimeMs = Stack::InitParams().DvMaxUpdateTimeSecs() * 1000;
    TUint updateTimeMs = Random((2*maxUpdateTimeMs)/3, maxUpdateTimeMs/3);
    iAliveTimer->FireIn(updateTimeMs);
    iLock.Signal();
}

void DviDeviceUpnp::SendUpdateNotifications()
{
    iLock.Wait();
    iAliveTimer->Cancel();
    iUpdateCount = (TUint)iInterfaces.size();
    Functor functor = MakeFunctor(*this, &DviDeviceUpnp::SubnetUpdated);
    for (TUint i=0; i<iInterfaces.size(); i++) {
        Bwh uri;
        GetUriDeviceXml(uri, iInterfaces[i]->UriBase());
        iMsgSchedulers.push_back(new DeviceMsgSchedulerNotifyUpdate(iDevice, *this, iInterfaces[i]->Interface(),
                                                                    uri, iDevice.ConfigId(), functor));
    }
    iLock.Signal();
}

void DviDeviceUpnp::GetUriDeviceXml(Bwh& aUri, const Brx& aUriBase)
{
    aUri.Grow(aUriBase.Bytes() + kDeviceXmlName.Bytes());
    aUri.Append(aUriBase);
    aUri.Append(kDeviceXmlName);
}

void DviDeviceUpnp::GetDeviceXml(Brh& aXml, TIpAddress aInterface)
{
    DviDeviceUpnpXmlWriter writer(*this);
    writer.Write(aInterface);
    writer.TransferTo(aXml);
}

void DviDeviceUpnp::WriteServiceXml(const DviService& aService, IResourceWriter& aResourceWriter)
{
    WriterBwh writer(1024);

    writer.Write("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
    writer.Write("<scpd xmlns=\"urn:schemas-upnp-org:service-1-0\">");
    writer.Write("<specVersion>");
    writer.Write("<major>1</major>");
    writer.Write("<minor>1</minor>");
    writer.Write("</specVersion>");
    writer.Write("<actionList>");
    DviService::VectorActions actions = aService.DvActions();
    for (TUint i=0; i<actions.size(); i++) {
        const Action* action = actions[i].Action();
        writer.Write("<action>");
        writer.Write("<name>");
        writer.Write(action->Name());
        writer.Write("</name>");
        writer.Write("<argumentList>");
        WriteServiceActionParams(writer, *action, true);
        WriteServiceActionParams(writer, *action, false);
        writer.Write("</argumentList>");
        writer.Write("</action>");
    }
    writer.Write("</actionList>");
    writer.Write("<serviceStateTable>");
    const DviService::VectorProperties& properties = aService.Properties();
    for (TUint i=0; i<properties.size(); i++) {
        WriteStateVariable(writer, properties[i]->Parameter(), true, NULL);
    }
    for (TUint i=0; i<actions.size(); i++) {
        const Action* action = actions[i].Action();
        WriteTechnicalStateVariables(writer, action, action->InputParameters());
        WriteTechnicalStateVariables(writer, action, action->OutputParameters());
    }
    writer.Write("</serviceStateTable>");
    writer.Write("</scpd>");

    Brh xml;
    writer.TransferTo(xml);
    aResourceWriter.WriteResourceBegin(xml.Bytes(), kOhNetMimeTypeXml);
    aResourceWriter.WriteResource(xml.Ptr(), xml.Bytes());
    aResourceWriter.WriteResourceEnd();
}

void DviDeviceUpnp::WriteServiceActionParams(WriterBwh& aWriter, const Action& aAction, TBool aIn)
{
    const Action::VectorParameters& params = (aIn? aAction.InputParameters() : aAction.OutputParameters());
    for (TUint i=0; i<params.size(); i++) {
        OpenHome::Net::Parameter* param = params[i];
        aWriter.Write("<argument>");
        aWriter.Write("<name>");
        aWriter.Write(param->Name());
        aWriter.Write("</name>");
        aWriter.Write("<direction>");
        aWriter.Write(aIn? "in" : "out");
        aWriter.Write("</direction>");
        aWriter.Write("<relatedStateVariable>");
        if (param->Type() == OpenHome::Net::Parameter::eTypeRelated) {
            const Brx& relatedVar = static_cast<ParameterRelated*>(param)->Related().Parameter().Name();
            aWriter.Write(relatedVar);
        }
        else {
            Bwh relatedVar;
            GetRelatedVariableName(relatedVar, aAction.Name(), param->Name());
            aWriter.Write(relatedVar);
        }
        aWriter.Write("</relatedStateVariable>");
        aWriter.Write("</argument>");
    }
}

void DviDeviceUpnp::GetRelatedVariableName(Bwh& aName, const Brx& aActionName, const Brx& aParameterName)
{
    static const Brn prefix("A_ARG_");
    const TUint len = prefix.Bytes() + aActionName.Bytes() + 1 + aParameterName.Bytes();
    aName.Grow(len);
    aName.Append(prefix);
    aName.Append(aActionName);
    aName.Append('_');
    aName.Append(aParameterName);
}


void DviDeviceUpnp::WriteStateVariable(IWriter& aWriter, const OpenHome::Net::Parameter& aParam, TBool aEvented, const Action* aAction)
{
    aWriter.Write(Brn("<stateVariable sendEvents="));
    if (aEvented) {
        aWriter.Write(Brn("\"yes\">"));
    }
    else {
        aWriter.Write(Brn("\"no\">"));
    }
    aWriter.Write(Brn("<name>"));
    if (aEvented) {
        aWriter.Write(aParam.Name());
    }
    else {
        Bwh name;
        GetRelatedVariableName(name, aAction->Name(), aParam.Name());
        aWriter.Write(name);
    }
    aWriter.Write(Brn("</name>"));
    aWriter.Write(Brn("<dataType>"));
    switch (aParam.Type())
    {
    case OpenHome::Net::Parameter::eTypeBool:
        aWriter.Write(Brn("boolean"));
        break;
    case OpenHome::Net::Parameter::eTypeInt:
        aWriter.Write(Brn("i4"));
        break;
    case OpenHome::Net::Parameter::eTypeUint:
        aWriter.Write(Brn("ui4"));
        break;
    case OpenHome::Net::Parameter::eTypeString:
        aWriter.Write(Brn("string"));
        break;
    case OpenHome::Net::Parameter::eTypeBinary:
        aWriter.Write(Brn("bin.base64"));
        break;
    case OpenHome::Net::Parameter::eTypeRelated:
        ASSERTS();
        break;
    }
    aWriter.Write(Brn("</dataType>"));
    switch (aParam.Type())
    {
    case OpenHome::Net::Parameter::eTypeBool:
    case OpenHome::Net::Parameter::eTypeBinary:
        break;
    case OpenHome::Net::Parameter::eTypeInt:
    {
        const OpenHome::Net::ParameterInt& paramInt = static_cast<const OpenHome::Net::ParameterInt&>(aParam);
        if (paramInt.MinValue() != ParameterInt::kValueMin ||
            paramInt.MaxValue() != ParameterInt::kValueMax ||
            paramInt.Step()     != ParameterInt::kStep) {
            aWriter.Write(Brn("<allowedValueRange>"));
            aWriter.Write(Brn("<minimum>"));
            WriterAscii writerAscii(aWriter);
            writerAscii.WriteInt(paramInt.MinValue());
            aWriter.Write(Brn("</minimum>"));
            aWriter.Write(Brn("<maximum>"));
            writerAscii.WriteInt(paramInt.MaxValue());
            aWriter.Write(Brn("</maximum>"));
            aWriter.Write(Brn("<step>"));
            writerAscii.WriteInt(paramInt.Step());
            aWriter.Write(Brn("</step>"));
            aWriter.Write(Brn("</allowedValueRange>"));
            }
    }
        break;
    case OpenHome::Net::Parameter::eTypeUint:
    {
        const OpenHome::Net::ParameterUint& paramUint = static_cast<const OpenHome::Net::ParameterUint&>(aParam);
        if (paramUint.MinValue() != ParameterUint::kValueMin ||
            paramUint.MaxValue() != ParameterUint::kValueMax ||
            paramUint.Step()     != ParameterUint::kStep) {
            aWriter.Write(Brn("<allowedValueRange>"));
            aWriter.Write(Brn("<minimum>"));
            WriterAscii writerAscii(aWriter);
            writerAscii.WriteUint(paramUint.MinValue());
            aWriter.Write(Brn("</minimum>"));
            aWriter.Write(Brn("<maximum>"));
            writerAscii.WriteUint(paramUint.MaxValue());
            aWriter.Write(Brn("</maximum>"));
            aWriter.Write(Brn("<step>"));
            writerAscii.WriteUint(paramUint.Step());
            aWriter.Write(Brn("</step>"));
            aWriter.Write(Brn("</allowedValueRange>"));
            }
    }
        break;
    case OpenHome::Net::Parameter::eTypeString:
    {
        const OpenHome::Net::ParameterString& paramStr = static_cast<const OpenHome::Net::ParameterString&>(aParam);
        const ParameterString::Map& allowedVals = paramStr.AllowedValues();
        if (allowedVals.size() > 0) {
            aWriter.Write(Brn("<allowedValueList>"));
            ParameterString::Map::const_iterator it = allowedVals.begin();
            while (it != allowedVals.end()) {
                aWriter.Write(Brn("<allowedValue>"));
                aWriter.Write(*(it->second));
                aWriter.Write(Brn("</allowedValue>"));
                it++;
            }
            aWriter.Write(Brn("</allowedValueList>"));
        }
    }
        break;
    case OpenHome::Net::Parameter::eTypeRelated:
        ASSERTS();
        break;
    }
    aWriter.Write(Brn("</stateVariable>"));
}

void DviDeviceUpnp::WriteTechnicalStateVariables(IWriter& aWriter, const Action* aAction, const Action::VectorParameters& aParams)
{
    for (TUint i=0; i<aParams.size(); i++) {
        if (aParams[i]->Type() != OpenHome::Net::Parameter::eTypeRelated) {
            WriteStateVariable(aWriter, *(aParams[i]), false, aAction);
        }
    }
}

void DviDeviceUpnp::SsdpSearchAll(const Endpoint& aEndpoint, TUint aMx, TIpAddress aInterface)
{
    if (iDevice.Enabled()) {
        iLock.Wait();
        TInt index = FindListenerForInterface(aInterface);
        if (index != -1) {
            Bwh uri;
            GetUriDeviceXml(uri, iInterfaces[index]->UriBase());
            iMsgSchedulers.push_back(new DeviceMsgSchedulerMsearchAll(iDevice, *this, aEndpoint, aMx,
                                                                      uri, iDevice.ConfigId()));
        }
        iLock.Signal();
    }
}

void DviDeviceUpnp::SsdpSearchRoot(const Endpoint& aEndpoint, TUint aMx, TIpAddress aInterface)
{
    if (iDevice.Enabled() && iDevice.IsRoot()) {
        iLock.Wait();
        TInt index = FindListenerForInterface(aInterface);
        if (index != -1) {
            Bwh uri;
            GetUriDeviceXml(uri, iInterfaces[index]->UriBase());
            iMsgSchedulers.push_back(new DeviceMsgSchedulerMsearchRoot(iDevice, *this, aEndpoint, aMx,
                                                                       uri, iDevice.ConfigId()));
        }
        iLock.Signal();
    }
}

void DviDeviceUpnp::SsdpSearchUuid(const Endpoint& aEndpoint, TUint aMx, TIpAddress aInterface, const Brx& aUuid)
{
    if (iDevice.Enabled() && iDevice.Udn() == aUuid) {
        iLock.Wait();
        TInt index = FindListenerForInterface(aInterface);
        if (index != -1) {
            Bwh uri;
            GetUriDeviceXml(uri, iInterfaces[index]->UriBase());
            iMsgSchedulers.push_back(new DeviceMsgSchedulerMsearchUuid(iDevice, *this, aEndpoint, aMx,
                                                                       uri, iDevice.ConfigId()));
        }
        iLock.Signal();
    }
}

void DviDeviceUpnp::SsdpSearchDeviceType(const Endpoint& aEndpoint, TUint aMx, TIpAddress aInterface, const Brx& aDomain, const Brx& aType, TUint aVersion)
{
    if (iDevice.Enabled() && Version() >= aVersion && Domain() == aDomain && Type() == aType) {
        iLock.Wait();
        TInt index = FindListenerForInterface(aInterface);
        if (index != -1) {
            Bwh uri;
            GetUriDeviceXml(uri, iInterfaces[index]->UriBase());
            iMsgSchedulers.push_back(new DeviceMsgSchedulerMsearchDeviceType(iDevice, *this, aEndpoint, aMx,
                                                                             uri, iDevice.ConfigId()));
        }
        iLock.Signal();
    }
}

void DviDeviceUpnp::SsdpSearchServiceType(const Endpoint& aEndpoint, TUint aMx, TIpAddress aInterface, const Brx& aDomain, const Brx& aType, TUint aVersion)
{
    iLock.Wait();
    if (iDevice.Enabled()) {
        const TUint count = iDevice.ServiceCount();
        for (TUint i=0; i<count; i++) {
            const OpenHome::Net::ServiceType& serviceType = iDevice.Service(i).ServiceType();
            if (serviceType.Version() >= aVersion && serviceType.Domain() == aDomain && serviceType.Name() == aType) {
                TInt index = FindListenerForInterface(aInterface);
                if (index != -1) {
                    Bwh uri;
                    GetUriDeviceXml(uri, iInterfaces[index]->UriBase());
                    iMsgSchedulers.push_back(new DeviceMsgSchedulerMsearchServiceType(iDevice, *this, aEndpoint, aMx, serviceType,
                                                                                      uri, iDevice.ConfigId()));
                }
                break;
            }
        }
    }
    iLock.Signal();
}


// DviDeviceUpnp::Nif

DviDeviceUpnp::Nif::Nif(DviDeviceUpnp& aDeviceUpnp, DviDevice& aDevice, const NetworkInterface& aNif, Bwh& aUriBase, TUint aServerPort)
    : iDeviceUpnp(&aDeviceUpnp)
    , iDevice(aDevice)
    , iServerPort(aServerPort)
    , iBonjourWebPage(NULL)
{
    iListener = &Stack::MulticastListenerClaim(aNif.Address());
    iId = iListener->AddMsearchHandler(this);
    iSubnet = aNif.Subnet();
    iInterface = aNif.Address();
    aUriBase.TransferTo(iUriBase);
}

DviDeviceUpnp::Nif::~Nif()
{
    if (iBonjourWebPage != NULL) {
        iBonjourWebPage->SetDisabled();
        delete iBonjourWebPage;
    }
    iListener->RemoveMsearchHandler(iId);
    Stack::MulticastListenerRelease(iInterface);
}

TIpAddress DviDeviceUpnp::Nif::Interface() const
{
    return iListener->Interface();
}

TIpAddress DviDeviceUpnp::Nif::Subnet() const
{
    return iSubnet;
}

const Brx& DviDeviceUpnp::Nif::UriBase() const
{
    ASSERT(iUriBase.Bytes() > 0);
    return iUriBase;
}

void DviDeviceUpnp::Nif::UpdateServerPort(DviServerUpnp& aServer)
{
    iServerPort = aServer.Port(iInterface);
}

void DviDeviceUpnp::Nif::UpdateUriBase(Bwh& aUriBase)
{
    aUriBase.TransferTo(iUriBase);
}

TUint DviDeviceUpnp::Nif::ServerPort() const
{
    return iServerPort;
}

const Brx& DviDeviceUpnp::Nif::DeviceXml() const
{
    return iDeviceXml;
}

void DviDeviceUpnp::Nif::SetDeviceXml(Brh& aXml)
{
    aXml.TransferTo(iDeviceXml);
}

void DviDeviceUpnp::Nif::ClearDeviceXml()
{
    Brh tmp;
    iDeviceXml.TransferTo(tmp);
}

void DviDeviceUpnp::Nif::SetPendingDelete()
{
	Stack::Mutex().Wait();
	iDeviceUpnp = NULL;
	Stack::Mutex().Signal();
}

void DviDeviceUpnp::Nif::BonjourRegister(const TChar* aName)
{
    if (aName != NULL) {
        if (iBonjourWebPage == NULL) {
            IMdnsProvider* mdnsProvider = DviStack::MdnsProvider();
            if (mdnsProvider != NULL) {
                iBonjourWebPage = new BonjourWebPage(*mdnsProvider);
            }
        }
        if (iBonjourWebPage != NULL) {
            Bwh path(iDevice.Udn().Bytes() + iDeviceUpnp->kProtocolName.Bytes() + iDevice.kResourceDir.Bytes() + 5);
            path.Append('/');
            path.Append(iDevice.Udn());
            path.Append('/');
            path.Append(iDeviceUpnp->kProtocolName);
            path.Append('/');
            path.Append(iDevice.kResourceDir);
            path.Append('/');
            path.PtrZ();
            iBonjourWebPage->SetEnabled(aName, iInterface, iServerPort, (const TChar*)path.Ptr());
        }
    }
}

void DviDeviceUpnp::Nif::BonjourDeregister()
{
    if (iBonjourWebPage != NULL) {
        iBonjourWebPage->SetDisabled();
    }
}

DviDeviceUpnp* DviDeviceUpnp::Nif::Device()
{
	Stack::Mutex().Wait();
	DviDeviceUpnp* device = iDeviceUpnp;
	Stack::Mutex().Signal();
	return device;
}

void DviDeviceUpnp::Nif::SsdpSearchAll(const Endpoint& aEndpoint, TUint aMx)
{
	DviDeviceUpnp* device = Device();
	if (device != NULL) {
		device->SsdpSearchAll(aEndpoint, aMx, iListener->Interface());
	}
}

void DviDeviceUpnp::Nif::SsdpSearchRoot(const Endpoint& aEndpoint, TUint aMx)
{
    DviDeviceUpnp* device = Device();
	if (device != NULL) {
		device->SsdpSearchRoot(aEndpoint, aMx, iListener->Interface());
	}
}

void DviDeviceUpnp::Nif::SsdpSearchUuid(const Endpoint& aEndpoint, TUint aMx, const Brx& aUuid)
{
    DviDeviceUpnp* device = Device();
	if (device != NULL) {
		device->SsdpSearchUuid(aEndpoint, aMx, iListener->Interface(), aUuid);
	}
}

void DviDeviceUpnp::Nif::SsdpSearchDeviceType(const Endpoint& aEndpoint, TUint aMx, const Brx& aDomain, const Brx& aType, TUint aVersion)
{
    DviDeviceUpnp* device = Device();
	if (device != NULL) {
		device->SsdpSearchDeviceType(aEndpoint, aMx, iListener->Interface(), aDomain, aType, aVersion);
	}
}

void DviDeviceUpnp::Nif::SsdpSearchServiceType(const Endpoint& aEndpoint, TUint aMx, const Brx& aDomain, const Brx& aType, TUint aVersion)
{
    DviDeviceUpnp* device = Device();
	if (device != NULL) {
		device->SsdpSearchServiceType(aEndpoint, aMx, iListener->Interface(), aDomain, aType, aVersion);
	}
}


// DviDeviceUpnpXmlWriter

DviDeviceUpnpXmlWriter::DviDeviceUpnpXmlWriter(DviDeviceUpnp& aDeviceUpnp)
    : iDeviceUpnp(aDeviceUpnp)
    , iWriter(1024)
{
}

void DviDeviceUpnpXmlWriter::Write(TIpAddress aInterface)
{
    if (iDeviceUpnp.iDevice.IsRoot()) { // root device header
        iWriter.Write("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
        iWriter.Write("<root xmlns=\"urn:schemas-upnp-org:device-1-0\">");
        iWriter.Write("<specVersion>");
        iWriter.Write("<major>1</major>");
        iWriter.Write("<minor>1</minor>");
        iWriter.Write("</specVersion>");
    }

    iWriter.Write(Brn("<device>"));
    iWriter.Write(Brn("<deviceType>"));
    iWriter.Write(Ssdp::kUrn);
    Brn upnpDomain = iDeviceUpnp.Domain();
    Bwh canonicalDomain(upnpDomain.Bytes() + 10);
    Ssdp::UpnpDomainToCanonical(upnpDomain, canonicalDomain);
    iWriter.Write(canonicalDomain);
    iWriter.Write(Ssdp::kDeviceSeparator);
    Brn type = iDeviceUpnp.Type();
    iWriter.Write(type);
    iWriter.Write(Ssdp::kUrnSeparator);
    Bws<Ascii::kMaxUintStringBytes> verBuf;
    (void)Ascii::AppendDec(verBuf, iDeviceUpnp.Version());
    iWriter.Write(verBuf);
    iWriter.Write(Brn("</deviceType>"));
    const Brx& xmlExtension = iDeviceUpnp.iDevice.XmlExtension();
    if (xmlExtension.Bytes() != 0) {
        iWriter.Write(xmlExtension);
    }

    if (iDeviceUpnp.iDevice.ResourceManager() != NULL) {
        iWriter.Write('<');
        iWriter.Write("presentationURL");
        iWriter.Write('>');
        /* UPnP spec says to publish a relative url
           Intel device spy messes up resolution of this against the base
           (device xml) url so publish an absolute url instead */
        for (TUint i=0; i<iDeviceUpnp.iInterfaces.size(); i++) {
            if (iDeviceUpnp.iInterfaces[i]->Interface() == aInterface) {
                iWriter.Write(iDeviceUpnp.iInterfaces[i]->UriBase());
                break;
            }
        }
        iWriter.Write(DviDevice::kResourceDir);
        iWriter.Write('/');
        iWriter.Write("</");
        iWriter.Write("presentationURL");
        iWriter.Write('>');
    }
    WriteTag("friendlyName", "FriendlyName", eTagMandatory);
    WriteTag("manufacturer", "Manufacturer", eTagMandatory);
    WriteTag("manufacturerURL", "ManufacturerUrl", eTagOptional);
    WriteTag("modelDescription", "ModelDescription", eTagRecommended);
    WriteTag("modelName", "ModelName", eTagMandatory);
    WriteTag("modelNumber", "ModelNumber", eTagRecommended);
    WriteTag("modelURL", "ModelUrl", eTagOptional);
    WriteTag("serialNumber", "SerialNumber", eTagRecommended);

    iWriter.Write("<UDN>");
    iWriter.Write("uuid:");
    iWriter.Write(iDeviceUpnp.iDevice.Udn());
    iWriter.Write("</UDN>");

    WriteTag("UPC", "Upc", eTagOptional);

    const TUint serviceCount = iDeviceUpnp.iDevice.ServiceCount();
    if (serviceCount > 0) {
        iWriter.Write("<serviceList>");
        for (TUint i=0; i<serviceCount; i++) {
            const OpenHome::Net::ServiceType& serviceType = iDeviceUpnp.iDevice.Service(i).ServiceType();
            iWriter.Write("<service>");
            iWriter.Write("<serviceType>");
            iWriter.Write(serviceType.FullNameUpnp());
            iWriter.Write("</serviceType>");
            iWriter.Write("<serviceId>");
            iWriter.Write(serviceType.ServiceId());
            iWriter.Write("</serviceId>");
            iWriter.Write("<SCPDURL>");
            iWriter.Write('/');
            iWriter.Write(iDeviceUpnp.iDevice.Udn());
            iWriter.Write('/');
            iWriter.Write(iDeviceUpnp.ProtocolName());
            iWriter.Write('/');
            iWriter.Write(serviceType.PathUpnp());
            iWriter.Write('/');
            iWriter.Write(DviDeviceUpnp::kServiceXmlName);
            iWriter.Write("</SCPDURL>");
            iWriter.Write("<controlURL>");
            iWriter.Write('/');
            iWriter.Write(iDeviceUpnp.iDevice.Udn());
            iWriter.Write('/');
            iWriter.Write(serviceType.PathUpnp());
            iWriter.Write('/');
            iWriter.Write(DviDeviceUpnp::kControlUrlTail);
            iWriter.Write("</controlURL>");
            iWriter.Write("<eventSubURL>");
            iWriter.Write('/');
            iWriter.Write(iDeviceUpnp.iDevice.Udn());
            iWriter.Write('/');
            iWriter.Write(serviceType.PathUpnp());
            iWriter.Write('/');
            iWriter.Write(DviDeviceUpnp::kEventUrlTail);
            iWriter.Write("</eventSubURL>");
            iWriter.Write("</service>");
        }
        iWriter.Write("</serviceList>");
    }

    const TUint deviceCount = iDeviceUpnp.iDevice.DeviceCount();
    if (deviceCount > 0) {
        iWriter.Write("<deviceList>");
        std::vector<char*> emptyLanguageList;
        for (TUint i=0; i<deviceCount; i++) {
            TUint len = iDeviceUpnp.kProtocolName.Bytes() + 1 + iDeviceUpnp.kDeviceXmlName.Bytes();
            Bwh uri(len);
            uri.Append(iDeviceUpnp.kProtocolName);
            uri.Append('/');
            uri.Append(iDeviceUpnp.kDeviceXmlName);
            iDeviceUpnp.iDevice.Device(i).WriteResource(uri, aInterface, emptyLanguageList, *this);
        }
        iWriter.Write("</deviceList>");
    }
    iWriter.Write("</device>");
    if (iDeviceUpnp.iDevice.IsRoot()) {
        iWriter.Write("</root>");
    }
}

void DviDeviceUpnpXmlWriter::TransferTo(Brh& aBuf)
{
    iWriter.TransferTo(aBuf);
}

void DviDeviceUpnpXmlWriter::WriteTag(const TChar* aTagName, const TChar* aAttributeKey, ETagRequirementLevel aRequirementLevel)
{
    const TChar* val;
    iDeviceUpnp.GetAttribute(aAttributeKey, &val);
    if (val != NULL) {
        iWriter.Write('<');
        iWriter.Write(aTagName);
        iWriter.Write('>');
        Brn buf(val);
        Converter::ToXmlEscaped(iWriter, buf);
        iWriter.Write("</");
        iWriter.Write(aTagName);
        iWriter.Write('>');
    }
    else if (aRequirementLevel == eTagMandatory) {
        iWriter.Write('<');
        iWriter.Write(aTagName);
        iWriter.Write("/>");
    }
}

void DviDeviceUpnpXmlWriter::WriteResourceBegin(TUint /*aTotalBytes*/, const TChar* /*aMimeType*/)
{
}

void DviDeviceUpnpXmlWriter::WriteResource(const TByte* aData, TUint aBytes)
{
    Brn buf(aData, aBytes);
    iWriter.Write(buf);
}

void DviDeviceUpnpXmlWriter::WriteResourceEnd()
{
}


// DeviceMsgScheduler

DeviceMsgScheduler::~DeviceMsgScheduler()
{
    /* timer is deleted by all client-instantiated sub-classes to ensure that timer
       callbacks can't run after the most derived class dtor completes (clearing the
       v-table which gets used by the callback) */
    delete iNotifier;
}

void DeviceMsgScheduler::Stop()
{
	/* No use of mutex for iStop.  Its a signal for a scheduler to exit early and it
	   doesn't really matter if we just miss the stop signal in NextMsg - we'll either
	   get it for the next message or the scheduler will stop itself in this case */
	iStop = true;
}

DeviceMsgScheduler::DeviceMsgScheduler(DviDevice& aDevice, DviDeviceUpnp& aDeviceUpnp, TUint aEndTimeMs, TUint aTotalMsgs, Bwh& aUri)
    : iDevice(aDevice)
    , iDeviceUpnp(aDeviceUpnp)
    , iTotal(aTotalMsgs)
    , iIndex(0)
    , iEndTimeMs(aEndTimeMs)
	, iStop(false)
{
    ASSERT(iTotal > 0);
    aUri.TransferTo(iUri);
    Functor functor = MakeFunctor(*this, &DeviceMsgScheduler::NextMsg);
    iTimer = new Timer(functor);
}

void DeviceMsgScheduler::Next(TUint aIndex)
{
    if (!iDevice.IsRoot()) {
        aIndex++; // skip the root device announcement for embedded devices
    }

    switch (aIndex)
    {
    case 0:
        iNotifier->SsdpNotifyRoot(iDevice.Udn(), iUri);
        break;
    case 1:
        iNotifier->SsdpNotifyUuid(iDevice.Udn(), iUri);
        break;
    case 2:
        iNotifier->SsdpNotifyDeviceType(iDeviceUpnp.Domain(), iDeviceUpnp.Type(), iDeviceUpnp.Version(), iDevice.Udn(), iUri);
        break;
    default:
        DviService& service = iDevice.Service(aIndex - 3);
        const OpenHome::Net::ServiceType& serviceType = service.ServiceType();
        iNotifier->SsdpNotifyServiceType(serviceType.Domain(), serviceType.Name(), serviceType.Version(), iDevice.Udn(), iUri);
        break;
    }
}

void DeviceMsgScheduler::NextMsg()
{
	if (iStop) {
		iTotal = iIndex;
	}
	else {
		Next(iIndex);
		iIndex++;
	}
    if (iTotal == iIndex) {
        iDeviceUpnp.MsgSchedulerComplete(this);
        return;
    }
    else {
        ScheduleNextTimer();
    }
}

void DeviceMsgScheduler::ScheduleNextTimer() const
{
    TUint interval;
    TInt remaining = iEndTimeMs - Os::TimeInMs();
    TInt maxInterval = (remaining / (TInt)(iTotal - iIndex));
    if (maxInterval < kMinTimerIntervalMs) {
        // we're running behind.  Schedule another timer to run immediately
        interval = 0;
    }
    else {
        interval = Random((TUint)maxInterval);
    }
    iTimer->FireIn(interval);
}


// DeviceMsgSchedulerMsearch

DeviceMsgSchedulerMsearch::DeviceMsgSchedulerMsearch(DviDevice& aDevice, DviDeviceUpnp& aDeviceUpnp, const Endpoint& aRemote,
                                                     TUint aMx, TUint aTotalMsgs,
                                                     Bwh& aUri, TUint aConfigId)
    : DeviceMsgScheduler(aDevice, aDeviceUpnp, Os::TimeInMs() + (aMx * 900), aTotalMsgs, aUri)
{
    SsdpMsearchResponder* responder = new SsdpMsearchResponder(aConfigId);
    responder->SetRemote(aRemote);
    iNotifier = responder;
    ScheduleNextTimer();
}


// DeviceMsgSchedulerMsearchAll

DeviceMsgSchedulerMsearchAll::DeviceMsgSchedulerMsearchAll(DviDevice& aDevice, DviDeviceUpnp& aDeviceUpnp,
                                                           const Endpoint& aRemote, TUint aMx,
                                                           Bwh& aUri, TUint aConfigId)
    : DeviceMsgSchedulerMsearch(aDevice, aDeviceUpnp, aRemote, aMx,
                                aDevice.ServiceCount() + (aDevice.IsRoot()? 3 : 2),
                                aUri, aConfigId)
{
}

DeviceMsgSchedulerMsearchAll::~DeviceMsgSchedulerMsearchAll()
{
    delete iTimer;
}


// DeviceMsgSchedulerMsearchRoot

DeviceMsgSchedulerMsearchRoot::DeviceMsgSchedulerMsearchRoot(DviDevice& aDevice, DviDeviceUpnp& aDeviceUpnp,
                                                             const Endpoint& aRemote, TUint aMx,
                                                             Bwh& aUri, TUint aConfigId)
    : DeviceMsgSchedulerMsearch(aDevice, aDeviceUpnp, aRemote, aMx, 1, aUri, aConfigId)
{
}

DeviceMsgSchedulerMsearchRoot::~DeviceMsgSchedulerMsearchRoot()
{
    delete iTimer;
}

void DeviceMsgSchedulerMsearchRoot::Next(TUint aIndex)
{
    ASSERT(iDevice.IsRoot());
    ASSERT(aIndex == 0);
    iNotifier->SsdpNotifyRoot(iDevice.Udn(), iUri);
}


// DeviceMsgSchedulerMsearchUuid

DeviceMsgSchedulerMsearchUuid::DeviceMsgSchedulerMsearchUuid(DviDevice& aDevice, DviDeviceUpnp& aDeviceUpnp,
                                                             const Endpoint& aRemote, TUint aMx,
                                                             Bwh& aUri, TUint aConfigId)
    : DeviceMsgSchedulerMsearch(aDevice, aDeviceUpnp, aRemote, aMx, 1, aUri, aConfigId)
{
}

DeviceMsgSchedulerMsearchUuid::~DeviceMsgSchedulerMsearchUuid()
{
    delete iTimer;
}

void DeviceMsgSchedulerMsearchUuid::Next(TUint aIndex)
{
    ASSERT(aIndex == 0);
    iNotifier->SsdpNotifyUuid(iDevice.Udn(), iUri);
}


// DeviceMsgSchedulerMsearchDeviceType

DeviceMsgSchedulerMsearchDeviceType::DeviceMsgSchedulerMsearchDeviceType(DviDevice& aDevice, DviDeviceUpnp& aDeviceUpnp,
                                                                         const Endpoint& aRemote, TUint aMx,
                                                                         Bwh& aUri, TUint aConfigId)
    : DeviceMsgSchedulerMsearch(aDevice, aDeviceUpnp, aRemote, aMx, 1, aUri, aConfigId)
{
}

DeviceMsgSchedulerMsearchDeviceType::~DeviceMsgSchedulerMsearchDeviceType()
{
    delete iTimer;
}

void DeviceMsgSchedulerMsearchDeviceType::Next(TUint aIndex)
{
    ASSERT(aIndex == 0);
    iNotifier->SsdpNotifyDeviceType(iDeviceUpnp.Domain(), iDeviceUpnp.Type(), iDeviceUpnp.Version(), iDevice.Udn(), iUri);
}


// DeviceMsgSchedulerMsearchServiceType

DeviceMsgSchedulerMsearchServiceType::DeviceMsgSchedulerMsearchServiceType(DviDevice& aDevice, DviDeviceUpnp& aDeviceUpnp,
                                                                           const Endpoint& aRemote, TUint aMx,
                                                                           const OpenHome::Net::ServiceType& aServiceType,
                                                                           Bwh& aUri, TUint aConfigId)
    : DeviceMsgSchedulerMsearch(aDevice, aDeviceUpnp, aRemote, aMx, 1, aUri, aConfigId)
    , iServiceType(aServiceType)
{
}

DeviceMsgSchedulerMsearchServiceType::~DeviceMsgSchedulerMsearchServiceType()
{
    delete iTimer;
}

void DeviceMsgSchedulerMsearchServiceType::Next(TUint aIndex)
{
    ASSERT(aIndex == 0);
    iNotifier->SsdpNotifyServiceType(iServiceType.Domain(), iServiceType.Name(), iServiceType.Version(), iDevice.Udn(), iUri);
}


// DeviceMsgSchedulerNotify

DeviceMsgSchedulerNotify::DeviceMsgSchedulerNotify(DviDevice& aDevice, DviDeviceUpnp& aDeviceUpnp,
                                                   TUint aIntervalMs, TUint aTotalMsgs,
                                                   TIpAddress aInterface, Bwh& aUri, TUint aConfigId)
    : DeviceMsgScheduler(aDevice, aDeviceUpnp, Os::TimeInMs() + (aIntervalMs * aTotalMsgs), aTotalMsgs, aUri)
    , iSsdpNotifier(aInterface, aConfigId)
{
}


// DeviceMsgSchedulerNotifyAlive

DeviceMsgSchedulerNotifyAlive::DeviceMsgSchedulerNotifyAlive(DviDevice& aDevice, DviDeviceUpnp& aDeviceUpnp,
                                                             TIpAddress aInterface, Bwh& aUri, TUint aConfigId)
    : DeviceMsgSchedulerNotify(aDevice, aDeviceUpnp, kMsgIntervalMs,
                               aDevice.ServiceCount() + (aDevice.IsRoot()? 3 : 2),
                               aInterface, aUri, aConfigId)
{
    iNotifier = new SsdpNotifierAlive(iSsdpNotifier);
    ScheduleNextTimer();
}

DeviceMsgSchedulerNotifyAlive::~DeviceMsgSchedulerNotifyAlive()
{
    delete iTimer;
}


// DeviceMsgSchedulerNotifyByeBye

DeviceMsgSchedulerNotifyByeBye::DeviceMsgSchedulerNotifyByeBye(DviDevice& aDevice, DviDeviceUpnp& aDeviceUpnp,
                                                               TIpAddress aInterface, Bwh& aUri, TUint aConfigId,
                                                               Functor& aCompleted)
    : DeviceMsgSchedulerNotify(aDevice, aDeviceUpnp, kMsgIntervalMs,
                               aDevice.ServiceCount() + (aDevice.IsRoot()? 3 : 2),
                               aInterface, aUri, aConfigId)
    , iCompleted(aCompleted)
{
    iNotifier = new SsdpNotifierByeBye(iSsdpNotifier);
    ScheduleNextTimer();
}

DeviceMsgSchedulerNotifyByeBye::~DeviceMsgSchedulerNotifyByeBye()
{
    iCompleted();
    delete iTimer;
}


// DeviceMsgSchedulerNotifyUpdate

DeviceMsgSchedulerNotifyUpdate::DeviceMsgSchedulerNotifyUpdate(DviDevice& aDevice, DviDeviceUpnp& aDeviceUpnp,
                                                               TIpAddress aInterface, Bwh& aUri, TUint aConfigId,
                                                               Functor& aCompleted)
    : DeviceMsgSchedulerNotify(aDevice, aDeviceUpnp, kMsgIntervalMs,
                               aDevice.ServiceCount() + (aDevice.IsRoot()? 3 : 2),
                               aInterface, aUri, aConfigId)
    , iCompleted(aCompleted)
{
    iNotifier = new SsdpNotifierUpdate(iSsdpNotifier);
    ScheduleNextTimer();
}


DeviceMsgSchedulerNotifyUpdate::~DeviceMsgSchedulerNotifyUpdate()
{
    iCompleted();
    delete iTimer;
}
