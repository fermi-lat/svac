ObjSuf        = o
SrcSuf        = cxx
ExeSuf        =
DllSuf        = so
OutputOpt     = -o 

TMP_DIR = tmp
SRC_DIR = ../src
INC_DIR = ../include

ORACLE_HOME = /usr/oracle

OCILINKOPT = -L /usr/oracle/lib -lclntsh /usr/oracle/rdbms/lib/kpuadef.o  `sed -e 's/-ljava//g' /usr/oracle/lib/ldflags`     -lnsgr8 -lnzjs8 -ln8 -lnl8 -lnro8 `sed -e 's/-ljava//g' /usr/oracle/lib/ldflags`     -lnsgr8 -lnzjs8 -ln8 -lnl8 -lclient8  -lvsn8 -lwtc8 -lcommon8 -lgeneric8 -lwtc8 -lmm -lnls8  -lcore8 -lnls8 -lcore8 -lnls8  `sed -e 's/-ljava//g' /usr/oracle/lib/ldflags`     -lnsgr8 -lnzjs8 -ln8 -lnl8 -lnro8 `sed -e 's/-ljava//g' /usr/oracle/lib/ldflags`     -lnsgr8 -lnzjs8 -ln8 -lnl8 -lclient8  -lvsn8 -lwtc8 -lcommon8 -lgeneric8  -ltrace8 -lnls8  -lcore8 -lnls8 -lcore8 -lnls8  -lclient8  -lvsn8 -lwtc8 -lcommon8 -lgeneric8 -lnls8  -lcore8 -lnls8 -lcore8 -lnls8    `cat /usr/oracle/lib/sysliblist` `if [ -f /usr/lib/libsched.so ] ; then echo -lsched ; else true; fi`  -ldl -lm  -ldl `sed -e 's/-ljava//g' /usr/oracle/lib/ldflags`     -lnsgr8 -lnzjs8 -ln8 -lnl8 -lnro8 `sed -e 's/-ljava//g' /usr/oracle/lib/ldflags`     -lnsgr8 -lnzjs8 -ln8 -lnl8 `sed -e 's/-ljava//g' /usr/oracle/lib/ldflags`     -lnsgr8 -lnzjs8 -ln8 -lnl8 -lnro8 `sed -e 's/-ljava//g' /usr/oracle/lib/ldflags` -lnsgr8 -lnzjs8 -ln8 -lnl8 `sed -e 's/-ljava//g' /usr/oracle/lib/ldflags`     -lnsgr8 -lnzjs8 -ln8 -lnl8 -lnro8 `sed -e 's/-ljava//g' /usr/oracle/lib/ldflags`   -lnsgr8 -lnzjs8 -ln8 -lnl8 `sed -e 's/-ljava//g' /usr/oracle/lib/ldflags` -lnsgr8 -lnzjs8 -ln8 -lnl8 -lnro8 `sed -e 's/-ljava//g' /usr/oracle/lib/ldflags`     -lnsgr8 -lnzjs8 -ln8 -lnl8 `sed -e 's/-ljava//g' /usr/oracle/lib/ldflags`    -lnsgr8 -lnzjs8 -ln8 -lnl8 -lnro8 `sed -e 's/-ljava//g' /usr/oracle/lib/ldflags`     -lnsgr8 -lnzjs8 -ln8 -lnl8 -lsql8 -lsql8 

CXX           = g++

CXXFLAGS      = -g -Wall -fPIC -I$(INC_DIR)/ -I$(ORACLE_HOME)/rdbms/demo -I$(ORACLE_HOME)/rdbms/public

PREPROCESS_FLAG = -MM

LD            = g++
LDFLAGS       = -g $(OCILINKOPT)
SOFLAGS       = -shared
LIBS          = 

all: libOciWrapper.so test.exe

libOciWrapperObj := OCIWrapper.o 
libOciWrapperSource := $(patsubst %.o, $(TMP_DIR)/%.o, $(libOciWrapperObj))
libOciWrapperDependence := $(patsubst %.o, $(TMP_DIR)/%.d, $(libOciWrapperObj))

libOciWrapper.so: $(libOciWrapperDependence) $(libOciWrapperSource)
	$(LD) $(LDFLAGS) $(SOFLAGS) $(LIBS)  $(libOciWrapperSource) $(OutputOpt)$@
	@echo "$@ done"

-include $(libOciWrapperDependence)

testOciWrapperObj := Test.o 
testOciWrapperSource := $(patsubst %.o, $(TMP_DIR)/%.o, $(testOciWrapperObj))
testOciWrapperDependence := $(patsubst %.o, $(TMP_DIR)/%.d, $(testOciWrapperObj))

test.exe: $(testOciWrapperDependence) $(testOciWrapperSource)
	$(LD) -g -L. -lOciWrapper $(LIBS)  $(testOciWrapperSource) $(OutputOpt)$@
	@echo "$@ done"

-include $(testOciWrapperDependence)

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