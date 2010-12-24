# Targets specifically intended for the user to invoke on the command-line.
#
# (Note that some of these depend on variables defined in the generated
# makefiles, and so cannot be defined in Common.mak.)

all : Tests $(proxy_dlls) $(proxy_dotnet_assemblies_with_path) $(device_dlls) $(device_dotnet_assemblies_with_path)

clean :
	$(rmdir) $(objdir)
	$(rmdir) $(inc_build)

mostlyclean : clean clean-t4
	$(rmdir) Generated

maintainer-clean : mostlyclean

generate-makefiles : Generated$(dirsep)GenerateSourceFiles.mak Generated$(dirsep)Proxies.mak Generated$(dirsep)Devices.mak	



