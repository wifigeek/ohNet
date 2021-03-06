#ifndef HEADER_UPNPC
#define HEADER_UPNPC

#include <OsTypes.h>
#include <C/Async.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef THandle OhNetHandleNetworkInterface;
typedef THandle OhNetHandleNetworkInterfaceList;
typedef THandle OhNetHandleInitParams;

/**
 * Callback which runs when a library component has a message to deliver
 * @ingroup Callbacks
 *
 * @param[in] aPtr   Client-specified data
 * @param[in] aMsg   Nul-terminated message
 */
typedef void (*OhNetCallbackMsg)(void* aPtr, const char* aMsg);
/**
 * Callback which runs to notify a listener of a change in a library component
 * @ingroup Callbacks
 *
 * @param[in] aPtr   Client-specified data
 */
typedef void (*OhNetCallback)(void* aPtr);
/**
 * Callback pointing to function which can be used to free memory allocated by a client
 * @ingroup Callbacks
 *
 * @param[in] aPtr   Client-allocated memory to be freed
 */
typedef void (*OhNetCallbackFreeExternal)(void* aPtr);

/**
 * @addtogroup Library
 * @ingroup Core
 * @{
 */

/**
 * Initialise the UPnP library.
 *
 * Must be called before any other library function.
 *
 * @param aInitParams  Initialisation options.  Ownership of these passes to the library.
 *
 * @return 0 if initialisation succeeded; non-zero otherwise
 */
DllExport int32_t OhNetLibraryInitialise(OhNetHandleInitParams aInitParams);

/**
 * Lightweight alternative to UpnpLibraryInitialise.
 *
 * Intended for unit tests which are useful to platform porting only.
 * No class APIs other than Close() can be called if this is used.
 *
 * @param aInitParams  Initialisation options.  Only ILogOutput will be used.
 *                     Ownership of these passes to the library.
 *
 * @return 0 if initialisation succeeded; non-zero otherwise
 */
DllExport int32_t OhNetLibraryInitialiseMinimal(OhNetHandleInitParams aInitParams);

/**
 * Start the library as a UPnP control point stack
 *
 * Must be called after OhNetLibraryInitialise but before any function from other headers
 */
DllExport void OhNetLibraryStartCp();

/**
 * Start the library as a UPnP device stack
 *
 * Must be called after OhNetLibraryInitialise but before any function from other headers
 */
DllExport void OhNetLibraryStartDv();

/**
 * Start the library as both UPnP control point and device stacks
 *
 * Must be called after OhNetLibraryInitialise but before any function from other headers
 */
DllExport void OhNetLibraryStartCombined();

/**
 * Close the UPnP library.
 *
 * Will not fail.  No more library functions should be called after this.
 */
DllExport void OhNetLibraryClose();

/* @} */
/**
 * @addtogroup InitParams
 * @ingroup Core
 * @{
 */

/**
 * Create the initialisation parameters which must be passed to the library's initialiser
 *
 * @return  Handle to initialisation params object.
 */
DllExport OhNetHandleInitParams OhNetInitParamsCreate();

/**
 * Destroy an object previously created by OhNetInitParamsCreate()
 *
 * @param[in] aParams          Initialisation params
 */
DllExport void OhNetInitParamsDestroy(OhNetHandleInitParams aParams);

/**
 * Set a callback to run for any logging output
 * Note that this can only be called before OhNetLibraryInitialise
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aCallback        Callback which will be run when the library has
 *                             data to be logged
 * @param[in] aPtr             Data which will be passed to aCallback
 */
DllExport void OhNetInitParamsSetLogOutput(OhNetHandleInitParams aParams, OhNetCallbackMsg aCallback, void* aPtr);

/**
 * Set a callback which will be run if the library encounters an error it
 * cannot recover from.
 *
 * Suggested action if this is called is to exit the process and restart the
 * library and its owning application. Note that the string passed to the callback
 * is an error message so would be useful to log.
 * Note that this can only be called before OhNetLibraryInitialise
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aCallback        Callback which will be run if a fatal error occurs
 * @param[in] aPtr             Data which will be passed to aCallback
 */
DllExport void OhNetInitParamsSetFatalErrorHandler(OhNetHandleInitParams aParams, OhNetCallbackMsg aCallback, void* aPtr);

/**
 * Set a callback which will run at the start of every async opertion
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aCallback        Callback which will be run at the start of every async opertion
 * @param[in] aPtr             Data which will be passed to aCallback
 */
DllExport void OhNetInitParamsSetAsyncBeginHandler(OhNetHandleInitParams aParams, OhNetCallbackAsync aCallback, void* aPtr);

/**
 * Set a callback which will run at the end of every async opertion
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aCallback        Callback which will be run at the end of every async opertion
 * @param[in] aPtr             Data which will be passed to aCallback
 */
DllExport void OhNetInitParamsSetAsyncEndHandler(OhNetHandleInitParams aParams, OhNetCallbackAsync aCallback, void* aPtr);

/**
 * Set a callback which will run if an async opertion fails
 * Note that The library supplies a default implementation which logs these errors.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aCallback        Callback which will be run if an async opertion fails
 * @param[in] aPtr             Data which will be passed to aCallback
 */
DllExport void OhNetInitParamsSetAsyncErrorHandler(OhNetHandleInitParams aParams, OhNetCallbackAsync aCallback, void* aPtr);

/**
 * Set which subnet to use on startup
 * The OS layer will select the most appropriate subnet if this is not called.
 * Note that this can only be called before OhNetLibraryInitialise
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aSubnet          The subnet to use on startup
 */
DllExport void OhNetInitParamsSetDefaultSubnet(OhNetHandleInitParams aParams, TIpAddress aSubnet);

/**
 * Set a listener for changes in the subnet being used
 *
 * This will run if the active subnet becomes unavailable or a seemingly more
 * appropriate subnet becomes available.
 * Note that this can only be called before OhNetLibraryInitialise
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aCallback        Callback which will be run if the active subnet changes
 * @param[in] aPtr             Data which will be passed to aCallback
 */
DllExport void OhNetInitParamsSetSubnetChangedListener(OhNetHandleInitParams aParams, OhNetCallback aCallback, void* aPtr);

/**
 * Set a custom timeout for TCP connections.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aTimeoutMs       Timeout in milliseconds.  Must be greater that zero
 */
DllExport void OhNetInitParamsSetTcpConnectTimeout(OhNetHandleInitParams aParams, uint32_t aTimeoutMs);

/**
 * Set a custom time that msearch responses should be spread out over.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aSecs            Time in seconds.  Must be between 1 and 5 (inclusive)
 */
DllExport void OhNetInitParamsSetMsearchTime(OhNetHandleInitParams aParams, uint32_t aSecs);

/**
 * Set a custom time-to-live value for msearches.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aTtl             Time to live
 */
DllExport void OhNetInitParamsSetMsearchTtl(OhNetHandleInitParams aParams, uint32_t aTtl);

/**
 * Set a custom number of threads which will be dedicated to eventing (handling
 * updates to subscribed state variables)
 *
 * A higher number of threads may allow faster processing  but will certainly
 * require more system resources.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aNumThreads      Number of threads.  Must be greater than zero.
 */
DllExport void OhNetInitParamsSetNumEventSessionThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads);

/**
 * Set the number of threads which should be dedicated to fetching device/service XML.
 *
 * A higher number of threads will allow faster population of device lists but
 * will also require more system resources.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aNumThreads      Number of threads.  Must be greater than zero.
 */
DllExport void OhNetInitParamsSetNumXmlFetcherThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads);

/**
 * Set the number of threads which should be dedicated to invoking actions on devices.
 *
 * A higher number of threads will allow faster population of device lists
 * but will also require more system resources.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aNumThreads      Number of threads.  Must be greater than zero.
 */
DllExport void OhNetInitParamsSetNumActionInvokerThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads);

/**
 * Set the number of invocations (actions) which should be pre-allocated.
 *
 * If more that this number are pending, the additional attempted invocations
 * will block until a pre-allocated slot becomes clear.
 * A higher number of invocations will decrease the likelihood and duration of
 * any UI-level delays but will also increase the peaks in RAM requirements.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aNumInvocations  Number of invocations.  Must be greater than zero.
 */
DllExport void OhNetInitParamsSetNumInvocations(OhNetHandleInitParams aParams, uint32_t aNumInvocations);

/**
 * Set the number of threads which should be dedicated to (un)subscribing
 * to state variables on a service + device.
 *
 * A higher number of threads may allow faster initialisation of some application
 * views but will also require more system resources.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aNumThreads      Number of threads.  Must be greater than zero.
 */
DllExport void OhNetInitParamsSetNumSubscriberThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads);

/**
 * It is possible for initial information on state variables to arrive before
 * a subscription is noted as complete.
 * Set the maximim time to wait before rejecting an event update from an unknown source.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aTimeoutMs       Timeout in milliseconds.  Must be greater than zero.
 */
DllExport void OhNetInitParamsSetPendingSubscriptionTimeout(OhNetHandleInitParams aParams, uint32_t aTimeoutMs);

/**
 * Set a callback which will be used to free memory that is allocated outside the library
 * This is intended for C# wrappers and can be ignored by most (all?) other clients
 */
DllExport void OhNetInitParamsSetFreeExternalCallback(OhNetHandleInitParams aParams, OhNetCallbackFreeExternal aCallback);

/**
 * Limit the library to using only the loopback network interface.
 * Useful for testing but not expected to be used in production code
 */
DllExport void OhNetInitParamsSetUseLoopbackNetworkInterface(OhNetHandleInitParams aParams);

/**
 * Set the maximum time between device announcements for the device stack
 */
DllExport void OhNetInitParamsSetDvMaxUpdateTime(OhNetHandleInitParams aParams, uint32_t aSecs);

/**
 * Set the number of threads which should be dedicated to processing
 * control/eventing/presentation requests.
 *
 * A higher number of threads may allow faster response to multiple clients
 * making concurrent requests but will also require more system resources.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aNumThreads      Number of threads.  Must be greater than zero.
 */
DllExport void OhNetInitParamsSetDvNumServerThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads);

/**
 * Set the number of threads which should be dedicated to publishing changes
 * to state variables on a service + device.
 *
 * A higher number of threads may allow faster publication of changes (enabling more
 * responsive client apps) views but will also require more system resources.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aNumThreads      Number of threads.  Must be greater than zero.
 */
DllExport void OhNetInitParamsSetDvNumPublisherThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads);

/**
 * Set the number of threads which will be dedicated to published changes to state
 * variables via WebSockets.
 *
 * One thread will be used per active (web browser) connection so a higher number of threads
 * will allow more concurrent clients but will also require more system resources.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aNumThreads      Number of threads.  Must be greater than zero.
 */
DllExport void OhNetInitParamsSetDvNumWebSocketThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads);

/**
 * Set the tcp port number web socket servers will run on.
 *
 * You should question your design if you need to use this.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aPort            Port number.  0 (the default value) implies an OS-assigned port.
 */
DllExport void OhNetInitParamsSetDvWebSocketPort(OhNetHandleInitParams aParams, uint32_t aPort);

/**
 * Enable use of Bonjour.
 * All DvDevice instances with a resource manager will be published using Bonjour.
 * If a device sets the "Upnp.MdnsHostName" attribute, its presentation will be available via http://[hostname].local.
 * Behaviour when more than one DvDevice sets the "MdnsHostName" attribute is undefined.
 * Note that enabling Bonjour will cause the device stack to run a http server on port 80, requiring root privileges on linux.
 *
 * @param[in] aParams          Initialisation params
 */
DllExport void OhNetInitParamsSetDvEnableBonjour(OhNetHandleInitParams aParams);

/**
 * Query the tcp connection timeout
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  timeout (in milliseconds)
 */
DllExport uint32_t OhNetInitParamsTcpConnectTimeoutMs(OhNetHandleInitParams aParams);

/**
 * Query the time msearch responses are requested to be spread over
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  time (in seconds)
 */
DllExport uint32_t OhNetInitParamsMsearchTimeSecs(OhNetHandleInitParams aParams);

/**
 * Query the time to live value for multicast queries
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  ttl value
 */
DllExport uint32_t OhNetInitParamsMsearchTtl(OhNetHandleInitParams aParams);

/**
 * Query the number of event session threads
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  number of threads
 */
DllExport uint32_t OhNetInitParamsNumEventSessionThreads(OhNetHandleInitParams aParams);

/**
 * Query the number of XML fetcher threads
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  number of threads
 */
DllExport uint32_t OhNetInitParamsNumXmlFetcherThreads(OhNetHandleInitParams aParams);

/**
 * Query the number of invocation threads
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  number of threads
 */
DllExport uint32_t OhNetInitParamsNumActionInvokerThreads(OhNetHandleInitParams aParams);

/**
 * Query the number of pre-allocated invocations
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  number of invocations
 */
DllExport uint32_t OhNetInitParamsNumInvocations(OhNetHandleInitParams aParams);

/**
 * Query the number of subscriber threads
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  number of threads
 */
DllExport uint32_t OhNetInitParamsNumSubscriberThreads(OhNetHandleInitParams aParams);

/**
 * Query the maximum delay allowed between initial values of state variables
 * being delivered and a subscription identifier being provided
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  maximum delay (in milliseconds)
 */
DllExport uint32_t OhNetInitParamsPendingSubscriptionTimeoutMs(OhNetHandleInitParams aParams);

/**
 * Query the maximum delay between device announcements (for the device stack only)
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  maximum delay (in seconds)
 */
DllExport uint32_t OhNetInitParamsDvMaxUpdateTimeSecs(OhNetHandleInitParams aParams);

/**
 * Query the number of device stack server threads
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  number of threads
 */
DllExport uint32_t OhNetInitParamsDvNumServerThreads(OhNetHandleInitParams aParams);

/**
 * Query the number of device stack publisher threads
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  number of threads
 */
DllExport uint32_t OhNetInitParamsDvNumPublisherThreads(OhNetHandleInitParams aParams);

/**
 * Query the number of device stack WebSocket threads
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  number of threads
 */
DllExport uint32_t OhNetInitParamsDvNumWebSocketThreads(OhNetHandleInitParams aParams);

/**
 * Query the port the WebSocket server will run on.
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  port number
 */
DllExport uint32_t OhNetInitParamsDvWebSocketPort(OhNetHandleInitParams aParams);

/**
 * Query whether Bonjour is enabled
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  1 if Bonjour is enabled; 0 otherwise
 */
DllExport uint32_t OhNetInitParamsDvIsBonjourEnabled(OhNetHandleInitParams aParams);

/* @} */

/**
 * @addtogroup NetworkInterface
 * @ingroup Core
 * @{
 */

/**
 * Query the address of a network interface
 *
 * @param[in] aNif             Network interface handle
 *
 * @return  IpV4 address as network order uint32
 */
DllExport TIpAddress OhNetNetworkInterfaceAddress(OhNetHandleNetworkInterface aNif);

/**
 * Query the subnet of a network interface is available on
 *
 * @param[in] aNif             Network interface handle
 *
 * @return  IpV4 address as network order uint32
 */
DllExport TIpAddress OhNetNetworkInterfaceSubnet(OhNetHandleNetworkInterface aNif);

/**
 * Query the name of a network interface
 *
 * @param[in] aNif             Network interface handle
 *
 * @return  IpV4 address as network order uint32
 */
DllExport const char* OhNetNetworkInterfaceName(OhNetHandleNetworkInterface aNif);

/**
 * Create a list of all available subnets
 *
 * @return  Handle to list of subnets.  Ownership transfers to caller.
 */
DllExport OhNetHandleNetworkInterfaceList OhNetSubnetListCreate();

/**
 * Query the number of elements in a subnet list
 *
 * @param[in] aList            Handle returned by OhNetSubnetListCreate()
 *
 * @return  number of elements (subnets) in the list
 */
DllExport uint32_t OhNetSubnetListSize(OhNetHandleNetworkInterfaceList aList);

/**
 * Get a handle to the subnet at a specified position in a subnet list.
 *
 * @param[in] aList            Handle returned by OhNetSubnetListCreate()
 * @param[in] aIndex           Index into the list to return the subnet from
 *
 * @return  subnet handle
 */
DllExport OhNetHandleNetworkInterface OhNetSubnetAt(OhNetHandleNetworkInterfaceList aList, uint32_t aIndex);

/**
 * Destroy a subnet list
 *
 * @param[in] aList            Handle returned by OhNetSubnetListCreate()
 */
DllExport void OhNetSubnetListDestroy(OhNetHandleNetworkInterfaceList aList);

/**
 * Set which subnet the library should use.
 *
 * This override any value set via OhNetInitParamsSetDefaultSubnet().
 * Device lists and subscriptions will be automatically updated.
 * No other subnet will be selected if aSubnet is not available
 *
 * @param aSubnet              The subnet to use
 */
DllExport void OhNetSetCurrentSubnet(OhNetHandleNetworkInterface aSubnet);

/**
 * Clear any subnet previously specified using OhNetSetCurrentSubnet() or
 * OhNetInitParamsSetDefaultSubnet().  OS-specified defaults will be used instead.
 *
 * Device lists and subscriptions will be automatically updated if necessary.
 */
DllExport void OhNetSetDefaultSubnet();

/* @} */

/**
 * @addtogroup Memory
 * @ingroup Core
 * @{
 */

/**
 * Free memory returned by the library.
 *
 * Use of this function is optional.  Calling free() directly is acceptable.
 *
 * @param[in] aPtr             Pointer to be freed
 */
DllExport void OhNetFree(void* aPtr);

/**
 * Free memory which was allocated by the client
 *
 * @param[in] aPtr             Memory to be freed
 */
DllExport void OhNetFreeExternal(void* aPtr);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_UPNPC
