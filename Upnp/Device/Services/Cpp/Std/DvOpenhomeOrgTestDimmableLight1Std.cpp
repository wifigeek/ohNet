#include "DvOpenhomeOrgTestDimmableLight1.h"
#include <OhNetTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace OpenHome;
using namespace OpenHome::Net;

bool DvProviderOpenhomeOrgTestDimmableLight1Cpp::SetPropertyA_ARG_Level(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyA_ARG_Level, aValue);
}

void DvProviderOpenhomeOrgTestDimmableLight1Cpp::GetPropertyA_ARG_Level(uint32_t& aValue)
{
    aValue = iPropertyA_ARG_Level->Value();
}

DvProviderOpenhomeOrgTestDimmableLight1Cpp::DvProviderOpenhomeOrgTestDimmableLight1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "openhome.org", "TestDimmableLight", 1)
{
    
    iPropertyA_ARG_Level = new PropertyUint(new ParameterUint("A_ARG_Level"));
    iService->AddProperty(iPropertyA_ARG_Level); // passes ownership
}

void DvProviderOpenhomeOrgTestDimmableLight1Cpp::EnableActionGetLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetLevel");
    action->AddOutputParameter(new ParameterRelated("Level", *iPropertyA_ARG_Level));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestDimmableLight1Cpp::DoGetLevel);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestDimmableLight1Cpp::EnableActionSetLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetLevel");
    action->AddInputParameter(new ParameterRelated("Level", *iPropertyA_ARG_Level));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestDimmableLight1Cpp::DoSetLevel);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestDimmableLight1Cpp::DoGetLevel(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respLevel;
    GetLevel(aVersion, respLevel);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterLevel(aInvocation, "Level");
    respWriterLevel.Write(respLevel);
	aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestDimmableLight1Cpp::DoSetLevel(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t Level = aInvocation.InvocationReadUint("Level");
    aInvocation.InvocationReadEnd();
    SetLevel(aVersion, Level);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestDimmableLight1Cpp::GetLevel(uint32_t /*aVersion*/, uint32_t& /*aLevel*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestDimmableLight1Cpp::SetLevel(uint32_t /*aVersion*/, uint32_t /*aLevel*/)
{
    ASSERTS();
}

