#!/bin/tcsh

# setup for SVAC pipeline

setenv GLASTROOT /afs/slac.stanford.edu/g/glast
source ${GLASTROOT}/ground/scripts/user.cshrc
setenv sasLocation /nfs/farm/g/glast/u09/builds/rh9_gcc32/EngineeringModel
setenv EngineeringModelVersion v3r0407p3
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

setenv iAndTPhase TowerA

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
