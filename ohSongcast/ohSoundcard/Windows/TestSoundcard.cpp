#include <OhNetTypes.h>
#include <OhNet.h>
#include <Ascii.h>
#include <Maths.h>
#include <Stack.h>
#include <Thread.h>
#include <OptionParser.h>
#include <Debug.h>

#include <vector>
#include <stdio.h>

#include "Soundcard.h"

#pragma warning(disable:4355) // use of 'this' in ctor lists safe in this case

#include <conio.h>

int mygetch()
{
    return (_getch());
}

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

void logger(void* /* aPtr */, EReceiverCallbackType aType, THandle aReceiver)
{
	const char* room = ReceiverRoom(aReceiver);
	const char* group = ReceiverGroup(aReceiver);
	const char* name = ReceiverName(aReceiver);
	EReceiverStatus status = ReceiverStatus(aReceiver);

	switch (aType) {
	case eAdded:
		printf("Added   %s %s %s %d\n", room, group, name, status);
		break;
	case eChanged:
		printf("Changed %s %s %s %d\n", room, group, name, status);
		break;
	case eRemoved:
		printf("Removed %s %s %s %d\n", room, group, name, status);
		break;
	}
}

int __cdecl main(int /* aArgc */, char* /* aArgv[] */)
{
	//Debug::SetLevel(Debug::kMedia);
	
	/*
    std::vector<NetworkInterface*>* ifs = Os::NetworkListInterfaces(false);
    
	ASSERT(ifs->size() > 0 && optionAdapter.Value() < ifs->size());
    
	TIpAddress iface = (*ifs)[optionAdapter.Value()]->Address();
    
	for (TUint i=0; i<ifs->size(); i++) {
        delete (*ifs)[i];
    }
    
	delete ifs;
    
    printf("Using network interface %d.%d.%d.%d\n", iface&0xff, (iface>>8)&0xff, (iface>>16)&0xff, (iface>>24)&0xff);
	*/

	TIpAddress subnet = 0;
    TUint channel = 0;
    TUint ttl = 4;
    TBool multicast = false;
    TBool disabled = false;
    TUint preset = 99;

	THandle soundcard = SoundcardCreate(subnet, channel, ttl, multicast, !disabled, preset, logger, 0);

	if (soundcard == 0) {
		printf("Soundcard error\n");
		return(1);
	}

	printf("preset = %d\n", preset);

    if (multicast) {
        printf("multicast\n");
    }
    else {
        printf("unicast\n");
    }

    if (disabled) {
        printf("disabled\n");
    }
    else {
        printf("enabled\n");
    }

	printf("q = quit, m = toggle multicast, e = toggle enabled\n");
	
    for (;;) {
    	int key = mygetch();
    	
    	if (key == 'q') {
    		break;
    	}

        if (key == 'm') {
            if (multicast) {
                multicast = false;
                SoundcardSetMulticast(soundcard, false);
                printf("unicast\n");
            }
            else {
                multicast = true;
                SoundcardSetMulticast(soundcard, true);
                printf("multicast\n");
            }
        }

        if (key == 'e') {
            if (disabled) {
                disabled = false;
                SoundcardSetEnabled(soundcard, true);
                printf("enabled\n");
            }
            else {
                disabled = true;
                SoundcardSetEnabled(soundcard, false);
                printf("disabled\n");
            }
        }
    }
    
	SoundcardDestroy(soundcard);

	printf("\n");
	
    return (0);
}
