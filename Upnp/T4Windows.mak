# Makefile for T4 on Windows

# Macros used by T4.mak

toolsDir = Build\Windows\Tools^\
t4 = $(toolsDir)TextTransform.exe
ohNetGen = $(toolsDir)OhNetGen.exe
upnpServiceXml = $(toolsDir)UpnpServiceXml.dll
upnpServiceMake = $(toolsDir)UpnpServiceMake.dll
argumentProcessor = $(toolsDir)ArgumentProcessor.dll
tt = $(toolsDir)UpnpServiceXml.dll $(toolsDir)UpnpServiceMake.dll $(toolsDir)Mono.TextTemplating.dll $(toolsDir)TextTransform.exe $(toolsDir)OhNetGen.exe

tt : $(tt)

dllsources =	T4\\TextTemplating\\Mono.TextTemplating\\AssemblyInfo.cs \
                T4\\TextTemplating\\Mono.TextTemplating\\Microsoft.VisualStudio.TextTemplating\\DirectiveProcessor.cs \
                T4\\TextTemplating\\Mono.TextTemplating\\Microsoft.VisualStudio.TextTemplating\\DirectiveProcessorException.cs \
                T4\\TextTemplating\\Mono.TextTemplating\\Microsoft.VisualStudio.TextTemplating\\RequiresProvidesDirectiveProcessor.cs \
                T4\\TextTemplating\\Mono.TextTemplating\\Microsoft.VisualStudio.TextTemplating\\ToStringHelper.cs \
                T4\\TextTemplating\\Mono.TextTemplating\\Microsoft.VisualStudio.TextTemplating\\ITextTemplatingEngineHost.cs \
                T4\\TextTemplating\\Mono.TextTemplating\\Microsoft.VisualStudio.TextTemplating\\Engine.cs \
                T4\\TextTemplating\\Mono.TextTemplating\\Microsoft.VisualStudio.TextTemplating\\TextTransformation.cs \
                T4\\TextTemplating\\Mono.TextTemplating\\Mono.TextTemplating\\TemplatingEngine.cs \
                T4\\TextTemplating\\Mono.TextTemplating\\Mono.TextTemplating\\CrossAppDomainAssemblyResolver.cs \
                T4\\TextTemplating\\Mono.TextTemplating\\Mono.TextTemplating\\TemplateGenerator.cs \
                T4\\TextTemplating\\Mono.TextTemplating\\Mono.TextTemplating\\Tokeniser.cs \
                T4\\TextTemplating\\Mono.TextTemplating\\Mono.TextTemplating\\IExtendedTextTemplatingEngineHost.cs \
                T4\\TextTemplating\\Mono.TextTemplating\\Mono.TextTemplating\\TemplateSettings.cs \
                T4\\TextTemplating\\Mono.TextTemplating\\Mono.TextTemplating\\ParsedTemplate.cs \
                T4\\TextTemplating\\Mono.TextTemplating\\Mono.TextTemplating\\CompiledTemplate.cs

$(toolsDir)Mono.TextTemplating.dll : $(dllsources)
	@if not exist $(toolsDir) mkdir $(toolsDir)
	csc /nologo /t:library -out:$(toolsDir)Mono.TextTemplating.dll $(dllsources)

exesources =	T4\\TextTemplating\\TextTransform\\AssemblyInfo.cs \
                T4\\TextTemplating\\TextTransform\\Options.cs \
                T4\\TextTemplating\\TextTransform\\TextTransform.cs

$(toolsDir)OhNetGen.exe : $(toolsDir)TextTransform.exe T4\\OhNetGen.cs
	@if not exist $(toolsDir) mkdir $(toolsDir)
	csc /t:exe /out:$(toolsDir)OhNetGen.exe T4\\OhNetGen.cs T4\\AssemblyInfo.cs

$(toolsDir)TextTransform.exe : $(toolsDir)Mono.TextTemplating.dll $(exesources)
	@if not exist $(toolsDir) mkdir $(toolsDir)
	csc /nologo /t:exe -out:$(toolsDir)TextTransform.exe /r:$(toolsDir)Mono.TextTemplating.dll $(exesources)

$(toolsDir)UpnpServiceDescription.xsd : T4\\UpnpServiceXml\\UpnpServiceDescription.xsd
	@if not exist $(toolsDir) mkdir $(toolsDir)
	copy /y T4\\UpnpServiceXml\\UpnpServiceDescription.xsd $(toolsDir)

$(toolsDir)UpnpServiceTemplate.xsd : T4\\UpnpServiceXml\\UpnpServiceTemplate.xsd
	@if not exist $(toolsDir) mkdir $(toolsDir)
	copy /y T4\\UpnpServiceXml\\UpnpServiceTemplate.xsd $(toolsDir)


xmlsources =	T4\\UpnpServiceXml\\AssemblyInfo.cs \
                T4\\UpnpServiceXml\\UpnpServiceXml.cs


$(toolsDir)UpnpServiceXml.dll: $(toolsDir)UpnpServiceDescription.xsd $(toolsDir)UpnpServiceTemplate.xsd $(xmlsources)
	@if not exist $(toolsDir) mkdir $(toolsDir)
	csc -target:library -out:$(upnpServiceXml) $(xmlsources)
	

makesources =	T4\\UpnpServiceMake\\AssemblyInfo.cs \
                T4\\UpnpServiceMake\\UpnpServiceMake.cs

$(toolsDir)UpnpServiceMake.dll : $(makesources)
	@if not exist $(toolsDir) mkdir $(toolsDir)
	csc -target:library -out:$(upnpServiceMake) $(makesources)

clean-t4:
	$(rmdir) $(toolsDir)

mkToolsDir:
	if not exist $(toolsDir) mkdir $(toolsDir)
