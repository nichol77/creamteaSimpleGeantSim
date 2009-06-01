# $Id: GNUmakefile,v 1.2 2000/10/19 12:22:10 stanaka Exp $
# --------------------------------------------------------------
# GNUmakefile for simpleGeantSim based on GEANT example makefile
# Ryan Nichol 16/09/08 (Original by Gabriele Cosmo, 06/04/98)
# Also hacked by Jason Koskinen
# --------------------------------------------------------------

name      := simpleGeantSim
G4TARGET  := $(name)
G4EXLIB   := true
G4WORKDIR := .
G4DEBUG   := true



ifndef G4INSTALL
  G4INSTALL = ../../..
endif

#for root
ARCH         := $(shell $(ROOTSYS)/bin/root-config --arch)
PLATFORM     := $(shell $(ROOTSYS)/bin/root-config --platform)
CPPFLAGS += -fPIC $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLDFLAGS = $(shell $(ROOTSYS)/bin/root-config --ldflags)
ROOTLIBS      = $(shell $(ROOTSYS)/bin/root-config --glibs) -lMinuit -lHtml


SOFLAGS	= -shared
ifeq ($(ARCH),macosx)
# MacOS X with cc (GNU cc 2.95.2 and gcc 3.3)
MACOSX_MINOR := $(shell sw_vers | sed -n 's/ProductVersion://p' | cut -d . -f 2)
MACOSXTARGET := MACOSX_DEPLOYMENT_TARGET=10.$(MACOSX_MINOR)
ifeq ($(MACOSX_MINOR),5)
MACOSX_MINOR  = 4
endif
# The SOFLAGS will be used to create the .dylib,
# the .so will be created separately
DLLSUF       = dylib
UNDEFOPT      = dynamic_lookup
ifneq ($(MACOSX_MINOR),4)
ifneq ($(MACOSX_MINOR),3)
UNDEFOPT      = suppress
endif
endif
LD = g++
SOFLAGS       = -dynamiclib -single_module -undefined $(UNDEFOPT)
INTYLIBS      += $(ROOTLIBS) -Wl,-dylib_file,/System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGL.dylib:/System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGL.dylib
else 
INTYLIBS      += $(ROOTLIBS) -lxerces-c -L/usr/X11R6/lib64
endif
#  ROOTLIBS      := $(filter-out -lNew,$(ROOTLIBS))
#  ROOTLIBS      := $(filter-out -lThread,$(ROOTLIBS))
#  ROOTLIBS      := $(filter-out -lpthread,$(ROOTLIBS))


.PHONY: all
all: sgsCint lib libsgsdict bin 

include $(G4INSTALL)/config/binmake.gmk

CXXFLAGS_WITHOUT_O := $(filter-out -O% , $(CXXFLAGS))
CXXFLAGS_WITHOUT_O := $(filter-out +O% , $(CXXFLAGS_WITHOUT_O))

sgsCint: include/ScintHitInfo.hh include/WorldSetup.hh Linkdef.h
	rootcint -f ./src/sgsCint.cc -c -I./include ../include/ScintHitInfo.hh ../include/WorldSetup.hh ../Linkdef.h

libsgsdict:  $(G4WORKDIR)/tmp/$(G4SYSTEM)/simpleGeantSim/ScintHitInfo.o sgsCint $(G4WORKDIR)/tmp/$(G4SYSTEM)/simpleGeantSim/sgsCint.o 
ifeq ($(PLATFORM),macosx)
# We need to make both the .dylib and the .so
	$(LD) $(SOFLAGS) $(G4WORKDIR)/tmp/$(G4SYSTEM)/simpleGeantSim/ScintHitInfo.o   $(G4WORKDIR)/tmp/$(G4SYSTEM)/simpleGeantSim/sgsCint.o -o libsgsdict.dylib
ifeq ($(MACOSX_MINOR),4)
	ln -sf $@.dylib $@.so
else
	$(LD) -bundle -undefined $(UNDEFOPT) $(LDFLAGS) $(G4WORKDIR)/tmp/$(G4SYSTEM)/simpleGeantSim/ScintHitInfo.o   $(G4WORKDIR)/tmp/$(G4SYSTEM)/simpleGeantSim/sgsCint.o -o $@.so
endif
else
ifneq ($(PLATFORM),win32)
	$(LD) $(SOFLAGS) $(LDFLAGS) $(G4WORKDIR)/tmp/$(G4SYSTEM)/simpleGeantSim/ScintHitInfo.o   $(G4WORKDIR)/tmp/$(G4SYSTEM)/simpleGeantSim/sgsCint.o $(LIBS) -o $@.so
endif
endif


visclean:
	rm -f g4*.prim g4*.eps g4*.wrl
	rm -f .DAWN_*

clean::
	@rm -f ./src/*Cint*
	@rm -f *.so

