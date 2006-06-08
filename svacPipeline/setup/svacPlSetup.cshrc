#!/bin/tcsh

# setup for SVAC pipeline

setenv svacVersion v1r030603p0

setenv GLASTROOT /afs/slac.stanford.edu/g/glast
source ${GLASTROOT}/ground/scripts/user.cshrc
setenv SVAC_CMTCONFIG rh9_gcc32opt
setenv SVAC_GLAST_EXT /afs/slac.stanford.edu/g/glast/ground/GLAST_EXT/${SVAC_CMTCONFIG}
setenv sasLocation /afs/slac.stanford.edu/g/glast/ground/releases/volume08
setenv EngineeringModelVersion v2r0903p0
setenv sasVersion BeamtestRelease-$EngineeringModelVersion
setenv sasCmt ${sasLocation}/${sasVersion}

setenv svacRoot /afs/slac.stanford.edu/g/glast/ground/PipelineConfig/BeamTest-tasks
setenv svacCmt ${svacRoot}/builds
setenv svacPlLib ${beamtestPlRoot}/lib

setenv CMTCONFIG ${SVAC_CMTCONFIG}
setenv GLAST_EXT ${SVAC_GLAST_EXT}
setenv CMTPATH ${svacCmt}:${sasCmt}

setenv diskHead /nfs/farm/g/glast
setenv webHead http://www.slac.stanford.edu/exp/glast/ground/LATSoft/nfsLinks
setenv dataDisk u34
setenv onlineDisk u25
setenv reconStageDir /afs/slac/g/glast/ground/PipelineStaging
setenv localDisk /scratch
setenv phase Integration
setenv subDir ${dataDisk}/${phase}
setenv dataHead ${diskHead}/${subDir}
setenv urlHead ${webHead}/${subDir}
setenv onlineHead ${diskHead}/${onlineDisk}/${phase}
setenv onlineSubDir rawData
setenv svacSubDir rootData
setenv rawUrl ${webHead}/${onlineDisk}/${phase}/${onlineSubDir}
setenv rootUrl ${webHead}/${subDir}/${svacSubDir}
setenv runSymbol '$(RUN_NAME)'

setenv cookedTail ${svacSubDir}/${runSymbol}
setenv emTail ${cookedTail}/${EngineeringModelVersion}

#setenv calibVersion calib-v1r0
setenv tkrCalibSerNo -9999
setenv calCalibSerNo -9999

#setenv calibTail ${emTail}/${calibVersion}

# Shouldn't normally use these, whoever is starting the run should do it.
#setenv SVAC_PDB_CONFIG /u/gl/glast/pdb_config/dpf_config_prod.csh
#setenv SVAC_PDB_CONFIG /u/gl/glast/pdb_config/dpf_config_test.csh

#setenv eLogTestOnly 1 # uncomment to disable eLog updates for testing

#++++++++++++++++++++++++++++++++ online ++++++++++++++++++++++++++++++++++++++
setenv onlineTaskVersion v2r4p1
setenv onlineTask online-${onlineTaskVersion}
setenv svacOnlineVersion ${svacVersion}
setenv svacOnlineDir ${beamtestPlRoot}/online
setenv svacOnlineScript ${svacOnlineDir}/SVACLaunch.pl
setenv onlineDataDir ${onlineSubDir}/${runSymbol}
setenv onlineDataDirFull ${onlineHead}/${onlineDataDir}
#-------------------------------- online --------------------------------------

#++++++++++++++++++++++++++++++++ eLogUpdate ++++++++++++++++++++++++++++++++++
setenv eLogTaskVersion ${svacVersion}
setenv eLogTaskLatte updateELogDB-latte-${eLogTaskVersion}
setenv eLogTaskLicos updateELogDB-licos-${eLogTaskVersion}
setenv eLogFeederVersion v2r3p2
setenv eLogDir ${svacCmt}/eLogFeeder/${eLogFeederVersion}
setenv eLogTaskDir ${beamtestPlRoot}/eLogUpdate
setenv eLogScript ${eLogTaskDir}/populateElogDb.pl
setenv decideDigiScript ${eLogTaskDir}/decideDigi.pl
setenv eLogDataDir ${cookedTail}
setenv eLogDataDirFull ${dataHead}/${eLogDataDir}
#-------------------------------- eLogUpdate ----------------------------------

#++++++++++++++++++++++++++++++++ configReport ++++++++++++++++++++++++++++++++
setenv configReportTaskVersion ${svacVersion}
setenv configReportTaskLatte configReport-latte-${configReportTaskVersion}
setenv configReportTaskLicos configReport-licos-${configReportTaskVersion}
setenv configReportVersion v4r0p2
setenv configReportUrl ConfigTables.html
setenv ConfigTablesDir ${svacCmt}/ConfigTables/${configReportVersion}
setenv configTaskDir ${beamtestPlRoot}/configReport
setenv configTablesScript ${ConfigTablesDir}/ConfigTables.py 
setenv configTablesDataDir ${cookedTail}/configReport/${configReportVersion}
setenv configTablesDataDirFull ${dataHead}/${configTablesDataDir}
#-------------------------------- configReport --------------------------------

#++++++++++++++++++++++++++++++++ digitization ++++++++++++++++++++++++++++++++
setenv digitizationTaskVersion ${svacVersion}
setenv digitizationTaskLatte digitization-latte-${digitizationTaskVersion}
setenv digitizationTaskLicos digitization-licos-${digitizationTaskVersion}
setenv Em2Version v6r16
setenv Em2Dir ${sasCmt}/Gleam/${Em2Version}
setenv ldfToDigiCmt ${Em2Dir}/cmt
setenv ldfToDigiApp ${Em2Dir}/rh9_gcc32opt/Gleam.exe
setenv ldfFileType LDFFITS
setenv digitizationTaskDir ${beamtestPlRoot}/digitization
setenv digitizationScript ${digitizationTaskDir}/ldfToDigi.pl
setenv decideReconScript ${digitizationTaskDir}/decideRecon.pl
setenv setEventsScript ${digitizationTaskDir}/setEvents.py
#setenv digitizationDataDir ${emTail}/grRoot
setenv digitizationDataDir ${emTail}/digi
setenv digitizationDataDirFull ${dataHead}/${digitizationDataDir}
#-------------------------------- digitization --------------------------------

#++++++++++++++++++++++++++++++++ digiReport ++++++++++++++++++++++++++++++++++
setenv digiReportTaskVersion ${svacVersion}
setenv digiReportTask digiReport-${digiReportTaskVersion}
setenv TestReportVersion v3r6p5
setenv TestReportDir ${svacCmt}/TestReport/${TestReportVersion}
setenv digiReportCmt ${TestReportDir}/cmt
setenv digiReportApp ${TestReportDir}/rh9_gcc32opt/TestReport.exe
setenv digiRepDoxyFile ${TestReportDir}/src/ReportDoxyfile
setenv latexHeaderFile ${TestReportDir}/src/latexHeader.tex
setenv digiReportUrl html/index.html
setenv digiReportTaskDir ${beamtestPlRoot}/digiReport
setenv digiReportScript ${digiReportTaskDir}/genDigiTestReport.pl
setenv digiReportDataDir ${emTail}/digiReport/${TestReportVersion}
setenv digiReportDataDirFull ${dataHead}/${digiReportDataDir}
#-------------------------------- digiReport ----------------------------------

#++++++++++++++++++++++++++++++++ recon +++++++++++++++++++++++++++++++++++++++
#setenv LATCalibRoot /nfs/slac/g/glast/calibrations/
setenv reconTaskVersion ${svacVersion}
setenv reconTask recon-${reconTaskVersion}
setenv reconCmt ${ldfToDigiCmt}
setenv reconApp ${ldfToDigiApp}
setenv reconTaskDir ${beamtestPlRoot}/recon
setenv reconSetupScript ${reconTaskDir}/setupRecon.py
setenv reconDoScript ${reconTaskDir}/doRecon.py
setenv reconMergeReconScript ${reconTaskDir}/mergeRecon.py
setenv hadd ${SVAC_GLAST_EXT}/ROOT/v4.02.00/root/bin/hadd
setenv haddMerge ${svacPlLib}/haddMerge.py
setenv haddWrapper ${svacPlLib}/haddWrapper.pl
setenv reconCleanupScript ${reconTaskDir}/cleanup.py
setenv reconOneScript ${reconTaskDir}/reconOne.csh
#setenv reconDataDir ${emTail}/grRoot
setenv reconDataDir ${emTail}/recon
setenv reconDataDirFull ${dataHead}/${reconDataDir}
setenv chunkQueue long
setenv chunkTime 10000 
setenv pldVersion v0r3
setenv pldLib ${svacCmt}/pipelineDatasets/${pldVersion}/${SVAC_CMTCONFIG}
#-------------------------------- recon ---------------------------------------

#++++++++++++++++++++++++++++++++ reconReport +++++++++++++++++++++++++++++++++
setenv reconReportTaskVersion ${svacVersion}
setenv reconReportTask reconReport-${reconReportTaskVersion}
setenv reconReportCmt ${digiReportCmt}
setenv reconReportApp ${digiReportApp}
setenv reconRepDoxyFile ${digiRepDoxyFile}
setenv reconReportUrl html/index.html
setenv reconReportTaskDir ${beamtestPlRoot}/reconReport
setenv reconReportScript ${reconReportTaskDir}/genReconTestReport.pl
setenv reconReportDataDir ${emTail}/reconReport/${TestReportVersion}
setenv reconReportDataDirFull ${dataHead}/${reconReportDataDir}
#-------------------------------- reconReport ---------------------------------

#++++++++++++++++++++++++++++++++ svacTuple +++++++++++++++++++++++++++++++++++
setenv svacTupleTaskVersion ${svacVersion}
setenv svacTupleTask svacTuple-${svacTupleTaskVersion}
setenv RunRootAnalyzerVersion v0r0p1
setenv RunRootAnalyzerDir ${sasCmt}/BeamTestTuple/${RunRootAnalyzerVersion}
setenv svacTupleCmt ${RunRootAnalyzerDir}/cmt
setenv svacTupleApp ${RunRootAnalyzerDir}/rh9_gcc32opt/RunRootAnalyzer.exe
#setenv svacTupleVersion emRootv0r0
setenv svacTupleTaskDir ${beamtestPlRoot}/svacTuple
setenv svacTupleScript ${svacTupleTaskDir}/RunRootAnalyzer.pl
setenv svacTupleDataDir ${emTail}/svacTuple/${RunRootAnalyzerVersion}
setenv svacTupleDataDirFull ${dataHead}/${svacTupleDataDir}
#-------------------------------- svacTuple -----------------------------------

#++++++++++++++++++++++++++++++++ many ++++++++++++++++++++++++++++++++++++++++
setenv taskLauncher ${svacPlLib}/TaskLaunch.pl
setenv urlUpdateWrapper ${svacPlLib}/urlWrapper.pl
setenv urlUpdateScript  ${svacPlLib}/updateUrl.py
setenv batchgroup glastdata
setenv eLogQuery ${svacPlLib}/queryElogReportTable.pl
setenv eLogUpdate ${svacPlLib}/updateElogReportTable.pl
setenv tryAFewTimes ${svacPlLib}/tryAFewTimes.csh
setenv deleter ${svacPlLib}/deleteWrapper.pl
setenv copier ${svacPlLib}/copyWrapper.pl
#-------------------------------- many ----------------------------------------

setenv ROOTSYS ${SVAC_GLAST_EXT}/ROOT/v4.02.00/root
setenv rootLib ${ROOTSYS}/lib

setenv SVACPYTHON ${ConfigTablesDir}:${eLogDir}:${svacPlLib}:${rootLib}
if ( ${?PYTHONPATH} == '1' ) then
    setenv PYTHONPATH ${SVACPYTHON}:${PYTHONPATH}
else
    setenv PYTHONPATH ${SVACPYTHON}
endif

setenv PATH ${PATH}:${svacPlLib}

setenv SVAC_LD_LIBARARY_PATH ${rootLib}:${sasCmt}/lib:${pldLib}
if ( ${?LD_LIBRARY_PATH} == '1' ) then
    setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:${SVAC_LD_LIBARARY_PATH}
else
    setenv LD_LIBRARY_PATH ${SVAC_LD_LIBARARY_PATH}
endif
