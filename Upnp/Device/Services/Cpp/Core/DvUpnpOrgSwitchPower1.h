#ifndef HEADER_DVUPNPORGSWITCHPOWER1
#define HEADER_DVUPNPORGSWITCHPOWER1

#include <OhNetTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvProvider.h>

namespace OpenHome {
namespace Net {

class IDviInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Provider for the upnp.org:SwitchPower:1 UPnP service
 * @ingroup Providers
 */
class DvProviderUpnpOrgSwitchPower1 : public DvProvider
{
public:
    virtual ~DvProviderUpnpOrgSwitchPower1() {}
    /**
     * Set the value of the Status property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyStatus(TBool aValue);
    /**
     * Get a copy of the value of the Status property
     */
    void GetPropertyStatus(TBool& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderUpnpOrgSwitchPower1(DvDevice& aDevice);
    /**
     * Signal that the action SetTarget is supported.
     * The action's availability will be published in the device's service.xml.
     * SetTarget must be overridden if this is called.
     */
    void EnableActionSetTarget();
    /**
     * Signal that the action GetTarget is supported.
     * The action's availability will be published in the device's service.xml.
     * GetTarget must be overridden if this is called.
     */
    void EnableActionGetTarget();
    /**
     * Signal that the action GetStatus is supported.
     * The action's availability will be published in the device's service.xml.
     * GetStatus must be overridden if this is called.
     */
    void EnableActionGetStatus();
private:
    /**
     * SetTarget action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetTarget action for the owning device.
     * Must be implemented iff EnableActionSetTarget was called.
     */
    virtual void SetTarget(IInvocationResponse& aResponse, TUint aVersion, TBool anewTargetValue);
    /**
     * GetTarget action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetTarget action for the owning device.
     * Must be implemented iff EnableActionGetTarget was called.
     */
    virtual void GetTarget(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aRetTargetValue);
    /**
     * GetStatus action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetStatus action for the owning device.
     * Must be implemented iff EnableActionGetStatus was called.
     */
    virtual void GetStatus(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aResultStatus);
private:
    DvProviderUpnpOrgSwitchPower1();
    void DoSetTarget(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetTarget(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetStatus(IDviInvocation& aInvocation, TUint aVersion);
private:
    PropertyBool* iPropertyStatus;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVUPNPORGSWITCHPOWER1

