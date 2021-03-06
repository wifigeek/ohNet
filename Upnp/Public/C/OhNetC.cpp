#include <C/OhNet.h>
#include <OhNet.h>
#include <Functor.h>
#include <FunctorMsg.h>
#include <Stack.h>

#include <stdlib.h>

using namespace OpenHome;
using namespace OpenHome::Net;

int32_t OhNetLibraryInitialise(OhNetHandleInitParams aInitParams)
{
    if (Stack::IsInitialised()) {
        return -1;
    }
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aInitParams);
    try {
        UpnpLibrary::Initialise(ip);
    }
    catch(...) {
        return -1;
    }
    return 0;
}

int32_t OhNetLibraryInitialiseMinimal(OhNetHandleInitParams aInitParams)
{
    if (Stack::IsInitialised()) {
        return -1;
    }
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aInitParams);
    try {
        UpnpLibrary::InitialiseMinimal(ip);
    }
    catch(...) {
        return -1;
    }
    return 0;
}

void OhNetLibraryClose()
{
    UpnpLibrary::Close();
}

void OhNetFree(void* aPtr)
{
    free(aPtr);
}

OhNetHandleInitParams OhNetInitParamsCreate()
{
    return (OhNetHandleInitParams)InitialisationParams::Create();
}

void OhNetInitParamsDestroy(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    delete ip;
}

void OhNetInitParamsSetLogOutput(OhNetHandleInitParams aParams, OhNetCallbackMsg aCallback, void* aPtr)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    FunctorMsg functor = MakeFunctorMsgC(aPtr, aCallback);
    ip->SetLogOutput(functor);
}

void OhNetInitParamsSetFatalErrorHandler(OhNetHandleInitParams aParams, OhNetCallbackMsg aCallback, void* aPtr)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    FunctorMsg functor = MakeFunctorMsgC(aPtr, aCallback);
    ip->SetFatalErrorHandler(functor);
}

void OhNetInitParamsSetAsyncBeginHandler(OhNetHandleInitParams aParams, OhNetCallbackAsync aCallback, void* aPtr)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    ip->SetAsyncBeginHandler(functor);
}

void OhNetInitParamsSetAsyncEndHandler(OhNetHandleInitParams aParams, OhNetCallbackAsync aCallback, void* aPtr)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    ip->SetAsyncEndHandler(functor);
}

void OhNetInitParamsSetAsyncErrorHandler(OhNetHandleInitParams aParams, OhNetCallbackAsync aCallback, void* aPtr)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    ip->SetAsyncErrorHandler(functor);
}

void OhNetInitParamsSetDefaultSubnet(OhNetHandleInitParams aParams, TIpAddress aSubnet)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetDefaultSubnet(aSubnet);
}

void OhNetInitParamsSetSubnetChangedListener(OhNetHandleInitParams aParams, OhNetCallback aCallback, void* aPtr)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    Functor functor = MakeFunctor(aPtr, aCallback);
    ip->SetSubnetChangedListener(functor);
}

void OhNetInitParamsSetTcpConnectTimeout(OhNetHandleInitParams aParams, uint32_t aTimeoutMs)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetTcpConnectTimeout(aTimeoutMs);
}

void OhNetInitParamsSetMsearchTime(OhNetHandleInitParams aParams, uint32_t aSecs)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetMsearchTime(aSecs);
}

void OhNetInitParamsSetMsearchTtl(OhNetHandleInitParams aParams, uint32_t aTtl)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetMsearchTtl(aTtl);
}

void OhNetInitParamsSetNumEventSessionThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetNumEventSessionThreads(aNumThreads);
}

void OhNetInitParamsSetNumXmlFetcherThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetNumXmlFetcherThreads(aNumThreads);
}

void OhNetInitParamsSetNumActionInvokerThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetNumActionInvokerThreads(aNumThreads);
}

void OhNetInitParamsSetNumInvocations(OhNetHandleInitParams aParams, uint32_t aNumInvocations)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetNumInvocations(aNumInvocations);
}

void OhNetInitParamsSetNumSubscriberThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetNumSubscriberThreads(aNumThreads);
}

void OhNetInitParamsSetPendingSubscriptionTimeout(OhNetHandleInitParams aParams, uint32_t aTimeoutMs)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetPendingSubscriptionTimeout(aTimeoutMs);
}

void OhNetInitParamsSetFreeExternalCallback(OhNetHandleInitParams aParams, OhNetCallbackFreeExternal aCallback)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetFreeExternalCallback(aCallback);
}

void OhNetInitParamsSetUseLoopbackNetworkInterface(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetUseLoopbackNetworkInterface();
}

void OhNetInitParamsSetDvMaxUpdateTime(OhNetHandleInitParams aParams, uint32_t aSecs)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetDvMaxUpdateTime(aSecs);
}

void OhNetInitParamsSetDvNumServerThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
	ip->SetDvNumServerThreads(aNumThreads);
}

void OhNetInitParamsSetDvNumPublisherThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
	ip->SetDvNumPublisherThreads(aNumThreads);
}

void OhNetInitParamsSetDvNumWebSocketThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
	ip->SetDvNumWebSocketThreads(aNumThreads);
}

void OhNetInitParamsSetDvWebSocketPort(OhNetHandleInitParams aParams, uint32_t aPort)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
	ip->SetDvWebSocketPort(aPort);
}

void OhNetInitParamsSetDvEnableBonjour(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    ip->SetDvEnableBonjour();
}

uint32_t OhNetInitParamsTcpConnectTimeoutMs(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->TcpConnectTimeoutMs();
}

uint32_t OhNetInitParamsMsearchTimeSecs(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->MsearchTimeSecs();
}

uint32_t OhNetInitParamsMsearchTtl(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->MsearchTtl();
}

uint32_t OhNetInitParamsNumEventSessionThreads(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->NumEventSessionThreads();
}

uint32_t OhNetInitParamsNumXmlFetcherThreads(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->NumXmlFetcherThreads();
}

uint32_t OhNetInitParamsNumActionInvokerThreads(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->NumActionInvokerThreads();
}

uint32_t OhNetInitParamsNumInvocations(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->NumInvocations();
}

uint32_t OhNetInitParamsNumSubscriberThreads(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->NumSubscriberThreads();
}

uint32_t OhNetInitParamsPendingSubscriptionTimeoutMs(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->PendingSubscriptionTimeoutMs();
}

uint32_t OhNetInitParamsDvMaxUpdateTimeSecs(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
    return ip->DvMaxUpdateTimeSecs();
}

uint32_t OhNetInitParamsDvNumServerThreads(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
	return ip->DvNumServerThreads();
}

uint32_t OhNetInitParamsDvNumPublisherThreads(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
	return ip->DvNumPublisherThreads();
}

uint32_t OhNetInitParamsDvNumWebSocketThreads(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
	return ip->DvNumWebSocketThreads();
}

uint32_t OhNetInitParamsDvWebSocketPort(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
	return ip->DvWebSocketPort();
}

uint32_t OhNetInitParamsDvIsBonjourEnabled(OhNetHandleInitParams aParams)
{
    InitialisationParams* ip = reinterpret_cast<InitialisationParams*>(aParams);
	return (ip->DvIsBonjourEnabled()? 1 : 0);
}

TIpAddress OhNetNetworkInterfaceAddress(OhNetHandleNetworkInterface aNif)
{
    NetworkInterface* nif = reinterpret_cast<NetworkInterface*>(aNif);
    ASSERT(nif != NULL);
    return nif->Address();
}

TIpAddress OhNetNetworkInterfaceSubnet(OhNetHandleNetworkInterface aNif)
{
    NetworkInterface* nif = reinterpret_cast<NetworkInterface*>(aNif);
    ASSERT(nif != NULL);
    return nif->Subnet();
}

const char* OhNetNetworkInterfaceName(OhNetHandleNetworkInterface aNif)
{
    NetworkInterface* nif = reinterpret_cast<NetworkInterface*>(aNif);
    ASSERT(nif != NULL);
    return nif->Name();
}

OhNetHandleNetworkInterfaceList OhNetSubnetListCreate()
{
    return (OhNetHandleNetworkInterfaceList)UpnpLibrary::SubnetList();
}

uint32_t OhNetSubnetListSize(OhNetHandleNetworkInterfaceList aList)
{
    std::vector<NetworkInterface*>* list = reinterpret_cast<std::vector<NetworkInterface*>*>(aList);
    ASSERT(list != NULL);
    return (TUint)list->size();
}

OhNetHandleNetworkInterface OhNetSubnetAt(OhNetHandleNetworkInterfaceList aList, uint32_t aIndex)
{
    std::vector<NetworkInterface*>* list = reinterpret_cast<std::vector<NetworkInterface*>*>(aList);
    ASSERT(list != NULL);
    return (OhNetHandleNetworkInterface)(*list)[aIndex];
}

void OhNetSubnetListDestroy(OhNetHandleNetworkInterfaceList aList)
{
    std::vector<NetworkInterface*>* list = reinterpret_cast<std::vector<NetworkInterface*>*>(aList);
    if (list != NULL) {
        for (uint32_t i=0; i<list->size(); i++) {
            delete (*list)[i];
        }
        delete list;
    }
}

void OhNetSetCurrentSubnet(OhNetHandleNetworkInterface aSubnet)
{
    NetworkInterface* nif = reinterpret_cast<NetworkInterface*>(aSubnet);
    UpnpLibrary::SetCurrentSubnet(*nif);
}

void OhNetSetDefaultSubnet()
{
    UpnpLibrary::SetDefaultSubnet();
}

void OhNetFreeExternal(void* aPtr)
{
	OhNetCallbackFreeExternal cb = Stack::InitParams().FreeExternal();
	if (cb != NULL) {
		cb(aPtr);
	}
	else {
		free(aPtr);
	}
}
