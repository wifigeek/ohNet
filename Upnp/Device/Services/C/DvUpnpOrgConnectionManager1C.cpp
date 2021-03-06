#include "DvUpnpOrgConnectionManager1.h"
#include <OhNetTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <DvProvider.h>
#include <C/OhNet.h>
#include <OhNetTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace OpenHome;
using namespace OpenHome::Net;

class DvProviderUpnpOrgConnectionManager1C : public DvProvider
{
public:
    DvProviderUpnpOrgConnectionManager1C(DvDeviceC aDevice);
    TBool SetPropertySourceProtocolInfo(const Brx& aValue);
    void GetPropertySourceProtocolInfo(Brhz& aValue);
    TBool SetPropertySinkProtocolInfo(const Brx& aValue);
    void GetPropertySinkProtocolInfo(Brhz& aValue);
    TBool SetPropertyCurrentConnectionIDs(const Brx& aValue);
    void GetPropertyCurrentConnectionIDs(Brhz& aValue);
    void EnableActionGetProtocolInfo(CallbackConnectionManager1GetProtocolInfo aCallback, void* aPtr);
    void EnableActionPrepareForConnection(CallbackConnectionManager1PrepareForConnection aCallback, void* aPtr);
    void EnableActionConnectionComplete(CallbackConnectionManager1ConnectionComplete aCallback, void* aPtr);
    void EnableActionGetCurrentConnectionIDs(CallbackConnectionManager1GetCurrentConnectionIDs aCallback, void* aPtr);
    void EnableActionGetCurrentConnectionInfo(CallbackConnectionManager1GetCurrentConnectionInfo aCallback, void* aPtr);
private:
    void DoGetProtocolInfo(IDviInvocation& aInvocation, TUint aVersion);
    void DoPrepareForConnection(IDviInvocation& aInvocation, TUint aVersion);
    void DoConnectionComplete(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetCurrentConnectionIDs(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetCurrentConnectionInfo(IDviInvocation& aInvocation, TUint aVersion);
private:
    CallbackConnectionManager1GetProtocolInfo iCallbackGetProtocolInfo;
    void* iPtrGetProtocolInfo;
    CallbackConnectionManager1PrepareForConnection iCallbackPrepareForConnection;
    void* iPtrPrepareForConnection;
    CallbackConnectionManager1ConnectionComplete iCallbackConnectionComplete;
    void* iPtrConnectionComplete;
    CallbackConnectionManager1GetCurrentConnectionIDs iCallbackGetCurrentConnectionIDs;
    void* iPtrGetCurrentConnectionIDs;
    CallbackConnectionManager1GetCurrentConnectionInfo iCallbackGetCurrentConnectionInfo;
    void* iPtrGetCurrentConnectionInfo;
    PropertyString* iPropertySourceProtocolInfo;
    PropertyString* iPropertySinkProtocolInfo;
    PropertyString* iPropertyCurrentConnectionIDs;
};

DvProviderUpnpOrgConnectionManager1C::DvProviderUpnpOrgConnectionManager1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "upnp.org", "ConnectionManager", 1)
{
    
    iPropertySourceProtocolInfo = new PropertyString(new ParameterString("SourceProtocolInfo"));
    iService->AddProperty(iPropertySourceProtocolInfo); // passes ownership
    iPropertySinkProtocolInfo = new PropertyString(new ParameterString("SinkProtocolInfo"));
    iService->AddProperty(iPropertySinkProtocolInfo); // passes ownership
    iPropertyCurrentConnectionIDs = new PropertyString(new ParameterString("CurrentConnectionIDs"));
    iService->AddProperty(iPropertyCurrentConnectionIDs); // passes ownership
}

TBool DvProviderUpnpOrgConnectionManager1C::SetPropertySourceProtocolInfo(const Brx& aValue)
{
    return SetPropertyString(*iPropertySourceProtocolInfo, aValue);
}

void DvProviderUpnpOrgConnectionManager1C::GetPropertySourceProtocolInfo(Brhz& aValue)
{
    aValue.Set(iPropertySourceProtocolInfo->Value());
}

TBool DvProviderUpnpOrgConnectionManager1C::SetPropertySinkProtocolInfo(const Brx& aValue)
{
    return SetPropertyString(*iPropertySinkProtocolInfo, aValue);
}

void DvProviderUpnpOrgConnectionManager1C::GetPropertySinkProtocolInfo(Brhz& aValue)
{
    aValue.Set(iPropertySinkProtocolInfo->Value());
}

TBool DvProviderUpnpOrgConnectionManager1C::SetPropertyCurrentConnectionIDs(const Brx& aValue)
{
    return SetPropertyString(*iPropertyCurrentConnectionIDs, aValue);
}

void DvProviderUpnpOrgConnectionManager1C::GetPropertyCurrentConnectionIDs(Brhz& aValue)
{
    aValue.Set(iPropertyCurrentConnectionIDs->Value());
}

void DvProviderUpnpOrgConnectionManager1C::EnableActionGetProtocolInfo(CallbackConnectionManager1GetProtocolInfo aCallback, void* aPtr)
{
    iCallbackGetProtocolInfo = aCallback;
    iPtrGetProtocolInfo = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetProtocolInfo");
    action->AddOutputParameter(new ParameterRelated("Source", *iPropertySourceProtocolInfo));
    action->AddOutputParameter(new ParameterRelated("Sink", *iPropertySinkProtocolInfo));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgConnectionManager1C::DoGetProtocolInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgConnectionManager1C::EnableActionPrepareForConnection(CallbackConnectionManager1PrepareForConnection aCallback, void* aPtr)
{
    iCallbackPrepareForConnection = aCallback;
    iPtrPrepareForConnection = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PrepareForConnection");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterString("RemoteProtocolInfo"));
    action->AddInputParameter(new ParameterString("PeerConnectionManager"));
    action->AddInputParameter(new ParameterInt("PeerConnectionID"));
    index = 0;
    allowedValues = new TChar*[2];
    allowedValues[index++] = (TChar*)"Input";
    allowedValues[index++] = (TChar*)"Output";
    action->AddInputParameter(new ParameterString("Direction", allowedValues, 2));
    delete[] allowedValues;
    action->AddOutputParameter(new ParameterInt("ConnectionID"));
    action->AddOutputParameter(new ParameterInt("AVTransportID"));
    action->AddOutputParameter(new ParameterInt("RcsID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgConnectionManager1C::DoPrepareForConnection);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgConnectionManager1C::EnableActionConnectionComplete(CallbackConnectionManager1ConnectionComplete aCallback, void* aPtr)
{
    iCallbackConnectionComplete = aCallback;
    iPtrConnectionComplete = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ConnectionComplete");
    action->AddInputParameter(new ParameterInt("ConnectionID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgConnectionManager1C::DoConnectionComplete);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgConnectionManager1C::EnableActionGetCurrentConnectionIDs(CallbackConnectionManager1GetCurrentConnectionIDs aCallback, void* aPtr)
{
    iCallbackGetCurrentConnectionIDs = aCallback;
    iPtrGetCurrentConnectionIDs = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetCurrentConnectionIDs");
    action->AddOutputParameter(new ParameterRelated("ConnectionIDs", *iPropertyCurrentConnectionIDs));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgConnectionManager1C::DoGetCurrentConnectionIDs);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgConnectionManager1C::EnableActionGetCurrentConnectionInfo(CallbackConnectionManager1GetCurrentConnectionInfo aCallback, void* aPtr)
{
    iCallbackGetCurrentConnectionInfo = aCallback;
    iPtrGetCurrentConnectionInfo = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetCurrentConnectionInfo");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterInt("ConnectionID"));
    action->AddOutputParameter(new ParameterInt("RcsID"));
    action->AddOutputParameter(new ParameterInt("AVTransportID"));
    action->AddOutputParameter(new ParameterString("ProtocolInfo"));
    action->AddOutputParameter(new ParameterString("PeerConnectionManager"));
    action->AddOutputParameter(new ParameterInt("PeerConnectionID"));
    index = 0;
    allowedValues = new TChar*[2];
    allowedValues[index++] = (TChar*)"Input";
    allowedValues[index++] = (TChar*)"Output";
    action->AddOutputParameter(new ParameterString("Direction", allowedValues, 2));
    delete[] allowedValues;
    index = 0;
    allowedValues = new TChar*[5];
    allowedValues[index++] = (TChar*)"OK";
    allowedValues[index++] = (TChar*)"ContentFormatMismatch";
    allowedValues[index++] = (TChar*)"InsufficientBandwidth";
    allowedValues[index++] = (TChar*)"UnreliableChannel";
    allowedValues[index++] = (TChar*)"Unknown";
    action->AddOutputParameter(new ParameterString("Status", allowedValues, 5));
    delete[] allowedValues;
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgConnectionManager1C::DoGetCurrentConnectionInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgConnectionManager1C::DoGetProtocolInfo(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* Source;
    char* Sink;
    ASSERT(iCallbackGetProtocolInfo != NULL);
    if (0 != iCallbackGetProtocolInfo(iPtrGetProtocolInfo, aVersion, &Source, &Sink)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respSource(aInvocation, "Source");
    InvocationResponseString respSink(aInvocation, "Sink");
    resp.Start();
    Brhz bufSource((const TChar*)Source);
    OhNetFreeExternal(Source);
    respSource.Write(bufSource);
    respSource.WriteFlush();
    Brhz bufSink((const TChar*)Sink);
    OhNetFreeExternal(Sink);
    respSink.Write(bufSink);
    respSink.WriteFlush();
    resp.End();
}

void DvProviderUpnpOrgConnectionManager1C::DoPrepareForConnection(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RemoteProtocolInfo;
    aInvocation.InvocationReadString("RemoteProtocolInfo", RemoteProtocolInfo);
    Brhz PeerConnectionManager;
    aInvocation.InvocationReadString("PeerConnectionManager", PeerConnectionManager);
    TInt PeerConnectionID = aInvocation.InvocationReadInt("PeerConnectionID");
    Brhz Direction;
    aInvocation.InvocationReadString("Direction", Direction);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    int32_t ConnectionID;
    int32_t AVTransportID;
    int32_t RcsID;
    ASSERT(iCallbackPrepareForConnection != NULL);
    if (0 != iCallbackPrepareForConnection(iPtrPrepareForConnection, aVersion, (const char*)RemoteProtocolInfo.Ptr(), (const char*)PeerConnectionManager.Ptr(), PeerConnectionID, (const char*)Direction.Ptr(), &ConnectionID, &AVTransportID, &RcsID)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseInt respConnectionID(aInvocation, "ConnectionID");
    InvocationResponseInt respAVTransportID(aInvocation, "AVTransportID");
    InvocationResponseInt respRcsID(aInvocation, "RcsID");
    resp.Start();
    respConnectionID.Write(ConnectionID);
    respAVTransportID.Write(AVTransportID);
    respRcsID.Write(RcsID);
    resp.End();
}

void DvProviderUpnpOrgConnectionManager1C::DoConnectionComplete(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt ConnectionID = aInvocation.InvocationReadInt("ConnectionID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackConnectionComplete != NULL);
    if (0 != iCallbackConnectionComplete(iPtrConnectionComplete, aVersion, ConnectionID)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgConnectionManager1C::DoGetCurrentConnectionIDs(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* ConnectionIDs;
    ASSERT(iCallbackGetCurrentConnectionIDs != NULL);
    if (0 != iCallbackGetCurrentConnectionIDs(iPtrGetCurrentConnectionIDs, aVersion, &ConnectionIDs)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respConnectionIDs(aInvocation, "ConnectionIDs");
    resp.Start();
    Brhz bufConnectionIDs((const TChar*)ConnectionIDs);
    OhNetFreeExternal(ConnectionIDs);
    respConnectionIDs.Write(bufConnectionIDs);
    respConnectionIDs.WriteFlush();
    resp.End();
}

void DvProviderUpnpOrgConnectionManager1C::DoGetCurrentConnectionInfo(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt ConnectionID = aInvocation.InvocationReadInt("ConnectionID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    int32_t RcsID;
    int32_t AVTransportID;
    char* ProtocolInfo;
    char* PeerConnectionManager;
    int32_t PeerConnectionID;
    char* Direction;
    char* Status;
    ASSERT(iCallbackGetCurrentConnectionInfo != NULL);
    if (0 != iCallbackGetCurrentConnectionInfo(iPtrGetCurrentConnectionInfo, aVersion, ConnectionID, &RcsID, &AVTransportID, &ProtocolInfo, &PeerConnectionManager, &PeerConnectionID, &Direction, &Status)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseInt respRcsID(aInvocation, "RcsID");
    InvocationResponseInt respAVTransportID(aInvocation, "AVTransportID");
    InvocationResponseString respProtocolInfo(aInvocation, "ProtocolInfo");
    InvocationResponseString respPeerConnectionManager(aInvocation, "PeerConnectionManager");
    InvocationResponseInt respPeerConnectionID(aInvocation, "PeerConnectionID");
    InvocationResponseString respDirection(aInvocation, "Direction");
    InvocationResponseString respStatus(aInvocation, "Status");
    resp.Start();
    respRcsID.Write(RcsID);
    respAVTransportID.Write(AVTransportID);
    Brhz bufProtocolInfo((const TChar*)ProtocolInfo);
    OhNetFreeExternal(ProtocolInfo);
    respProtocolInfo.Write(bufProtocolInfo);
    respProtocolInfo.WriteFlush();
    Brhz bufPeerConnectionManager((const TChar*)PeerConnectionManager);
    OhNetFreeExternal(PeerConnectionManager);
    respPeerConnectionManager.Write(bufPeerConnectionManager);
    respPeerConnectionManager.WriteFlush();
    respPeerConnectionID.Write(PeerConnectionID);
    Brhz bufDirection((const TChar*)Direction);
    OhNetFreeExternal(Direction);
    respDirection.Write(bufDirection);
    respDirection.WriteFlush();
    Brhz bufStatus((const TChar*)Status);
    OhNetFreeExternal(Status);
    respStatus.Write(bufStatus);
    respStatus.WriteFlush();
    resp.End();
}



THandle DvProviderUpnpOrgConnectionManager1Create(DvDeviceC aDevice)
{
	return new DvProviderUpnpOrgConnectionManager1C(aDevice);
}

void DvProviderUpnpOrgConnectionManager1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderUpnpOrgConnectionManager1C*>(aProvider);
}

void DvProviderUpnpOrgConnectionManager1EnableActionGetProtocolInfo(THandle aProvider, CallbackConnectionManager1GetProtocolInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgConnectionManager1C*>(aProvider)->EnableActionGetProtocolInfo(aCallback, aPtr);
}

void DvProviderUpnpOrgConnectionManager1EnableActionPrepareForConnection(THandle aProvider, CallbackConnectionManager1PrepareForConnection aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgConnectionManager1C*>(aProvider)->EnableActionPrepareForConnection(aCallback, aPtr);
}

void DvProviderUpnpOrgConnectionManager1EnableActionConnectionComplete(THandle aProvider, CallbackConnectionManager1ConnectionComplete aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgConnectionManager1C*>(aProvider)->EnableActionConnectionComplete(aCallback, aPtr);
}

void DvProviderUpnpOrgConnectionManager1EnableActionGetCurrentConnectionIDs(THandle aProvider, CallbackConnectionManager1GetCurrentConnectionIDs aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgConnectionManager1C*>(aProvider)->EnableActionGetCurrentConnectionIDs(aCallback, aPtr);
}

void DvProviderUpnpOrgConnectionManager1EnableActionGetCurrentConnectionInfo(THandle aProvider, CallbackConnectionManager1GetCurrentConnectionInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgConnectionManager1C*>(aProvider)->EnableActionGetCurrentConnectionInfo(aCallback, aPtr);
}

int32_t DvProviderUpnpOrgConnectionManager1SetPropertySourceProtocolInfo(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgConnectionManager1C*>(aProvider)->SetPropertySourceProtocolInfo(buf)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgConnectionManager1GetPropertySourceProtocolInfo(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgConnectionManager1C*>(aProvider)->GetPropertySourceProtocolInfo(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderUpnpOrgConnectionManager1SetPropertySinkProtocolInfo(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgConnectionManager1C*>(aProvider)->SetPropertySinkProtocolInfo(buf)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgConnectionManager1GetPropertySinkProtocolInfo(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgConnectionManager1C*>(aProvider)->GetPropertySinkProtocolInfo(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderUpnpOrgConnectionManager1SetPropertyCurrentConnectionIDs(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgConnectionManager1C*>(aProvider)->SetPropertyCurrentConnectionIDs(buf)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgConnectionManager1GetPropertyCurrentConnectionIDs(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgConnectionManager1C*>(aProvider)->GetPropertyCurrentConnectionIDs(buf);
    *aValue = (char*)buf.Transfer();
}

