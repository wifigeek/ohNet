#include "DvUpnpOrgRenderingControl1.h"
#include <OhNetTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace OpenHome;
using namespace OpenHome::Net;

bool DvProviderUpnpOrgRenderingControl1Cpp::SetPropertyLastChange(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyLastChange, buf);
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetPropertyLastChange(std::string& aValue)
{
    const Brx& val = iPropertyLastChange->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvProviderUpnpOrgRenderingControl1Cpp::DvProviderUpnpOrgRenderingControl1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "upnp.org", "RenderingControl", 1)
{
    
    iPropertyLastChange = new PropertyString(new ParameterString("LastChange"));
    iService->AddProperty(iPropertyLastChange); // passes ownership
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionListPresets()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ListPresets");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterString("CurrentPresetNameList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoListPresets);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSelectPreset()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SelectPreset");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"FactoryDefaults";
    action->AddInputParameter(new ParameterString("PresetName", allowedValues, 1));
    delete[] allowedValues;
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSelectPreset);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetBrightness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBrightness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBrightness", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetBrightness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetBrightness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBrightness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBrightness", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetBrightness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetContrast()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetContrast");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentContrast", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetContrast);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetContrast()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetContrast");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredContrast", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetContrast);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetSharpness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSharpness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentSharpness", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetSharpness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetSharpness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetSharpness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredSharpness", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetSharpness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetRedVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRedVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentRedVideoGain"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetRedVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetRedVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetRedVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredRedVideoGain"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetRedVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetGreenVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetGreenVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentGreenVideoGain", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetGreenVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetGreenVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetGreenVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredGreenVideoGain", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetGreenVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetBlueVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBlueVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBlueVideoGain", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetBlueVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetBlueVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBlueVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBlueVideoGain", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetBlueVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetRedVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRedVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentRedVideoBlackLevel", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetRedVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetRedVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetRedVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredRedVideoBlackLevel", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetRedVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetGreenVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetGreenVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentGreenVideoBlackLevel", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetGreenVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetGreenVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetGreenVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredGreenVideoBlackLevel", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetGreenVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetBlueVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBlueVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBlueVideoBlackLevel", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetBlueVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetBlueVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBlueVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBlueVideoBlackLevel", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetBlueVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetColorTemperature()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetColorTemperature");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentColorTemperature", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetColorTemperature);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetColorTemperature()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetColorTemperature");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredColorTemperature", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetColorTemperature);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetHorizontalKeystone()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetHorizontalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterInt("CurrentHorizontalKeystone"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetHorizontalKeystone);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetHorizontalKeystone()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetHorizontalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterInt("DesiredHorizontalKeystone"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetHorizontalKeystone);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetVerticalKeystone()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetVerticalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterInt("CurrentVerticalKeystone"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetVerticalKeystone);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetVerticalKeystone()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetVerticalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterInt("DesiredVerticalKeystone"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetVerticalKeystone);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetMute()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetMute");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    action->AddInputParameter(new ParameterString("Channel", allowedValues, 1));
    delete[] allowedValues;
    action->AddOutputParameter(new ParameterBool("CurrentMute"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetMute);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetMute()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetMute");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    action->AddInputParameter(new ParameterString("Channel", allowedValues, 1));
    delete[] allowedValues;
    action->AddInputParameter(new ParameterBool("DesiredMute"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetMute);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetVolume()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetVolume");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    action->AddInputParameter(new ParameterString("Channel", allowedValues, 1));
    delete[] allowedValues;
    action->AddOutputParameter(new ParameterUint("CurrentVolume", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetVolume);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetVolume()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetVolume");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    action->AddInputParameter(new ParameterString("Channel", allowedValues, 1));
    delete[] allowedValues;
    action->AddInputParameter(new ParameterUint("DesiredVolume", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetVolume);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetVolumeDB()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetVolumeDB");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    action->AddInputParameter(new ParameterString("Channel", allowedValues, 1));
    delete[] allowedValues;
    action->AddOutputParameter(new ParameterInt("CurrentVolume"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetVolumeDB);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetVolumeDB()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetVolumeDB");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    action->AddInputParameter(new ParameterString("Channel", allowedValues, 1));
    delete[] allowedValues;
    action->AddInputParameter(new ParameterInt("DesiredVolume"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetVolumeDB);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetVolumeDBRange()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetVolumeDBRange");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    action->AddInputParameter(new ParameterString("Channel", allowedValues, 1));
    delete[] allowedValues;
    action->AddOutputParameter(new ParameterInt("MinValue"));
    action->AddOutputParameter(new ParameterInt("MaxValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetVolumeDBRange);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetLoudness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetLoudness");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    action->AddInputParameter(new ParameterString("Channel", allowedValues, 1));
    delete[] allowedValues;
    action->AddOutputParameter(new ParameterBool("CurrentLoudness"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetLoudness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetLoudness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetLoudness");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    action->AddInputParameter(new ParameterString("Channel", allowedValues, 1));
    delete[] allowedValues;
    action->AddInputParameter(new ParameterBool("DesiredLoudness"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetLoudness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoListPresets(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    std::string respCurrentPresetNameList;
    ListPresets(aVersion, InstanceID, respCurrentPresetNameList);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterCurrentPresetNameList(aInvocation, "CurrentPresetNameList");
    Brn buf_CurrentPresetNameList((const TByte*)respCurrentPresetNameList.c_str(), (TUint)respCurrentPresetNameList.length());
    respWriterCurrentPresetNameList.Write(buf_CurrentPresetNameList);
    aInvocation.InvocationWriteStringEnd("CurrentPresetNameList");
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoSelectPreset(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_PresetName;
    aInvocation.InvocationReadString("PresetName", buf_PresetName);
    std::string PresetName((const char*)buf_PresetName.Ptr(), buf_PresetName.Bytes());
    aInvocation.InvocationReadEnd();
    SelectPreset(aVersion, InstanceID, PresetName);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetBrightness(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentBrightness;
    GetBrightness(aVersion, InstanceID, respCurrentBrightness);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterCurrentBrightness(aInvocation, "CurrentBrightness");
    respWriterCurrentBrightness.Write(respCurrentBrightness);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetBrightness(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredBrightness = aInvocation.InvocationReadUint("DesiredBrightness");
    aInvocation.InvocationReadEnd();
    SetBrightness(aVersion, InstanceID, DesiredBrightness);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetContrast(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentContrast;
    GetContrast(aVersion, InstanceID, respCurrentContrast);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterCurrentContrast(aInvocation, "CurrentContrast");
    respWriterCurrentContrast.Write(respCurrentContrast);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetContrast(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredContrast = aInvocation.InvocationReadUint("DesiredContrast");
    aInvocation.InvocationReadEnd();
    SetContrast(aVersion, InstanceID, DesiredContrast);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetSharpness(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentSharpness;
    GetSharpness(aVersion, InstanceID, respCurrentSharpness);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterCurrentSharpness(aInvocation, "CurrentSharpness");
    respWriterCurrentSharpness.Write(respCurrentSharpness);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetSharpness(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredSharpness = aInvocation.InvocationReadUint("DesiredSharpness");
    aInvocation.InvocationReadEnd();
    SetSharpness(aVersion, InstanceID, DesiredSharpness);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetRedVideoGain(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentRedVideoGain;
    GetRedVideoGain(aVersion, InstanceID, respCurrentRedVideoGain);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterCurrentRedVideoGain(aInvocation, "CurrentRedVideoGain");
    respWriterCurrentRedVideoGain.Write(respCurrentRedVideoGain);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetRedVideoGain(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredRedVideoGain = aInvocation.InvocationReadUint("DesiredRedVideoGain");
    aInvocation.InvocationReadEnd();
    SetRedVideoGain(aVersion, InstanceID, DesiredRedVideoGain);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetGreenVideoGain(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentGreenVideoGain;
    GetGreenVideoGain(aVersion, InstanceID, respCurrentGreenVideoGain);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterCurrentGreenVideoGain(aInvocation, "CurrentGreenVideoGain");
    respWriterCurrentGreenVideoGain.Write(respCurrentGreenVideoGain);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetGreenVideoGain(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredGreenVideoGain = aInvocation.InvocationReadUint("DesiredGreenVideoGain");
    aInvocation.InvocationReadEnd();
    SetGreenVideoGain(aVersion, InstanceID, DesiredGreenVideoGain);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetBlueVideoGain(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentBlueVideoGain;
    GetBlueVideoGain(aVersion, InstanceID, respCurrentBlueVideoGain);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterCurrentBlueVideoGain(aInvocation, "CurrentBlueVideoGain");
    respWriterCurrentBlueVideoGain.Write(respCurrentBlueVideoGain);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetBlueVideoGain(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredBlueVideoGain = aInvocation.InvocationReadUint("DesiredBlueVideoGain");
    aInvocation.InvocationReadEnd();
    SetBlueVideoGain(aVersion, InstanceID, DesiredBlueVideoGain);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetRedVideoBlackLevel(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentRedVideoBlackLevel;
    GetRedVideoBlackLevel(aVersion, InstanceID, respCurrentRedVideoBlackLevel);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterCurrentRedVideoBlackLevel(aInvocation, "CurrentRedVideoBlackLevel");
    respWriterCurrentRedVideoBlackLevel.Write(respCurrentRedVideoBlackLevel);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetRedVideoBlackLevel(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredRedVideoBlackLevel = aInvocation.InvocationReadUint("DesiredRedVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    SetRedVideoBlackLevel(aVersion, InstanceID, DesiredRedVideoBlackLevel);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetGreenVideoBlackLevel(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentGreenVideoBlackLevel;
    GetGreenVideoBlackLevel(aVersion, InstanceID, respCurrentGreenVideoBlackLevel);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterCurrentGreenVideoBlackLevel(aInvocation, "CurrentGreenVideoBlackLevel");
    respWriterCurrentGreenVideoBlackLevel.Write(respCurrentGreenVideoBlackLevel);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetGreenVideoBlackLevel(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredGreenVideoBlackLevel = aInvocation.InvocationReadUint("DesiredGreenVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    SetGreenVideoBlackLevel(aVersion, InstanceID, DesiredGreenVideoBlackLevel);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetBlueVideoBlackLevel(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentBlueVideoBlackLevel;
    GetBlueVideoBlackLevel(aVersion, InstanceID, respCurrentBlueVideoBlackLevel);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterCurrentBlueVideoBlackLevel(aInvocation, "CurrentBlueVideoBlackLevel");
    respWriterCurrentBlueVideoBlackLevel.Write(respCurrentBlueVideoBlackLevel);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetBlueVideoBlackLevel(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredBlueVideoBlackLevel = aInvocation.InvocationReadUint("DesiredBlueVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    SetBlueVideoBlackLevel(aVersion, InstanceID, DesiredBlueVideoBlackLevel);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetColorTemperature(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentColorTemperature;
    GetColorTemperature(aVersion, InstanceID, respCurrentColorTemperature);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterCurrentColorTemperature(aInvocation, "CurrentColorTemperature");
    respWriterCurrentColorTemperature.Write(respCurrentColorTemperature);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetColorTemperature(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredColorTemperature = aInvocation.InvocationReadUint("DesiredColorTemperature");
    aInvocation.InvocationReadEnd();
    SetColorTemperature(aVersion, InstanceID, DesiredColorTemperature);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetHorizontalKeystone(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    int32_t respCurrentHorizontalKeystone;
    GetHorizontalKeystone(aVersion, InstanceID, respCurrentHorizontalKeystone);
	aInvocation.InvocationWriteStart();
    InvocationResponseInt respWriterCurrentHorizontalKeystone(aInvocation, "CurrentHorizontalKeystone");
    respWriterCurrentHorizontalKeystone.Write(respCurrentHorizontalKeystone);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetHorizontalKeystone(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    int32_t DesiredHorizontalKeystone = aInvocation.InvocationReadInt("DesiredHorizontalKeystone");
    aInvocation.InvocationReadEnd();
    SetHorizontalKeystone(aVersion, InstanceID, DesiredHorizontalKeystone);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetVerticalKeystone(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    int32_t respCurrentVerticalKeystone;
    GetVerticalKeystone(aVersion, InstanceID, respCurrentVerticalKeystone);
	aInvocation.InvocationWriteStart();
    InvocationResponseInt respWriterCurrentVerticalKeystone(aInvocation, "CurrentVerticalKeystone");
    respWriterCurrentVerticalKeystone.Write(respCurrentVerticalKeystone);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetVerticalKeystone(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    int32_t DesiredVerticalKeystone = aInvocation.InvocationReadInt("DesiredVerticalKeystone");
    aInvocation.InvocationReadEnd();
    SetVerticalKeystone(aVersion, InstanceID, DesiredVerticalKeystone);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetMute(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_Channel;
    aInvocation.InvocationReadString("Channel", buf_Channel);
    std::string Channel((const char*)buf_Channel.Ptr(), buf_Channel.Bytes());
    aInvocation.InvocationReadEnd();
    bool respCurrentMute;
    GetMute(aVersion, InstanceID, Channel, respCurrentMute);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriterCurrentMute(aInvocation, "CurrentMute");
    respWriterCurrentMute.Write(respCurrentMute);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetMute(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_Channel;
    aInvocation.InvocationReadString("Channel", buf_Channel);
    std::string Channel((const char*)buf_Channel.Ptr(), buf_Channel.Bytes());
    bool DesiredMute = aInvocation.InvocationReadBool("DesiredMute");
    aInvocation.InvocationReadEnd();
    SetMute(aVersion, InstanceID, Channel, DesiredMute);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetVolume(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_Channel;
    aInvocation.InvocationReadString("Channel", buf_Channel);
    std::string Channel((const char*)buf_Channel.Ptr(), buf_Channel.Bytes());
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentVolume;
    GetVolume(aVersion, InstanceID, Channel, respCurrentVolume);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterCurrentVolume(aInvocation, "CurrentVolume");
    respWriterCurrentVolume.Write(respCurrentVolume);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetVolume(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_Channel;
    aInvocation.InvocationReadString("Channel", buf_Channel);
    std::string Channel((const char*)buf_Channel.Ptr(), buf_Channel.Bytes());
    uint32_t DesiredVolume = aInvocation.InvocationReadUint("DesiredVolume");
    aInvocation.InvocationReadEnd();
    SetVolume(aVersion, InstanceID, Channel, DesiredVolume);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetVolumeDB(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_Channel;
    aInvocation.InvocationReadString("Channel", buf_Channel);
    std::string Channel((const char*)buf_Channel.Ptr(), buf_Channel.Bytes());
    aInvocation.InvocationReadEnd();
    int32_t respCurrentVolume;
    GetVolumeDB(aVersion, InstanceID, Channel, respCurrentVolume);
	aInvocation.InvocationWriteStart();
    InvocationResponseInt respWriterCurrentVolume(aInvocation, "CurrentVolume");
    respWriterCurrentVolume.Write(respCurrentVolume);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetVolumeDB(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_Channel;
    aInvocation.InvocationReadString("Channel", buf_Channel);
    std::string Channel((const char*)buf_Channel.Ptr(), buf_Channel.Bytes());
    int32_t DesiredVolume = aInvocation.InvocationReadInt("DesiredVolume");
    aInvocation.InvocationReadEnd();
    SetVolumeDB(aVersion, InstanceID, Channel, DesiredVolume);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetVolumeDBRange(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_Channel;
    aInvocation.InvocationReadString("Channel", buf_Channel);
    std::string Channel((const char*)buf_Channel.Ptr(), buf_Channel.Bytes());
    aInvocation.InvocationReadEnd();
    int32_t respMinValue;
    int32_t respMaxValue;
    GetVolumeDBRange(aVersion, InstanceID, Channel, respMinValue, respMaxValue);
	aInvocation.InvocationWriteStart();
    InvocationResponseInt respWriterMinValue(aInvocation, "MinValue");
    respWriterMinValue.Write(respMinValue);
    InvocationResponseInt respWriterMaxValue(aInvocation, "MaxValue");
    respWriterMaxValue.Write(respMaxValue);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetLoudness(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_Channel;
    aInvocation.InvocationReadString("Channel", buf_Channel);
    std::string Channel((const char*)buf_Channel.Ptr(), buf_Channel.Bytes());
    aInvocation.InvocationReadEnd();
    bool respCurrentLoudness;
    GetLoudness(aVersion, InstanceID, Channel, respCurrentLoudness);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriterCurrentLoudness(aInvocation, "CurrentLoudness");
    respWriterCurrentLoudness.Write(respCurrentLoudness);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetLoudness(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_Channel;
    aInvocation.InvocationReadString("Channel", buf_Channel);
    std::string Channel((const char*)buf_Channel.Ptr(), buf_Channel.Bytes());
    bool DesiredLoudness = aInvocation.InvocationReadBool("DesiredLoudness");
    aInvocation.InvocationReadEnd();
    SetLoudness(aVersion, InstanceID, Channel, DesiredLoudness);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl1Cpp::ListPresets(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, std::string& /*aCurrentPresetNameList*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SelectPreset(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aPresetName*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetBrightness(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentBrightness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetBrightness(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredBrightness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetContrast(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentContrast*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetContrast(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredContrast*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetSharpness(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentSharpness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetSharpness(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredSharpness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetRedVideoGain(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentRedVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetRedVideoGain(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredRedVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetGreenVideoGain(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentGreenVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetGreenVideoGain(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredGreenVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetBlueVideoGain(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentBlueVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetBlueVideoGain(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredBlueVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetRedVideoBlackLevel(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentRedVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetRedVideoBlackLevel(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredRedVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetGreenVideoBlackLevel(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentGreenVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetGreenVideoBlackLevel(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredGreenVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetBlueVideoBlackLevel(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentBlueVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetBlueVideoBlackLevel(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredBlueVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetColorTemperature(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentColorTemperature*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetColorTemperature(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredColorTemperature*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetHorizontalKeystone(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, int32_t& /*aCurrentHorizontalKeystone*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetHorizontalKeystone(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, int32_t /*aDesiredHorizontalKeystone*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetVerticalKeystone(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, int32_t& /*aCurrentVerticalKeystone*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetVerticalKeystone(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, int32_t /*aDesiredVerticalKeystone*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetMute(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, bool& /*aCurrentMute*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetMute(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, bool /*aDesiredMute*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetVolume(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, uint32_t& /*aCurrentVolume*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetVolume(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, uint32_t /*aDesiredVolume*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetVolumeDB(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, int32_t& /*aCurrentVolume*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetVolumeDB(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, int32_t /*aDesiredVolume*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetVolumeDBRange(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, int32_t& /*aMinValue*/, int32_t& /*aMaxValue*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetLoudness(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, bool& /*aCurrentLoudness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetLoudness(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, bool /*aDesiredLoudness*/)
{
    ASSERTS();
}

