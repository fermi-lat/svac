#!/bin/tcsh

# setup for SVAC pipeline

setenv svacVersion v3r1p18

setenv GLASTROOT /afs/slac.stanford.edu/g/glast
source ${GLASTROOT}/ground/scripts/user.cshrc
setenv SVAC_CMTCONFIG rh9_gcc32opt
setenv SVAC_GLAST_EXT /nfs/farm/g/glast/u05/GLAST_EXT/${SVAC_CMTCONFIG}
setenv sasLocation /nfs/farm/g/glast/u09/builds/${SVAC_CMTCONFIG}/EngineeringModel
setenv EngineeringModelVersion v4r060302p23
setenv sasVersion EngineeringModel-$EngineeringModelVersion
setenv sasCmt ${sasLocation}/${sasVersion}

setenv svacRoot /nfs/slac/g/svac/common
setenv svacCmt ${svacRoot}/builds
# svacPlRoot is set in the pipeline
#setenv svacPlRoot ${svacRoot}/pipeline/EM2/svacPipeline
setenv svacPlLib ${svacPlRoot}/lib

setenv CMTPATH ${svacCmt}:${sasCmt}

setenv diskHead /nfs/farm/g/glast
setenv webHead http://www.slac.stanford.edu/exp/glast/ground/LATSoft/nfsLinks
setenv dataDisk u16
setenv phase Integration
setenv subDir ${dataDisk}/${phase}
setenv dataHead ${diskHead}/${subDir}
setenv urlHead ${webHead}/${subDir}
setenv onlineSubDir rawData
setenv svacSubDir rootData
setenv rawUrl ${webHead}/${subDir}/${onlineSubDir}
setenv rootUrl ${webHead}/${subDir}/${svacSubDir}
setenv runSymbol '$(RUN_NAME)'

setenv cookedTail ${svacSubDir}/${runSymbol}
setenv emTail ${cookedTail}/${EngineeringModelVersion}

setenv calibVersion calib-v1r0
setenv tkrCalibSerNo -9999
setenv calCalibSerNo -9999

setenv calibTail ${emTail}/${calibVersion}

#++++++++++++++++++++++++++++++++ online ++++++++++++++++++++++++++++++++++++++
setenv onlineTaskVersion v2r1p1
setenv onlineTask online-${onlineTaskVersion}
setenv svacOnlineVersion ${svacVersion}
setenv svacOnlineDir ${svacPlRoot}/online
setenv svacOnlineScript ${svacOnlineDir}/SVACLaunch.pl
setenv onlineDataDir ${onlineSubDir}/${runSymbol}
setenv onlineDataDirFull ${dataHead}/${onlineDataDir}
#-------------------------------- online --------------------------------------

#++++++++++++++++++++++++++++++++ eLogUpdate ++++++++++++++++++++++++++++++++++
setenv eLogTaskVersion ${svacVersion}
setenv eLogTask updateELogDB-${eLogTaskVersion}
setenv eLogFeederVersion v2r2p6
setenv eLogDir ${svacCmt}/eLogFeeder/${eLogFeederVersion}
setenv eLogTaskDir ${svacPlRoot}/eLogUpdate
setenv eLogScript ${eLogTaskDir}/populateElogDb.pl
setenv decideDigiScript ${eLogTaskDir}/decideDigi.pl
setenv eLogDataDir ${cookedTail}
setenv eLogDataDirFull ${dataHead}/${eLogDataDir}
#-------------------------------- eLogUpdate ----------------------------------

#++++++++++++++++++++++++++++++++ configReport ++++++++++++++++++++++++++++++++
setenv configReportTaskVersion ${svacVersion}
setenv configReportTask configReport-${configReportTaskVersion}
setenv configReportVersion v3r1p4
setenv configReportUrl ConfigTables.html
setenv ConfigTablesDir ${svacCmt}/ConfigTables/${configReportVersion}/Src
setenv configTaskDir ${svacPlRoot}/configReport
setenv configTablesScript ${ConfigTablesDir}/ConfigTables.py 
setenv configTablesDataDir ${cookedTail}/configReport/${configReportVersion}
setenv configTablesDataDirFull ${dataHead}/${configTablesDataDir}
#-------------------------------- configReport --------------------------------

#++++++++++++++++++++++++++++++++ digitization ++++++++++++++++++++++++++++++++
setenv digitizationTaskVersion ${svacVersion}
setenv digitizationTask digitization-${digitizationTaskVersion}
setenv Em2Version v2r26
setenv Em2Dir ${sasCmt}/LatIntegration/${Em2Version}
setenv ldfToDigiCmt ${Em2Dir}/cmt
setenv ldfToDigiApp ${Em2Dir}/rh9_gcc32opt/LatIntegration.exe
setenv ldfFileType LDFFITS
setenv digitizationTaskDir ${svacPlRoot}/digitization
setenv digitizationScript ${digitizationTaskDir}/ldfToDigi.pl
setenv decideReconScript ${digitizationTaskDir}/decideRecon.pl
setenv digitizationDataDir ${emTail}/grRoot
setenv digitizationDataDirFull ${dataHead}/${digitizationDataDir}
#-------------------------------- digitization --------------------------------

#++++++++++++++++++++++++++++++++ digiReport ++++++++++++++++++++++++++++++++++
setenv digiReportTaskVersion ${svacVersion}
setenv digiReportTask digiReport-${digiReportTaskVersion}
setenv TestReportVersion v3r2p7
setenv TestReportDir ${svacCmt}/TestReport/${TestReportVersion}
setenv digiReportCmt ${TestReportDir}/cmt
setenv digiReportApp ${TestReportDir}/rh9_gcc32opt/TestReport.exe
setenv digiRepDoxyFile ${TestReportDir}/src/ReportDoxyfile
setenv latexHeaderFile ${TestReportDir}/src/latexHeader.tex
setenv digiReportVersion v1r0p0
setenv digiReportUrl html/index.html
setenv digiReportTaskDir ${svacPlRoot}/digiReport
setenv digiReportScript ${digiReportTaskDir}/genDigiTestReport.pl
setenv digiReportDataDir ${emTail}/digiReport/${TestReportVersion}
setenv digiReportDataDirFull ${dataHead}/${digiReportDataDir}
#-------------------------------- digiReport ----------------------------------

#++++++++++++++++++++++++++++++++ recon +++++++++++++++++++++++++++++++++++++++
setenv LATCalibRoot /nfs/slac/g/glast/calibrations/
setenv reconTaskVersion ${svacVersion}
setenv reconTask recon-${reconTaskVersion}
setenv reconCmt ${Em2Dir}/cmt
setenv reconApp ${Em2Dir}/rh9_gcc32opt/LatIntegration.exe
setenv reconTaskDir ${svacPlRoot}/recon
setenv reconScript ${reconTaskDir}/recon.pl
setenv reconDataDir ${calibTail}/grRoot
setenv reconDataDirFull ${dataHead}/${reconDataDir}
#-------------------------------- recon ---------------------------------------

#++++++++++++++++++++++++++++++++ reconReport +++++++++++++++++++++++++++++++++
setenv reconReportTaskVersion ${svacVersion}
setenv reconReportTask reconReport-${reconReportTaskVersion}
setenv reconReportCmt ${TestReportDir}/cmt
setenv reconReportApp ${TestReportDir}/rh9_gcc32opt/TestReport.exe
setenv reconRepDoxyFile ${TestReportDir}/src/ReportDoxyfile
setenv reconReportVersion v1r0p0
setenv reconReportUrl html/index.html
setenv reconReportTaskDir ${svacPlRoot}/reconReport
setenv reconReportScript ${reconReportTaskDir}/genReconTestReport.pl
setenv reconReportDataDir ${calibTail}/reconReport/${TestReportVersion}
setenv reconReportDataDirFull ${dataHead}/${reconReportDataDir}
#-------------------------------- reconReport ---------------------------------

#++++++++++++++++++++++++++++++++ svacTuple +++++++++++++++++++++++++++++++++++
setenv svacTupleTaskVersion ${svacVersion}
setenv svacTupleTask svacTuple-${svacTupleTaskVersion}
setenv RunRootAnalyzerVersion v1r3p18
setenv RunRootAnalyzerDir ${svacCmt}/EngineeringModelRoot/${RunRootAnalyzerVersion}
setenv svacTupleCmt ${RunRootAnalyzerDir}/cmt
setenv svacTupleApp ${RunRootAnalyzerDir}/rh9_gcc32opt/RunRootAnalyzer.exe
setenv svacTupleVersion emRootv0r0
setenv svacTupleTaskDir ${svacPlRoot}/svacTuple
setenv svacTupleScript ${svacTupleTaskDir}/RunRootAnalyzer.pl
setenv svacTupleDataDir ${calibTail}/svacTuple/${svacTupleVersion}
setenv svacTupleDataDirFull ${dataHead}/${svacTupleDataDir}
#-------------------------------- svacTuple -----------------------------------

#++++++++++++++++++++++++++++++++ many ++++++++++++++++++++++++++++++++++++++++
setenv taskLauncher ${svacPlLib}/TaskLaunch.pl
setenv urlUpdateWrapper ${svacPlLib}/urlWrapper.pl
setenv urlUpdateScript  ${svacPlLib}/updateUrl.py
setenv batchgroup glastdata
setenv eLogQuery ${svacPlLib}/queryElogReportTable.pl
setenv eLogUpdate ${svacPlLib}/updateElogReportTable.pl
#-------------------------------- many ----------------------------------------

setenv SVACPYTHON ${ConfigTablesDir}:${eLogDir}:${svacPlLib}
if ( ${?PYTHONPATH} == '1' ) then
    setenv PYTHONPATH ${SVACPYTHON}:${PYTHONPATH}
else
    setenv PYTHONPATH ${SVACPYTHON}
endif

setenv PATH ${PATH}:${svacPlLib}
