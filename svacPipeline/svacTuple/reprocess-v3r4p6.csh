#!/bin/tcsh

# This reprocesses runs that were originally done with version v3r4p6
# of the digi&recon tasks.
# It won't work unless the new task is on the same disk (u27).

set run=$1
if ( { test -z $run } ) then
	echo "You must supply a run #."
	exit 1
endif

source ${beamtestPlRoot}/setup/svacPlSetup.cshrc

alias run 'echo \!* ; \!*'

set newTask=${svacTupleTask}

set dataDir=`echo ${digitizationDataDirFull} | sed s/'$(RUN_NAME)'/$run/`
test -e ${dataDir} || ( run mkdirhier ${dataDir} )
run cd ${dataDir}

set dataSets='digi_DIGI.root'

set oldTask=digitization-v3r4p6

foreach dataSet ($dataSets)
    set oldName=${oldTask}_${run}_${dataSet}
	echo ${oldName}
	test -e ${oldName} || continue
	set newName=`echo $oldName | sed s/${oldTask}/${newTask}/`
	test -e ${newName} || ( run ln -s ${oldName} ${newName} )
end


set dataDir=`echo ${reconDataDirFull} | sed s/'$(RUN_NAME)'/$run/`
test -e ${dataDir} || ( run mkdirhier ${dataDir} )
run cd ${dataDir}

set dataSets='recon_RECON.root'

set oldTask=recon-v3r4p6

foreach dataSet ($dataSets)
    set oldName=${oldTask}_${run}_${dataSet}
	echo ${oldName}
	test -e ${oldName} || continue
	set newName=`echo $oldName | sed s/${oldTask}/${newTask}/`
	test -e ${newName} || ( run ln -s ${oldName} ${newName} )
end

run ${PDB_HOME}/createRun.pl $newTask $run
