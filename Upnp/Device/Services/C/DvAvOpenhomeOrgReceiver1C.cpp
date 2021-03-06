#include "DvAvOpenhomeOrgReceiver1.h"
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

class DvProviderAvOpenhomeOrgReceiver1C : public DvProvider
{
public:
    DvProviderAvOpenhomeOrgReceiver1C(DvDeviceC aDevice);
    TBool SetPropertyUri(const Brx& aValue);
    void GetPropertyUri(Brhz& aValue);
    TBool SetPropertyMetadata(const Brx& aValue);
    void GetPropertyMetadata(Brhz& aValue);
    TBool SetPropertyTransportState(const Brx& aValue);
    void GetPropertyTransportState(Brhz& aValue);
    TBool SetPropertyProtocolInfo(const Brx& aValue);
    void GetPropertyProtocolInfo(Brhz& aValue);
    void EnableActionPlay(CallbackReceiver1Play aCallback, void* aPtr);
    void EnableActionStop(CallbackReceiver1Stop aCallback, void* aPtr);
    void EnableActionSetSender(CallbackReceiver1SetSender aCallback, void* aPtr);
    void EnableActionSender(CallbackReceiver1Sender aCallback, void* aPtr);
    void EnableActionProtocolInfo(CallbackReceiver1ProtocolInfo aCallback, void* aPtr);
    void EnableActionTransportState(CallbackReceiver1TransportState aCallback, void* aPtr);
private:
    void DoPlay(IDviInvocation& aInvocation, TUint aVersion);
    void DoStop(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetSender(IDviInvocation& aInvocation, TUint aVersion);
    void DoSender(IDviInvocation& aInvocation, TUint aVersion);
    void DoProtocolInfo(IDviInvocation& aInvocation, TUint aVersion);
    void DoTransportState(IDviInvocation& aInvocation, TUint aVersion);
private:
    CallbackReceiver1Play iCallbackPlay;
    void* iPtrPlay;
    CallbackReceiver1Stop iCallbackStop;
    void* iPtrStop;
    CallbackReceiver1SetSender iCallbackSetSender;
    void* iPtrSetSender;
    CallbackReceiver1Sender iCallbackSender;
    void* iPtrSender;
    CallbackReceiver1ProtocolInfo iCallbackProtocolInfo;
    void* iPtrProtocolInfo;
    CallbackReceiver1TransportState iCallbackTransportState;
    void* iPtrTransportState;
    PropertyString* iPropertyUri;
    PropertyString* iPropertyMetadata;
    PropertyString* iPropertyTransportState;
    PropertyString* iPropertyProtocolInfo;
};

DvProviderAvOpenhomeOrgReceiver1C::DvProviderAvOpenhomeOrgReceiver1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "av.openhome.org", "Receiver", 1)
{
    
    TChar** allowedValues;
    TUint index;
    iPropertyUri = new PropertyString(new ParameterString("Uri"));
    iService->AddProperty(iPropertyUri); // passes ownership
    iPropertyMetadata = new PropertyString(new ParameterString("Metadata"));
    iService->AddProperty(iPropertyMetadata); // passes ownership
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"Stopped";
    allowedValues[index++] = (TChar*)"Playing";
    allowedValues[index++] = (TChar*)"Waiting";
    allowedValues[index++] = (TChar*)"Buffering";
    iPropertyTransportState = new PropertyString(new ParameterString("TransportState", allowedValues, 4));
    delete[] allowedValues;
    iService->AddProperty(iPropertyTransportState); // passes ownership
    iPropertyProtocolInfo = new PropertyString(new ParameterString("ProtocolInfo"));
    iService->AddProperty(iPropertyProtocolInfo); // passes ownership
}

TBool DvProviderAvOpenhomeOrgReceiver1C::SetPropertyUri(const Brx& aValue)
{
    return SetPropertyString(*iPropertyUri, aValue);
}

void DvProviderAvOpenhomeOrgReceiver1C::GetPropertyUri(Brhz& aValue)
{
    aValue.Set(iPropertyUri->Value());
}

TBool DvProviderAvOpenhomeOrgReceiver1C::SetPropertyMetadata(const Brx& aValue)
{
    return SetPropertyString(*iPropertyMetadata, aValue);
}

void DvProviderAvOpenhomeOrgReceiver1C::GetPropertyMetadata(Brhz& aValue)
{
    aValue.Set(iPropertyMetadata->Value());
}

TBool DvProviderAvOpenhomeOrgReceiver1C::SetPropertyTransportState(const Brx& aValue)
{
    return SetPropertyString(*iPropertyTransportState, aValue);
}

void DvProviderAvOpenhomeOrgReceiver1C::GetPropertyTransportState(Brhz& aValue)
{
    aValue.Set(iPropertyTransportState->Value());
}

TBool DvProviderAvOpenhomeOrgReceiver1C::SetPropertyProtocolInfo(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProtocolInfo, aValue);
}

void DvProviderAvOpenhomeOrgReceiver1C::GetPropertyProtocolInfo(Brhz& aValue)
{
    aValue.Set(iPropertyProtocolInfo->Value());
}

void DvProviderAvOpenhomeOrgReceiver1C::EnableActionPlay(CallbackReceiver1Play aCallback, void* aPtr)
{
    iCallbackPlay = aCallback;
    iPtrPlay = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Play");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgReceiver1C::DoPlay);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgReceiver1C::EnableActionStop(CallbackReceiver1Stop aCallback, void* aPtr)
{
    iCallbackStop = aCallback;
    iPtrStop = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Stop");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgReceiver1C::DoStop);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgReceiver1C::EnableActionSetSender(CallbackReceiver1SetSender aCallback, void* aPtr)
{
    iCallbackSetSender = aCallback;
    iPtrSetSender = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetSender");
    action->AddInputParameter(new ParameterRelated("Uri", *iPropertyUri));
    action->AddInputParameter(new ParameterRelated("Metadata", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgReceiver1C::DoSetSender);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgReceiver1C::EnableActionSender(CallbackReceiver1Sender aCallback, void* aPtr)
{
    iCallbackSender = aCallback;
    iPtrSender = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Sender");
    action->AddOutputParameter(new ParameterRelated("Uri", *iPropertyUri));
    action->AddOutputParameter(new ParameterRelated("Metadata", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgReceiver1C::DoSender);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgReceiver1C::EnableActionProtocolInfo(CallbackReceiver1ProtocolInfo aCallback, void* aPtr)
{
    iCallbackProtocolInfo = aCallback;
    iPtrProtocolInfo = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ProtocolInfo");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyProtocolInfo));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgReceiver1C::DoProtocolInfo);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgReceiver1C::EnableActionTransportState(CallbackReceiver1TransportState aCallback, void* aPtr)
{
    iCallbackTransportState = aCallback;
    iPtrTransportState = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("TransportState");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyTransportState));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgReceiver1C::DoTransportState);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgReceiver1C::DoPlay(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackPlay != NULL);
    if (0 != iCallbackPlay(iPtrPlay, aVersion)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderAvOpenhomeOrgReceiver1C::DoStop(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackStop != NULL);
    if (0 != iCallbackStop(iPtrStop, aVersion)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderAvOpenhomeOrgReceiver1C::DoSetSender(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz Uri;
    aInvocation.InvocationReadString("Uri", Uri);
    Brhz Metadata;
    aInvocation.InvocationReadString("Metadata", Metadata);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetSender != NULL);
    if (0 != iCallbackSetSender(iPtrSetSender, aVersion, (const char*)Uri.Ptr(), (const char*)Metadata.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderAvOpenhomeOrgReceiver1C::DoSender(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* Uri;
    char* Metadata;
    ASSERT(iCallbackSender != NULL);
    if (0 != iCallbackSender(iPtrSender, aVersion, &Uri, &Metadata)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respUri(aInvocation, "Uri");
    InvocationResponseString respMetadata(aInvocation, "Metadata");
    resp.Start();
    Brhz bufUri((const TChar*)Uri);
    OhNetFreeExternal(Uri);
    respUri.Write(bufUri);
    respUri.WriteFlush();
    Brhz bufMetadata((const TChar*)Metadata);
    OhNetFreeExternal(Metadata);
    respMetadata.Write(bufMetadata);
    respMetadata.WriteFlush();
    resp.End();
}

void DvProviderAvOpenhomeOrgReceiver1C::DoProtocolInfo(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* Value;
    ASSERT(iCallbackProtocolInfo != NULL);
    if (0 != iCallbackProtocolInfo(iPtrProtocolInfo, aVersion, &Value)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respValue(aInvocation, "Value");
    resp.Start();
    Brhz bufValue((const TChar*)Value);
    OhNetFreeExternal(Value);
    respValue.Write(bufValue);
    respValue.WriteFlush();
    resp.End();
}

void DvProviderAvOpenhomeOrgReceiver1C::DoTransportState(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* Value;
    ASSERT(iCallbackTransportState != NULL);
    if (0 != iCallbackTransportState(iPtrTransportState, aVersion, &Value)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respValue(aInvocation, "Value");
    resp.Start();
    Brhz bufValue((const TChar*)Value);
    OhNetFreeExternal(Value);
    respValue.Write(bufValue);
    respValue.WriteFlush();
    resp.End();
}



THandle DvProviderAvOpenhomeOrgReceiver1Create(DvDeviceC aDevice)
{
	return new DvProviderAvOpenhomeOrgReceiver1C(aDevice);
}

void DvProviderAvOpenhomeOrgReceiver1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider);
}

void DvProviderAvOpenhomeOrgReceiver1EnableActionPlay(THandle aProvider, CallbackReceiver1Play aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->EnableActionPlay(aCallback, aPtr);
}

void DvProviderAvOpenhomeOrgReceiver1EnableActionStop(THandle aProvider, CallbackReceiver1Stop aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->EnableActionStop(aCallback, aPtr);
}

void DvProviderAvOpenhomeOrgReceiver1EnableActionSetSender(THandle aProvider, CallbackReceiver1SetSender aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->EnableActionSetSender(aCallback, aPtr);
}

void DvProviderAvOpenhomeOrgReceiver1EnableActionSender(THandle aProvider, CallbackReceiver1Sender aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->EnableActionSender(aCallback, aPtr);
}

void DvProviderAvOpenhomeOrgReceiver1EnableActionProtocolInfo(THandle aProvider, CallbackReceiver1ProtocolInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->EnableActionProtocolInfo(aCallback, aPtr);
}

void DvProviderAvOpenhomeOrgReceiver1EnableActionTransportState(THandle aProvider, CallbackReceiver1TransportState aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->EnableActionTransportState(aCallback, aPtr);
}

int32_t DvProviderAvOpenhomeOrgReceiver1SetPropertyUri(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->SetPropertyUri(buf)? 1 : 0);
    return 0;
}

void DvProviderAvOpenhomeOrgReceiver1GetPropertyUri(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->GetPropertyUri(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderAvOpenhomeOrgReceiver1SetPropertyMetadata(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->SetPropertyMetadata(buf)? 1 : 0);
    return 0;
}

void DvProviderAvOpenhomeOrgReceiver1GetPropertyMetadata(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->GetPropertyMetadata(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderAvOpenhomeOrgReceiver1SetPropertyTransportState(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->SetPropertyTransportState(buf)? 1 : 0);
    return 0;
}

void DvProviderAvOpenhomeOrgReceiver1GetPropertyTransportState(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->GetPropertyTransportState(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderAvOpenhomeOrgReceiver1SetPropertyProtocolInfo(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->SetPropertyProtocolInfo(buf)? 1 : 0);
    return 0;
}

void DvProviderAvOpenhomeOrgReceiver1GetPropertyProtocolInfo(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgReceiver1C*>(aProvider)->GetPropertyProtocolInfo(buf);
    *aValue = (char*)buf.Transfer();
}

