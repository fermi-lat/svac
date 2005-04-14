CMT_tag=$(tag)
CMTROOT=/afs/slac.stanford.edu/g/glast/applications/CMT/v1r16p20040701
CMT_root=/afs/slac.stanford.edu/g/glast/applications/CMT/v1r16p20040701
CMTVERSION=v1r16p20040701
CMTrelease=15
cmt_hardware_query_command=uname -m
cmt_hardware=`$(cmt_hardware_query_command)`
cmt_system_version_query_command=${CMTROOT}/mgr/cmt_linux_version.sh | ${CMTROOT}/mgr/cmt_filter_version.sh
cmt_system_version=`$(cmt_system_version_query_command)`
cmt_compiler_version_query_command=${CMTROOT}/mgr/cmt_gcc_version.sh | ${CMTROOT}/mgr/cmt_filter_version.sh
cmt_compiler_version=`$(cmt_compiler_version_query_command)`
PATH=/nfs/farm/g/glast/u06/chen/svac/InstallArea/share/bin:/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2/InstallArea/share/bin:/nfs/farm/g/glast/u06/chen/svac/InstallArea/rh9_gcc32/bin:/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2/InstallArea/rh9_gcc32/bin:/afs/slac.stanford.edu/g/glast/applications/CMT/v1r16p20040701/${CMTBIN}:/usr/local/bin:/usr/afsws/bin:/usr/afsws/etc:/bin:/usr/bin:/usr/etc:/usr/bin/X11:.:/afs/slac.stanford.edu/package/cernlib/rs_aix41/cern/98/bin:/afs/slac.stanford.edu/u/ek/dsl/bin:/space1/ARGOS/USA/bin:/space1/ARGOS/USA/scripts:/usr/oracle/bin:/usr/oracle/ctx/lib:/afs/slac.stanford.edu/g/glast/applications/install/@sys/usr/bin:/afs/slac.stanford.edu/g/glast/ground/releases:/afs/slac.stanford.edu/g/glast/ground/scripts:/afs/slac.stanford.edu/g/glast/ground/scripts/ReleaseManager:${ROOTSYS}/bin
CLASSPATH=/nfs/farm/g/glast/u06/chen/svac/InstallArea/share/bin:/nfs/farm/g/glast/u06/chen/svac/InstallArea/share/lib:/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2/InstallArea/share/bin:/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2/InstallArea/share/lib:/usr/oracle/jdbc/lib/classes111.zip:/usr/oracle/sqlj/lib/translator.zip:/usr/oracle/rdbms/jlib/aqapi11.jar:/usr/oracle/sqlj/demo:/afs/slac.stanford.edu/g/glast/applications/CMT/v1r16p20040701/java
debug_option=-g
cc=gcc
cdebugflags=$(debug_option)
pp_cflags=-Di586
ccomp=$(cc) -c $(includes) $(cdebugflags) $(cflags) $(pp_cflags)
clink=$(cc) $(clinkflags) $(cdebugflags)
ppcmd=-I
preproc=c++ -MD -c 
cpp=g++
cppdebugflags=$(debug_option)
cppflags=-pipe -ansi -W -Wall  -fPIC -shared -D_GNU_SOURCE -Dlinux -Dunix 
pp_cppflags=-D_GNU_SOURCE
cppcomp=$(cpp) -c $(includes) $(cppoptions) $(cppflags) $(pp_cppflags)
cpplinkflags=-Wl,-Bdynamic  $(linkdebug)
cpplink=$(cpp)   $(cpplinkflags)
for=g77
fflags=$(debug_option)
fcomp=$(for) -c $(fincludes) $(fflags) $(pp_fflags)
flink=$(for) $(flinkflags)
javacomp=javac -classpath $(src):$(CLASSPATH) 
javacopy=cp
jar=jar
X11_cflags=-I/usr/include
Xm_cflags=-I/usr/include
X_linkopts=-L/usr/X11R6/lib -lXm -lXt -lXext -lX11 -lm
lex=flex $(lexflags)
yaccflags= -l -d 
yacc=yacc $(yaccflags)
ar=ar r
ranlib=ranlib
make_shlib=${CMTROOT}/mgr/cmt_make_shlib_common.sh extract
shlibsuffix=so
shlibbuilder=g++ $(cmt_installarea_linkopts) 
shlibflags=-shared
symlink=/bin/ln -fs 
symunlink=/bin/rm -f 
build_library_links=$(cmtexe) build library_links -quiet -tag=$(tags)
remove_library_links=$(cmtexe) remove library_links -quiet -tag=$(tags)
cmtexe=${CMTROOT}/${CMTBIN}/cmt.exe
build_prototype=$(cmtexe) build prototype
build_dependencies=$(cmtexe) -quiet -tag=$(tags) build dependencies
build_triggers=$(cmtexe) build triggers
implied_library_prefix=-l
SHELL=/bin/sh
src=../src/
doc=../doc/
inc=../src/
mgr=../cmt/
application_suffix=.exe
library_prefix=lib
lock_command=chmod -R a-w ../*
unlock_command=chmod -R g+w ../*
MAKEFLAGS= --no-print-directory 
gmake_hosts=lx1 rsplus lxtest as7 dxplus ax7 hp2 aleph hp1 hpplus papou1-fe atlas
make_hosts=virgo-control1 rio0a vmpc38a
everywhere=hosts
install_command=cp 
uninstall_command=/bin/rm -f 
cmt_installarea_command=ln -s 
cmt_uninstallarea_command=/bin/rm -f 
cmt_install_area_command=$(cmt_installarea_command)
cmt_uninstall_area_command=$(cmt_uninstallarea_command)
cmt_install_action=$(CMTROOT)/mgr/cmt_install_action.sh
cmt_installdir_action=$(CMTROOT)/mgr/cmt_installdir_action.sh
cmt_uninstall_action=$(CMTROOT)/mgr/cmt_uninstall_action.sh
cmt_uninstalldir_action=$(CMTROOT)/mgr/cmt_uninstalldir_action.sh
mkdir=mkdir
cmt_installarea_prefix=InstallArea
CMT_PATH_remove_regexp=/[^/]*/
CMT_PATH_remove_share_regexp=/share/
NEWCMTCONFIG=i686-rhel31-gcc32
NtupleCompare_tag=$(tag)
NTUPLECOMPAREROOT=/a/sulky27/g.glast.u06/chen/svac/NtupleCompare/v0
NtupleCompare_root=/a/sulky27/g.glast.u06/chen/svac/NtupleCompare/v0
NTUPLECOMPAREVERSION=v0
NtupleCompare_cmtpath=/nfs/farm/g/glast/u06/chen/svac
NtupleCompare_offset=a/sulky27/g.glast.u06/chen/svac
NtupleCompare_project=Project1
GlastPolicy_tag=$(tag)
GLASTPOLICYROOT=/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2/GlastPolicy/v6r3p2
GlastPolicy_root=/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2/GlastPolicy/v6r3p2
GLASTPOLICYVERSION=v6r3p2
GlastPolicy_cmtpath=/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2
GlastPolicy_project=Project2
GlastPatternPolicy_tag=$(tag)
GLASTPATTERNPOLICYROOT=/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2/GlastPolicy/GlastPatternPolicy/v0r1
GlastPatternPolicy_root=/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2/GlastPolicy/GlastPatternPolicy/v0r1
GLASTPATTERNPOLICYVERSION=v0r1
GlastPatternPolicy_cmtpath=/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2
GlastPatternPolicy_offset=GlastPolicy
GlastPatternPolicy_project=Project2
GlastMain=${GLASTPOLICYROOT}/src/GlastMain.cxx
TestGlastMain=${GLASTPOLICYROOT}/src/TestGlastMain.cxx
GlastCppPolicy_tag=$(tag)
GLASTCPPPOLICYROOT=/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2/GlastPolicy/GlastCppPolicy/v0r2
GlastCppPolicy_root=/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2/GlastPolicy/GlastCppPolicy/v0r2
GLASTCPPPOLICYVERSION=v0r2
GlastCppPolicy_cmtpath=/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2
GlastCppPolicy_offset=GlastPolicy
GlastCppPolicy_project=Project2
BINDIR=rh9_gcc32
cppoptions=$(cppdebugflags_s)
cppdebugflags_s=-g
cppoptimized_s=-O2
cppprofiled_s=-pg
linkdebug=-g 
makeLinkMap=-Wl,-Map,Linux.map
componentshr_linkopts=-fPIC  -ldl 
libraryshr_linkopts=-fPIC -ldl 
GlastInstallPolicy_tag=$(tag)
GLASTINSTALLPOLICYROOT=/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2/GlastPolicy/GlastInstallPolicy/v0r1
GlastInstallPolicy_root=/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2/GlastPolicy/GlastInstallPolicy/v0r1
GLASTINSTALLPOLICYVERSION=v0r1
GlastInstallPolicy_cmtpath=/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2
GlastInstallPolicy_offset=GlastPolicy
GlastInstallPolicy_project=Project2
filesep=:
ROOT_tag=$(tag)
ROOTROOT=/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2/IExternal/ROOT/v2r31002p3
ROOT_root=/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2/IExternal/ROOT/v2r31002p3
ROOTVERSION=v2r31002p3
ROOT_cmtpath=/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2
ROOT_offset=IExternal
ROOT_project=Project2
ExternalLibs_tag=$(tag)
EXTERNALLIBSROOT=/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2/IExternal/ExternalLibs/v4r0p5
ExternalLibs_root=/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2/IExternal/ExternalLibs/v4r0p5
EXTERNALLIBSVERSION=v4r0p5
ExternalLibs_cmtpath=/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2
ExternalLibs_offset=IExternal
ExternalLibs_project=Project2
PLATARCHdef=rh9_gcc32
PLATARCH=$(PLATARCHdef)
EXTPACK_DIR=${GLAST_EXT}
CLHEP_DIR=${EXTPACK_DIR}/CLHEP
ROOT_DIR=${EXTPACK_DIR}/ROOT
PYTHON_DIR=${EXTPACK_DIR}/Python
XERCES_DIR=${EXTPACK_DIR}/Xerces-C
BOOST_DIR=${EXTPACK_DIR}/boost
CFITSIO_DIR=${EXTPACK_DIR}/cfitsio
AIDA_DIR=${EXTPACK_DIR}/AIDA
HTL_DIR=${EXTPACK_DIR}/HTL
GEANT4_DIR=${EXTPACK_DIR}/geant4
MYSQL_DIR=${EXTPACK_DIR}/MYSQL
GAUDI_DIR=${EXTPACK_DIR}/gaudi
PIL_DIR=${EXTPACK_DIR}/pil
ROOT_native_version=v3.10.02
ROOT_PATH=${ROOT_DIR}/$(ROOT_native_version)/root
ROOTSYS=/nfs/farm/g/glast/u05/GLAST_EXT/rh9_gcc32/ROOT/v3.10.02/root
dict=../dict/
rootcint=rootcint
ROOT_libs=-L$(ROOT_PATH)/lib -lCore -lCint -lTree -lMatrix -lPhysics -lpthread -lm -ldl -rdynamic
ROOT_GUI_libs=-L$(ROOT_PATH)/lib -lHist -lGraf -lGraf3d -lGpad -lRint -lPostscript
ROOT_linkopts=$(ROOT_libs) -lHist -lGpad -lGraf -lGui -lGraf3d 
ROOT_cppflagsEx=$(ppcmd) "$(ROOT_PATH)/include" -DUSE_ROOT
LD_LIBRARY_PATH=/nfs/farm/g/glast/u06/chen/svac/InstallArea/rh9_gcc32/lib:/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2/InstallArea/rh9_gcc32/lib:/nfs/farm/g/glast/u06/chen/svac/NumericRecipe/lib/:/nfs/farm/g/glast/u05/GLAST_EXT/rh9_gcc32/ROOT/v3.10.02/root/bin:/nfs/farm/g/glast/u05/GLAST_EXT/rh9_gcc32/ROOT/v3.10.02/root/lib
RootPolicy_tag=$(tag)
ROOTPOLICYROOT=/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2/RootPolicy/v4r8
RootPolicy_root=/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2/RootPolicy/v4r8
ROOTPOLICYVERSION=v4r8
RootPolicy_cmtpath=/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2
RootPolicy_project=Project2
includes=-I $(NTUPLECOMPAREROOT)  $(ppcmd)"$(NTUPLECOMPAREROOT)" $(ppcmd)"/nfs/farm/g/glast/u06/chen/svac/NumericRecipe/src" $(use_includes)
source=*.cxx
NRLINKOPT=-L /nfs/farm/g/glast/u06/chen/svac/NumericRecipe/lib/ -lNR 
NtupleCompare_linkopts= $(NRLINKOPT) 
GlastPatternPolicyDir=${GLASTPATTERNPOLICYROOT}/${BINDIR}
GlastPolicyDir=${GLASTPOLICYROOT}/${BINDIR}
RootPolicyDir=${ROOTPOLICYROOT}/${BINDIR}
NtupleCompareDir=${NTUPLECOMPAREROOT}/${BINDIR}
CMTINSTALLAREA=/nfs/farm/g/glast/u06/chen/svac/InstallArea
tag=rh9_gcc32
package=NtupleCompare
version=v0
PACKAGE_ROOT=$(NTUPLECOMPAREROOT)
srcdir=../src
bin=../$(NtupleCompare_tag)/
javabin=../classes/
mgrdir=cmt
project=Project1
use_requirements=requirements $(CMTROOT)/mgr/requirements $(ROOTPOLICYROOT)/cmt/requirements $(GLASTPOLICYROOT)/cmt/requirements $(GLASTPATTERNPOLICYROOT)/cmt/requirements $(GLASTCPPPOLICYROOT)/cmt/requirements $(GLASTINSTALLPOLICYROOT)/cmt/requirements $(ROOTROOT)/cmt/requirements $(EXTERNALLIBSROOT)/cmt/requirements 
use_includes= $(ppcmd)"$(ROOT_PATH)/include" 
use_fincludes= $(use_includes)
use_stamps= $(NtupleCompare_stamps)  $(RootPolicy_stamps)  $(GlastPolicy_stamps)  $(GlastPatternPolicy_stamps)  $(GlastCppPolicy_stamps)  $(GlastInstallPolicy_stamps)  $(ROOT_stamps)  $(ExternalLibs_stamps) 
use_cflags=  $(NtupleCompare_cflags)  $(RootPolicy_cflags)  $(GlastPolicy_cflags)  $(GlastPatternPolicy_cflags)  $(GlastCppPolicy_cflags)  $(GlastInstallPolicy_cflags)  $(ROOT_cflags)  $(ExternalLibs_cflags) 
use_pp_cflags=  $(NtupleCompare_pp_cflags)  $(RootPolicy_pp_cflags)  $(GlastPolicy_pp_cflags)  $(GlastPatternPolicy_pp_cflags)  $(GlastCppPolicy_pp_cflags)  $(GlastInstallPolicy_pp_cflags)  $(ROOT_pp_cflags)  $(ExternalLibs_pp_cflags) 
use_cppflags=  $(NtupleCompare_cppflags)  $(RootPolicy_cppflags)  $(GlastPolicy_cppflags)  $(GlastPatternPolicy_cppflags)  $(GlastCppPolicy_cppflags)  $(GlastInstallPolicy_cppflags)  $(ROOT_cppflags)  $(ExternalLibs_cppflags) 
use_pp_cppflags=  $(NtupleCompare_pp_cppflags)  $(RootPolicy_pp_cppflags)  $(GlastPolicy_pp_cppflags)  $(GlastPatternPolicy_pp_cppflags)  $(GlastCppPolicy_pp_cppflags)  $(GlastInstallPolicy_pp_cppflags)  $(ROOT_pp_cppflags)  $(ExternalLibs_pp_cppflags) 
use_fflags=  $(NtupleCompare_fflags)  $(RootPolicy_fflags)  $(GlastPolicy_fflags)  $(GlastPatternPolicy_fflags)  $(GlastCppPolicy_fflags)  $(GlastInstallPolicy_fflags)  $(ROOT_fflags)  $(ExternalLibs_fflags) 
use_pp_fflags=  $(NtupleCompare_pp_fflags)  $(RootPolicy_pp_fflags)  $(GlastPolicy_pp_fflags)  $(GlastPatternPolicy_pp_fflags)  $(GlastCppPolicy_pp_fflags)  $(GlastInstallPolicy_pp_fflags)  $(ROOT_pp_fflags)  $(ExternalLibs_pp_fflags) 
use_linkopts= $(cmt_installarea_linkopts)   $(NtupleCompare_linkopts)  $(RootPolicy_linkopts)  $(GlastPolicy_linkopts)  $(GlastPatternPolicy_linkopts)  $(GlastCppPolicy_linkopts)  $(GlastInstallPolicy_linkopts)  $(ROOT_linkopts)  $(ExternalLibs_linkopts) 
use_libraries= $(RootPolicy_libraries)  $(GlastPolicy_libraries)  $(GlastPatternPolicy_libraries)  $(GlastCppPolicy_libraries)  $(GlastInstallPolicy_libraries)  $(ROOT_libraries)  $(ExternalLibs_libraries) 
fincludes= $(includes)
NtupleCompare_use_linkopts=  $(NtupleCompare_linkopts)  $(RootPolicy_linkopts)  $(GlastPolicy_linkopts)  $(GlastPatternPolicy_linkopts)  $(GlastCppPolicy_linkopts)  $(GlastInstallPolicy_linkopts)  $(ROOT_linkopts)  $(ExternalLibs_linkopts) 
constituents= install_includes  NtupleCompare 
all_constituents= $(constituents)
constituentsclean= NtupleCompareclean 
all_constituentsclean= $(constituentsclean)
cmt_installarea_paths=$(cmt_installarea_prefix)/$(tag)/bin $(cmt_installarea_prefix)/$(tag)/lib $(cmt_installarea_prefix)/share/lib $(cmt_installarea_prefix)/share/bin
Project2_installarea_prefix=$(cmt_installarea_prefix)
Project2_installarea_prefix_remove=$(Project2_installarea_prefix)
Project1_installarea_prefix=$(cmt_installarea_prefix)
Project1_installarea_prefix_remove=$(Project1_installarea_prefix)
cmt_installarea_linkopts= -L/nfs/farm/g/glast/u06/chen/svac/$(Project1_installarea_prefix)/$(tag)/lib  -L/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2/$(Project2_installarea_prefix)/$(tag)/lib 
JOBOPTSEARCHPATH=:/nfs/farm/g/glast/u06/chen/svac/InstallArea/jobOptions:/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2/InstallArea/jobOptions
XMLPATH=/nfs/farm/g/glast/u06/chen/svac/InstallArea/xmlData:/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2/InstallArea/xmlData
PFILES=/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2/InstallArea/pfiles:/nfs/farm/g/glast/u06/chen/svac/InstallArea/pfiles
DATAPATH=/nfs/farm/g/glast/u06/chen/svac/InstallArea/data:/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2/InstallArea/data
