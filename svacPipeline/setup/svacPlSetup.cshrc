#!/bin/tcsh

# setup for SVAC pipeline

setenv GLASTROOT /afs/slac.stanford.edu/g/glast
source ${GLASTROOT}/ground/scripts/user.cshrc
setenv CMTCONFIG rh9_gcc32opt
setenv GLAST_EXT /nfs/farm/g/glast/u05/GLAST_EXT/rh9_gcc32opt
setenv sasLocation /nfs/farm/g/glast/u09/builds/rh9_gcc32opt/EngineeringModel
setenv EngineeringModelVersion v3r0407p13
setenv sasVersion EngineeringModel-$EngineeringModelVersion
setenv sasCmt ${sasLocation}/${sasVersion}

setenv svacRoot /nfs/slac/g/svac/common
setenv svacCmt ${svacRoot}/builds
# svacPlRoot is set in the pipeline
#setenv svacPlRoot ${svacRoot}/pipeline/EM2/svacPipeline
setenv svacPlLibVersion v3r0p0
setenv svacPlLib ${svacPlRoot}/lib/${svacPlLibVersion}

setenv CMTPATH ${svacCmt}:${sasCmt}

#setenv dataHead /nfs/farm/g/glast/u12/Integration
setenv dataHead /nfs/farm/g/glast/u12
setenv rootUrl /glast.u12/Integration/rootData
setenv rawUrl /glast.u12/EM2/rawData

setenv cookedTail Integration/'$(RUN_NAME)'
setenv emTail ${cookedRoot}/${EngineeringModelVersion}

setenv calibVersion calib-v1r0
setenv tkrCalibSerNo -9999
setenv calCalibSerNo -9999

setenv calibTail ${cookedRoot}/${calibVersion}

#++++++++++++++++++++++++++++++++ online ++++++++++++++++++++++++++++++++++++++
setenv svacOnlineVersion v3r0p0
setenv svacOnlineDir ${svacPlRoot}/online/${svacOnlineVersion}
setenv svacOnlineScript ${svacOnlineDir}/SVACLaunch.pl
setenv onlineDataDir EM2/rawData/'$(RUN_NAME)'
#-------------------------------- online --------------------------------------

#++++++++++++++++++++++++++++++++ eLogUpdate ++++++++++++++++++++++++++++++++++
setenv eLogTaskVersion v3r0p0
setenv eLogTask updateELogDB-EM2-${eLogTaskVersion}
setenv eLogFeederVersion v2r0
setenv eLogDir ${svacCmt}/eLogFeeder/${eLogFeederVersion}
setenv eLogTaskDir ${svacPlRoot}/eLogUpdate/${eLogTaskVersion}
setenv eLogScript ${eLogTaskDir}/populateElogDb.pl
setenv decideDigiScript ${eLogTaskDir}/decideDigi.pl
setenv eLogDataDir ${cookedTail}
setenv eLogDataDirFull ${dataHead}/${eLogDataDir}
#-------------------------------- eLogUpdate ----------------------------------

#++++++++++++++++++++++++++++++++ configReport ++++++++++++++++++++++++++++++++
setenv configReportTaskVersion v3r0p0
setenv configReportTask configReport-EM2-${configReportTaskVersion}
setenv configReportVersion v3r1p0
setenv configReportUrl ConfigTables.html
setenv ConfigTablesDir ${svacCmt}/ConfigTables/${configReportVersion}/Src
setenv configTaskDir ${svacPlRoot}/configReport/${configReportTaskVersion}
setenv configTablesScript ${ConfigTablesDir}/ConfigTables.py 
setenv configTablesDataDir ${cookedTail}/configReport/${configReportVersion}
setenv configTablesDataDirFull ${dataHead}/${configTablesDataDir}
#-------------------------------- configReport --------------------------------

#++++++++++++++++++++++++++++++++ digitization ++++++++++++++++++++++++++++++++
setenv digitizationTaskVersion v3r0p0
setenv digitizationTask digitization-EM2-${digitizationTaskVersion}
setenv Em2Version v2r8p2
setenv Em2Dir ${sasCmt}/LatIntegration/${Em2Version}
setenv ldfToDigiCmt ${Em2Dir}/cmt
setenv ldfToDigiApp ${Em2Dir}/rh9_gcc32opt/LatIntegration.exe
setenv ldfFileType LDFFITS
setenv digitizationTaskDir ${svacPlRoot}/digitization/${digitizationTaskVersion}
setenv digitizationScript ${digitizationTaskDir}/ldfToDigi.pl
setenv decideReconScript ${digitizationTaskDir}/decideRecon.pl
setenv digitizationDataDir ${emTail}/grRoot
setenv digitizationDataDirFull ${dataHead}/${digitizationDataDir}
#-------------------------------- digitization --------------------------------

#++++++++++++++++++++++++++++++++ digiReport ++++++++++++++++++++++++++++++++++
setenv digiReportTaskVersion v3r0p0
setenv digiReportTask digiReport-EM2-${digiReportTaskVersion}
setenv TestReportVersion v3r2p2
setenv TestReportDir ${svacCmt}/TestReport/${TestReportVersion}
setenv digiReportCmt ${TestReportDir}/cmt
setenv digiReportApp ${TestReportDir}/rh9_gcc32opt/TestReport.exe
setenv digiRepDoxyFile ${TestReportDir}/src/ReportDoxyfile
setenv latexHeaderFile ${TestReportDir}/src/latexHeader.tex
setenv digiReportVersion v1r0p0
setenv digiReportUrl html/index.html
setenv digiReportTaskDir ${svacPlRoot}/digiReport/${digiReportTaskVersion}
setenv digiReportScript ${digiReportTaskDir}/genDigiTestReport.pl
setenv digiReportDataDir ${emTail}/digiReport/${TestReportVersion}
setenv digiReportDataDirFull ${dataHead}/${digiReportDataDir}
#-------------------------------- digiReport ----------------------------------

#++++++++++++++++++++++++++++++++ recon +++++++++++++++++++++++++++++++++++++++
setenv reconTaskVersion v3r0p0
setenv reconTask recon-EM2-${reconTaskVersion}
setenv reconCmt ${Em2Dir}/cmt
setenv reconApp ${Em2Dir}/rh9_gcc32opt/LatIntegration.exe
setenv reconTaskDir ${svacPlRoot}/recon/${reconTaskVersion}
setenv reconScript ${reconTaskDir}/recon.pl
setenv reconDataDir ${calibTail}/grRoot
setenv reconDataDirFull ${dataHead}/${reconDataDir}
#-------------------------------- recon ---------------------------------------

#++++++++++++++++++++++++++++++++ reconReport +++++++++++++++++++++++++++++++++
setenv reconReportTaskVersion v3r0p0
setenv reconReportTask reconReport-EM2-${reconReportTaskVersion}
setenv reconReportCmt ${TestReportDir}/cmt
setenv reconReportApp ${TestReportDir}/rh9_gcc32opt/TestReport.exe
setenv reconRepDoxyFile ${TestReportDir}/src/ReportDoxyfile
setenv reconReportVersion v1r0p0
setenv reconReportUrl html/index.html
setenv reconReportTaskDir ${svacPlRoot}/reconReport/${reconReportTaskVersion}
setenv reconReportScript ${reconReportTaskDir}/genReconTestReport.pl
setenv reconReportDataDir ${calibTail}/reconReport/${TestReportVersion}
setenv reconReportDataDirFull ${dataHead}/${reconReportDataDir}
#-------------------------------- reconReport ---------------------------------

#++++++++++++++++++++++++++++++++ svacTuple +++++++++++++++++++++++++++++++++++
setenv svacTupleTaskVersion v3r0p0
setenv svacTupleTask svacTuple-EM2-${svacTupleTaskVersion}
setenv RunRootAnalyzerVersion v1r3p4
setenv RunRootAnalyzerDir ${svacCmt}/EngineeringModelRoot/${RunRootAnalyzerVersion}
setenv svacTupleCmt ${RunRootAnalyzerDir}/cmt
setenv svacTupleApp ${RunRootAnalyzerDir}/rh9_gcc32opt/RunRootAnalyzer.exe
setenv svacTupleVersion emRootv0r0
setenv svacTupleTaskDir ${svacPlRoot}/svacTuple/${svacTupleTaskVersion}
setenv svacTupleScript ${svacTupleTaskDir}/RunRootAnalyzer.pl
setenv svacTupleDataDir ${calibTail}/svacTuple/${svacTupleVersion}
setenv svacTupleDataDirFull ${dataHead}/${svacTupleDataDir}
#-------------------------------- svacTuple -----------------------------------

#++++++++++++++++++++++++++++++++ many ++++++++++++++++++++++++++++++++++++++++
setenv taskLauncher ${svacPlLib}/TaskLaunch.pl
setenv urlUpdateWrapper ${svacPlLib}/urlWrapper.pl
setenv urlUpdateScript  ${eLogDir}/updateUrl.py
#-------------------------------- many ----------------------------------------

setenv SVACPYTHON ${ConfigTablesDir}:${eLogDir}:${svacPlLib}
if ( ${?PYTHONPATH} == '1' ) then
    setenv PYTHONPATH ${SVACPYTHON}:$PYTHONPATH}
else
    setenv PYTHONPATH ${SVACPYTHON}
endif

setenv PATH ${PATH}:${svacPlLib}
