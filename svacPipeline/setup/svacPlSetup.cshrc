#!/bin/sh

setenv GLASTROOT /afs/slac.stanford.edu/g/glast
source $GLASTROOT/ground/scripts/user.cshrc

setenv svacRoot /nfs/slac/g/svac/common
setenv svacCmt $svacRoot/builds
setenv svacPlRoot $svacRoot/pipeline/v1r0p0
setenv sasCmt /nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0402p16

setenv CMTPATH $svacCmt:$sasCmt

setenv rootUrl /glast.u12/EM2/rootData

setenv eLogTask updateELogDB-EM2-v1r0
setenv eLogDir $svacCmt/eLogFeeder/v1r1

setenv ldfToDigiCmt /nfs/farm/g/glast/u06/chen/glast_mc/EngineeringModel_v3r0402p16/Em2/v0r0p0/cmt
setenv ldfToDigiApp /nfs/farm/g/glast/u06/chen/glast_mc/EngineeringModel_v3r0402p16/Em2/v0r0p0/rh9_gcc32/Em2.exe

setenv configReportTask configReport-EM2-v1r0
setenv configReportVersion v1r0
setenv configReportUrl ConfigTables.html

setenv digiReportTask digiReport-EM2-v1r0
setenv digiReportCmt $svacCmt/TestReport/v2r0/cmt
setenv digiReportApp $svacCmt/TestReport/v2r0/rh9_gcc32/TestReport.exe
setenv digiRepDoxyFile $svacCmt/TestReport/v2r0/src/ReportDoxyfile
setenv digiReportVersion v1r0
setenv digiReportUrl html/index.html

setenv calibVersion calib-v1r0

setenv reconTask recon-EM2-v1r0
setenv reconCmt /nfs/farm/g/glast/u06/chen/glast_mc/EngineeringModel_v3r0402p16/Em2/v0r0p0/cmt
setenv reconApp /nfs/farm/g/glast/u06/chen/glast_mc/EngineeringModel_v3r0402p16/Em2/v0r0p0/rh9_gcc32/Em2.exe

setenv reconReportTask reconReport-EM2-v1r0
setenv reconReportCmt $svacCmt/TestReport/v2r0/cmt
setenv reconReportApp $svacCmt/TestReport/v2r0/rh9_gcc32/TestReport.exe
setenv reconRepDoxyFile $svacCmt/TestReport/v2r0/src/ReportDoxyfile
setenv reconReportVersion v1r0
setenv reconReportUrl html/index.html

setenv svacTupleTask svacTuple-EM2-v1r0
setenv svacTupleCmt $svacCmt/EngineeringModelRoot/v1/cmt
setenv svacTupleApp $svacCmt/EngineeringModelRoot/v1/rh9_gcc32/RunRootAnalyzer.exe
setenv svacTupleVersion emRootv0r0
