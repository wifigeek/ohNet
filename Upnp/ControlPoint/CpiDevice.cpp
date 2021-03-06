#include <CpiDevice.h>
#include <Thread.h>
#include <Debug.h>
#include <OhNetTypes.h>
#include <Stack.h>
#include <CpiStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// CpiDevice

CpiDevice::CpiDevice(const Brx& aUdn, ICpiProtocol& aProtocol, ICpiDeviceObserver& aObserver, void* aOwnerData)
    : iUdn(aUdn)
    , iLock("CDVM")
    , iProtocol(aProtocol)
    , iObserver(aObserver)
    , iOwnerData(aOwnerData)
    , iRefCount(1)
    , iReady(false)
    , iExpired(false)
{
    Stack::AddObject(this, "CpiDevice");
}

const Brx& CpiDevice::Udn() const
{
    return iUdn;
}

const TChar* CpiDevice::UdnAsCString() const
{
    return iUdn.CString();
}

TBool CpiDevice::operator==(const CpiDevice& aDevice) const
{
    return (&aDevice == this);
}

TBool CpiDevice::operator!=(const CpiDevice& aDevice) const
{
    return (&aDevice != this);
}

void* CpiDevice::OwnerData()
{
    return iOwnerData;
}

void CpiDevice::AddRef()
{
    iLock.Wait();
    iRefCount++;
    iLock.Signal();
}

void CpiDevice::RemoveRef()
{
    TBool dead;
    iLock.Wait();
    dead = (--iRefCount <= 0);
    iLock.Signal();
    if (dead) {
        iObserver.Release();
        delete this;
    }
}

TBool CpiDevice::GetAttribute(const char* aKey, Brh& aValue) const
{
    return iProtocol.GetAttribute(aKey, aValue);
}

void CpiDevice::InvokeAction(Invocation& aInvocation)
{
    iProtocol.InvokeAction(aInvocation);
}

TUint CpiDevice::Subscribe(CpiSubscription& aSubscription, const Uri& aSubscriber)
{
    return iProtocol.Subscribe(aSubscription, aSubscriber);
}

TUint CpiDevice::Renew(CpiSubscription& aSubscription)
{
    return iProtocol.Renew(aSubscription);
}

void CpiDevice::Unsubscribe(CpiSubscription& aSubscription, const Brx& aSid)
{
    iProtocol.Unsubscribe(aSubscription, aSid);
}

void CpiDevice::SetReady()
{
    iReady = true;
}

TBool CpiDevice::IsReady() const
{
    return iReady;
}

void CpiDevice::SetExpired(TBool aExpired)
{
    iExpired = aExpired;
}

TBool CpiDevice::HasExpired() const
{
    return iExpired;
}

CpiDevice::~CpiDevice()
{
    LOG(kDevice, "~CpiDevice for device ");
    LOG(kDevice, iUdn);
    LOG(kDevice, "\n");
    ASSERT(iRefCount == 0);
    Stack::RemoveObject(this, "CpiDevice");
}


// CpiDeviceList

void CpiDeviceList::Refresh()
{
}

CpiDevice* CpiDeviceList::RefDevice(const Brx& aUdn)
{
    AutoMutex a(iLock);
    return RefDeviceLocked(aUdn);
}

CpiDevice* CpiDeviceList::RefDeviceLocked(const Brx& aUdn)
{
    Brn udn(aUdn);
    Map::iterator it = iMap.find(udn);
    if (it == iMap.end()) {
        return NULL;
    }
    CpiDevice* device = it->second;
    device->AddRef();
    return device;
}

CpiDeviceList::CpiDeviceList(FunctorCpiDevice aAdded, FunctorCpiDevice aRemoved)
    : iActive(false)
    , iRefreshing(false)
    , iLock("CDLM")
    , iAdded(aAdded)
    , iRemoved(aRemoved)
    , iRefCount(0)
    , iShutdownSem("CDLS", 0)
{
    ASSERT(iAdded);
    ASSERT(iRemoved);
    Stack::AddObject(this, "CpiDeviceList");
}

CpiDeviceList::~CpiDeviceList()
{
    TBool wait = false;
    Stack::Mutex().Wait();
    if (iRefCount > 0) {
        wait = true;
        iShutdownSem.Clear();
    }
    Stack::Mutex().Signal();
    if (wait) {
        iShutdownSem.Wait();
    }
    ClearMap(iMap);
    ClearMap(iRefreshMap);
    Stack::RemoveObject(this, "CpiDeviceList");
}

void CpiDeviceList::Add(CpiDevice* aDevice)
{
    LOG(kDevice, "CpiDeviceList::Add for device ");
    LOG(kDevice, aDevice->Udn());
    LOG(kDevice, "\n");
    iLock.Wait();
    if (aDevice->HasExpired() || !iActive) {
        LOG(kDevice, "< CpiDeviceList::Add, device expired or list stopped\n");
        aDevice->RemoveRef();
        iLock.Signal();
        return;
    }
    if (iRefreshing) {
        Brn udn(aDevice->Udn());
        Map::iterator it = iRefreshMap.find(udn);
        if (it == iRefreshMap.end()) {
            iRefreshMap.insert(std::pair<Brn,CpiDevice*>(udn, aDevice));
            aDevice->AddRef(); // for refresh list
        }
    }
    CpiDevice* tmp = RefDeviceLocked(aDevice->Udn());
    if (tmp != NULL) {
        // device is already in the list, ignore this call to Add()
        LOG(kDevice, "< CpiDeviceList::Add, device already in list\n");
        tmp->RemoveRef();
        aDevice->RemoveRef();
        iLock.Signal();
        return;
    }
    Brn udn(aDevice->Udn());
    iMap.insert(std::pair<Brn,CpiDevice*>(udn, aDevice));
    aDevice->AddRef(); // for observer
    iLock.Signal();
    if (IsDeviceReady(*aDevice)) {
        SetDeviceReady(*aDevice);
    }
    aDevice->RemoveRef(); // observer's ref
}

void CpiDeviceList::Remove(const Brx& aUdn)
{
    CpiDeviceListUpdater::QueueRemoved(*this, aUdn);
}

TBool CpiDeviceList::IsDeviceReady(CpiDevice& /*aDevice*/)
{
    return true;
}

TBool CpiDeviceList::StartRefresh()
{
    TBool refreshAlreadyInProgress;
    iLock.Wait();
    refreshAlreadyInProgress = iRefreshing;
    iRefreshing = true;
    iLock.Signal();
    return refreshAlreadyInProgress;
}

void CpiDeviceList::RefreshComplete()
{
    CpiDeviceListUpdater::QueueRefreshed(*this);
}

void CpiDeviceList::SetDeviceReady(CpiDevice& aDevice)
{
    aDevice.SetReady();
    CpiDeviceListUpdater::QueueAdded(*this, aDevice);
}

void CpiDeviceList::ClearMap(Map& aMap)
{
    Map::iterator it = aMap.begin();
    while (it != aMap.end()) {
        it->second->RemoveRef();
        it->second = NULL;
        it++;
    }
    aMap.clear();
}

void CpiDeviceList::AddRef()
{
    Stack::Mutex().Wait();
    ++iRefCount;
    Stack::Mutex().Signal();
}

void CpiDeviceList::RemoveRef()
{
    Stack::Mutex().Wait();
    if (--iRefCount == 0) {
        iShutdownSem.Signal();
    }
    Stack::Mutex().Signal();
}

void CpiDeviceList::NotifyAdded(CpiDevice& aDevice)
{
    LOG(kDevice, "CpiDeviceList::NotifyAdded for device ");
    LOG(kDevice, aDevice.Udn());
    LOG(kDevice, "\n");
    iLock.Wait();
    if (!iActive) {
        iLock.Signal();
        return;
    }
    iLock.Signal();
    iAdded(aDevice);
}

void CpiDeviceList::NotifyRemoved(const Brx& aUdn)
{
    DoRemove(aUdn);
}

void CpiDeviceList::DoRemove(const Brx& aUdn)
{
    LOG(kDevice, "> CpiDeviceList::DoRemove for device ");
    LOG(kDevice, aUdn);
    LOG(kDevice, "\n");
    iLock.Wait();
    TBool callObserver;
    Brn udn(aUdn);
    Map::iterator it = iMap.find(udn);
    if (it == iMap.end()) {
        // device isn't in this list
        LOG(kDevice, "< CpiDeviceList::DoRemove, device not in list\n");
        iLock.Signal();
        return;
    }
    CpiDevice* device = it->second;
    // don't remove our ref to the device yet, re-use it for the observer
    callObserver = (iActive && device->IsReady());
    it->second = NULL;
    iMap.erase(it);
    iLock.Signal();
    if (callObserver) {
        iRemoved(*device);
    }
    device->RemoveRef();
}

void CpiDeviceList::NotifyRefreshed()
{
    iLock.Wait();
    iRefreshing = false;
    if (iActive) {
        /* map iterator is invalidated by removing an item so we'll need to iterate once per removal
           assume that the 0.5 * O(n^2) ish cost is bearable as refresh is a rare operation which
           can only feasibly run once ever few seconds in the worst possible case */
        Map::iterator it = iMap.begin();
        while (it != iMap.end()) {
            Map::iterator found = iRefreshMap.find(it->first);
            if (found != iRefreshMap.end()) {
                // device still exists
                it++;
            }
            else {
                CpiDevice* device = it->second;
                // skip devices which aren't ready yet
                // ...assume that they'll either become ready or will be removed via other routes in time
                // Upnp lists don't cope with devices being removed in this state
                if (!device->IsReady()) {
                    it++;
                }
                else {    
                    device->AddRef();
                    iLock.Signal();
                    DoRemove(device->Udn());
                    device->RemoveRef();
                    iLock.Wait();
                    it = iMap.begin();
                }    
            }
        }
    }
    ClearMap(iRefreshMap);
    iLock.Signal();
}


// CpiDeviceListUpdater

CpiDeviceListUpdater::CpiDeviceListUpdater()
    : Thread("DLUP")
    , iLock("DLUM")
{
    Start();
}

CpiDeviceListUpdater::~CpiDeviceListUpdater()
{
    Kill();
    Join();
    while (iList.size() > 0) {
        iLock.Wait();
        UpdateBase* update = iList.front();
        iList.pop_front();
        iLock.Signal();
        delete update;
    }
}

void CpiDeviceListUpdater::QueueAdded(IDeviceListUpdater& aUpdater, CpiDevice& aDevice)
{ // static
    CpiDeviceListUpdater::Queue(new UpdateAdded(aUpdater, aDevice));
}

void CpiDeviceListUpdater::QueueRemoved(IDeviceListUpdater& aUpdater, const Brx& aUdn)
{ // static
    CpiDeviceListUpdater::Queue(new UpdateRemoved(aUpdater, aUdn));
}

void CpiDeviceListUpdater::QueueRefreshed(IDeviceListUpdater& aUpdater)
{ // static
    CpiDeviceListUpdater::Queue(new UpdateRefresh(aUpdater));
}

void CpiDeviceListUpdater::Queue(UpdateBase* aUpdate)
{ // static
    CpiDeviceListUpdater& self = CpiStack::DeviceListUpdater();
    self.iLock.Wait();
    self.iList.push_back(aUpdate);
    self.iLock.Signal();
    self.Signal();
}

void CpiDeviceListUpdater::Run()
{
    for (;;) {
        Wait();
        iLock.Wait();
        UpdateBase* update = iList.front();
        iList.pop_front();
        iLock.Signal();
        update->Update();
        delete update;
    }
}


// CpiDeviceListUpdater::UpdateBase

CpiDeviceListUpdater::UpdateBase::~UpdateBase()
{
    iUpdater.RemoveRef();
}

CpiDeviceListUpdater::UpdateBase::UpdateBase(IDeviceListUpdater& aUpdater)
    : iUpdater(aUpdater)
{
    iUpdater.AddRef();
}


// CpiDeviceListUpdater::UpdateAdded

CpiDeviceListUpdater::UpdateAdded::UpdateAdded(IDeviceListUpdater& aUpdater, CpiDevice& aDevice)
    : CpiDeviceListUpdater::UpdateBase(aUpdater)
    , iDevice(aDevice)
{
    iDevice.AddRef();
}

CpiDeviceListUpdater::UpdateAdded::~UpdateAdded()
{
    iDevice.RemoveRef();
}

void CpiDeviceListUpdater::UpdateAdded::Update()
{
    iUpdater.NotifyAdded(iDevice);
}


// CpiDeviceListUpdater::UpdateRemoved

CpiDeviceListUpdater::UpdateRemoved::UpdateRemoved(IDeviceListUpdater& aUpdater, const Brx& aUdn)
    : CpiDeviceListUpdater::UpdateBase(aUpdater)
    , iUdn(aUdn)
{
}

void CpiDeviceListUpdater::UpdateRemoved::Update()
{
    iUpdater.NotifyRemoved(iUdn);
}


// CpiDeviceListUpdater::UpdateRefresh

CpiDeviceListUpdater::UpdateRefresh::UpdateRefresh(IDeviceListUpdater& aUpdater)
    : CpiDeviceListUpdater::UpdateBase(aUpdater)
{
}

void CpiDeviceListUpdater::UpdateRefresh::Update()
{
    iUpdater.NotifyRefreshed();
}
