/**
 * Proxy for openhome.org:TestDimmableLight:1
 */
#ifndef HEADER_OPENHOMEORGTESTDIMMABLELIGHT1_C
#define HEADER_OPENHOMEORGTESTDIMMABLELIGHT1_C

#include <OsTypes.h>
#include <C/Async.h>
#include <C/OhNet.h>
#include <C/CpDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup CpProxyOpenhomeOrgTestDimmableLight1
 * @ingroup Proxies
 * @{
 */

/**
 * Constructor.
 * Creates an instance of CpProxyOpenhomeOrgTestDimmableLight1 without support for eventing.
 * Use CpProxyC[Un]Subscribe() to enable/disable querying of state variable and
 * reporting of their changes.
 *
 * @param[in]  aDevice   The device to use
 *
 * @return  Handle which should be used with all other functions in this header
 */
DllExport THandle CpProxyOpenhomeOrgTestDimmableLight1Create(CpDeviceC aDevice);
/**
 * Destructor.
 * If any asynchronous method is in progress, this will block until they complete.
 * [Note that any methods still in progress are likely to complete with an error.]
 * Clients who have called CpProxyCSubscribe() do not need to call CpProxyCSubscribe()
 * before calling delete.  An unsubscribe will be triggered automatically when required.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestDimmableLight1Create
 */
DllExport void CpProxyOpenhomeOrgTestDimmableLight1Destroy(THandle aHandle);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestDimmableLight1Create
 * @param[out] aLevel
 */
DllExport void CpProxyOpenhomeOrgTestDimmableLight1SyncGetLevel(THandle aHandle, uint32_t* aLevel);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestDimmableLight1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyOpenhomeOrgTestDimmableLight1BeginGetLevel(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestDimmableLight1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aLevel
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyOpenhomeOrgTestDimmableLight1EndGetLevel(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aLevel);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestDimmableLight1Create
 * @param[in]  aLevel
 */
DllExport void CpProxyOpenhomeOrgTestDimmableLight1SyncSetLevel(THandle aHandle, uint32_t aLevel);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestDimmableLight1Create
 * @param[in]  aLevel
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyOpenhomeOrgTestDimmableLight1BeginSetLevel(THandle aHandle, uint32_t aLevel, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestDimmableLight1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyOpenhomeOrgTestDimmableLight1EndSetLevel(THandle aHandle, OhNetHandleAsync aAsync);
/**
 * Set a callback to be run when the A_ARG_Level state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyOpenhomeOrgTestDimmableLight1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestDimmableLight1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyOpenhomeOrgTestDimmableLight1SetPropertyA_ARG_LevelChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr);

/**
 * Query the value of the A_ARG_Level property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestDimmableLight1Create
 * @param[out] aA_ARG_Level
 */
DllExport void CpProxyOpenhomeOrgTestDimmableLight1PropertyA_ARG_Level(THandle aHandle, uint32_t* aA_ARG_Level);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_OPENHOMEORGTESTDIMMABLELIGHT1_C

