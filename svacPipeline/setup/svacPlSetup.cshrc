#!/bin/sh

setenv GLASTROOT /afs/slac.stanford.edu/g/glast
source $GLASTROOT/ground/scripts/user.cshrc

setenv svacRoot /nfs/slac/g/svac/common
setenv svacCmt $svacRoot/builds
setenv sasCmt /nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0402p16
setenv svacPlRoot $svacRoot/pipeline/v1r0p0
setenv svacPlLib $svacPlRoot/lib

setenv CMTPATH $svacCmt:$sasCmt

setenv rootUrl /glast.u12/EM2/rootData

setenv eLogTask updateELogDB-EM2-v1r0
setenv eLogFeederVersion v1r1
setenv eLogDir $svacCmt/eLogFeeder/$eLogFeederVersion

setenv digitizationTask digitization-EM2-v1r0
setenv Em2Version v0r0p0
setenv Em2Dir $sasCmt/Em2/$Em2Version
setenv ldfToDigiCmt $Em2Dir/cmt
setenv ldfToDigiApp $Em2Dir/rh9_gcc32/Em2.exe

setenv configReportTask configReport-EM2-v1r0
setenv configReportVersion v1r0p0
setenv configReportUrl ConfigTables.html

setenv digiReportTask digiReport-EM2-v1r0
setenv TestReportVersion v2r0
setenv TestReportDir $svacCmt/TestReport/$TestReportVersion
setenv digiReportCmt $TestReportDir/cmt
setenv digiReportApp $TestReportDir/rh9_gcc32/TestReport.exe
setenv digiRepDoxyFile $TestReportDir/src/ReportDoxyfile
setenv digiReportVersion v1r0p0
setenv digiReportUrl html/index.html

setenv calibVersion calib-v1r0

setenv reconTask recon-EM2-v1r0
setenv reconCmt $Em2Dir/cmt
setenv reconApp $Em2Dir/rh9_gcc32/Em2.exe

setenv reconReportTask reconReport-EM2-v1r0
setenv reconReportCmt $TestReportDir/cmt
setenv reconReportApp $TestReportDir/rh9_gcc32/TestReport.exe
setenv reconRepDoxyFile $TestReportDir/src/ReportDoxyfile
setenv reconReportVersion v1r0p0
setenv reconReportUrl html/index.html

setenv svacTupleTask svacTuple-EM2-v1r0
setenv RunRootAnalyzerVersion v1
setenv RunRootAnalyzerDir $svacCmt/EngineeringModelRoot/$RunRootAnalyzerVersion
setenv svacTupleCmt $RunRootAnalyzerDir/cmt
setenv svacTupleApp $RunRootAnalyzerDir/rh9_gcc32/RunRootAnalyzer.exe
setenv svacTupleVersion emRootv0r0
