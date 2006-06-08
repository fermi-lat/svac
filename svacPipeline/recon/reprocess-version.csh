#!/bin/tcsh

# this reprocesses runs that were originally done with the current version
# (whatever that is) of online's task

set run=$2
if ( { test -z $run } ) then
	echo "Arguments are oldDigiTask runId"
	exit 1
endif

source ${beamtestPlRoot}/setup/svacPlSetup.cshrc

alias run 'echo \!* ; \!*'

set dataDir=`echo ${digitizationDataDirFull} | sed s/'$(RUN_NAME)'/$run/`
test -e ${dataDir} || ( run mkdirhier ${dataDir} )
run cd ${dataDir}

set dataSets='digi_DIGI.root'

set oldTask=$1
set newTask=${reconTask}

foreach dataSet ($dataSets)
    set oldName=${oldTask}_${run}_${dataSet}
	echo ${oldName}
	test -e ${oldName} || continue
	set newName=`echo $oldName | sed s/${oldTask}/${newTask}/`
	test -e ${newName} || ( run ln -s ${oldName} ${newName} )
end

run ${PDB_HOME}/createRun.pl $newTask $run
