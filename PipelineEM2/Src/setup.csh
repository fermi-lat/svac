#!/bin/csh

source /afs/slac.stanford.edu/g/glast/ground/scripts/user.cshrc

setenv CMTPATH /nfs/slac/g/svac/common/builds:/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0402p16

setenv eLogDir /nfs/slac/g/svac/common/builds/eLogFeeder/v1r1

setenv ldfToDigiCmt /nfs/farm/g/glast/u06/chen/glast_mc/EngineeringModel_v3r0402p16/Em2/v0r0p0/cmt
setenv ldfToDigiApp /nfs/farm/g/glast/u06/chen/glast_mc/EngineeringModel_v3r0402p16/Em2/v0r0p0/rh9_gcc32/Em2.exe

setenv configReportVersion v1r0

setenv DigiReportCmt /nfs/slac/g/svac/common/builds/TestReport/v2r0/cmt
setenv DigiReportApp /nfs/slac/g/svac/common/builds/TestReport/v2r0/rh9_gcc32/TestReport.exe
setenv digiReportVersion v1r0

setenv calibVersion calib-v1r0

setenv reconCmt /nfs/farm/g/glast/u06/chen/glast_mc/EngineeringModel_v3r0402p16/Em2/v0r0p0/cmt
setenv reconApp /nfs/farm/g/glast/u06/chen/glast_mc/EngineeringModel_v3r0402p16/Em2/v0r0p0/rh9_gcc32/Em2.exe

setenv ReconReportCmt /nfs/slac/g/svac/common/builds/TestReport/v2r0/cmt
setenv ReconReportApp /nfs/slac/g/svac/common/builds/TestReport/v2r0/rh9_gcc32/TestReport.exe
setenv reconReportVersion v1r0

setenv svacCmt /nfs/slac/g/svac/common/builds/EngineeringModelRoot/v1/cmt
setenv svacApp /nfs/slac/g/svac/common/builds/EngineeringModelRoot/v1/rh9_gcc32/RunRootAnalyzer.exe
