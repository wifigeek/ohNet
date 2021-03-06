#include "DvAvOpenhomeOrgTime1.h"
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

class DvProviderAvOpenhomeOrgTime1C : public DvProvider
{
public:
    DvProviderAvOpenhomeOrgTime1C(DvDeviceC aDevice);
    TBool SetPropertyTrackCount(TUint aValue);
    void GetPropertyTrackCount(TUint& aValue);
    TBool SetPropertyDuration(TUint aValue);
    void GetPropertyDuration(TUint& aValue);
    TBool SetPropertySeconds(TUint aValue);
    void GetPropertySeconds(TUint& aValue);
    void EnableActionTime(CallbackTime1Time aCallback, void* aPtr);
private:
    void DoTime(IDviInvocation& aInvocation, TUint aVersion);
private:
    CallbackTime1Time iCallbackTime;
    void* iPtrTime;
    PropertyUint* iPropertyTrackCount;
    PropertyUint* iPropertyDuration;
    PropertyUint* iPropertySeconds;
};

DvProviderAvOpenhomeOrgTime1C::DvProviderAvOpenhomeOrgTime1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "av.openhome.org", "Time", 1)
{
    
    iPropertyTrackCount = new PropertyUint(new ParameterUint("TrackCount"));
    iService->AddProperty(iPropertyTrackCount); // passes ownership
    iPropertyDuration = new PropertyUint(new ParameterUint("Duration"));
    iService->AddProperty(iPropertyDuration); // passes ownership
    iPropertySeconds = new PropertyUint(new ParameterUint("Seconds"));
    iService->AddProperty(iPropertySeconds); // passes ownership
}

TBool DvProviderAvOpenhomeOrgTime1C::SetPropertyTrackCount(TUint aValue)
{
    return SetPropertyUint(*iPropertyTrackCount, aValue);
}

void DvProviderAvOpenhomeOrgTime1C::GetPropertyTrackCount(TUint& aValue)
{
    aValue = iPropertyTrackCount->Value();
}

TBool DvProviderAvOpenhomeOrgTime1C::SetPropertyDuration(TUint aValue)
{
    return SetPropertyUint(*iPropertyDuration, aValue);
}

void DvProviderAvOpenhomeOrgTime1C::GetPropertyDuration(TUint& aValue)
{
    aValue = iPropertyDuration->Value();
}

TBool DvProviderAvOpenhomeOrgTime1C::SetPropertySeconds(TUint aValue)
{
    return SetPropertyUint(*iPropertySeconds, aValue);
}

void DvProviderAvOpenhomeOrgTime1C::GetPropertySeconds(TUint& aValue)
{
    aValue = iPropertySeconds->Value();
}

void DvProviderAvOpenhomeOrgTime1C::EnableActionTime(CallbackTime1Time aCallback, void* aPtr)
{
    iCallbackTime = aCallback;
    iPtrTime = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Time");
    action->AddOutputParameter(new ParameterRelated("TrackCount", *iPropertyTrackCount));
    action->AddOutputParameter(new ParameterRelated("Duration", *iPropertyDuration));
    action->AddOutputParameter(new ParameterRelated("Seconds", *iPropertySeconds));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgTime1C::DoTime);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgTime1C::DoTime(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t TrackCount;
    uint32_t Duration;
    uint32_t Seconds;
    ASSERT(iCallbackTime != NULL);
    if (0 != iCallbackTime(iPtrTime, aVersion, &TrackCount, &Duration, &Seconds)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respTrackCount(aInvocation, "TrackCount");
    InvocationResponseUint respDuration(aInvocation, "Duration");
    InvocationResponseUint respSeconds(aInvocation, "Seconds");
    resp.Start();
    respTrackCount.Write(TrackCount);
    respDuration.Write(Duration);
    respSeconds.Write(Seconds);
    resp.End();
}



THandle DvProviderAvOpenhomeOrgTime1Create(DvDeviceC aDevice)
{
	return new DvProviderAvOpenhomeOrgTime1C(aDevice);
}

void DvProviderAvOpenhomeOrgTime1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderAvOpenhomeOrgTime1C*>(aProvider);
}

void DvProviderAvOpenhomeOrgTime1EnableActionTime(THandle aProvider, CallbackTime1Time aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgTime1C*>(aProvider)->EnableActionTime(aCallback, aPtr);
}

int32_t DvProviderAvOpenhomeOrgTime1SetPropertyTrackCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgTime1C*>(aProvider)->SetPropertyTrackCount(aValue)? 1 : 0);
    return 0;
}

void DvProviderAvOpenhomeOrgTime1GetPropertyTrackCount(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgTime1C*>(aProvider)->GetPropertyTrackCount(val);
    *aValue = val;
}

int32_t DvProviderAvOpenhomeOrgTime1SetPropertyDuration(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgTime1C*>(aProvider)->SetPropertyDuration(aValue)? 1 : 0);
    return 0;
}

void DvProviderAvOpenhomeOrgTime1GetPropertyDuration(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgTime1C*>(aProvider)->GetPropertyDuration(val);
    *aValue = val;
}

int32_t DvProviderAvOpenhomeOrgTime1SetPropertySeconds(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgTime1C*>(aProvider)->SetPropertySeconds(aValue)? 1 : 0);
    return 0;
}

void DvProviderAvOpenhomeOrgTime1GetPropertySeconds(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgTime1C*>(aProvider)->GetPropertySeconds(val);
    *aValue = val;
}

