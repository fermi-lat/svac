#!/bin/tcsh

set run=$1

source ${svacPlRoot}/setup-current/svacPlSetup.cshrc

set dataDir=`echo ${onlineDataDirFull} | sed s/'$(RUN_NAME)'/$run/`
echo cd ${dataDir}
cd ${dataDir}

dataSets='ldf_LDF.fits rcReport_rcReport.xml schema_text.xml snapshot_text.xml'

set oldTask=${onlineTask}
set newTask=${eLogTask}

foreach dataSet ($dataSets)
    set oldName=${oldTask}_${run}_${dataSet}
	test -e ${oldName} || continue
	set newName=`echo $oldName | sed s/${oldTask}/${newTask}/`
	echo ln -s ${oldName} ${newName}
end

echo createRun.pl $newTask $run
