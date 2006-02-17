#!/bin/tcsh

# this reprocesses runs that were originally done with version
# v2r4p0 of online's task

set run=$1
if ( { test -z $run } ) then
	echo "You must supply a run #."
	exit 1
endif

source ${svacPlRoot}/setup/svacPlSetup.cshrc

alias run 'echo \!* ; \!*'

set dataDir=`echo ${onlineDataDirFull} | sed s/'$(RUN_NAME)'/$run/`
test -e ${dataDir} || ( run mkdir ${dataDir} )
run cd ${dataDir}

set dataSets='ldf_LDF.fits rcReport_rcReport.xml snapshot_text.xml'

set oldDir=../../../../../../nfs/farm/g/glast/u21/Integration/rawData/${run}
set oldTask=online-v2r4p0
set newTask=${eLogTask}

foreach dataSet ($dataSets)
    set oldTail=${oldTask}_${run}_${dataSet}
    set oldName=${oldDir}/${oldTail}
	test -e ${oldName} || continue
	set newName=`echo $oldTail | sed s/${oldTask}/${newTask}/`
	test -e ${newName} || ( run ln -s ${oldName} ${newName} )
end

run ${PDB_HOME}/createRun.pl $newTask $run
