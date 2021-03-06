// Auomated test for complex topology layers

#include <TestFramework.h>
#include <OptionParser.h>
#include <OhNetTypes.h>
#include <Discovery.h>
#include <Thread.h>
#include <Timer.h>
#include <OsWrapper.h>
#include "CpTopology3.h"

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

class TestDevice : public ICpTopology2GroupHandler
{
public:
    virtual void SetSourceIndex(TUint aIndex);
    virtual void SetStandby(TBool aValue);
};

void TestDevice::SetSourceIndex(TUint /* aIndex */)
{
}

void TestDevice::SetStandby(TBool /* aValue */)
{
}

class TestEntry
{
public:
    TestEntry(const Brx& aType, const Brx& aValue, const Brx& aInfo);
    TBool Check(const Brx& aType, const Brx& aValue, const Brx& aInfo);
    void Print(const TChar* aPrefix) const;
private:
    Bws<100> iType;
    Bws<100> iValue;
    Bws<100> iInfo;
};

TestEntry::TestEntry(const Brx& aType, const Brx& aValue, const Brx& aInfo)
    : iType(aType)
    , iValue(aValue)
    , iInfo(aInfo)
{
}

TBool TestEntry::Check(const Brx& aType, const Brx& aValue, const Brx& aInfo)
{
    if (iType == aType) {
        if (iValue == aValue) {
            if (iInfo == aInfo) {
                return (true);
            }
        }
    }
    
    TestEntry expected(aType, aValue, aInfo);
    
    expected.Print("E");
    
    ASSERTS();
    
    return (false);
}

void TestEntry::Print(const TChar* aPrefix) const
{
    ::Print(aPrefix);
    ::Print(" ");
    ::Print(iType);
    ::Print(":");
    ::Print(iValue);
    ::Print(":");
    ::Print(iInfo);
    ::Print("\n");
}

class TestRoom
{
public:
    TestRoom(const Brx& aName);
    void AddSource(const Brx& aName, const Brx& aType, TBool aDiscard);
    const Brx& Name() const;
    TUint SourceCount() const;
    const Brx& SourceName(TUint aIndex) const;
    const Brx& SourceType(TUint aIndex) const;
private:
    Bws<100> iName;
    TUint iCount;
    Bws<100> iNames[100];
    Bws<100> iTypes[100];
};

TestRoom::TestRoom(const Brx& aName)
    : iName(aName)
    , iCount(0)
{
}

void TestRoom::AddSource(const Brx& aName, const Brx& aType, TBool aVisible)
{
    if (aVisible) {
        iNames[iCount].Replace(aName);
        iTypes[iCount++].Replace(aType);
    }
}

const Brx& TestRoom::Name() const
{
    return (iName);
}

TUint TestRoom::SourceCount() const
{
    return (iCount);
}

const Brx& TestRoom::SourceName(TUint aIndex) const
{
    return (iNames[aIndex]);
}

const Brx& TestRoom::SourceType(TUint aIndex) const
{
    return (iTypes[aIndex]);
}

class TestTopology3Handler : public ICpTopology3Handler
{
    static const TUint kMaxFifoSlots = 100;
    
public:
    TestTopology3Handler();
    TBool CheckRoomAdded(const TestRoom& aRoom);
    TBool CheckRoomChanged(const TestRoom& aRoom);
    TBool CheckRoomRemoved(const TestRoom& aRoom);
    TBool CheckRoomSourceChanged(const TestRoom& aRoom, const Brx& aName);
    TBool CheckComplete();
    
private:
	virtual void RoomAdded(CpTopology3Room& aRoom);
    virtual void RoomChanged(CpTopology3Room& aRoom);
    virtual void RoomRemoved(CpTopology3Room& aRoom);
	virtual void RoomStandbyChanged(CpTopology3Room& aRoom);
	virtual void RoomSourceChanged(CpTopology3Room& aRoom);
	virtual void RoomVolumeControlChanged(CpTopology3Room& aRoom);
	
    void Add(const Brx& aType, const Brx& aValue, const Brx& aInfo);
    TBool Check(const Brx& aType, const Brx& aValue, const Brx& aInfo);
    
private:
    Fifo<TestEntry*> iFifo;
};

TestTopology3Handler::TestTopology3Handler()
    : iFifo(kMaxFifoSlots)
{
}

TBool TestTopology3Handler::CheckRoomAdded(const TestRoom& aRoom)
{
    Bws<10> count;
    
    Ascii::AppendDec(count, aRoom.SourceCount());
    
    if (!Check(Brn("Added"), aRoom.Name(), count)) {
        return (false);
    }
    
    for (TUint i = 0; i < aRoom.SourceCount(); i++) {
        if (!Check(Brn("Source"), aRoom.SourceName(i), aRoom.SourceType(i))) {
            return (false);
        }
    }
    
    return (true);
}

TBool TestTopology3Handler::CheckRoomChanged(const TestRoom& aRoom)
{
    Bws<10> count;
    
    Ascii::AppendDec(count, aRoom.SourceCount());
    
    if (!Check(Brn("List"), aRoom.Name(), count)) {
        return (false);
    }
    
    for (TUint i = 0; i < aRoom.SourceCount(); i++) {
        if (!Check(Brn("Source"), aRoom.SourceName(i), aRoom.SourceType(i))) {
            return (false);
        }
    }
    
    return (true);
}

TBool TestTopology3Handler::CheckRoomRemoved(const TestRoom& aRoom)
{
    return (Check(Brn("Removed"), aRoom.Name(), Brx::Empty()));
}

TBool TestTopology3Handler::CheckRoomSourceChanged(const TestRoom& aRoom, const Brx& aName)
{
    return (Check(Brn("Change"), aRoom.Name(), aName));
}

TBool TestTopology3Handler::CheckComplete()
{
    if (iFifo.SlotsUsed() == 0) {
        return (true);
    }
    
    Print("TOO MUCH\n");
    return (false);
}

void TestTopology3Handler::Add(const Brx& aType, const Brx& aValue, const Brx& aInfo)
{   TestEntry* entry = new TestEntry(aType, aValue, aInfo);
    entry->Print("I"); 
    iFifo.Write(entry);
}

TBool TestTopology3Handler::Check(const Brx& aType, const Brx& aValue, const Brx& aInfo)
{
    TestEntry* entry = iFifo.Read();
    entry->Print("O");
    TBool result = entry->Check(aType, aValue, aInfo);
    delete (entry);
    return (result);
}

void TestTopology3Handler::RoomAdded(CpTopology3Room& aRoom)
{
    Bws<10> count;
    
    Ascii::AppendDec(count, aRoom.SourceCount());
    
    Add(Brn("Added"), aRoom.Name(), count);
    
    for (TUint i = 0; i < aRoom.SourceCount(); i++) {
        Add(Brn("Source"), aRoom.SourceName(i), aRoom.SourceType(i));
    }
}

void TestTopology3Handler::RoomChanged(CpTopology3Room& aRoom)
{
    Bws<10> count;
    
    Ascii::AppendDec(count, aRoom.SourceCount());
    
    Add(Brn("List"), aRoom.Name(), count);
    
    for (TUint i = 0; i < aRoom.SourceCount(); i++) {
        Add(Brn("Source"), aRoom.SourceName(i), aRoom.SourceType(i));
    }
}

void TestTopology3Handler::RoomRemoved(CpTopology3Room& aRoom)
{
    Add(Brn("Removed"), aRoom.Name(), Brx::Empty());
}

void TestTopology3Handler::RoomStandbyChanged(CpTopology3Room& aRoom)
{
	Bws<10> standby;

	switch(aRoom.Standby()) {
	case CpTopology3Room::eOff:
		standby.Replace(Brn("Off"));
		break;
	case CpTopology3Room::eMixed:
		standby.Replace(Brn("Mixed"));
		break;
	case CpTopology3Room::eOn:
		standby.Replace(Brn("On"));
		break;
	}

    Add(Brn("Standby"), aRoom.Name(), standby);
}

void TestTopology3Handler::RoomSourceChanged(CpTopology3Room& aRoom)
{
    Add(Brn("Change"), aRoom.Name(), aRoom.CurrentSourceName());
}

void TestTopology3Handler::RoomVolumeControlChanged(CpTopology3Room& aRoom)
{
    Add(Brn("Volume Control"), aRoom.Name(), aRoom.HasVolumeControl() ? Brn("Yes") : Brn("No"));
}

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], InitialisationParams* aInitParams)
{
    UpnpLibrary::Initialise(aInitParams);

    // Debug::SetLevel(Debug::kTopology);
    // Debug::SetLevel(Debug::kAll);

    TestDevice device;
    TestTopology3Handler handler3;
    
	ICpTopology2Handler* handler2 = NULL;

	CpTopology3* topology3 = new CpTopology3(handler3, &handler2);

    Print("Test 1\n");
    Print("Add and remove 1\n");
    
    CpDevice* cpdevice = 0;
    
    CpTopology2Group* group1 = new CpTopology2Group(*cpdevice, device, false, Brn("Kitchen"), Brn("Majik DS-I"), 0, false);
    
    group1->AddSource(Brn("Playlist"), Brn("Playlist"), true);
    group1->AddSource(Brn("Radio"), Brn("Radio"), true);
    group1->AddSource(Brn("Songcast"), Brn("Receiver"), true);
    group1->AddSource(Brn("UpnpAv"), Brn("UpnpAv"), false);
    group1->AddSource(Brn("Analog1"), Brn("Analog"), true);
    group1->AddSource(Brn("Analog2"), Brn("Analog"), true);
    group1->AddSource(Brn("Analog3"), Brn("Analog"), true);
    group1->AddSource(Brn("Phono"), Brn("Analog"), true);
    group1->AddSource(Brn("Front Aux"), Brn("Analog"), true);
    group1->AddSource(Brn("Spdif1"), Brn("Digital"), true);
    group1->AddSource(Brn("Spdif2"), Brn("Digital"), true);
    group1->AddSource(Brn("Spdif3"), Brn("Digital"), true);
    group1->AddSource(Brn("Toslink1"), Brn("Digital"), true);
    group1->AddSource(Brn("Toslink2"), Brn("Digital"), true);
    group1->AddSource(Brn("Toslink3"), Brn("Digital"), true);
    
    TestRoom* room1 = new TestRoom(Brn("Kitchen"));
    room1->AddSource(Brn("Playlist"), Brn("Playlist"), true);
    room1->AddSource(Brn("Radio"), Brn("Radio"), true);
    room1->AddSource(Brn("Songcast"), Brn("Receiver"), true);
    room1->AddSource(Brn("UpnpAv"), Brn("UpnpAv"), false);
    room1->AddSource(Brn("Analog1"), Brn("Analog"), true);
    room1->AddSource(Brn("Analog2"), Brn("Analog"), true);
    room1->AddSource(Brn("Analog3"), Brn("Analog"), true);
    room1->AddSource(Brn("Phono"), Brn("Analog"), true);
    room1->AddSource(Brn("Front Aux"), Brn("Analog"), true);
    room1->AddSource(Brn("Spdif1"), Brn("Digital"), true);
    room1->AddSource(Brn("Spdif2"), Brn("Digital"), true);
    room1->AddSource(Brn("Spdif3"), Brn("Digital"), true);
    room1->AddSource(Brn("Toslink1"), Brn("Digital"), true);
    room1->AddSource(Brn("Toslink2"), Brn("Digital"), true);
    room1->AddSource(Brn("Toslink3"), Brn("Digital"), true);

    handler2->GroupAdded(*group1);
    handler3.CheckRoomAdded(*room1);
    
    handler2->GroupRemoved(*group1);
    handler3.CheckRoomRemoved(*room1);

    Print("Test 2\n");
    Print("Add 1, add 2\n");

    CpTopology2Group* group2 = new CpTopology2Group(*cpdevice, device, false, Brn("Kitchen"), Brn("Phono"), 0, true);
    
    group2->AddSource(Brn("Playlist"), Brn("Playlist"), true);
    group2->AddSource(Brn("Radio"), Brn("Radio"), true);
    group2->AddSource(Brn("Songcast"), Brn("Receiver"), true);
    group2->AddSource(Brn("UpnpAv"), Brn("UpnpAv"), false);
    group2->AddSource(Brn("Analog1"), Brn("Analog"), true);
    group2->AddSource(Brn("Analog2"), Brn("Analog"), true);
    group2->AddSource(Brn("Analog3"), Brn("Analog"), true);
    group2->AddSource(Brn("Phono"), Brn("Analog"), true);
    group2->AddSource(Brn("Front Aux"), Brn("Analog"), true);
    group2->AddSource(Brn("Spdif1"), Brn("Digital"), true);
    group2->AddSource(Brn("Spdif2"), Brn("Digital"), true);
    group2->AddSource(Brn("Spdif3"), Brn("Digital"), true);
    group2->AddSource(Brn("Toslink1"), Brn("Digital"), true);
    group2->AddSource(Brn("Toslink2"), Brn("Digital"), true);
    group2->AddSource(Brn("Toslink3"), Brn("Digital"), true);
    
    TestRoom* room2 = new TestRoom(Brn("Kitchen"));
    room2->AddSource(Brn("Playlist"), Brn("Playlist"), true);
    room2->AddSource(Brn("Radio"), Brn("Radio"), true);
    room2->AddSource(Brn("Songcast"), Brn("Receiver"), true);
    room2->AddSource(Brn("UpnpAv"), Brn("UpnpAv"), false);
    room2->AddSource(Brn("Analog1"), Brn("Analog"), true);
    room2->AddSource(Brn("Analog2"), Brn("Analog"), true);
    room2->AddSource(Brn("Analog3"), Brn("Analog"), true);
    room2->AddSource(Brn("Phono"), Brn("Analog"), true);
    room2->AddSource(Brn("Front Aux"), Brn("Analog"), true);
    room2->AddSource(Brn("Spdif1"), Brn("Digital"), true);
    room2->AddSource(Brn("Spdif2"), Brn("Digital"), true);
    room2->AddSource(Brn("Spdif3"), Brn("Digital"), true);
    room2->AddSource(Brn("Toslink1"), Brn("Digital"), true);
    room2->AddSource(Brn("Toslink2"), Brn("Digital"), true);
    room2->AddSource(Brn("Toslink3"), Brn("Digital"), true);

    TestRoom* room1and2 = new TestRoom(Brn("Kitchen"));
    room1and2->AddSource(Brn("Playlist"), Brn("Playlist"), true);
    room1and2->AddSource(Brn("Radio"), Brn("Radio"), true);
    room1and2->AddSource(Brn("Songcast"), Brn("Receiver"), true);
    room1and2->AddSource(Brn("UpnpAv"), Brn("UpnpAv"), false);
    room1and2->AddSource(Brn("Analog1"), Brn("Analog"), true);
    room1and2->AddSource(Brn("Analog2"), Brn("Analog"), true);
    room1and2->AddSource(Brn("Analog3"), Brn("Analog"), true);
    // START room1and2->AddSource(Brn("Phono"), Brn("Analog"), true);
    room1and2->AddSource(Brn("Playlist"), Brn("Playlist"), true);
    room1and2->AddSource(Brn("Radio"), Brn("Radio"), true);
    room1and2->AddSource(Brn("Songcast"), Brn("Receiver"), true);
    room1and2->AddSource(Brn("UpnpAv"), Brn("UpnpAv"), false);
    room1and2->AddSource(Brn("Analog1"), Brn("Analog"), true);
    room1and2->AddSource(Brn("Analog2"), Brn("Analog"), true);
    room1and2->AddSource(Brn("Analog3"), Brn("Analog"), true);
    room1and2->AddSource(Brn("Phono"), Brn("Analog"), true);
    room1and2->AddSource(Brn("Front Aux"), Brn("Analog"), true);
    room1and2->AddSource(Brn("Spdif1"), Brn("Digital"), true);
    room1and2->AddSource(Brn("Spdif2"), Brn("Digital"), true);
    room1and2->AddSource(Brn("Spdif3"), Brn("Digital"), true);
    room1and2->AddSource(Brn("Toslink1"), Brn("Digital"), true);
    room1and2->AddSource(Brn("Toslink2"), Brn("Digital"), true);
    room1and2->AddSource(Brn("Toslink3"), Brn("Digital"), true);
    // END
    room1and2->AddSource(Brn("Front Aux"), Brn("Analog"), true);
    room1and2->AddSource(Brn("Spdif1"), Brn("Digital"), true);
    room1and2->AddSource(Brn("Spdif2"), Brn("Digital"), true);
    room1and2->AddSource(Brn("Spdif3"), Brn("Digital"), true);
    room1and2->AddSource(Brn("Toslink1"), Brn("Digital"), true);
    room1and2->AddSource(Brn("Toslink2"), Brn("Digital"), true);
    room1and2->AddSource(Brn("Toslink3"), Brn("Digital"), true);

    handler2->GroupAdded(*group1);
    handler2->GroupAdded(*group2);
    handler3.CheckRoomAdded(*room1);
    handler3.CheckRoomChanged(*room1and2);

    Print("Test 3\n");
    Print("Remove 2\n");

    handler2->GroupRemoved(*group2);
    handler3.CheckRoomChanged(*room1);

    Print("Test 4\n");
    Print("Add 2\n");

    handler2->GroupAdded(*group2);
    handler3.CheckRoomChanged(*room1and2);

    Print("Test 5\n");
    Print("Remove 1\n");

    handler2->GroupRemoved(*group1);
	handler3.CheckRoomSourceChanged(*room2, Brn("Playlist"));
    handler3.CheckRoomChanged(*room2);

    Print("Test 6\n");
    Print("Add 1\n");

    handler2->GroupAdded(*group1);
	handler3.CheckRoomSourceChanged(*room1and2, Brn("Playlist"));
    handler3.CheckRoomChanged(*room1and2);

    Print("Test 7\n");
    Print("Remove 1 and 2\n");

    handler2->GroupRemoved(*group1);
    handler2->GroupRemoved(*group2);
	handler3.CheckRoomSourceChanged(*room2, Brn("Playlist"));
    handler3.CheckRoomChanged(*room2);
    handler3.CheckRoomRemoved(*room1);

    delete topology3;

    UpnpLibrary::Close();
}
