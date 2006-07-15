#!/bin/tcsh

set run=$1

source $beamtestPlRoot/setup/svacPlSetup.cshrc

foreach field (digirootfile reconrootfile meritrootfile calrootfile svacrootfile configreporturl digireporturl reconreporturl)
	$beamtestPlRoot/lib/updateElogReportTable.pl $run $field ''
end
