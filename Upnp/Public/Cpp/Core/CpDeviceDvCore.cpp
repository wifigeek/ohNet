#include <Core/CpDeviceDv.h>
#include <CpiDeviceDv.h>
#include <DviDevice.h>

using namespace OpenHome;
using namespace OpenHome::Net;

CpDeviceDv* CpDeviceDv::New(DvDevice& aDevice)
{
    CpiDeviceDv* device = new CpiDeviceDv(aDevice.Device());
    CpDeviceDv* self = new CpDeviceDv(*device);
    self->Device().RemoveRef();
    return self;
}

CpDeviceDv::~CpDeviceDv()
{
}

CpDeviceDv::CpDeviceDv(CpiDeviceDv& aDevice)
    : CpDevice(aDevice.Device())
{
}
