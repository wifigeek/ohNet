/**
 * Provider for the upnp.org:SwitchPower:1 UPnP service
 */
#ifndef HEADER_DVUPNPORGSWITCHPOWER1_C
#define HEADER_DVUPNPORGSWITCHPOWER1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderUpnpOrgSwitchPower1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the SetTarget action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgSwitchPower1EnableActionSetTarget
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  anewTargetValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackSwitchPower1SetTarget)(void* aPtr, uint32_t aVersion, uint32_t anewTargetValue);
/**
 * Callback which runs when the GetTarget action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgSwitchPower1EnableActionGetTarget
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aRetTargetValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackSwitchPower1GetTarget)(void* aPtr, uint32_t aVersion, uint32_t* aRetTargetValue);
/**
 * Callback which runs when the GetStatus action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgSwitchPower1EnableActionGetStatus
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aResultStatus
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackSwitchPower1GetStatus)(void* aPtr, uint32_t aVersion, uint32_t* aResultStatus);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderUpnpOrgSwitchPower1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgSwitchPower1Create
 */
DllExport void DvProviderUpnpOrgSwitchPower1Destroy(THandle aProvider);

/**
 * Register a callback for the action SetTarget
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgSwitchPower1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgSwitchPower1EnableActionSetTarget(THandle aProvider, CallbackSwitchPower1SetTarget aCallback, void* aPtr);
/**
 * Register a callback for the action GetTarget
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgSwitchPower1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgSwitchPower1EnableActionGetTarget(THandle aProvider, CallbackSwitchPower1GetTarget aCallback, void* aPtr);
/**
 * Register a callback for the action GetStatus
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgSwitchPower1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgSwitchPower1EnableActionGetStatus(THandle aProvider, CallbackSwitchPower1GetStatus aCallback, void* aPtr);

/**
 * Set the value of the Status property
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgSwitchPower1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderUpnpOrgSwitchPower1SetPropertyStatus(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Status property
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgSwitchPower1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderUpnpOrgSwitchPower1GetPropertyStatus(THandle aProvider, uint32_t* aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGSWITCHPOWER1_C

