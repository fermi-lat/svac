#!/bin/tcsh

set run=$1

source $svacPlRoot/setup/svacPlSetup.cshrc

foreach field (digirootfile reconrootfile meritrootfile calrootfile svacrootfile configreporturl digireporturl reconreporturl tkrreporturl)
	$svacPlRoot/lib/updateElogReportTable.pl $run $field ''
end
