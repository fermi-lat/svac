#!/bin/csh

set printexitvalue

set anyErrors=0

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
set stageDir=$3

set localDir=$localDisk

alias run 'date ; echo \!* ; \!* ; date'

if ( { test -d $localDir } ) set relocate=1

if ( $relocate ) then
    set myLocal=$localDir/$$
    mkdir -p $myLocal
	@ anyErrors=($anyErrors | $status)
	if ( $anyErrors != 0 ) goto cleanup

    setenv inDir $myLocal
    setenv procDir $myLocal

	echo Copying JO file to local disk
	$tryAFewTimes cp $JOBOPTIONS $inDir
	@ anyErrors=($anyErrors | $status)
	if ( $anyErrors != 0 ) goto cleanup

    set joBase=`echo $JOBOPTIONS | awk -F/ '{print $NF}'`
    setenv JOBOPTIONS $inDir/$joBase

    set digiBase=`basename $digiFile`
    set reconFile=`awk -F'"' '/RECON\.root/{print $2}' $JOBOPTIONS`
    set reconBase=`basename $reconFile`
    set meritFile=`awk -F'"' '/merit\.root/{print $2}' $JOBOPTIONS`
    set meritBase=`basename $meritFile`
    set calFile=`awk -F'"' '/calTuple\.root/{print $2}' $JOBOPTIONS`
    set calBase=`basename $calFile`

	echo Copying digi file to local disk
	$tryAFewTimes cp $digiFile $inDir
	@ anyErrors=($anyErrors | $status)
	if ( $anyErrors != 0 ) goto cleanup

else
    set relocate=0
    setenv procDir $stageDir
    setenv inDir `dirname $digiFile`
endif
echo Reading digi file from $inDir
echo Writing chunk files to $procDir

date
echo $reconApp
$reconApp
@ anyErrors=($anyErrors | $status)
if ( $anyErrors != 0 ) goto cleanup
date

cleanup:

if ( $relocate ) then

	if ( $anyErrors == 0 ) then
		echo Relocating chunk files from $procDir to $stageDir
		pushd $procDir
		foreach outFile ($reconBase $meritBase $calBase)
			$tryAFewTimes mv $outFile $stageDir
			@ anyErrors=($anyErrors | $status)
		end
		popd
	endif

	run rm -rf $myLocal 
endif

run $cleanupOne

exit $anyErrors
