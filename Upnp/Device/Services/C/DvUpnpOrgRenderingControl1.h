/**
 * Provider for the upnp.org:RenderingControl:1 UPnP service
 */
#ifndef HEADER_DVUPNPORGRENDERINGCONTROL1_C
#define HEADER_DVUPNPORGRENDERINGCONTROL1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderUpnpOrgRenderingControl1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the ListPresets action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionListPresets
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[out] aCurrentPresetNameList
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1ListPresets)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, char** aCurrentPresetNameList);
/**
 * Callback which runs when the SelectPreset action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionSelectPreset
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[in]  aPresetName
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1SelectPreset)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aPresetName);
/**
 * Callback which runs when the GetBrightness action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionGetBrightness
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[out] aCurrentBrightness
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1GetBrightness)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentBrightness);
/**
 * Callback which runs when the SetBrightness action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionSetBrightness
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[in]  aDesiredBrightness
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1SetBrightness)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredBrightness);
/**
 * Callback which runs when the GetContrast action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionGetContrast
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[out] aCurrentContrast
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1GetContrast)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentContrast);
/**
 * Callback which runs when the SetContrast action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionSetContrast
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[in]  aDesiredContrast
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1SetContrast)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredContrast);
/**
 * Callback which runs when the GetSharpness action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionGetSharpness
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[out] aCurrentSharpness
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1GetSharpness)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentSharpness);
/**
 * Callback which runs when the SetSharpness action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionSetSharpness
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[in]  aDesiredSharpness
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1SetSharpness)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredSharpness);
/**
 * Callback which runs when the GetRedVideoGain action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionGetRedVideoGain
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[out] aCurrentRedVideoGain
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1GetRedVideoGain)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentRedVideoGain);
/**
 * Callback which runs when the SetRedVideoGain action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionSetRedVideoGain
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[in]  aDesiredRedVideoGain
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1SetRedVideoGain)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredRedVideoGain);
/**
 * Callback which runs when the GetGreenVideoGain action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionGetGreenVideoGain
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[out] aCurrentGreenVideoGain
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1GetGreenVideoGain)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentGreenVideoGain);
/**
 * Callback which runs when the SetGreenVideoGain action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionSetGreenVideoGain
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[in]  aDesiredGreenVideoGain
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1SetGreenVideoGain)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredGreenVideoGain);
/**
 * Callback which runs when the GetBlueVideoGain action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionGetBlueVideoGain
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[out] aCurrentBlueVideoGain
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1GetBlueVideoGain)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentBlueVideoGain);
/**
 * Callback which runs when the SetBlueVideoGain action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionSetBlueVideoGain
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[in]  aDesiredBlueVideoGain
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1SetBlueVideoGain)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredBlueVideoGain);
/**
 * Callback which runs when the GetRedVideoBlackLevel action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionGetRedVideoBlackLevel
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[out] aCurrentRedVideoBlackLevel
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1GetRedVideoBlackLevel)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentRedVideoBlackLevel);
/**
 * Callback which runs when the SetRedVideoBlackLevel action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionSetRedVideoBlackLevel
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[in]  aDesiredRedVideoBlackLevel
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1SetRedVideoBlackLevel)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredRedVideoBlackLevel);
/**
 * Callback which runs when the GetGreenVideoBlackLevel action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionGetGreenVideoBlackLevel
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[out] aCurrentGreenVideoBlackLevel
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1GetGreenVideoBlackLevel)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentGreenVideoBlackLevel);
/**
 * Callback which runs when the SetGreenVideoBlackLevel action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionSetGreenVideoBlackLevel
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[in]  aDesiredGreenVideoBlackLevel
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1SetGreenVideoBlackLevel)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredGreenVideoBlackLevel);
/**
 * Callback which runs when the GetBlueVideoBlackLevel action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionGetBlueVideoBlackLevel
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[out] aCurrentBlueVideoBlackLevel
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1GetBlueVideoBlackLevel)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentBlueVideoBlackLevel);
/**
 * Callback which runs when the SetBlueVideoBlackLevel action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionSetBlueVideoBlackLevel
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[in]  aDesiredBlueVideoBlackLevel
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1SetBlueVideoBlackLevel)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredBlueVideoBlackLevel);
/**
 * Callback which runs when the GetColorTemperature action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionGetColorTemperature
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[out] aCurrentColorTemperature
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1GetColorTemperature)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentColorTemperature);
/**
 * Callback which runs when the SetColorTemperature action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionSetColorTemperature
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[in]  aDesiredColorTemperature
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1SetColorTemperature)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredColorTemperature);
/**
 * Callback which runs when the GetHorizontalKeystone action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionGetHorizontalKeystone
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[out] aCurrentHorizontalKeystone
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1GetHorizontalKeystone)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, int32_t* aCurrentHorizontalKeystone);
/**
 * Callback which runs when the SetHorizontalKeystone action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionSetHorizontalKeystone
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[in]  aDesiredHorizontalKeystone
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1SetHorizontalKeystone)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, int32_t aDesiredHorizontalKeystone);
/**
 * Callback which runs when the GetVerticalKeystone action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionGetVerticalKeystone
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[out] aCurrentVerticalKeystone
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1GetVerticalKeystone)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, int32_t* aCurrentVerticalKeystone);
/**
 * Callback which runs when the SetVerticalKeystone action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionSetVerticalKeystone
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[in]  aDesiredVerticalKeystone
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1SetVerticalKeystone)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, int32_t aDesiredVerticalKeystone);
/**
 * Callback which runs when the GetMute action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionGetMute
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[out] aCurrentMute
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1GetMute)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentMute);
/**
 * Callback which runs when the SetMute action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionSetMute
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[in]  aDesiredMute
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1SetMute)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredMute);
/**
 * Callback which runs when the GetVolume action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionGetVolume
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[out] aCurrentVolume
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1GetVolume)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentVolume);
/**
 * Callback which runs when the SetVolume action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionSetVolume
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[in]  aDesiredVolume
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1SetVolume)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredVolume);
/**
 * Callback which runs when the GetVolumeDB action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionGetVolumeDB
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[out] aCurrentVolume
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1GetVolumeDB)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, int32_t* aCurrentVolume);
/**
 * Callback which runs when the SetVolumeDB action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionSetVolumeDB
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[in]  aDesiredVolume
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1SetVolumeDB)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, int32_t aDesiredVolume);
/**
 * Callback which runs when the GetVolumeDBRange action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionGetVolumeDBRange
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[out] aMinValue
 * @param[out] aMaxValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1GetVolumeDBRange)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, int32_t* aMinValue, int32_t* aMaxValue);
/**
 * Callback which runs when the GetLoudness action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionGetLoudness
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[out] aCurrentLoudness
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1GetLoudness)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentLoudness);
/**
 * Callback which runs when the SetLoudness action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgRenderingControl1EnableActionSetLoudness
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[in]  aDesiredLoudness
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackRenderingControl1SetLoudness)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredLoudness);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderUpnpOrgRenderingControl1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 */
DllExport void DvProviderUpnpOrgRenderingControl1Destroy(THandle aProvider);

/**
 * Register a callback for the action ListPresets
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionListPresets(THandle aProvider, CallbackRenderingControl1ListPresets aCallback, void* aPtr);
/**
 * Register a callback for the action SelectPreset
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSelectPreset(THandle aProvider, CallbackRenderingControl1SelectPreset aCallback, void* aPtr);
/**
 * Register a callback for the action GetBrightness
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetBrightness(THandle aProvider, CallbackRenderingControl1GetBrightness aCallback, void* aPtr);
/**
 * Register a callback for the action SetBrightness
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetBrightness(THandle aProvider, CallbackRenderingControl1SetBrightness aCallback, void* aPtr);
/**
 * Register a callback for the action GetContrast
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetContrast(THandle aProvider, CallbackRenderingControl1GetContrast aCallback, void* aPtr);
/**
 * Register a callback for the action SetContrast
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetContrast(THandle aProvider, CallbackRenderingControl1SetContrast aCallback, void* aPtr);
/**
 * Register a callback for the action GetSharpness
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetSharpness(THandle aProvider, CallbackRenderingControl1GetSharpness aCallback, void* aPtr);
/**
 * Register a callback for the action SetSharpness
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetSharpness(THandle aProvider, CallbackRenderingControl1SetSharpness aCallback, void* aPtr);
/**
 * Register a callback for the action GetRedVideoGain
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetRedVideoGain(THandle aProvider, CallbackRenderingControl1GetRedVideoGain aCallback, void* aPtr);
/**
 * Register a callback for the action SetRedVideoGain
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetRedVideoGain(THandle aProvider, CallbackRenderingControl1SetRedVideoGain aCallback, void* aPtr);
/**
 * Register a callback for the action GetGreenVideoGain
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetGreenVideoGain(THandle aProvider, CallbackRenderingControl1GetGreenVideoGain aCallback, void* aPtr);
/**
 * Register a callback for the action SetGreenVideoGain
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetGreenVideoGain(THandle aProvider, CallbackRenderingControl1SetGreenVideoGain aCallback, void* aPtr);
/**
 * Register a callback for the action GetBlueVideoGain
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetBlueVideoGain(THandle aProvider, CallbackRenderingControl1GetBlueVideoGain aCallback, void* aPtr);
/**
 * Register a callback for the action SetBlueVideoGain
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetBlueVideoGain(THandle aProvider, CallbackRenderingControl1SetBlueVideoGain aCallback, void* aPtr);
/**
 * Register a callback for the action GetRedVideoBlackLevel
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetRedVideoBlackLevel(THandle aProvider, CallbackRenderingControl1GetRedVideoBlackLevel aCallback, void* aPtr);
/**
 * Register a callback for the action SetRedVideoBlackLevel
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetRedVideoBlackLevel(THandle aProvider, CallbackRenderingControl1SetRedVideoBlackLevel aCallback, void* aPtr);
/**
 * Register a callback for the action GetGreenVideoBlackLevel
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetGreenVideoBlackLevel(THandle aProvider, CallbackRenderingControl1GetGreenVideoBlackLevel aCallback, void* aPtr);
/**
 * Register a callback for the action SetGreenVideoBlackLevel
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetGreenVideoBlackLevel(THandle aProvider, CallbackRenderingControl1SetGreenVideoBlackLevel aCallback, void* aPtr);
/**
 * Register a callback for the action GetBlueVideoBlackLevel
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetBlueVideoBlackLevel(THandle aProvider, CallbackRenderingControl1GetBlueVideoBlackLevel aCallback, void* aPtr);
/**
 * Register a callback for the action SetBlueVideoBlackLevel
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetBlueVideoBlackLevel(THandle aProvider, CallbackRenderingControl1SetBlueVideoBlackLevel aCallback, void* aPtr);
/**
 * Register a callback for the action GetColorTemperature
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetColorTemperature(THandle aProvider, CallbackRenderingControl1GetColorTemperature aCallback, void* aPtr);
/**
 * Register a callback for the action SetColorTemperature
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetColorTemperature(THandle aProvider, CallbackRenderingControl1SetColorTemperature aCallback, void* aPtr);
/**
 * Register a callback for the action GetHorizontalKeystone
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetHorizontalKeystone(THandle aProvider, CallbackRenderingControl1GetHorizontalKeystone aCallback, void* aPtr);
/**
 * Register a callback for the action SetHorizontalKeystone
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetHorizontalKeystone(THandle aProvider, CallbackRenderingControl1SetHorizontalKeystone aCallback, void* aPtr);
/**
 * Register a callback for the action GetVerticalKeystone
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetVerticalKeystone(THandle aProvider, CallbackRenderingControl1GetVerticalKeystone aCallback, void* aPtr);
/**
 * Register a callback for the action SetVerticalKeystone
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetVerticalKeystone(THandle aProvider, CallbackRenderingControl1SetVerticalKeystone aCallback, void* aPtr);
/**
 * Register a callback for the action GetMute
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetMute(THandle aProvider, CallbackRenderingControl1GetMute aCallback, void* aPtr);
/**
 * Register a callback for the action SetMute
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetMute(THandle aProvider, CallbackRenderingControl1SetMute aCallback, void* aPtr);
/**
 * Register a callback for the action GetVolume
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetVolume(THandle aProvider, CallbackRenderingControl1GetVolume aCallback, void* aPtr);
/**
 * Register a callback for the action SetVolume
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetVolume(THandle aProvider, CallbackRenderingControl1SetVolume aCallback, void* aPtr);
/**
 * Register a callback for the action GetVolumeDB
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetVolumeDB(THandle aProvider, CallbackRenderingControl1GetVolumeDB aCallback, void* aPtr);
/**
 * Register a callback for the action SetVolumeDB
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetVolumeDB(THandle aProvider, CallbackRenderingControl1SetVolumeDB aCallback, void* aPtr);
/**
 * Register a callback for the action GetVolumeDBRange
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetVolumeDBRange(THandle aProvider, CallbackRenderingControl1GetVolumeDBRange aCallback, void* aPtr);
/**
 * Register a callback for the action GetLoudness
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetLoudness(THandle aProvider, CallbackRenderingControl1GetLoudness aCallback, void* aPtr);
/**
 * Register a callback for the action SetLoudness
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetLoudness(THandle aProvider, CallbackRenderingControl1SetLoudness aCallback, void* aPtr);

/**
 * Set the value of the LastChange property
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderUpnpOrgRenderingControl1SetPropertyLastChange(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the LastChange property
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgRenderingControl1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderUpnpOrgRenderingControl1GetPropertyLastChange(THandle aProvider, char** aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGRENDERINGCONTROL1_C

