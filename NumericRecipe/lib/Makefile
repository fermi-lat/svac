ObjSuf        = o
SrcSuf        = C
ExeSuf        =
DllSuf        = so
OutputOpt     = -o 

TMP_DIR = tmp
SRC_DIR = ../src

CXX           = g++

CXXFLAGS      = -g -Wall -fPIC -I$(SRC_DIR)/
PREPROCESS_FLAG = -MM

LD            = g++
LDFLAGS       = -g
SOFLAGS       = -shared
LIBS          = 

all: libNR.so

libNRObj := NRUTIL.o POLINT.o QROMB.o TRAPZD.o KSTWO.o PROBKS.o SORT.o
libNRSource := $(patsubst %.o, $(TMP_DIR)/%.o, $(libNRObj))
libNRDependence := $(patsubst %.o, $(TMP_DIR)/%.d, $(libNRObj))

libNR.so: $(libNRDependence) $(libNRSource)
	$(LD) $(LDFLAGS) $(SOFLAGS) $(LIBS)  $(libNRSource) $(OutputOpt)$@
	@echo "$@ done"

-include $(libNRDependence)

$(TMP_DIR)/%.$(ObjSuf): $(SRC_DIR)/%.$(SrcSuf)
	$(CXX) $(CXXFLAGS) -c $< $(OutputOpt) $@ 


$(TMP_DIR)/%.d: $(SRC_DIR)/%.${SrcSuf}
	@if [ ! -d $(TMP_DIR) ] ; then mkdir $(TMP_DIR) ;fi
	@if [ ! -d $(SRC_DIR) ] ; then mkdir $(SRC_DIR) ;fi
	@echo Making dependency for file $<...
	@set -e;\
	$(CXX) $(PREPROCESS_FLAG) $(CXXFLAGS) $< |\
	sed 's!\($*\)\.o!$(TMP_DIR)/& $@!' >$@;\
	[ -s $@ ] || rm -f $@