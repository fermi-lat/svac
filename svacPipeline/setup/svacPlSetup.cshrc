#!/bin/tcsh

# setup for SVAC pipeline

setenv GLASTROOT /afs/slac.stanford.edu/g/glast
source ${GLASTROOT}/ground/scripts/user.cshrc
setenv sasLocation /nfs/farm/g/glast/u09/builds/rh9_gcc32/EngineeringModel
setenv EngineeringModelVersion v3r0407p13
setenv sasVersion EngineeringModel-$EngineeringModelVersion
setenv sasCmt ${sasLocation}/${sasVersion}

setenv svacRoot /nfs/slac/g/svac/common
setenv svacCmt ${svacRoot}/builds
# svacPlRoot is set in the pipeline
#setenv svacPlRoot ${svacRoot}/pipeline/EM2/svacPipeline
#setenv svacPlLibVersion v1r0
#setenv svacPlLib ${svacPlRoot}/lib/${svacPlLibVersion}
setenv svacPlLib ${svacPlRoot}/lib
setenv svacPlLibVersion v2r1

setenv CMTPATH ${svacCmt}:${sasCmt}

setenv iAndTPhase Integration

setenv dataHead /nfs/farm/g/glast/u12/$iAndTPhase
setenv onlineTail rawData
setenv svacTail rootData
setenv onlineHead $dataHead/$onlineTail/'$(RUN_NAME)'
setenv svacHead $dataHead/$svacTail/'$(RUN_NAME)'
setenv urlHead /glast.u12/$iAndTPhase
setenv rootUrl $urlHead/$svacTail
setenv rawUrl $urlHead/$onlineTail
setenv svacEmDir $svacHead/$EngineeringModelVersion

setenv calibVersion calib-v1r0
setenv calibGenTKRVersion v0r1p8
setenv calibGenCALVersion v2r3p4

setenv calibRoot $svacEmDir/$calibVersion

setenv batchgroup glastdata

#++++++++++++++++++++++++++++++++ online ++++++++++++++++++++++++++++++++++++++
setenv onlineVersion V1r0
setenv svacOnlineVersion v2r0p1
setenv onlineTask online-EM2-${onlineVersion}
setenv svacOnlineDir ${svacPlRoot}/online/${svacOnlineVersion}
setenv onlineTaskDir /nfs/slac/g/svac/common/pipeline/EM2/onlinePipeline
setenv svacOnlineScript ${svacOnlineDir}/SVACLaunch.pl
#-------------------------------- online --------------------------------------

#++++++++++++++++++++++++++++++++ eLogUpdate ++++++++++++++++++++++++++++++++++
setenv eLogTaskVersion v2r0p1
setenv eLogTask updateELogDB-${eLogTaskVersion}
setenv eLogFeederVersion v2r0
setenv eLogDir ${svacCmt}/eLogFeeder/${eLogFeederVersion}
setenv eLogTaskDir ${svacPlRoot}/eLogUpdate/${eLogTaskVersion}
setenv eLogScript ${eLogTaskDir}/populateElogDb.pl
#-------------------------------- eLogUpdate ----------------------------------

#++++++++++++++++++++++++++++++++ configReport ++++++++++++++++++++++++++++++++
setenv configReportTaskVersion v2r0p1
setenv configReportTask configReport-${configReportTaskVersion}
setenv configReportVersion v3r0p0
setenv configReportUrl ConfigTables.html
setenv ConfigTablesDir ${svacCmt}/ConfigTables/${configReportVersion}/Src
setenv configTaskDir ${svacPlRoot}/configReport/${configReportTaskVersion}
setenv configTablesScript ${ConfigTablesDir}/ConfigTables.py 
#-------------------------------- configReport --------------------------------

#++++++++++++++++++++++++++++++++ digitization ++++++++++++++++++++++++++++++++
setenv digitizationTaskVersion v2r0p1
setenv digitizationTask digitization-${digitizationTaskVersion}
setenv Em2Version v2r8p2
setenv Em2Dir ${sasCmt}/LatIntegration/${Em2Version}
setenv ldfToDigiCmt ${Em2Dir}/cmt
setenv ldfToDigiApp ${Em2Dir}/rh9_gcc32/LatIntegration.exe
setenv ldfFileType LDFFITS
setenv digitizationTaskDir ${svacPlRoot}/digitization/${digitizationTaskVersion}
setenv digitizationScript ${digitizationTaskDir}/ldfToDigi.pl
setenv decideReconScript ${digitizationTaskDir}/decideRecon.pl
#-------------------------------- digitization --------------------------------

#++++++++++++++++++++++++++++++++ digiReport ++++++++++++++++++++++++++++++++++
setenv digiReportTaskVersion v2r0p1
setenv digiReportTask digiReport-${digiReportTaskVersion}
setenv TestReportVersion v3r1p0
setenv TestReportDir ${svacCmt}/TestReport/${TestReportVersion}
setenv digiReportCmt ${TestReportDir}/cmt
setenv digiReportApp ${TestReportDir}/rh9_gcc32/TestReport.exe
setenv digiRepDoxyFile ${TestReportDir}/src/ReportDoxyfile
setenv latexHeaderFile ${TestReportDir}/src/latexHeader.tex
setenv digiReportVersion $TestReportVersion
setenv digiReportUrl html/index.html
setenv digiReportTaskDir ${svacPlRoot}/digiReport/${digiReportTaskVersion}
setenv digiReportScript ${digiReportTaskDir}/genDigiTestReport.pl
#-------------------------------- digiReport ----------------------------------

#++++++++++++++++++++++++++++++++ recon +++++++++++++++++++++++++++++++++++++++
setenv reconTaskVersion v2r0p1
setenv reconTask recon-${reconTaskVersion}
setenv reconCmt ${Em2Dir}/cmt
setenv reconApp ${Em2Dir}/rh9_gcc32/LatIntegration.exe
setenv reconTaskDir ${svacPlRoot}/recon/${reconTaskVersion}
setenv reconScript ${reconTaskDir}/recon.pl
#-------------------------------- recon ---------------------------------------

#++++++++++++++++++++++++++++++++ reconReport +++++++++++++++++++++++++++++++++
setenv reconReportTaskVersion v2r0p1
setenv reconReportTask reconReport-${reconReportTaskVersion}
setenv reconReportCmt ${TestReportDir}/cmt
setenv reconReportApp ${TestReportDir}/rh9_gcc32/TestReport.exe
setenv reconRepDoxyFile ${TestReportDir}/src/ReportDoxyfile
setenv reconReportVersion $TestReportVersion
setenv reconReportUrl html/index.html
setenv reconReportTaskDir ${svacPlRoot}/reconReport/${reconReportTaskVersion}
setenv reconReportScript ${reconReportTaskDir}/genReconTestReport.pl
#-------------------------------- reconReport ---------------------------------

#++++++++++++++++++++++++++++++++ svacTuple +++++++++++++++++++++++++++++++++++
setenv svacTupleTaskVersion v2r0p1
setenv svacTupleTask svacTuple-${svacTupleTaskVersion}
setenv RunRootAnalyzerVersion v1r3p4
setenv RunRootAnalyzerDir ${svacCmt}/EngineeringModelRoot/${RunRootAnalyzerVersion}
setenv svacTupleCmt ${RunRootAnalyzerDir}/cmt
setenv svacTupleApp ${RunRootAnalyzerDir}/rh9_gcc32/RunRootAnalyzer.exe
setenv svacTupleVersion emRootv0r0
setenv svacTupleTaskDir ${svacPlRoot}/svacTuple/${svacTupleTaskVersion}
setenv svacTupleScript ${svacTupleTaskDir}/RunRootAnalyzer.pl
#-------------------------------- svacTuple -----------------------------------

#++++++++++++++++++++++++++++++++ many ++++++++++++++++++++++++++++++++++++++++
setenv taskLauncher ${svacPlLib}/TaskLaunch.pl
setenv urlUpdateWrapper ${svacPlLib}/urlWrapper.pl
setenv urlUpdateScript  ${eLogDir}/updateUrl.py
#-------------------------------- many ----------------------------------------

setenv SVACPYTHON ${ConfigTablesDir}:${eLogDir}
if ( ${?PYTHONPATH} == '1' ) then
    setenv PYTHONPATH ${SVACPYTHON}:$PYTHONPATH}
else
    setenv PYTHONPATH ${SVACPYTHON}
endif
