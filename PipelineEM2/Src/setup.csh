#!/bin/csh

source /afs/slac.stanford.edu/g/glast/ground/scripts/user.cshrc

setenv CMTPATH /nfs/slac/g/svac/common/builds:/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0402p16

setenv rootUrl /glast.u12/rootData

setenv eLogDir /nfs/slac/g/svac/common/builds/eLogFeeder/v1r1

setenv ldfToDigiCmt /nfs/farm/g/glast/u06/chen/glast_mc/EngineeringModel_v3r0402p16/Em2/v0r0p0/cmt
setenv ldfToDigiApp /nfs/farm/g/glast/u06/chen/glast_mc/EngineeringModel_v3r0402p16/Em2/v0r0p0/rh9_gcc32/Em2.exe
setenv ldfFile

setenv configReportVersion v1r0
setenv configReportFile
setenv configReportUrl

setenv DigiReportCmt /nfs/slac/g/svac/common/builds/TestReport/v2r0/cmt
setenv DigiReportApp /nfs/slac/g/svac/common/builds/TestReport/v2r0/rh9_gcc32/TestReport.exe
setenv digiReportVersion v1r0
setenv digiRepDoxyFile /nfs/slac/g/svac/common/builds/TestReport/v2r0/src/ReportDoxyfile
setenv digiReportFile
setenv digiReportUrl

setenv calibVersion calib-v1r0

setenv reconCmt /nfs/farm/g/glast/u06/chen/glast_mc/EngineeringModel_v3r0402p16/Em2/v0r0p0/cmt
setenv reconApp /nfs/farm/g/glast/u06/chen/glast_mc/EngineeringModel_v3r0402p16/Em2/v0r0p0/rh9_gcc32/Em2.exe
setenv reconFile

setenv reconReportCmt /nfs/slac/g/svac/common/builds/TestReport/v2r0/cmt
setenv reconReportApp /nfs/slac/g/svac/common/builds/TestReport/v2r0/rh9_gcc32/TestReport.exe
setenv reconRepDoxyFile /nfs/slac/g/svac/common/builds/TestReport/v2r0/src/ReportDoxyfile
setenv reconReportVersion v1r0
setenv reconReportFile
setenv reconReportUrl

setenv svacCmt /nfs/slac/g/svac/common/builds/EngineeringModelRoot/v1/cmt
setenv svacApp /nfs/slac/g/svac/common/builds/EngineeringModelRoot/v1/rh9_gcc32/RunRootAnalyzer.exe
setenv svacFile
