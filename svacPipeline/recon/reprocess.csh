#!/bin/tcsh

# this reprocesses runs that were originally digitized with the current version
# (whatever that is) of SVAC's digitization-latte task

set run=$1
if ( { test -z $run } ) then
	echo "You must supply a run #."
	exit 1
endif

source ${svacPlRoot}/setup/svacPlSetup.cshrc

alias run 'echo \!* ; \!*'

set dataDir=`echo ${digitizationDataDirFull} | sed s/'$(RUN_NAME)'/$run/`
test -e ${dataDir} || ( run mkdirhier ${dataDir} )
run cd ${dataDir}

set dataSets='digi_DIGI.root'

set oldTask=${digitizationTaskLatte}
set newTask=${reconTask}

foreach dataSet ($dataSets)
    set oldName=${oldTask}_${run}_${dataSet}
	echo ${oldName}
	test -e ${oldName} || continue
	set newName=`echo $oldName | sed s/${oldTask}/${newTask}/`
	test -e ${newName} || ( run ln -s ${oldName} ${newName} )
end

run ${PDB_HOME}/createRun.pl $newTask $run
