#!/bin/sh

CMTPATH=/nfs/slac/g/svac/common/builds:/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0402p16 ; export CMTPATH

rootUrl=/glast.u12/rootData ; export rootUrl

eLogDir=/nfs/slac/g/svac/common/builds/eLogFeeder/v1r1 ; export eLogDir

ldfToDigiCmt=/nfs/farm/g/glast/u06/chen/glast_mc/EngineeringModel_v3r0402p16/Em2/v0r0p0/cmt ; export ldfToDigiCmt
ldfToDigiApp=/nfs/farm/g/glast/u06/chen/glast_mc/EngineeringModel_v3r0402p16/Em2/v0r0p0/rh9_gcc32/Em2.exe ; export ldfToDigiApp

configReportVersion=v1r0 ; export configReportVersion
configReportUrl=ConfigTables.html ; export configReportUrl

DigiReportCmt=/nfs/slac/g/svac/common/builds/TestReport/v2r0/cmt ; export DigiReportCmt
DigiReportApp=/nfs/slac/g/svac/common/builds/TestReport/v2r0/rh9_gcc32/TestReport.exe ; export DigiReportApp
digiRepDoxyFile=/nfs/slac/g/svac/common/builds/TestReport/v2r0/src/ReportDoxyfile ; export digiRepDoxyFile
digiReportUrl=html/index.html ; export digiReportUrl

calibVersion=calib-v1r0 ; export calibVersion

reconCmt=/nfs/farm/g/glast/u06/chen/glast_mc/EngineeringModel_v3r0402p16/Em2/v0r0p0/cmt ; export reconCmt
reconApp=/nfs/farm/g/glast/u06/chen/glast_mc/EngineeringModel_v3r0402p16/Em2/v0r0p0/rh9_gcc32/Em2.exe ; export reconApp

reconReportCmt=/nfs/slac/g/svac/common/builds/TestReport/v2r0/cmt ; export reconReportCmt
reconReportApp=/nfs/slac/g/svac/common/builds/TestReport/v2r0/rh9_gcc32/TestReport.exe ; export reconReportApp
reconRepDoxyFile=/nfs/slac/g/svac/common/builds/TestReport/v2r0/src/ReportDoxyfile ; export reconRepDoxyFile
reconReportUrl=html/index.html ; export reconReportUrl

svacCmt=/nfs/slac/g/svac/common/builds/EngineeringModelRoot/v1/cmt ; export svacCmt
svacApp=/nfs/slac/g/svac/common/builds/EngineeringModelRoot/v1/rh9_gcc32/RunRootAnalyzer.exe ; export svacApp
