#ifndef HEADER_NETWORKINTERFACELIST
#define HEADER_NETWORKINTERFACELIST

#include <OhNetTypes.h>
#include <OhNet.h>
#include <Functor.h>
#include <Thread.h>

#include <vector>
#include <map>

namespace OpenHome {

class NetworkInterfaceList
{
public:
    static const TUint kListenerIdNull = 0;
public:
    NetworkInterfaceList(TIpAddress aDefaultSubnet=0);
    ~NetworkInterfaceList();
    NetworkInterface* CurrentInterface() const;
    const std::vector<NetworkInterface*>& List() const;
    std::vector<NetworkInterface*>* CreateSubnetList() const;
    static void DestroySubnetList(std::vector<NetworkInterface*>* aList);
    void SetCurrentSubnet(const NetworkInterface& aSubnet);
    void ClearCurrentSubnet();
    TUint AddCurrentChangeListener(Functor aFunctor);
    void RemoveCurrentChangeListener(TUint aId);
    TUint AddSubnetChangeListener(Functor aFunctor);
    void RemoveSubnetChangeListener(TUint aId);
private:
    typedef std::map<TUint,Functor> Map;
    void SetDefaultSubnet(const NetworkInterface* aSubnet);
    std::vector<NetworkInterface*>* CreateSubnetListLocked() const;
    TUint AddListener(Functor aFunctor, Map& aMap);
    void RemoveSubnetChangeListener(TUint aId, Map& aMap);
    static void InterfaceListChanged(void* aPtr);
    static TInt FindSubnet(TIpAddress aSubnet, const std::vector<NetworkInterface*>& aList);
    void UpdateCurrentInterface();
    void HandleInterfaceListChanged();
    void RunCallbacks(Map& aMap);
    void ClearInterfaces(std::vector<NetworkInterface*>* aList);
private:
    mutable Mutex iListLock;
    Mutex iListenerLock;
    std::vector<NetworkInterface*>* iNetworkInterfaces;
    std::vector<NetworkInterface*>* iSubnets;
    const NetworkInterface* iCurrent;
    TIpAddress iDefaultSubnet;
    Map iListenersCurrent;
    Map iListenersSubnet;
    TUint iNextListenerId;
};

} // namespace OpenHome

#endif // HEADER_NETWORKINTERFACELIST
