#ifndef HEADER_AVOPENHOMEORGTIME1
#define HEADER_AVOPENHOMEORGTIME1

#include <OhNetTypes.h>
#include <Buffer.h>
#include <Exception.h>
#include <Functor.h>
#include <FunctorAsync.h>
#include <CpProxy.h>

namespace OpenHome {
namespace Net {

class CpDevice;
class Action;
class PropertyBinary;
class PropertyBool;
class PropertyInt;
class PropertyString;
class PropertyUint;

/**
 * Proxy for av.openhome.org:Time:1
 * @ingroup Proxies
 */
class CpProxyAvOpenhomeOrgTime1 : public CpProxy
{
public:
    /**
     * Constructor.
     *
     * Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable
     * and reporting of their changes.
     *
     * @param[in]  aDevice   The device to use
     */
    CpProxyAvOpenhomeOrgTime1(CpDevice& aDevice);
    /**
     * Destructor.
     * If any asynchronous method is in progress, this will block until they complete.
     * [Note that any methods still in progress are likely to complete with an error.]
     * Clients who have called Subscribe() do not need to call Unsubscribe() before
     * calling delete.  An unsubscribe will be triggered automatically when required.
     */
    ~CpProxyAvOpenhomeOrgTime1();

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aTrackCount
     * @param[out] aDuration
     * @param[out] aSeconds
     */
    void SyncTime(TUint& aTrackCount, TUint& aDuration, TUint& aSeconds);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndTime().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginTime(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aTrackCount
     * @param[out] aDuration
     * @param[out] aSeconds
     */
    void EndTime(IAsync& aAsync, TUint& aTrackCount, TUint& aDuration, TUint& aSeconds);

    /**
     * Set a callback to be run when the TrackCount state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgTime1 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyTrackCountChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the Duration state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgTime1 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyDurationChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the Seconds state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgTime1 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertySecondsChanged(Functor& aFunctor);

    /**
     * Query the value of the TrackCount property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aTrackCount
     */
    void PropertyTrackCount(TUint& aTrackCount) const;
    /**
     * Query the value of the Duration property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aDuration
     */
    void PropertyDuration(TUint& aDuration) const;
    /**
     * Query the value of the Seconds property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aSeconds
     */
    void PropertySeconds(TUint& aSeconds) const;
private:
    void TrackCountPropertyChanged();
    void DurationPropertyChanged();
    void SecondsPropertyChanged();
private:
    Action* iActionTime;
    PropertyUint* iTrackCount;
    PropertyUint* iDuration;
    PropertyUint* iSeconds;
    Functor iTrackCountChanged;
    Functor iDurationChanged;
    Functor iSecondsChanged;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_AVOPENHOMEORGTIME1

