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
setenv ldfToDigiCmt $sasCmt/Em2/v0r0p0/cmt
setenv ldfToDigiApp $sasCmt/Em2/v0r0p0/rh9_gcc32/Em2.exe

setenv configReportTask configReport-EM2-v1r0
setenv configReportVersion v1r0
setenv configReportUrl ConfigTables.html

setenv digiReportTask digiReport-EM2-v1r0
setenv TestReportVersion v2r0
setenv digiReportCmt $svacCmt/TestReport/$TestReportVersion/cmt
setenv digiReportApp $svacCmt/TestReport/$TestReportVersion/rh9_gcc32/TestReport.exe
setenv digiRepDoxyFile $svacCmt/TestReport/$TestReportVersion/src/ReportDoxyfile
setenv digiReportVersion v1r0
setenv digiReportUrl html/index.html

setenv calibVersion calib-v1r0

setenv reconTask recon-EM2-v1r0
setenv Em2Version v0r0p0
setenv reconCmt $sasCmt/Em2/$Em2Version/cmt
setenv reconApp $sasCmt/Em2/$Em2Version/rh9_gcc32/Em2.exe

setenv reconReportTask reconReport-EM2-v1r0
setenv TestReportVersion v2r0
setenv reconReportCmt $svacCmt/TestReport/$TestReportVersion/cmt
setenv reconReportApp $svacCmt/TestReport/$TestReportVersion/rh9_gcc32/TestReport.exe
setenv reconRepDoxyFile $svacCmt/TestReport/$TestReportVersion/src/ReportDoxyfile
setenv reconReportVersion v1r0
setenv reconReportUrl html/index.html

setenv svacTupleTask svacTuple-EM2-v1r0
setenv RunRootAnalyzerVersion v1
setenv svacTupleCmt $svacCmt/EngineeringModelRoot/$RunRootAnalyzerVersion/cmt
setenv svacTupleApp $svacCmt/EngineeringModelRoot/$RunRootAnalyzerVersion/rh9_gcc32/RunRootAnalyzer.exe
setenv svacTupleVersion emRootv0r0
