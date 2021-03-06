#ifndef HEADER_DVI_SERVER
#define HEADER_DVI_SERVER

#include <OhNetTypes.h>
#include <Network.h>
#include <OhNet.h>
#include <Thread.h>

#include <vector>

namespace OpenHome {
namespace Net {

class DviServer
{
public:
    ~DviServer();
    TUint Port(TIpAddress aInterface);
protected:
    DviServer();
    void Initialise();
    virtual SocketTcpServer* CreateServer(const NetworkInterface& aNif) = 0;
private:
    void AddServer(const NetworkInterface& aNif);
    void SubnetChanged();
    TInt FindInterface(TIpAddress aInterface, const std::vector<NetworkInterface*>& aNifList);
    TInt FindServer(TIpAddress aSubnet);
private:
    class Server
    {
    public:
        Server(SocketTcpServer* aTcpServer, const NetworkInterface& aNif);
        ~Server();
        TIpAddress Interface() const { return iNif->Address(); }
        TIpAddress Subnet() const { return iNif->Subnet(); }
        TUint Port() const { return iServer->Port(); }
    private:
        Server() {}
    private:
        SocketTcpServer* iServer;
        NetworkInterface* iNif;
    };
private:
    Mutex iLock;
    std::vector<DviServer::Server*> iServers;
    TInt iSubnetChangeListenerId;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVI_SERVER
