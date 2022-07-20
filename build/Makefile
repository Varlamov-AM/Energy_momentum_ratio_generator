######################################################################
# Makefile for building Pythia's ROOT examples.
# Axel Naumann, 2011-03-03
######################################################################

PYTHIA8      := $(ALICE_ROOT)
# Need this to get SHAREDSUFFIX (e.g. dylib or so)
SHAREDSUFFIX=so
#-include $(PYTHIA8)/config.mk

# A few variables used in this Makefile:
EX           := Energy_momentum_ratio_generator
EXE          := $(addsuffix .exe,$(EX))
STATICLIB    := $(PYTHIA8)/lib/archive/libpythia8.a
SHAREDLIB    := $(PYTHIA8)/lib/libpythia8210.$(SHAREDSUFFIX)
DICTCXXFLAGS := -I$(HOME)/chi_c2/PYTHIA8/pythia8210/include
ROOTCXXFLAGS := $(DICTCXXFLAGS) $(shell root-config --cflags)
CXXFLAGS     := -Wall -g

# Libraries to include if GZIP support is enabled
ifeq (x$(ENABLEGZIP),xyes)
LIBGZIP=-L$(BOOSTLIBLOCATION) -lboost_iostreams -L$(ZLIBLOCATION) -lz
endif


# LDFLAGS1 for static library, LDFLAGS2 for shared library
LDFLAGS1 := $(shell root-config --ldflags --glibs) \
  -L$(PYTHIA8)/lib -lpythia8210 -llhapdf $(LIBGZIP)
LDFLAGS2 := $(shell root-config --ldflags --glibs) \
  -L$(PYTHIA8)/lib -lpythia8210 -llhapdf $(LIBGZIP)

FILES_SRC =  ../src/main.cpp ../src/configuration.cpp ../src/smearP.cpp ../src/smearE.cpp ../src/energy_edeption.cpp ../src/initialization_pythia.cpp
FILES_OBJ =  $(FILES_SRC:%.cpp=%.o)


# Default target; make examples (but not shared dictionary)
all: $(EX)

# Rule to build hist example. Needs static PYTHIA 8 library
$(EX): $(SHAREDLIB) $(FILES_OBJ) $(ROOT_DICT)
	$(CXX) $(ROOTCXXFLAGS) $(FILES_OBJ) -o $@.exe $(LDFLAGS1)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(ROOTCXXFLAGS) 

# Rule to build full dictionary
$(ROOT_DICT):
	rootcint -f pythiaDict.cc -c $(DICTCXXFLAGS) \
	-DPYTHIA8_COMPLETE_ROOT_DICTIONARY \
	LinkDef.h
	$(CXX) -shared -fPIC -o $(ROOT_DICT) pythiaDict.cc \
         -DPYTHIA8_COMPLETE_ROOT_DICTIONARY \
         $(ROOTCXXFLAGS) $(LDFLAGS2)


# Error messages if PYTHIA libraries don't exist
$(STATICLIB):
	@echo "Error: PYTHIA 8 archive library must be built"
	@false
$(SHAREDLIB):
	@echo "Error: PYTHIA 8 shared library must be built"
	@false

# Clean up
clean:
	rm -f $(EXE) $(FILES_OBJ) pythia_chic2.root pythiaDict.*
