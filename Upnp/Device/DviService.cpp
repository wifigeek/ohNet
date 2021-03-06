#include <DviService.h>
#include <Service.h>
#include <OhNetTypes.h>
#include <Buffer.h>
#include <Http.h>
#include <Printer.h>
#include <DviSubscription.h>
#include <Error.h>
#include <DviStack.h>

#include <stdlib.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// DvAction

DvAction::DvAction(OpenHome::Net::Action* aAction, FunctorDviInvocation aFunctor)
    : iAction(aAction)
    , iFunctor(aFunctor)
{
}

OpenHome::Net::Action* DvAction::Action()
{
    return iAction;
}

const OpenHome::Net::Action* DvAction::Action() const
{
    return iAction;
}

FunctorDviInvocation DvAction::Functor() const
{
    return iFunctor;
}


// DviService

DviService::DviService(const TChar* aDomain, const TChar* aName, TUint aVersion)
    : Service(aDomain, aName, aVersion)
    , iLock("DVSM")
    , iRefCount(1)
    , iPropertiesLock("SPRM")
{
    Stack::AddObject(this, "DviService");
}

DviService::~DviService()
{
    iLock.Wait();
    TUint i=0;
    for (; i<iSubscriptions.size(); i++) {
        DviSubscription* subscription = iSubscriptions[i];
        DviSubscriptionManager::RemoveSubscription(*subscription);
        subscription->RemoveRef();
    }
    for (i=0; i<iDvActions.size(); i++) {
        delete iDvActions[i].Action();
    }
    for (i=0; i<iProperties.size(); i++) {
        delete iProperties[i];
    }
    iLock.Signal();
    Stack::RemoveObject(this, "DviService");
}

void DviService::AddRef()
{
    Stack::Mutex().Wait();
    iRefCount++;
    Stack::Mutex().Signal();
}

void DviService::RemoveRef()
{
    Stack::Mutex().Wait();
    iRefCount--;
    TBool dead = (iRefCount == 0);
    Stack::Mutex().Signal();
    if (dead) {
        delete this;
    }
}

void DviService::AddAction(Action* aAction, FunctorDviInvocation aFunctor)
{
    DvAction action(aAction, aFunctor);
    iDvActions.push_back(action);
}

const DviService::VectorActions& DviService::DvActions() const
{
    return iDvActions;
}

void DviService::Invoke(IDviInvocation& aInvocation, TUint aVersion, const Brx& aActionName)
{
    for (TUint i=0; i<iDvActions.size(); i++) {
        if (iDvActions[i].Action()->Name() == aActionName) {
            iDvActions[i].Functor()(aInvocation, aVersion);
            return;
        }
    }

    aInvocation.InvocationReportError(501, Brn("Action not implemented"));
}

void DviService::PropertiesLock()
{
    iPropertiesLock.Wait();
}

void DviService::PropertiesUnlock()
{
    iPropertiesLock.Signal();
}

void DviService::AddProperty(Property* aProperty)
{
    iProperties.push_back(aProperty);
}

const DviService::VectorProperties& DviService::Properties() const
{
    return iProperties;
}

void DviService::PublishPropertyUpdates()
{
    iLock.Wait();
    for (TUint i=0; i<iSubscriptions.size(); i++) {
        DviSubscriptionManager::QueueUpdate(*(iSubscriptions[i]));
    }
    iLock.Signal();
}

void DviService::AddSubscription(DviSubscription* aSubscription)
{
    aSubscription->Start(*this);
    iLock.Wait();
    iSubscriptions.push_back(aSubscription);
    iLock.Signal();
    DviSubscriptionManager::QueueUpdate(*aSubscription);
}

void DviService::RemoveSubscription(const Brx& aSid)
{
    iLock.Wait();
    for (TUint i=0; i<iSubscriptions.size(); i++) {
        DviSubscription* subscription = iSubscriptions[i];
        if (subscription->Sid() == aSid) {
            DviSubscriptionManager::RemoveSubscription(*subscription);
            iSubscriptions.erase(iSubscriptions.begin() + i);
            iLock.Signal();
            subscription->RemoveRef();
            return;
        }
    }
    iLock.Signal();
}


// InvocationResponse

InvocationResponse::InvocationResponse(IDviInvocation& aInvocation)
    : iInvocation(aInvocation)
{
}

void InvocationResponse::Error(TInt aCode, const Brx& aReason)
{
	iInvocation.InvocationReportError(aCode, aReason);
}

void InvocationResponse::Start()
{
	iInvocation.InvocationWriteStart();
}

void InvocationResponse::End()
{
	iInvocation.InvocationWriteEnd();
}


// InvocationResponseBool

InvocationResponseBool::InvocationResponseBool(IDviInvocation& aInvocation, const TChar* aName)
    : iInvocation(aInvocation)
    , iName(aName)
{
}

void InvocationResponseBool::Write(TBool aValue)
{
	iInvocation.InvocationWriteBool(iName, aValue);
}


// InvocationResponseUint

InvocationResponseUint::InvocationResponseUint(IDviInvocation& aInvocation, const TChar* aName)
    : iInvocation(aInvocation)
    , iName(aName)
{
}

void InvocationResponseUint::Write(TUint aValue)
{
	iInvocation.InvocationWriteUint(iName, aValue);
}


// InvocationResponseInt

InvocationResponseInt::InvocationResponseInt(IDviInvocation& aInvocation, const TChar* aName)
    : iInvocation(aInvocation)
    , iName(aName)
{
}

void InvocationResponseInt::Write(TInt aValue)
{
	iInvocation.InvocationWriteInt(iName, aValue);
}


// InvocationResponseBinary

InvocationResponseBinary::InvocationResponseBinary(IDviInvocation& aInvocation, const TChar* aName)
    : iInvocation(aInvocation)
    , iName(aName)
    , iFirst(true)
{
}


void InvocationResponseBinary::CheckFirst()
{
	if (iFirst) {
		iInvocation.InvocationWriteBinaryStart(iName);
		iFirst = false;
	}
}

void InvocationResponseBinary::Write(TByte aValue)
{
	CheckFirst();
	iInvocation.InvocationWriteBinary(aValue);
}

void InvocationResponseBinary::Write(const Brx& aValue)
{
	CheckFirst();
	iInvocation.InvocationWriteBinary(aValue);
}

void InvocationResponseBinary::WriteFlush()
{
	CheckFirst();
	iInvocation.InvocationWriteBinaryEnd(iName);
}


// InvocationResponseString

InvocationResponseString::InvocationResponseString(IDviInvocation& aInvocation, const TChar* aName)
    : iInvocation(aInvocation)
    , iName(aName)
    , iFirst(true)
{
}


void InvocationResponseString::CheckFirst()
{
	if (iFirst) {
		iInvocation.InvocationWriteStringStart(iName);
		iFirst = false;
	}
}

void InvocationResponseString::Write(TByte aValue)
{
	CheckFirst();
	iInvocation.InvocationWriteString(aValue);
}

void InvocationResponseString::Write(const Brx& aValue)
{
	CheckFirst();
	iInvocation.InvocationWriteString(aValue);
}

void InvocationResponseString::WriteFlush()
{
	CheckFirst();
	iInvocation.InvocationWriteStringEnd(iName);
}
