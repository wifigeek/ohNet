objdir = Build/Obj/Posix
incdir = Build/Include
ohnetdir = ../Upnp/Build/Obj/Posix/Debug
toolsDir = ../Upnp/Build/Posix/Tools
templatesDir = ../Upnp/T4/Templates

# Macros used by Common.mak

ar = ${CROSS_COMPILE}ar rc $(objdir)
cflags = -fexceptions -Wall -Werror -pipe -D_GNU_SOURCE -D_REENTRANT -DDEFINE_LITTLE_ENDIAN -DDEFINE_TRACE -g -O0 -Wno-psabi -fvisibility=hidden -DDllImport="__attribute__ ((visibility(\"default\")))" -DDllExport="__attribute__ ((visibility(\"default\")))" -DDllExportClass="__attribute__ ((visibility(\"default\")))"
objdir = Build/Obj/Posix/
inc_build = Build/Include
includes = -I../Upnp/Build/Include/ -I../Upnp/Build/Include/Cpp/
bundle_build = Build/Bundles
osdir = Posix
objext = o
libprefix = lib
libext = a
exeext = elf
compiler = ${CROSS_COMPILE}gcc -fPIC -o $(objdir)
link = ${CROSS_COMPILE}g++ -lpthread
linkoutput = -o 
dllprefix = lib
dllext = so
link_dll = ${CROSS_COMPILE}g++ -lpthread -shared -shared-libgcc
csharp = gmcs /nologo
publiccsdir = Public/Cs/
dirsep = /
prefix = /usr/local
installlibdir = $(prefix)/lib/zapp
installincludedir = $(prefix)/include/zapp
installpkgconfdir = $(prefix)/lib/pkgconfig
mkdir = mkdir -p
rmdir = rm -rf
uset4 = no

all: $(objdir)/WavSender.exe 

$(objdir)/WavSender.exe :
	mkdir -p $(objdir)
	$(compiler)/DvAvOpenhomeOrgSender1.$(objext) -c $(cflags) $(includes) Services/DvAvOpenhomeOrgSender1.cpp
	$(compiler)/Ohm.$(objext) -c $(cflags) $(includes) Ohm.cpp
	$(compiler)/OhmSender.$(objext) -c $(cflags) $(includes) OhmSender.cpp
	$(compiler)/WavSender.$(objext) -c $(cflags) $(includes) WavSender/WavSender.cpp
	$(link) $(linkoutput)$(objdir)/WavSender.$(exeext) $(objdir)/WavSender.$(objext) $(objdir)/DvAvOpenhomeOrgSender1.$(objext) $(objdir)/Ohm.$(objext) $(objdir)/OhmSender.$(objext) $(ohnetdir)/$(libprefix)ohNetCore.$(libext) $(ohnetdir)/$(libprefix)TestFramework.$(libext)

$(objdir)/WavReceiver.exe :
	mkdir -p $(objdir)
	$(compiler)/DvAvOpenhomeOrgProduct1.$(objext) -c $(cflags) $(includes) Services/DvAvOpenhomeOrgProduct1.cpp
	$(compiler)/DvAvOpenhomeOrgReceiver1.$(objext) -c $(cflags) $(includes) Services/DvAvOpenhomeOrgReceiver1.cpp
	$(compiler)/Product.$(objext) -c $(cflags) $(includes) Product.cpp
	$(compiler)/Receiver.$(objext) -c $(cflags) $(includes) WavReceiver/Receiver.cpp
	$(link) $(linkoutput)$(objdir)/WavReceiver.$(exeext) $(objdir)/WavReceiver.$(objext) $(objdir)/Product.$(objext) $(objdir)/DvAvOpenhomeOrgProduct1.$(objext) $(objdir)/DvAvOpenhomeOrgReceiver1.$(objext) $(ohnetdir)/$(libprefix)ohNetCore.$(libext) $(ohnetdir)/$(libprefix)TestFramework.$(libext)

t4 = $(toolsDir)/TextTransform.exe

gen: DvAvOpenhomeOrgSender1.h DvAvOpenhomeOrgSender1.cpp DvAvOpenhomeOrgProduct1.h DvAvOpenhomeOrgProduct1.cpp DvAvOpenhomeOrgReceiver1.h DvAvOpenhomeOrgReceiver1.cpp

DvAvOpenhomeOrgSender1.h : $(templatesDir)/DvUpnpCppCoreHeader.tt Services/Sender1.xml
	$(t4) -o Services/DvAvOpenhomeOrgSender1.h $(templatesDir)/DvUpnpCppCoreHeader.tt -a "xml:Sender1.xml" -a domain:av.openhome.org -a type:Sender -a version:1
DvAvOpenhomeOrgSender1.cpp : ../Upnp/T4/Templates/DvUpnpCppCoreSource.tt Services/Sender1.xml
	$(t4) -o Services/DvAvOpenhomeOrgSender1.cpp $(templatesDir)/DvUpnpCppCoreSource.tt -a "xml:Sender1.xml" -a domain:av.openhome.org -a type:Sender -a version:1

DvAvOpenhomeOrgProduct1.h : $(templatesDir)/DvUpnpCppCoreHeader.tt Services/Product1.xml
	$(t4) -o Services/DvAvOpenhomeOrgProduct1.h $(templatesDir)/DvUpnpCppCoreHeader.tt -a "xml:Product1.xml" -a domain:av.openhome.org -a type:Product -a version:1
DvAvOpenhomeOrgProduct1.cpp : ../Upnp/T4/Templates/DvUpnpCppCoreSource.tt Services/Product1.xml
	$(t4) -o Services/DvAvOpenhomeOrgProduct1.cpp $(templatesDir)/DvUpnpCppCoreSource.tt -a "xml:Product1.xml" -a domain:av.openhome.org -a type:Product -a version:1

DvAvOpenhomeOrgReceiver1.h : $(templatesDir)/DvUpnpCppCoreHeader.tt Services/Receiver1.xml
	$(t4) -o Services/DvAvOpenhomeOrgReceiver1.h $(templatesDir)/DvUpnpCppCoreHeader.tt -a "xml:Receiver1.xml" -a domain:av.openhome.org -a type:Receiver -a version:1
DvAvOpenhomeOrgReceiver1.cpp : ../Upnp/T4/Templates/DvUpnpCppCoreSource.tt Services/Receiver1.xml
	$(t4) -o Services/DvAvOpenhomeOrgReceiver1.cpp $(templatesDir)/DvUpnpCppCoreSource.tt -a "xml:Receiver1.xml" -a domain:av.openhome.org -a type:Receiver -a version:1
