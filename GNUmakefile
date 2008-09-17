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
CPPFLAGS += -fPIC $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLDFLAGS = $(shell $(ROOTSYS)/bin/root-config --ldflags)
ROOTLIBS      = $(shell $(ROOTSYS)/bin/root-config --glibs) -lMinuit -lHtml
#  ROOTLIBS      := $(filter-out -lNew,$(ROOTLIBS))
#  ROOTLIBS      := $(filter-out -lThread,$(ROOTLIBS))
#  ROOTLIBS      := $(filter-out -lpthread,$(ROOTLIBS))
INTYLIBS      += $(ROOTLIBS) -lxerces-c -L/usr/X11R6/lib64

.PHONY: all
all: jdetCint lib libg4jdetDict bin 

include $(G4INSTALL)/config/binmake.gmk

CXXFLAGS_WITHOUT_O := $(filter-out -O% , $(CXXFLAGS))
CXXFLAGS_WITHOUT_O := $(filter-out +O% , $(CXXFLAGS_WITHOUT_O))

jdetCint: include/data_t.hh Linkdef.h
	rootcint -f ./src/jdetCint.cc -c -I./include ../include/data_t.hh ../Linkdef.h

libg4jdetDict:  $(G4WORKDIR)/tmp/$(G4SYSTEM)/simpleGeantSim/data_t.o $(G4WORKDIR)/tmp/$(G4SYSTEM)/simpleGeantSim/jdetCint.o jdetCint
	g++ $(ROOTLDFLAGS) --shared -o libgjdetDict.so  $(G4WORKDIR)/tmp/$(G4SYSTEM)/simpleGeantSim/data_t.o   $(G4WORKDIR)/tmp/$(G4SYSTEM)/simpleGeantSim/jdetCint.o

visclean:
	rm -f g4*.prim g4*.eps g4*.wrl
	rm -f .DAWN_*

clean::
	@rm -f ./src/*Cint*
	@rm -f *.so

