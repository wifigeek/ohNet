#include "CpAvOpenhomeOrgInfo1.h"
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>
#include <OhNetTypes.h>
#include <Buffer.h>
#include <Exception.h>
#include <Functor.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace OpenHome;
using namespace OpenHome::Net;

class CpProxyAvOpenhomeOrgInfo1C : public CpProxyC
{
public:
    CpProxyAvOpenhomeOrgInfo1C(CpDeviceC aDevice);
    ~CpProxyAvOpenhomeOrgInfo1C();
    //CpProxyAvOpenhomeOrgInfo1* Proxy() { return static_cast<CpProxyAvOpenhomeOrgInfo1*>(iProxy); }

    void SyncCounters(TUint& aTrackCount, TUint& aDetailsCount, TUint& aMetatextCount);
    void BeginCounters(FunctorAsync& aFunctor);
    void EndCounters(IAsync& aAsync, TUint& aTrackCount, TUint& aDetailsCount, TUint& aMetatextCount);

    void SyncTrack(Brh& aUri, Brh& aMetadata);
    void BeginTrack(FunctorAsync& aFunctor);
    void EndTrack(IAsync& aAsync, Brh& aUri, Brh& aMetadata);

    void SyncDetails(TUint& aDuration, TUint& aBitRate, TUint& aBitDepth, TUint& aSampleRate, TBool& aLossless, Brh& aCodecName);
    void BeginDetails(FunctorAsync& aFunctor);
    void EndDetails(IAsync& aAsync, TUint& aDuration, TUint& aBitRate, TUint& aBitDepth, TUint& aSampleRate, TBool& aLossless, Brh& aCodecName);

    void SyncMetatext(Brh& aValue);
    void BeginMetatext(FunctorAsync& aFunctor);
    void EndMetatext(IAsync& aAsync, Brh& aValue);

    void SetPropertyTrackCountChanged(Functor& aFunctor);
    void SetPropertyDetailsCountChanged(Functor& aFunctor);
    void SetPropertyMetatextCountChanged(Functor& aFunctor);
    void SetPropertyUriChanged(Functor& aFunctor);
    void SetPropertyMetadataChanged(Functor& aFunctor);
    void SetPropertyDurationChanged(Functor& aFunctor);
    void SetPropertyBitRateChanged(Functor& aFunctor);
    void SetPropertyBitDepthChanged(Functor& aFunctor);
    void SetPropertySampleRateChanged(Functor& aFunctor);
    void SetPropertyLosslessChanged(Functor& aFunctor);
    void SetPropertyCodecNameChanged(Functor& aFunctor);
    void SetPropertyMetatextChanged(Functor& aFunctor);

    void PropertyTrackCount(TUint& aTrackCount) const;
    void PropertyDetailsCount(TUint& aDetailsCount) const;
    void PropertyMetatextCount(TUint& aMetatextCount) const;
    void PropertyUri(Brhz& aUri) const;
    void PropertyMetadata(Brhz& aMetadata) const;
    void PropertyDuration(TUint& aDuration) const;
    void PropertyBitRate(TUint& aBitRate) const;
    void PropertyBitDepth(TUint& aBitDepth) const;
    void PropertySampleRate(TUint& aSampleRate) const;
    void PropertyLossless(TBool& aLossless) const;
    void PropertyCodecName(Brhz& aCodecName) const;
    void PropertyMetatext(Brhz& aMetatext) const;
private:
    void TrackCountPropertyChanged();
    void DetailsCountPropertyChanged();
    void MetatextCountPropertyChanged();
    void UriPropertyChanged();
    void MetadataPropertyChanged();
    void DurationPropertyChanged();
    void BitRatePropertyChanged();
    void BitDepthPropertyChanged();
    void SampleRatePropertyChanged();
    void LosslessPropertyChanged();
    void CodecNamePropertyChanged();
    void MetatextPropertyChanged();
private:
    Mutex iLock;
    Action* iActionCounters;
    Action* iActionTrack;
    Action* iActionDetails;
    Action* iActionMetatext;
    PropertyUint* iTrackCount;
    PropertyUint* iDetailsCount;
    PropertyUint* iMetatextCount;
    PropertyString* iUri;
    PropertyString* iMetadata;
    PropertyUint* iDuration;
    PropertyUint* iBitRate;
    PropertyUint* iBitDepth;
    PropertyUint* iSampleRate;
    PropertyBool* iLossless;
    PropertyString* iCodecName;
    PropertyString* iMetatext;
    Functor iTrackCountChanged;
    Functor iDetailsCountChanged;
    Functor iMetatextCountChanged;
    Functor iUriChanged;
    Functor iMetadataChanged;
    Functor iDurationChanged;
    Functor iBitRateChanged;
    Functor iBitDepthChanged;
    Functor iSampleRateChanged;
    Functor iLosslessChanged;
    Functor iCodecNameChanged;
    Functor iMetatextChanged;
};


class SyncCountersAvOpenhomeOrgInfo1C : public SyncProxyAction
{
public:
    SyncCountersAvOpenhomeOrgInfo1C(CpProxyAvOpenhomeOrgInfo1C& aProxy, TUint& aTrackCount, TUint& aDetailsCount, TUint& aMetatextCount);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgInfo1C& iService;
    TUint& iTrackCount;
    TUint& iDetailsCount;
    TUint& iMetatextCount;
};

SyncCountersAvOpenhomeOrgInfo1C::SyncCountersAvOpenhomeOrgInfo1C(CpProxyAvOpenhomeOrgInfo1C& aProxy, TUint& aTrackCount, TUint& aDetailsCount, TUint& aMetatextCount)
    : iService(aProxy)
    , iTrackCount(aTrackCount)
    , iDetailsCount(aDetailsCount)
    , iMetatextCount(aMetatextCount)
{
}

void SyncCountersAvOpenhomeOrgInfo1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndCounters(aAsync, iTrackCount, iDetailsCount, iMetatextCount);
}


class SyncTrackAvOpenhomeOrgInfo1C : public SyncProxyAction
{
public:
    SyncTrackAvOpenhomeOrgInfo1C(CpProxyAvOpenhomeOrgInfo1C& aProxy, Brh& aUri, Brh& aMetadata);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgInfo1C& iService;
    Brh& iUri;
    Brh& iMetadata;
};

SyncTrackAvOpenhomeOrgInfo1C::SyncTrackAvOpenhomeOrgInfo1C(CpProxyAvOpenhomeOrgInfo1C& aProxy, Brh& aUri, Brh& aMetadata)
    : iService(aProxy)
    , iUri(aUri)
    , iMetadata(aMetadata)
{
}

void SyncTrackAvOpenhomeOrgInfo1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndTrack(aAsync, iUri, iMetadata);
}


class SyncDetailsAvOpenhomeOrgInfo1C : public SyncProxyAction
{
public:
    SyncDetailsAvOpenhomeOrgInfo1C(CpProxyAvOpenhomeOrgInfo1C& aProxy, TUint& aDuration, TUint& aBitRate, TUint& aBitDepth, TUint& aSampleRate, TBool& aLossless, Brh& aCodecName);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgInfo1C& iService;
    TUint& iDuration;
    TUint& iBitRate;
    TUint& iBitDepth;
    TUint& iSampleRate;
    TBool& iLossless;
    Brh& iCodecName;
};

SyncDetailsAvOpenhomeOrgInfo1C::SyncDetailsAvOpenhomeOrgInfo1C(CpProxyAvOpenhomeOrgInfo1C& aProxy, TUint& aDuration, TUint& aBitRate, TUint& aBitDepth, TUint& aSampleRate, TBool& aLossless, Brh& aCodecName)
    : iService(aProxy)
    , iDuration(aDuration)
    , iBitRate(aBitRate)
    , iBitDepth(aBitDepth)
    , iSampleRate(aSampleRate)
    , iLossless(aLossless)
    , iCodecName(aCodecName)
{
}

void SyncDetailsAvOpenhomeOrgInfo1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDetails(aAsync, iDuration, iBitRate, iBitDepth, iSampleRate, iLossless, iCodecName);
}


class SyncMetatextAvOpenhomeOrgInfo1C : public SyncProxyAction
{
public:
    SyncMetatextAvOpenhomeOrgInfo1C(CpProxyAvOpenhomeOrgInfo1C& aProxy, Brh& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgInfo1C& iService;
    Brh& iValue;
};

SyncMetatextAvOpenhomeOrgInfo1C::SyncMetatextAvOpenhomeOrgInfo1C(CpProxyAvOpenhomeOrgInfo1C& aProxy, Brh& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncMetatextAvOpenhomeOrgInfo1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndMetatext(aAsync, iValue);
}

CpProxyAvOpenhomeOrgInfo1C::CpProxyAvOpenhomeOrgInfo1C(CpDeviceC aDevice)
    : CpProxyC("av-openhome-org", "Info", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
{
    OpenHome::Net::Parameter* param;

    iActionCounters = new Action("Counters");
    param = new OpenHome::Net::ParameterUint("TrackCount");
    iActionCounters->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("DetailsCount");
    iActionCounters->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("MetatextCount");
    iActionCounters->AddOutputParameter(param);

    iActionTrack = new Action("Track");
    param = new OpenHome::Net::ParameterString("Uri");
    iActionTrack->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("Metadata");
    iActionTrack->AddOutputParameter(param);

    iActionDetails = new Action("Details");
    param = new OpenHome::Net::ParameterUint("Duration");
    iActionDetails->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("BitRate");
    iActionDetails->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("BitDepth");
    iActionDetails->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("SampleRate");
    iActionDetails->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterBool("Lossless");
    iActionDetails->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("CodecName");
    iActionDetails->AddOutputParameter(param);

    iActionMetatext = new Action("Metatext");
    param = new OpenHome::Net::ParameterString("Value");
    iActionMetatext->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1C::TrackCountPropertyChanged);
    iTrackCount = new PropertyUint("TrackCount", functor);
    AddProperty(iTrackCount);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1C::DetailsCountPropertyChanged);
    iDetailsCount = new PropertyUint("DetailsCount", functor);
    AddProperty(iDetailsCount);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1C::MetatextCountPropertyChanged);
    iMetatextCount = new PropertyUint("MetatextCount", functor);
    AddProperty(iMetatextCount);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1C::UriPropertyChanged);
    iUri = new PropertyString("Uri", functor);
    AddProperty(iUri);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1C::MetadataPropertyChanged);
    iMetadata = new PropertyString("Metadata", functor);
    AddProperty(iMetadata);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1C::DurationPropertyChanged);
    iDuration = new PropertyUint("Duration", functor);
    AddProperty(iDuration);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1C::BitRatePropertyChanged);
    iBitRate = new PropertyUint("BitRate", functor);
    AddProperty(iBitRate);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1C::BitDepthPropertyChanged);
    iBitDepth = new PropertyUint("BitDepth", functor);
    AddProperty(iBitDepth);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1C::SampleRatePropertyChanged);
    iSampleRate = new PropertyUint("SampleRate", functor);
    AddProperty(iSampleRate);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1C::LosslessPropertyChanged);
    iLossless = new PropertyBool("Lossless", functor);
    AddProperty(iLossless);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1C::CodecNamePropertyChanged);
    iCodecName = new PropertyString("CodecName", functor);
    AddProperty(iCodecName);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1C::MetatextPropertyChanged);
    iMetatext = new PropertyString("Metatext", functor);
    AddProperty(iMetatext);
}

CpProxyAvOpenhomeOrgInfo1C::~CpProxyAvOpenhomeOrgInfo1C()
{
    DestroyService();
    delete iActionCounters;
    delete iActionTrack;
    delete iActionDetails;
    delete iActionMetatext;
}

void CpProxyAvOpenhomeOrgInfo1C::SyncCounters(TUint& aTrackCount, TUint& aDetailsCount, TUint& aMetatextCount)
{
    SyncCountersAvOpenhomeOrgInfo1C sync(*this, aTrackCount, aDetailsCount, aMetatextCount);
    BeginCounters(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgInfo1C::BeginCounters(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionCounters, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCounters->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgInfo1C::EndCounters(IAsync& aAsync, TUint& aTrackCount, TUint& aDetailsCount, TUint& aMetatextCount)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Counters"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aTrackCount = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aDetailsCount = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aMetatextCount = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgInfo1C::SyncTrack(Brh& aUri, Brh& aMetadata)
{
    SyncTrackAvOpenhomeOrgInfo1C sync(*this, aUri, aMetadata);
    BeginTrack(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgInfo1C::BeginTrack(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionTrack, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTrack->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgInfo1C::EndTrack(IAsync& aAsync, Brh& aUri, Brh& aMetadata)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Track"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aUri);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aMetadata);
}

void CpProxyAvOpenhomeOrgInfo1C::SyncDetails(TUint& aDuration, TUint& aBitRate, TUint& aBitDepth, TUint& aSampleRate, TBool& aLossless, Brh& aCodecName)
{
    SyncDetailsAvOpenhomeOrgInfo1C sync(*this, aDuration, aBitRate, aBitDepth, aSampleRate, aLossless, aCodecName);
    BeginDetails(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgInfo1C::BeginDetails(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDetails, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDetails->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgInfo1C::EndDetails(IAsync& aAsync, TUint& aDuration, TUint& aBitRate, TUint& aBitDepth, TUint& aSampleRate, TBool& aLossless, Brh& aCodecName)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Details"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aDuration = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aBitRate = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aBitDepth = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aSampleRate = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aLossless = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aCodecName);
}

void CpProxyAvOpenhomeOrgInfo1C::SyncMetatext(Brh& aValue)
{
    SyncMetatextAvOpenhomeOrgInfo1C sync(*this, aValue);
    BeginMetatext(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgInfo1C::BeginMetatext(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionMetatext, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionMetatext->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgInfo1C::EndMetatext(IAsync& aAsync, Brh& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Metatext"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aValue);
}

void CpProxyAvOpenhomeOrgInfo1C::SetPropertyTrackCountChanged(Functor& aFunctor)
{
    iLock.Wait();
    iTrackCountChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgInfo1C::SetPropertyDetailsCountChanged(Functor& aFunctor)
{
    iLock.Wait();
    iDetailsCountChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgInfo1C::SetPropertyMetatextCountChanged(Functor& aFunctor)
{
    iLock.Wait();
    iMetatextCountChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgInfo1C::SetPropertyUriChanged(Functor& aFunctor)
{
    iLock.Wait();
    iUriChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgInfo1C::SetPropertyMetadataChanged(Functor& aFunctor)
{
    iLock.Wait();
    iMetadataChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgInfo1C::SetPropertyDurationChanged(Functor& aFunctor)
{
    iLock.Wait();
    iDurationChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgInfo1C::SetPropertyBitRateChanged(Functor& aFunctor)
{
    iLock.Wait();
    iBitRateChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgInfo1C::SetPropertyBitDepthChanged(Functor& aFunctor)
{
    iLock.Wait();
    iBitDepthChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgInfo1C::SetPropertySampleRateChanged(Functor& aFunctor)
{
    iLock.Wait();
    iSampleRateChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgInfo1C::SetPropertyLosslessChanged(Functor& aFunctor)
{
    iLock.Wait();
    iLosslessChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgInfo1C::SetPropertyCodecNameChanged(Functor& aFunctor)
{
    iLock.Wait();
    iCodecNameChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgInfo1C::SetPropertyMetatextChanged(Functor& aFunctor)
{
    iLock.Wait();
    iMetatextChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgInfo1C::PropertyTrackCount(TUint& aTrackCount) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aTrackCount = iTrackCount->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgInfo1C::PropertyDetailsCount(TUint& aDetailsCount) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aDetailsCount = iDetailsCount->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgInfo1C::PropertyMetatextCount(TUint& aMetatextCount) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aMetatextCount = iMetatextCount->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgInfo1C::PropertyUri(Brhz& aUri) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aUri.Set(iUri->Value());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgInfo1C::PropertyMetadata(Brhz& aMetadata) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aMetadata.Set(iMetadata->Value());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgInfo1C::PropertyDuration(TUint& aDuration) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aDuration = iDuration->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgInfo1C::PropertyBitRate(TUint& aBitRate) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aBitRate = iBitRate->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgInfo1C::PropertyBitDepth(TUint& aBitDepth) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aBitDepth = iBitDepth->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgInfo1C::PropertySampleRate(TUint& aSampleRate) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aSampleRate = iSampleRate->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgInfo1C::PropertyLossless(TBool& aLossless) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aLossless = iLossless->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgInfo1C::PropertyCodecName(Brhz& aCodecName) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aCodecName.Set(iCodecName->Value());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgInfo1C::PropertyMetatext(Brhz& aMetatext) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aMetatext.Set(iMetatext->Value());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgInfo1C::TrackCountPropertyChanged()
{
    ReportEvent(iTrackCountChanged);
}

void CpProxyAvOpenhomeOrgInfo1C::DetailsCountPropertyChanged()
{
    ReportEvent(iDetailsCountChanged);
}

void CpProxyAvOpenhomeOrgInfo1C::MetatextCountPropertyChanged()
{
    ReportEvent(iMetatextCountChanged);
}

void CpProxyAvOpenhomeOrgInfo1C::UriPropertyChanged()
{
    ReportEvent(iUriChanged);
}

void CpProxyAvOpenhomeOrgInfo1C::MetadataPropertyChanged()
{
    ReportEvent(iMetadataChanged);
}

void CpProxyAvOpenhomeOrgInfo1C::DurationPropertyChanged()
{
    ReportEvent(iDurationChanged);
}

void CpProxyAvOpenhomeOrgInfo1C::BitRatePropertyChanged()
{
    ReportEvent(iBitRateChanged);
}

void CpProxyAvOpenhomeOrgInfo1C::BitDepthPropertyChanged()
{
    ReportEvent(iBitDepthChanged);
}

void CpProxyAvOpenhomeOrgInfo1C::SampleRatePropertyChanged()
{
    ReportEvent(iSampleRateChanged);
}

void CpProxyAvOpenhomeOrgInfo1C::LosslessPropertyChanged()
{
    ReportEvent(iLosslessChanged);
}

void CpProxyAvOpenhomeOrgInfo1C::CodecNamePropertyChanged()
{
    ReportEvent(iCodecNameChanged);
}

void CpProxyAvOpenhomeOrgInfo1C::MetatextPropertyChanged()
{
    ReportEvent(iMetatextChanged);
}


THandle CpProxyAvOpenhomeOrgInfo1Create(CpDeviceC aDevice)
{
    return new CpProxyAvOpenhomeOrgInfo1C(aDevice);
}

void CpProxyAvOpenhomeOrgInfo1Destroy(THandle aHandle)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    delete proxyC;
}

void CpProxyAvOpenhomeOrgInfo1SyncCounters(THandle aHandle, uint32_t* aTrackCount, uint32_t* aDetailsCount, uint32_t* aMetatextCount)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncCounters(*aTrackCount, *aDetailsCount, *aMetatextCount);
}

void CpProxyAvOpenhomeOrgInfo1BeginCounters(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginCounters(functor);
}

int32_t CpProxyAvOpenhomeOrgInfo1EndCounters(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aTrackCount, uint32_t* aDetailsCount, uint32_t* aMetatextCount)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndCounters(*async, *aTrackCount, *aDetailsCount, *aMetatextCount);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyAvOpenhomeOrgInfo1SyncTrack(THandle aHandle, char** aUri, char** aMetadata)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aUri;
    Brh buf_aMetadata;
    proxyC->SyncTrack(buf_aUri, buf_aMetadata);
    *aUri = buf_aUri.Extract();
    *aMetadata = buf_aMetadata.Extract();
}

void CpProxyAvOpenhomeOrgInfo1BeginTrack(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginTrack(functor);
}

int32_t CpProxyAvOpenhomeOrgInfo1EndTrack(THandle aHandle, OhNetHandleAsync aAsync, char** aUri, char** aMetadata)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aUri;
    *aUri = NULL;
    Brh buf_aMetadata;
    *aMetadata = NULL;
    try {
        proxyC->EndTrack(*async, buf_aUri, buf_aMetadata);
        *aUri = buf_aUri.Extract();
        *aMetadata = buf_aMetadata.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyAvOpenhomeOrgInfo1SyncDetails(THandle aHandle, uint32_t* aDuration, uint32_t* aBitRate, uint32_t* aBitDepth, uint32_t* aSampleRate, uint32_t* aLossless, char** aCodecName)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aLossless = 0;
    Brh buf_aCodecName;
    proxyC->SyncDetails(*aDuration, *aBitRate, *aBitDepth, *aSampleRate, *(TBool*)aLossless, buf_aCodecName);
    *aCodecName = buf_aCodecName.Extract();
}

void CpProxyAvOpenhomeOrgInfo1BeginDetails(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginDetails(functor);
}

int32_t CpProxyAvOpenhomeOrgInfo1EndDetails(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aDuration, uint32_t* aBitRate, uint32_t* aBitDepth, uint32_t* aSampleRate, uint32_t* aLossless, char** aCodecName)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aLossless = 0;
    Brh buf_aCodecName;
    *aCodecName = NULL;
    try {
        proxyC->EndDetails(*async, *aDuration, *aBitRate, *aBitDepth, *aSampleRate, *(TBool*)aLossless, buf_aCodecName);
        *aCodecName = buf_aCodecName.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyAvOpenhomeOrgInfo1SyncMetatext(THandle aHandle, char** aValue)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValue;
    proxyC->SyncMetatext(buf_aValue);
    *aValue = buf_aValue.Extract();
}

void CpProxyAvOpenhomeOrgInfo1BeginMetatext(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginMetatext(functor);
}

int32_t CpProxyAvOpenhomeOrgInfo1EndMetatext(THandle aHandle, OhNetHandleAsync aAsync, char** aValue)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aValue;
    *aValue = NULL;
    try {
        proxyC->EndMetatext(*async, buf_aValue);
        *aValue = buf_aValue.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyAvOpenhomeOrgInfo1SetPropertyTrackCountChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyTrackCountChanged(functor);
}

void CpProxyAvOpenhomeOrgInfo1SetPropertyDetailsCountChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyDetailsCountChanged(functor);
}

void CpProxyAvOpenhomeOrgInfo1SetPropertyMetatextCountChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyMetatextCountChanged(functor);
}

void CpProxyAvOpenhomeOrgInfo1SetPropertyUriChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyUriChanged(functor);
}

void CpProxyAvOpenhomeOrgInfo1SetPropertyMetadataChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyMetadataChanged(functor);
}

void CpProxyAvOpenhomeOrgInfo1SetPropertyDurationChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyDurationChanged(functor);
}

void CpProxyAvOpenhomeOrgInfo1SetPropertyBitRateChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyBitRateChanged(functor);
}

void CpProxyAvOpenhomeOrgInfo1SetPropertyBitDepthChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyBitDepthChanged(functor);
}

void CpProxyAvOpenhomeOrgInfo1SetPropertySampleRateChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertySampleRateChanged(functor);
}

void CpProxyAvOpenhomeOrgInfo1SetPropertyLosslessChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyLosslessChanged(functor);
}

void CpProxyAvOpenhomeOrgInfo1SetPropertyCodecNameChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyCodecNameChanged(functor);
}

void CpProxyAvOpenhomeOrgInfo1SetPropertyMetatextChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyMetatextChanged(functor);
}

void CpProxyAvOpenhomeOrgInfo1PropertyTrackCount(THandle aHandle, uint32_t* aTrackCount)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyTrackCount(*aTrackCount);
}

void CpProxyAvOpenhomeOrgInfo1PropertyDetailsCount(THandle aHandle, uint32_t* aDetailsCount)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyDetailsCount(*aDetailsCount);
}

void CpProxyAvOpenhomeOrgInfo1PropertyMetatextCount(THandle aHandle, uint32_t* aMetatextCount)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyMetatextCount(*aMetatextCount);
}

void CpProxyAvOpenhomeOrgInfo1PropertyUri(THandle aHandle, char** aUri)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aUri;
    proxyC->PropertyUri(buf_aUri);
    *aUri = buf_aUri.Transfer();
}

void CpProxyAvOpenhomeOrgInfo1PropertyMetadata(THandle aHandle, char** aMetadata)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aMetadata;
    proxyC->PropertyMetadata(buf_aMetadata);
    *aMetadata = buf_aMetadata.Transfer();
}

void CpProxyAvOpenhomeOrgInfo1PropertyDuration(THandle aHandle, uint32_t* aDuration)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyDuration(*aDuration);
}

void CpProxyAvOpenhomeOrgInfo1PropertyBitRate(THandle aHandle, uint32_t* aBitRate)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyBitRate(*aBitRate);
}

void CpProxyAvOpenhomeOrgInfo1PropertyBitDepth(THandle aHandle, uint32_t* aBitDepth)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyBitDepth(*aBitDepth);
}

void CpProxyAvOpenhomeOrgInfo1PropertySampleRate(THandle aHandle, uint32_t* aSampleRate)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertySampleRate(*aSampleRate);
}

void CpProxyAvOpenhomeOrgInfo1PropertyLossless(THandle aHandle, uint32_t* aLossless)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aLossless = false;
    proxyC->PropertyLossless(*(TBool*)aLossless);
}

void CpProxyAvOpenhomeOrgInfo1PropertyCodecName(THandle aHandle, char** aCodecName)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aCodecName;
    proxyC->PropertyCodecName(buf_aCodecName);
    *aCodecName = buf_aCodecName.Transfer();
}

void CpProxyAvOpenhomeOrgInfo1PropertyMetatext(THandle aHandle, char** aMetatext)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aMetatext;
    proxyC->PropertyMetatext(buf_aMetatext);
    *aMetatext = buf_aMetatext.Transfer();
}

