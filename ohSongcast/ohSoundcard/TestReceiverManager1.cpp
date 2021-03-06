#include <OhNetTypes.h>
#include <OhNet.h>
#include <Ascii.h>
#include <Maths.h>
#include <Stack.h>
#include <Thread.h>
#include <OptionParser.h>
#include <Debug.h>
#include <TestFramework.h>

#include <vector>
#include <stdio.h>

#include "ReceiverManager1.h"

namespace OpenHome {
namespace Net {

	class ReceiverManager1Logger : IReceiverManager1Handler
	{
	public:
		ReceiverManager1Logger();
		virtual void ReceiverAdded(ReceiverManager1Receiver& aReceiver);
		virtual void ReceiverChanged(ReceiverManager1Receiver& aReceiver);
		virtual void ReceiverRemoved(ReceiverManager1Receiver& aReceiver);
		~ReceiverManager1Logger();
	private:
		ReceiverManager1* iReceiverManager;
	};

} // namespace Net
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

ReceiverManager1Logger::ReceiverManager1Logger()
{
	iReceiverManager = new ReceiverManager1(*this);
}

ReceiverManager1Logger::~ReceiverManager1Logger()
{
	delete (iReceiverManager);
}

void ReceiverManager1Logger::ReceiverAdded(ReceiverManager1Receiver& aReceiver)
{
    Print("Added   ");
    Print(aReceiver.Room());
    Print("(");
    Print(aReceiver.Group());
    Print(")");
	if (aReceiver.Selected()) {
	    Print(" - Selected");
	}
    Print("\n");
}

void ReceiverManager1Logger::ReceiverChanged(ReceiverManager1Receiver& aReceiver)
{
    Print("Changed   ");
    Print(aReceiver.Room());
    Print("(");
    Print(aReceiver.Group());
    Print(")");
	if (aReceiver.Selected()) {
	    Print(" - Selected");
	}
    Print("\n");
}

void ReceiverManager1Logger::ReceiverRemoved(ReceiverManager1Receiver& aReceiver)
{
    Print("Removed ");
    Print(aReceiver.Room());
    Print("(");
    Print(aReceiver.Group());
    Print(")\n");
}

int __cdecl main(int aArgc, char* aArgv[])
{
	InitialisationParams* initParams = InitialisationParams::Create();

    OptionParser parser;
    
    OptionUint optionDuration("-d", "--duration", 30, "Number of seconds to run the test");

    parser.AddOption(&optionDuration);
    
    if (!parser.Parse(aArgc, aArgv)) {
        return (1);
    }

    UpnpLibrary::Initialise(initParams);
    
    UpnpLibrary::StartCp();

    //Debug::SetLevel(Debug::kTopology);

	ReceiverManager1Logger* logger = new ReceiverManager1Logger();
	
    Blocker* blocker = new Blocker;
    blocker->Wait(optionDuration.Value());
    delete blocker;
	
	delete (logger);

	UpnpLibrary::Close();
}
