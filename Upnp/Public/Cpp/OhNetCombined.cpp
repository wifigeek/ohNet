#include <OhNet.h>

using namespace OpenHome;
using namespace OpenHome::Net;

void UpnpLibrary::StartCombined()
{
    UpnpLibrary::StartCp();
    UpnpLibrary::StartDv();
}
