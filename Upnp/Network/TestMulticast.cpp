#include <Standard.h>
#include <Thread.h>
#include <TestFramework.h>
#include <OptionParser.h>
#include <Network.h>
#include <Debug.h>
#include <OsWrapper.h>
#include <Arch.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;

// SuiteTcpClient

void OpenHome::TestFramework::Runner::Main(TInt aArgc, TChar* aArgv[], Net::InitialisationParams* aInitParams)
{
    OptionParser parser;    

    OptionUint adapter("-i", "--interface", 0, "index of network adapter to use");
    parser.AddOption(&adapter);

    OptionBool receive("-r", "--receive", "Receive");
    parser.AddOption(&receive);

    OptionString endpoint("-a", "--address", Brn("239.255.255.250"), "Multicast address");
    parser.AddOption(&endpoint);

    OptionUint port("-p", "--port", 0, "Multicast port");
    parser.AddOption(&port);

    if (!parser.Parse(aArgc, aArgv) || parser.HelpDisplayed()) {
        return;
    }

    Net::UpnpLibrary::InitialiseMinimal(aInitParams);

    std::vector<NetworkInterface*>* ifs = Os::NetworkListInterfaces(false);
    ASSERT(ifs->size() > 0 && adapter.Value() < ifs->size());
    TIpAddress addr = (*ifs)[adapter.Value()]->Address();
    for (TUint i=0; i<ifs->size(); i++) {
        delete (*ifs)[i];
    }
    delete ifs;
    Endpoint endpt(0, addr);
    Endpoint::AddressBuf buf;
    endpt.AppendAddress(buf);
    Print("Using network interface %s\n\n", buf.Ptr());
    
    Endpoint multicast(port.Value(), endpoint.Value());
    
    if (receive.Value()) {
        SocketUdpMulticast socket(addr, multicast);

        Endpoint actual(socket.Port(), multicast.Address());
        Bws<100> buf2;
        actual.AppendEndpoint(buf2);
        Print("Receiving from multicast endpoint %s\n", buf2.Ptr());
    
        Bws<10000> message;
        Endpoint sender = socket.Receive(message);
        Bws<100> buf3;
        sender.AppendEndpoint(buf3);
        
        if (message == Brn("Test message")) {
            Print("Received test messsge from %s\n", buf3.Ptr());
        }
        else {
            Print("Received unrecognised messsge from %s\n", buf3.Ptr());
        }
    }
    else {
        if (multicast.Port() == 0) {
            Print("Cannot send to port 0\n");
        }
        else {
            Bws<100> buf2;
            multicast.AppendEndpoint(buf2);
            Print("Sending test message to %s\n", buf2.Ptr());
        
	        SocketUdpMulticast socket(addr, multicast);
            //SocketUdp socket(0, addr);
            
			socket.Send(Brn("Test message"), multicast);
        }
    } 

    Net::UpnpLibrary::Close();
}
