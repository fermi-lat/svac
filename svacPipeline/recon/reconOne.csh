#!/bin/csh
unsetenv LD_LIBRARY_PATH
setenv CMTCONFIG $SVAC_CMTCONFIG
setenv GLAST_EXT $SVAC_GLAST_EXT
# setenv CMTPATH 'already set'
# setenv LATCalibRoot 'already set'
pushd $reconCmt
source setup.csh ''
cmt show uses
popd
setenv JOBOPTIONS $1
set digiFile=$2

set stageDir=$runStageDir
set localDir=$localDisk

alias run 'echo \!* ; date ; \!*'

if ( { test -d $localDir } ) then
    set relocate=1

    set myLocal=$localDir/$$
    test -d $myLocal || run mkdir $myLocal

    setenv inDir $myLocal
    setenv procDir $myLocal

    run cp $JOBOPTIONS $inDir && set unDone=0 || set unDone=1
    while ($unDone)
        sleep 19 # randomish delay
        run cp $JOBOPTIONS $inDir && set unDone=0 || set unDone=1
    end
    set joBase=`echo $JOBOPTIONS | awk -F/ '{print $NF}'`
    setenv JOBOPTIONS $inDir/$joBase

    set digiBase=`basename $digiFile`
    set reconFile=`awk -F'"' '/RECON\.root/{print $2}' $JOBOPTIONS`
    set reconBase=`basename $reconFile`
    set meritFile=`awk -F'"' '/merit\.root/{print $2}' $JOBOPTIONS`
    set meritBase=`basename $meritFile`
    set calFile=`awk -F'"' '/calTuple\.root/{print $2}' $JOBOPTIONS`
    set calBase=`basename $calFile`

    run cp $digiFile $inDir && set unDone=0 || set unDone=1
    while ($unDone)
        sleep 17 # randomish delay
        run cp $digiFile $inDir && set unDone=0 || set unDone=1
    end

else
    set relocate=0
    setenv procDir $stageDir
    setenv inDir `dirname $digiFile`
endif
echo Reading digi file from $inDir
echo Writing chunk files to $procDir

$reconApp || exit 1

if ( $relocate ) then
    echo Relocating chunk files from $procDir to $stageDir
    pushd $procDir
    run mv $reconBase $meritBase $calBase $stageDir
    cd $inDir
    run rm $digiBase $joBase
    popd
	run rmdir $myLocal 
endif
