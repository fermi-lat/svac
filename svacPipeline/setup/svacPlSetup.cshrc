#!/bin/sh

# setup for SVAC pipeline

setenv GLASTROOT /afs/slac.stanford.edu/g/glast
source ${GLASTROOT}/ground/scripts/user.cshrc
setenv sasLocation /nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel
setenv sasVersion EngineeringModel-v3r0402p16
setenv sasCmt ${sasLocation}/${sasVersion}

setenv svacRoot /nfs/slac/g/svac/common
setenv svacCmt ${svacRoot}/builds
setenv svacPlRoot ${svacRoot}/pipeline
setenv svacPlLib ${svacPlRoot}/lib

setenv CMTPATH ${svacCmt}:${sasCmt}

setenv dataHead /nfs/farm/g/glast/u12/EM2
setenv rootUrl /glast.u12/EM2/rootData

setenv calibVersion calib-v1r0

#++++++++++++++++++++++++++++++++ eLogUpdate ++++++++++++++++++++++++++++++++++
setenv eLogTaskVersion v1r0
setenv eLogTask updateELogDB-EM2-${eLogTaskVersion}
setenv eLogFeederVersion v1r1
setenv eLogDir ${svacCmt}/eLogFeeder/${eLogFeederVersion}
#-------------------------------- eLogUpdate ----------------------------------

#++++++++++++++++++++++++++++++++ configReport ++++++++++++++++++++++++++++++++
setenv configReportTaskVersion v1r0
setenv configReportTask configReport-EM2-${configReportTaskVersion}
setenv configReportVersion v1r0p0
setenv configReportUrl ConfigTables.html
#-------------------------------- configReport --------------------------------

#++++++++++++++++++++++++++++++++ digitization ++++++++++++++++++++++++++++++++
setenv digitizationTaskVersion v1r0
setenv digitizationTask digitization-EM2-${digitizationTaskVersion}
setenv Em2Version v0r0p0
setenv Em2Dir ${sasCmt}/Em2/${Em2Version}
setenv ldfToDigiCmt ${Em2Dir}/cmt
setenv ldfToDigiApp ${Em2Dir}/rh9_gcc32/Em2.exe
setenv ldfFileType LDFFITS
#-------------------------------- digitization --------------------------------

#++++++++++++++++++++++++++++++++ digiReport ++++++++++++++++++++++++++++++++++
setenv digiReportTask digiReport-EM2-v1r0
setenv TestReportVersion v2r0
setenv TestReportDir ${svacCmt}/TestReport/${TestReportVersion}
setenv digiReportCmt ${TestReportDir}/cmt
setenv digiReportApp ${TestReportDir}/rh9_gcc32/TestReport.exe
setenv digiRepDoxyFile ${TestReportDir}/src/ReportDoxyfile
setenv digiReportVersion v1r0p0
setenv digiReportUrl html/index.html
#-------------------------------- digiReport ----------------------------------

#++++++++++++++++++++++++++++++++ recon +++++++++++++++++++++++++++++++++++++++
setenv reconTask recon-EM2-v1r0
setenv reconCmt ${Em2Dir}/cmt
setenv reconApp ${Em2Dir}/rh9_gcc32/Em2.exe
#-------------------------------- recon ---------------------------------------

#++++++++++++++++++++++++++++++++ reconReport +++++++++++++++++++++++++++++++++
setenv reconReportTask reconReport-EM2-v1r0
setenv reconReportCmt ${TestReportDir}/cmt
setenv reconReportApp ${TestReportDir}/rh9_gcc32/TestReport.exe
setenv reconRepDoxyFile ${TestReportDir}/src/ReportDoxyfile
setenv reconReportVersion v1r0p0
setenv reconReportUrl html/index.html
#-------------------------------- reconReport ---------------------------------

#++++++++++++++++++++++++++++++++ svacTuple +++++++++++++++++++++++++++++++++++
setenv svacTupleTask svacTuple-EM2-v1r0
setenv RunRootAnalyzerVersion v1
setenv RunRootAnalyzerDir ${svacCmt}/EngineeringModelRoot/${RunRootAnalyzerVersion}
setenv svacTupleCmt ${RunRootAnalyzerDir}/cmt
setenv svacTupleApp ${RunRootAnalyzerDir}/rh9_gcc32/RunRootAnalyzer.exe
setenv svacTupleVersion emRootv0r0
#-------------------------------- svacTuple -----------------------------------
