#!/bin/tcsh

source $svacPlRoot/setup/svacPlSetup.cshrc

#cd $reconStageDir
#rm -rf *

set junkDir=~/scratchJunk
mkdir -p $junkDir
cd $junkDir

# this should be all hosts eligible for long jobs
$set hosts=`bhosts meadow veldt | awk 'NR>1{print $1}'`
set hosts=`bhosts genfarm glastyilis | awk 'NR>1{print $1}'`

foreach host ($hosts)
	bsub -q express -m $host -o $host $svacPlRoot/lib/_cleanupOne.csh
end
