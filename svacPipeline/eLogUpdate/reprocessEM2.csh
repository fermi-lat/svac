#!/bin/tcsh

# this reprocesses runs that were originally done with the EM2 version
# of online's task

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

set oldDir=../../../EM2/rawData/${run}
set oldTask=online-EM2-V1r0

set newTask=${eLogTask}

foreach dataSet ($dataSets)
    set oldTail=${oldTask}_${run}_${dataSet}
	set oldName=${oldDir}/${oldTail}
	test -e ${oldName} || continue
	set newName=`echo $oldTail | sed s/${oldTask}/${newTask}/`
	test -e ${newName} || ( run ln -s ${oldName} ${newName} )
end

run ${PDB_HOME}/createRun.pl $newTask $run
