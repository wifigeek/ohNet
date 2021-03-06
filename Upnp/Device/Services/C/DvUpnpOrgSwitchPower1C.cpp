#include "DvUpnpOrgSwitchPower1.h"
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

class DvProviderUpnpOrgSwitchPower1C : public DvProvider
{
public:
    DvProviderUpnpOrgSwitchPower1C(DvDeviceC aDevice);
    TBool SetPropertyStatus(TBool aValue);
    void GetPropertyStatus(TBool& aValue);
    void EnableActionSetTarget(CallbackSwitchPower1SetTarget aCallback, void* aPtr);
    void EnableActionGetTarget(CallbackSwitchPower1GetTarget aCallback, void* aPtr);
    void EnableActionGetStatus(CallbackSwitchPower1GetStatus aCallback, void* aPtr);
private:
    void DoSetTarget(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetTarget(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetStatus(IDviInvocation& aInvocation, TUint aVersion);
private:
    CallbackSwitchPower1SetTarget iCallbackSetTarget;
    void* iPtrSetTarget;
    CallbackSwitchPower1GetTarget iCallbackGetTarget;
    void* iPtrGetTarget;
    CallbackSwitchPower1GetStatus iCallbackGetStatus;
    void* iPtrGetStatus;
    PropertyBool* iPropertyStatus;
};

DvProviderUpnpOrgSwitchPower1C::DvProviderUpnpOrgSwitchPower1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "upnp.org", "SwitchPower", 1)
{
    
    iPropertyStatus = new PropertyBool(new ParameterBool("Status"));
    iService->AddProperty(iPropertyStatus); // passes ownership
}

TBool DvProviderUpnpOrgSwitchPower1C::SetPropertyStatus(TBool aValue)
{
    return SetPropertyBool(*iPropertyStatus, aValue);
}

void DvProviderUpnpOrgSwitchPower1C::GetPropertyStatus(TBool& aValue)
{
    aValue = iPropertyStatus->Value();
}

void DvProviderUpnpOrgSwitchPower1C::EnableActionSetTarget(CallbackSwitchPower1SetTarget aCallback, void* aPtr)
{
    iCallbackSetTarget = aCallback;
    iPtrSetTarget = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetTarget");
    action->AddInputParameter(new ParameterBool("newTargetValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgSwitchPower1C::DoSetTarget);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgSwitchPower1C::EnableActionGetTarget(CallbackSwitchPower1GetTarget aCallback, void* aPtr)
{
    iCallbackGetTarget = aCallback;
    iPtrGetTarget = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetTarget");
    action->AddOutputParameter(new ParameterBool("RetTargetValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgSwitchPower1C::DoGetTarget);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgSwitchPower1C::EnableActionGetStatus(CallbackSwitchPower1GetStatus aCallback, void* aPtr)
{
    iCallbackGetStatus = aCallback;
    iPtrGetStatus = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetStatus");
    action->AddOutputParameter(new ParameterRelated("ResultStatus", *iPropertyStatus));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgSwitchPower1C::DoGetStatus);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgSwitchPower1C::DoSetTarget(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool newTargetValue = aInvocation.InvocationReadBool("newTargetValue");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetTarget != NULL);
    if (0 != iCallbackSetTarget(iPtrSetTarget, aVersion, newTargetValue)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgSwitchPower1C::DoGetTarget(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t RetTargetValue;
    ASSERT(iCallbackGetTarget != NULL);
    if (0 != iCallbackGetTarget(iPtrGetTarget, aVersion, &RetTargetValue)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respRetTargetValue(aInvocation, "RetTargetValue");
    resp.Start();
    respRetTargetValue.Write((RetTargetValue!=0));
    resp.End();
}

void DvProviderUpnpOrgSwitchPower1C::DoGetStatus(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t ResultStatus;
    ASSERT(iCallbackGetStatus != NULL);
    if (0 != iCallbackGetStatus(iPtrGetStatus, aVersion, &ResultStatus)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respResultStatus(aInvocation, "ResultStatus");
    resp.Start();
    respResultStatus.Write((ResultStatus!=0));
    resp.End();
}



THandle DvProviderUpnpOrgSwitchPower1Create(DvDeviceC aDevice)
{
	return new DvProviderUpnpOrgSwitchPower1C(aDevice);
}

void DvProviderUpnpOrgSwitchPower1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderUpnpOrgSwitchPower1C*>(aProvider);
}

void DvProviderUpnpOrgSwitchPower1EnableActionSetTarget(THandle aProvider, CallbackSwitchPower1SetTarget aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgSwitchPower1C*>(aProvider)->EnableActionSetTarget(aCallback, aPtr);
}

void DvProviderUpnpOrgSwitchPower1EnableActionGetTarget(THandle aProvider, CallbackSwitchPower1GetTarget aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgSwitchPower1C*>(aProvider)->EnableActionGetTarget(aCallback, aPtr);
}

void DvProviderUpnpOrgSwitchPower1EnableActionGetStatus(THandle aProvider, CallbackSwitchPower1GetStatus aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgSwitchPower1C*>(aProvider)->EnableActionGetStatus(aCallback, aPtr);
}

int32_t DvProviderUpnpOrgSwitchPower1SetPropertyStatus(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgSwitchPower1C*>(aProvider)->SetPropertyStatus((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgSwitchPower1GetPropertyStatus(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderUpnpOrgSwitchPower1C*>(aProvider)->GetPropertyStatus(val);
    *aValue = (val? 1 : 0);
}

