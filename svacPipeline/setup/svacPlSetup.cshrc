#!/bin/tcsh

# setup for SVAC pipeline

setenv svacVersion v4r0p2

setenv GLASTROOT /afs/slac.stanford.edu/g/glast
source ${GLASTROOT}/ground/scripts/user.cshrc
setenv SVAC_CMTCONFIG rh9_gcc32opt
setenv SVAC_GLAST_EXT /afs/slac.stanford.edu/g/glast/ground/GLAST_EXT/${SVAC_CMTCONFIG}
setenv sasLocation /afs/slac.stanford.edu/g/glast/ground/releases/volume14
setenv EngineeringModelVersion v13r6p1
setenv sasVersion GlastRelease-$EngineeringModelVersion
setenv sasCmt ${sasLocation}/${sasVersion}

setenv svacRoot /afs/slac.stanford.edu/g/glast/ground/PipelineConfig/EM-tasks
# We are redefining svacPlRoot here
setenv svacPlRoot ${svacRoot}/svacPipeline/${svacVersion}
setenv svacCmt ${svacRoot}/builds
setenv svacPlLib ${svacPlRoot}/lib

setenv CMTCONFIG ${SVAC_CMTCONFIG}
setenv GLAST_EXT ${SVAC_GLAST_EXT}
setenv CMTPATH ${svacCmt}:${sasCmt}

setenv diskHead /nfs/farm/g/glast
setenv webHead http://www.slac.stanford.edu/exp/glast/ground/LATSoft/nfsLinks
setenv ftpHead ftp://ftp-glast.slac.stanford.edu/glast.
setenv dataDisk u52
setenv onlineDisk u52
setenv reconStageDir /afs/slac/g/glast/ground/PipelineStaging2/svac
setenv localDisk /scratch
setenv phase Integration
setenv subDir ${dataDisk}/${phase}
setenv dataHead ${diskHead}/${subDir}
setenv onlineHead ${diskHead}/${onlineDisk}/${phase}
setenv onlineSubDir rawData
setenv svacSubDir rootData
setenv rawUrl ${webHead}/${onlineDisk}/${phase}/${onlineSubDir}
setenv rootUrl ${webHead}/${subDir}/${svacSubDir}
setenv rootFtp ${ftpHead}${subDir}/${svacSubDir}
setenv runSymbol '$(RUN_NAME)'

setenv cookedTail ${svacSubDir}/${runSymbol}
setenv emTail ${cookedTail}/${EngineeringModelVersion}

setenv tkrCalibSerNo -9999
setenv calCalibSerNo -9999

# uncomment to disable temp file deletion and eLog updates 
# for testing
#setenv svacTestMode 1 

setenv ROOTSYS ${SVAC_GLAST_EXT}/ROOT/v5.16.00-gl1/root
setenv rootLib ${ROOTSYS}/lib
setenv haddSys ${SVAC_GLAST_EXT}/ROOT/v5.16.00-gl1/root
setenv haddLib ${haddSys}/lib

setenv emiBase ${LATMonRoot}/TestReports/GD/EMC-EMI

#++++++++++++++++++++++++++++++++ online ++++++++++++++++++++++++++++++++++++++
setenv onlineTaskVersion v2r4p1
setenv onlineTask online-${onlineTaskVersion}
setenv svacOnlineVersion ${svacVersion}
setenv svacOnlineDir ${svacPlRoot}/online
setenv svacOnlineScript ${svacOnlineDir}/SVACLaunch.pl
setenv onlineDataDir ${onlineSubDir}/${runSymbol}
setenv onlineDataDirFull ${onlineHead}/${onlineDataDir}
#-------------------------------- online --------------------------------------

#++++++++++++++++++++++++++++++++ eLogUpdate ++++++++++++++++++++++++++++++++++
setenv eLogTaskVersion ${svacVersion}
setenv eLogTask updateELogDB-${eLogTaskVersion}
setenv eLogFeederVersion v2r3p3
setenv eLogDir ${svacCmt}/eLogFeeder/${eLogFeederVersion}
setenv eLogTaskDir ${svacPlRoot}/eLogUpdate
setenv eLogScript ${eLogTaskDir}/populateElogDb.pl
setenv decideDigiScript ${eLogTaskDir}/decideDigi.pl
setenv eLogDataDir ${cookedTail}
setenv eLogDataDirFull ${dataHead}/${eLogDataDir}
#-------------------------------- eLogUpdate ----------------------------------

#++++++++++++++++++++++++++++++++ digitization ++++++++++++++++++++++++++++++++
setenv digitizationTaskVersion ${svacVersion}
setenv digitizationTask digitization-${digitizationTaskVersion}
setenv Em2Version v6r33p7
setenv Em2Dir ${sasCmt}/Gleam/${Em2Version}
setenv ldfToDigiCmt ${Em2Dir}/cmt
setenv ldfToDigiApp ${Em2Dir}/${SVAC_CMTCONFIG}/Gleam.exe
setenv ldfFileType LDFFITS
setenv digitizationTaskDir ${svacPlRoot}/digitization
setenv digitizationScript ${digitizationTaskDir}/ldfToDigi.pl
setenv setEventsScript ${digitizationTaskDir}/setEvents.py
setenv digitizationDataDir ${emTail}/digi
setenv digitizationDataDirFull ${dataHead}/${digitizationDataDir}
#-------------------------------- digitization --------------------------------

#++++++++++++++++++++++++++++++++ digiReport ++++++++++++++++++++++++++++++++++
setenv digiReportTaskVersion ${svacVersion}
setenv digiReportTask digiReport-${digiReportTaskVersion}
setenv TestReportVersion v4r1
setenv TestReportDir ${svacCmt}/TestReport/${TestReportVersion}
setenv digiReportCmt ${TestReportDir}/cmt
setenv digiReportApp ${TestReportDir}/${SVAC_CMTCONFIG}/TestReport.exe
setenv digiRepDoxyFile ${TestReportDir}/src/ReportDoxyfile
setenv latexHeaderFile ${TestReportDir}/src/latexHeader.tex
setenv digiReportVersion ${TestReportVersion}
setenv digiReportUrl html/index.html
setenv digiReportTaskDir ${svacPlRoot}/digiReport
setenv digiReportScript ${digiReportTaskDir}/genDigiTestReport.pl
setenv digiReportDataDir ${emTail}/digiReport/${digiReportVersion}
setenv digiReportDataDirFull ${dataHead}/${digiReportDataDir}
setenv tkrHistDir ${emiBase}/TKR
setenv tkrCopyLimit 1800
setenv tkrCopyScript ${svacPlLib}/copyTkr.pl
#-------------------------------- digiReport ----------------------------------

#++++++++++++++++++++++++++++++++ configReport ++++++++++++++++++++++++++++++++
setenv configReportTaskVersion ${svacVersion}
setenv configReportTask configReport-${configReportTaskVersion}
setenv configReportVersion v1r4p1
#setenv configReportUrl ConfigTables.html
setenv configReportUrl ''
setenv configDataDir ${sasCmt}/configData/${configReportVersion}
setenv configTaskDir ${svacPlRoot}/configReport
setenv getConfigKey ${configTaskDir}/getConfigKey.C
setenv configDataCmt ${configDataDir}/cmt
setenv configDataBinDir ${configDataDir}/${SVAC_CMTCONFIG}
setenv ConfigXml2Root ${configDataBinDir}/ConfigXml2Root.exe
setenv dumpGemConfiguration ${configDataBinDir}/dumpGemConfiguration.exe
setenv configTablesDataDir ${cookedTail}/configReport/${configReportVersion}
setenv configTablesDataDirFull ${dataHead}/${configTablesDataDir}
#-------------------------------- configReport --------------------------------

#++++++++++++++++++++++++++++++++ recon +++++++++++++++++++++++++++++++++++++++
setenv reconTaskVersion ${svacVersion}
setenv reconTask recon-${reconTaskVersion}
setenv reconCmt ${ldfToDigiCmt}
setenv reconApp ${ldfToDigiApp}
setenv reconTaskDir ${svacPlRoot}/recon
setenv reconSetupScript ${reconTaskDir}/setupRecon.py
setenv reconDoScript ${reconTaskDir}/doRecon.py
setenv reconMergeReconScript ${reconTaskDir}/mergeRecon.py
setenv hadd ${haddSys}/bin/hadd
setenv haddMerge ${svacPlLib}/haddMerge.py
setenv haddWrapper ${svacPlLib}/haddWrapper.pl
setenv reconCleanupScript ${reconTaskDir}/cleanup.py
setenv reconOneScript ${reconTaskDir}/reconOne.csh
setenv reconDataDir ${emTail}/recon
setenv reconDataDirFull ${dataHead}/${reconDataDir}
setenv chunkQueue xlong
setenv chunkTime 60000
setenv chunkArch linux32
setenv pldVersion v0r4
#setenv pldLib ${svacCmt}/pipelineDatasets/${pldVersion}/${SVAC_CMTCONFIG}
setenv pldLib ${svacCmt}/lib
setenv doneUsingRecon zzzDone
#-------------------------------- recon ---------------------------------------

#++++++++++++++++++++++++++++++++ reconReport +++++++++++++++++++++++++++++++++
setenv reconReportTaskVersion ${svacVersion}
setenv reconReportTask reconReport-${reconReportTaskVersion}
setenv reconReportCmt ${digiReportCmt}
setenv reconReportApp ${digiReportApp}
setenv reconRepDoxyFile ${digiRepDoxyFile}
setenv reconReportVersion ${digiReportVersion}
setenv reconReportUrl ${digiReportUrl}
setenv reconReportTaskDir ${svacPlRoot}/reconReport
setenv reconReportScript ${reconReportTaskDir}/genReconTestReport.pl
setenv reconReportDataDir ${emTail}/reconReport/${reconReportVersion}
setenv reconReportDataDirFull ${dataHead}/${reconReportDataDir}
#-------------------------------- reconReport ---------------------------------

#++++++++++++++++++++++++++++++++ svacTuple +++++++++++++++++++++++++++++++++++
setenv svacTupleTaskVersion ${svacVersion}
setenv svacTupleTask svacTuple-${svacTupleTaskVersion}
setenv RunRootAnalyzerVersion v3r9p3
setenv RunRootAnalyzerDir ${svacCmt}/EngineeringModelRoot/${RunRootAnalyzerVersion}
setenv svacTupleCmt ${RunRootAnalyzerDir}/cmt
setenv svacTupleApp ${RunRootAnalyzerDir}/${SVAC_CMTCONFIG}/RunRootAnalyzer.exe
setenv svacTupleTaskDir ${svacPlRoot}/svacTuple
setenv svacTupleScript ${svacTupleTaskDir}/RunRootAnalyzer.pl
setenv svacTupleDataDir ${emTail}/svacTuple/${RunRootAnalyzerVersion}
setenv svacTupleDataDirFull ${dataHead}/${svacTupleDataDir}
#-------------------------------- svacTuple -----------------------------------

#++++++++++++++++++++++++++++++++ tkrReport +++++++++++++++++++++++++++++++++++
setenv tkrReportTaskVersion ${svacVersion}
setenv tkrReportTask tkrReport-${tkrReportTaskVersion}
setenv calibTkrUtilVersion v1r7p1
setenv tkrReportUrl index.html
setenv calibTkrUtilDir ${sasCmt}/calibTkrUtil/${calibTkrUtilVersion}
setenv tkrReportCmt ${calibTkrUtilDir}/cmt
setenv tkrReportApp ${calibTkrUtilDir}/${SVAC_CMTCONFIG}/genTkrNoiseRep.exe
setenv tkrReportTaskDir ${svacPlRoot}/tkrReport
setenv tkrReportDataDir ${emTail}/tkrReport/${calibTkrUtilVersion}
setenv tkrReportDataDirFull ${dataHead}/${tkrReportDataDir}
#-------------------------------- tkrReport -----------------------------------

#++++++++++++++++++++++++++++++++ acdReport +++++++++++++++++++++++++++++++++++
setenv acdReportTaskVersion ${svacVersion}
setenv acdReportTask acdReport-${acdReportTaskVersion}
setenv monitorVersion mk20070719
setenv monitorDir ${svacCmt}/Monitor/${monitorVersion}
setenv monitorCmt ${monitorDir}/cmt
setenv monitorApp ${monitorDir}/${SVAC_CMTCONFIG}/runStrip_t.exe
setenv dataMonitoringVersion acdemi2
setenv dataMonitoringDir ${svacCmt}/dataMonitoring/Common/${dataMonitoringVersion}
setenv dataMonitoringCmt ${dataMonitoringDir}/cmt
setenv dataMonitoringApp ${dataMonitoringDir}/python/pAlarmHandler.py
setenv acdReportTaskDir ${svacPlRoot}/acdReport
setenv acdMonitorScript ${acdReportTaskDir}/runStrip.pl
setenv acdMonitorJo ${acdReportTaskDir}/jobOptions.xml
setenv acdAlarmScript ${acdReportTaskDir}/alarmHandler.pl
setenv acdAlarmJo ${dataMonitoringDir}/xml/configacd.xml
setenv acdReportDataDir ${emTail}/acdReport/${monitorVersion}
setenv acdReportDataDirFull ${dataHead}/${acdReportDataDir}
setenv acdReportDestination ${emiBase}/ACD
#-------------------------------- acdReport -----------------------------------

#++++++++++++++++++++++++++++++++ many ++++++++++++++++++++++++++++++++++++++++
setenv taskLaunchWrapper ${svacPlLib}/LaunchWrapper.pl
setenv taskLauncher ${svacPlLib}/TaskLaunch.pl
setenv urlUpdateWrapper ${svacPlLib}/urlWrapper.pl
setenv urlUpdateScript  ${svacPlLib}/updateUrl.py
setenv batchgroup glastdata
setenv eLogQuery ${svacPlLib}/queryElogReportTable.pl
setenv eLogUpdate ${svacPlLib}/updateElogReportTable.pl
setenv tryAFewTimes ${svacPlLib}/tryAFewTimes.csh
setenv deleter ${svacPlLib}/deleteWrapper.pl
setenv copier ${svacPlLib}/copyWrapper.pl
setenv cleanupOne ${svacPlLib}/_cleanupOne.csh
setenv htAccess ${svacPlRoot}/setup/htaccess
setenv finalCleanup ${svacPlLib}/finalCleanup.pl
setenv decideReconScript ${svacPlLib}/decideRecon.pl
#-------------------------------- many ----------------------------------------

setenv SVACPYTHON ${eLogDir}:${svacPlLib}:${rootLib}
if ( ${?PYTHONPATH} == '1' ) then
    setenv PYTHONPATH ${SVACPYTHON}:${PYTHONPATH}
else
    setenv PYTHONPATH ${SVACPYTHON}
endif

setenv PATH ${PATH}:${svacPlLib}:${ROOTSYS}/bin

setenv SVAC_LD_LIBRARY_PATH ${rootLib}:${sasCmt}/lib:${pldLib}
if ( ${?LD_LIBRARY_PATH} == '1' ) then
    setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:${SVAC_LD_LIBRARY_PATH}
else
    setenv LD_LIBRARY_PATH ${SVAC_LD_LIBRARY_PATH}
endif
