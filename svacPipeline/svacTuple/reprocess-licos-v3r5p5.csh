#!/bin/tcsh

# this reprocesses runs that were originally done with the current version
# (whatever that is) of the digi&recon tasks

set run=$1
if ( { test -z $run } ) then
	echo "You must supply a run #."
	exit 1
endif

source ${beamtestPlRoot}/setup/svacPlSetup.cshrc

alias run 'echo \!* ; \!*'

set newTask=${svacTupleTask}

set dataDir=/nfs/farm/g/glast/u25/Integration/rootData/${run}/v6r070305p9/grRoot
test -e ${dataDir} || ( run mkdirhier ${dataDir} )
run cd ${dataDir}

set dataSets='digi_DIGI.root'

set oldTask=digitization-licos-v3r5p5

foreach dataSet ($dataSets)
    set oldName=${oldTask}_${run}_${dataSet}
	echo ${oldName}
	test -e ${oldName} || continue
	set newName=`echo $oldName | sed s/${oldTask}/${newTask}/`
	test -e ${newName} || ( run ln -s ${oldName} ${newName} )
end


set dataDir=/nfs/farm/g/glast/u25/Integration/rootData/${run}/v6r070305p9/calib-v1r0/grRoot
test -e ${dataDir} || ( run mkdirhier ${dataDir} )
run cd ${dataDir}

set dataSets='recon_RECON.root'

set oldTask=recon-v3r5p5

foreach dataSet ($dataSets)
    set oldName=${oldTask}_${run}_${dataSet}
	echo ${oldName}
	test -e ${oldName} || continue
	set newName=`echo $oldName | sed s/${oldTask}/${newTask}/`
	test -e ${newName} || ( run ln -s ${oldName} ${newName} )
end

run ${PDB_HOME}/createRun.pl $newTask $run
