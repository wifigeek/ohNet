#include <OhNetTypes.h>
#include <Exception.h>
#include <OsWrapper.h>
#include <Os.h>
#include <Network.h>
#include <Debug.h>

using namespace OpenHome;

Brn Os::GetPlatformNameAndVersion(TUint& aMajor, TUint& aMinor)
{
	char* name;
	OsGetPlatformNameAndVersion(&name, &aMajor, &aMinor);
	Brn nameBuf(name);
	return nameBuf;
}

THandle Os::NetworkCreate(ESocketType aSocketType)
{
    THandle handle = OsNetworkCreate((OsNetworkSocketType)aSocketType);
    if (handle == kHandleNull) {
        THROW(NetworkError);
    }
    return handle;
}

TInt Os::NetworkBind(THandle aHandle, const Endpoint& aEndpoint)
{
	TInt ret = OsNetworkBind(aHandle, aEndpoint.Address(), aEndpoint.Port());
	return ret;
}

TInt Os::NetworkPort(THandle aHandle, TUint& aPort)
{
    TUint port;
    TInt ret = OsNetworkPort(aHandle, &port);
    if (ret == 0) {
        aPort = port;
    }
    return ret;
}

TUint32 OpenHome::Os::NetworkGetHostByName(const Brx& aAddress)
{
    TUint32 addr;
    const TInt len = aAddress.Bytes();
    char* name = new char[len+1];
    (void)memcpy(name, aAddress.Ptr(), len);
    name[len] = '\0';
    int32_t ret = OsNetworkGetHostByName(name, &addr);
    delete[] name;
    if (ret == -1) {
        THROW(NetworkError);
    }
    return addr;
}

void OpenHome::Os::NetworkConnect(THandle aHandle, const Endpoint& aEndpoint, TUint aTimeoutMs)
{
    int32_t err = OsNetworkConnect(aHandle, aEndpoint.Address(), aEndpoint.Port(), aTimeoutMs);
    if (err != 0) {
        LOG2F(kNetwork, kError, "Os::NetworkConnect H = %d, RETURN VALUE = %d\n", aHandle, err);
        THROW(NetworkError);
    }
}

TInt OpenHome::Os::NetworkReceiveFrom(THandle aHandle, Bwx& aBuffer, Endpoint& aEndpoint)
{
    TIpAddress address;
    TUint16 port;
    TInt ret = OsNetworkReceiveFrom(aHandle, (uint8_t*)aBuffer.Ptr(), aBuffer.MaxBytes(), &address, &port);
    if (ret != -1) {
        aEndpoint.SetAddress(address);
        aEndpoint.SetPort(port);
    }
    return ret;
}

void OpenHome::Os::NetworkSocketSetSendBufBytes(THandle aHandle, TUint aBytes)
{
    int32_t err = OsNetworkSocketSetSendBufBytes(aHandle, aBytes);
    if(err != 0) {
        LOG2F(kNetwork, kError, "Os::NetworkSocketSetSendBufBytes H = %d, RETURN VALUE = %d\n", aHandle, err);
        THROW(NetworkError);
    }
}

void OpenHome::Os::NetworkSocketSetRecvBufBytes(THandle aHandle, TUint aBytes)
{
    int32_t err = OsNetworkSocketSetRecvBufBytes(aHandle, aBytes);
    if(err != 0) {
        LOG2F(kNetwork, kError, "Os::NetworkSocketSetRecvBufBytes H = %d, RETURN VALUE = %d\n", aHandle, err);
        THROW(NetworkError);
    }
}

void OpenHome::Os::NetworkSocketSetReceiveTimeout(THandle aHandle, TUint aMilliSeconds)
{
    int32_t err = OsNetworkSocketSetReceiveTimeout(aHandle, aMilliSeconds);
    if(err != 0) {
        LOG2F(kNetwork, kError, "Os::OsNetworkSocketSetReceiveTimeout H = %d, RETURN VALUE = %d\n", aHandle, err);
        THROW(NetworkError);
    }
}

void OpenHome::Os::NetworkTcpSetNoDelay(THandle aHandle)
{
    int32_t err = OsNetworkTcpSetNoDelay(aHandle);
    if(err != 0) {
        LOG2F(kNetwork, kError, "Os::OsNetworkTcpSetNoDelay H = %d, RETURN VALUE = %d\n", aHandle, err);
        THROW(NetworkError);
    }
}

void OpenHome::Os::NetworkSocketSetReuseAddress(THandle aHandle)
{
    int32_t err = OsNetworkSocketSetReuseAddress(aHandle);
    if(err != 0) {
        LOG2F(kNetwork, kError, "Os::OsNetworkSocketSetReuseAddress H = %d, RETURN VALUE = %d\n", aHandle, err);
        THROW(NetworkError);
    }
}

void OpenHome::Os::NetworkSocketSetMulticastTtl(THandle aHandle, TUint8 aTtl)
{
    int32_t err = OsNetworkSocketSetMulticastTtl(aHandle, aTtl);
    if(err != 0) {
        LOG2F(kNetwork, kError, "Os::OsNetworkSocketSetMulticastTtl H = %d, RETURN VALUE = %d\n", aHandle, err);
        THROW(NetworkError);
    }
}

void OpenHome::Os::NetworkSocketMulticastAddMembership(THandle aHandle, TIpAddress aInterface, TIpAddress aAddress)
{
    int32_t err = OsNetworkSocketMulticastAddMembership(aHandle, aInterface, aAddress);
    if(err != 0) {
        LOG2F(kNetwork, kError, "Os::OsNetworkSocketMulticastAddMembership H = %d, RETURN VALUE = %d\n", aHandle, err);
        THROW(NetworkError);
    }
}

void OpenHome::Os::NetworkSocketMulticastDropMembership(THandle aHandle, TIpAddress aInterface, TIpAddress aAddress)
{
    int32_t err = OsNetworkSocketMulticastDropMembership(aHandle, aInterface, aAddress);
    if(err != 0) {
        LOG2F(kNetwork, kError, "Os::OsNetworkSocketMulticastDropMembership H = %d, RETURN VALUE = %d\n", aHandle, err);
        THROW(NetworkError);
    }
}

std::vector<NetworkInterface*>* OpenHome::Os::NetworkListInterfaces(TBool aUseLoopback)
{
    OsNetworkInterface* cIfs = NULL;
    int32_t err = OsNetworkListInterfaces(&cIfs, (aUseLoopback? 1 : 0));
    if(err != 0) {
        LOG2F(kNetwork, kError, "Os::NetworkListInterfaces RETURN VALUE = %d\n", err);
        THROW(NetworkError);
    }
    std::vector<NetworkInterface*>* ifs = new std::vector<NetworkInterface*>;
    OsNetworkInterface* ptr = cIfs;
    while (ptr != NULL) {
        NetworkInterface* iface = new NetworkInterface(ptr->iAddress, ptr->iNetMask, ptr->iName);
        ifs->push_back(iface);
        ptr = ptr->iNext;
    }
    OsNetworkFreeInterfaces(cIfs);
    return ifs;
}
