#!/usr/bin/perl -w

use strict;

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

my $run = '$(RUN_NAME)';

my $raw = 'rawData';
my $cooked = 'rootData';

my $rawRoot = "$raw/$run";
my $cookedRoot = "$cooked/$run";
my $calibRoot = "$cookedRoot/$ENV{'calibVersion'}";

open FIELDS, '>', shift;

print FIELDS <<EOT;
$ENV{'eLogTask'}  	Report  	$ENV{'dataHead'} 	Populate eLog database

populateElogDb  	1  	populateElogDb.pl 	$ENV{'eLogTaskVersion'}  	/nfs/slac/g/svac/common/pipeLine/EM2/svacPipeline/eLogUpdate/v1r0p0/populateElogDbWrapper.pl  	short  	$cookedRoot  	/nfs/slac/g/svac/common/pipeLine/EM2/svacPipeline/eLogUpdate/v1r0p0  	Enter run in electronic logbook.
LaunchDigi 	2 	TaskLaunch.pl 	$ENV{'eLogTaskVersion'} 	/nfs/slac/g/svac/common/pipeLine/EM2/svacPipeline/eLogUpdate/v1r0p0/ldfTDLaunchWrapper.pl 	short 	$cookedRoot 	/nfs/slac/g/svac/common/pipeLine/EM2/svacPipeline/eLogUpdate/v1r0p0 	Launch Digitization task 
LaunchConfRep 	3 	TaskLaunch.pl 	$ENV{'eLogTaskVersion'} 	/nfs/slac/g/svac/common/pipeLine/EM2/svacPipeline/eLogUpdate/v1r0p0/ConfTLaunchWrapper.pl 	short 	$cookedRoot 	/nfs/slac/g/svac/common/pipeLine/EM2/svacPipeline/eLogUpdate/v1r0p0	Launch configuration report task 
											
ldf  	LDF  	fits  	$rawRoot  	raw data in electronics space
rcReport 	rcReport 	xml 	$rawRoot 	rcreport
schema 	text 	xml 	$rawRoot 	schema file
script 	script 	csh 	$cookedRoot 	script
snapshot 	text 	xml 	$rawRoot 	snapshot file



$ENV{'configReportTask'} 	Report  	$ENV{'dataHead'} 	Make instrument configuration report

ConfigTables  	1  	ConfigTables.py  	v1r0p0  	/nfs/slac/g/svac/common/pipeLine/EM2/svacPipeline/configReport/v1r0p0/ConfigTablesWrapper.pl  	short  	$cookedRoot/configReport/v1r0p0  	/nfs/slac/g/svac/common/pipeLine/EM2/ConfigTables/v1r0p0/Src  	Create instrument configuration tables.

schema  	text  	xml  	$rawRoot  			XML schema file
snapshot 	text 	xml 	$rawRoot 			XML snapshot file
tarBall 	Analysis 	tgz 	$cookedRoot/configReport/v1r0p0 	Tarball (.tgz) of configuration report directory
	

$ENV{'digitizationTask'} 	Digitization  	$ENV{'dataHead'} 	Make digi file

Convert 	 	1  	ldfToDigi.pl  	v1r0p0  	/nfs/slac/g/svac/common/pipeLine/EM2/svacPipeline/digitization/v1r0p0/ldfToDigiWrapper.pl  		medium  	$cookedRoot/grRoot 	/nfs/slac/g/svac/common/pipeLine/EM2/svacPipeline/digitization/v1r0p0  	Convert LDF to DIGI
LaunchRecon 	2 	TaskLaunch.pl 	v1r0p0 	/nfs/slac/g/svac/common/pipeLine/EM2/v1r0p0/svacPipeline/digitization/v1r0p0/recLaunchWrapper.pl 		short 	$cookedRoot/grRoot 	/nfs/slac/g/svac/common/pipeLine/EM2/v1r0p0/svacPipeline/digitization/v1r0p0 	launch recon task
LaunchReport 	3 	TaskLaunch.pl 	v1r0p0 	/nfs/slac/g/svac/common/pipeLine/EM2/v1r0p0/svacPipeline/digitization/v1r0p0/genDTRLaunchWrapper.pl 	short 	$cookedRoot/grRoot 	/nfs/slac/g/svac/common/pipeLine/EM2/v1r0p0/svacPipeline/digitization/v1r0p0	launch digi report task
											
digi  		DIGI  	root  	$cookedRoot/grRoot  	Raw data in detector space
jobOptions 	text 	jobOpt 	$cookedRoot/grRoot 	config file
ldf 		LDF 	fits 	$rawRoot 	Raw data in electronics space
script 		script 	csh 	$cookedRoot/grRoot 	script
	


$ENV{'digiReportTask'} 	Report  	$ENV{'dataHead'} 	Report on contents of digi file

genReport  	1  	TestReport.exe  	v1r0p0  	/nfs/slac/g/svac/common/pipeLine/EM2/svacPipeline/digiReport/v1r0p0/genDigiTestReportWrapper.pl  	short  	$cookedRoot/digiReport/v1r0p0  	/nfs/slac/g/svac/common/pipeLine/EM2/svacPipeline/digiReport/v1r0p0  	Make report on digi file contents

digi  		DIGI  	root  	$cookedRoot/grRoot  		input digi file
jobOptions 	text 	jobOpt 	$cookedRoot/digiReport/v1r0p0 	output config file
script 		script 	csh 	$cookedRoot/digiReport/v1r0p0 	output script file
tarBall 		Analysis 	tgz 	$cookedRoot/digiReport/v1r0p0 	tarball of report directory



$ENV{'reconTask'}  	Reconstruction  	$ENV{'dataHead'} 	Make recon and merit files

recon  		1  	recon.pl  	v1r0p0  	/nfs/slac/g/svac/common/pipeLine/EM2/svacPipeline/recon/v1r0p0/reconWrapper.pl  	long  	$calibRoot/grRoot  /nfs/slac/g/svac/common/pipeLine/EM2/svacPipeline/recon/v1r0p0  	Make recon & merit files
LaunchSVAC 	2 	TaskLaunch.pl 	v1r0p0 	/nfs/slac/g/svac/common/pipeLine/EM2/svacPipeline/recon/v1r0p0/RunRALaunchWrapper.pl 	short 	$calibRoot/grRoot 	/nfs/slac/g/svac/common/pipeLine/EM2/svacPipeline/recon/v1r0p0 	Launch SVAC tuple creation task
LaunchReport 	3 	TaskLaunch.pl 	v1r0p0 	/nfs/slac/g/svac/common/pipeLine/EM2/svacPipeline/recon/v1r0p0/genRTRLaunchWrapper.pl 	short 	$calibRoot/grRoot 	/nfs/slac/g/svac/common/pipeLine/EM2/svacPipeline/recon/v1r0p0 	Launch recon report task

digi  		DIGI  	root  	$cookedRoot/grRoot  		digi file
jobOptions 	text 	jobOpt 	$calibRoot/grRoot 	options for recon
merit 		merit 	root 	$calibRoot/grRoot 	merit tuple
recon 		RECON 	root 	$calibRoot/grRoot 	recon file
script 		script 	sh 	$calibRoot/grRoot 	script



$ENV{'reconReportTask'}  	Report  	$ENV{'dataHead'} 	Report on contents of recon & digi files

genReport  	1  	TestReport.exe  	v1r0p0  	/nfs/slac/g/svac/common/pipeLine/EM2/svacPipeline/reconReport/v1r0p0/genReconTestReportWrapper.pl  	short  	$calibRoot/reconReport/v1r0p0 	/nfs/slac/g/svac/common/pipeLine/EM2/svacPipeline/reconReport/v1r0p0	Create recon report

digi  		DIGI  	root  	$cookedRoot/grRoot  				Digi file
jobOptions 	text 	jobOpt 	$calibRoot/reconReport/v1r0p0 	Option file
recon 		RECON 	root 	$calibRoot/grRoot 			Recon file
script 		script 	csh 	$calibRoot/reconReport/v1r0p0 	Script
tarBall 		Analysis 	tgz 	$calibRoot/reconReport/v1r0p0 	tarball of report directory



$ENV{'svacTupleTask'}  	Analysis  $ENV{'dataHead'}	 	Make SVAC "tuple"

svacTuple  	1  	RunRootAnalyzer.exe  	v1r0p0  	/nfs/slac/g/svac/common/pipeLine/EM2/svacPipeline/svacTuple/v1r0p0/RunRootAnalyzerWrapper.pl  	short  	$calibRoot/svacRoot/emRootv1r0p0  	/nfs/slac/g/svac/common/pipeLine/EM2/svacPipeline/svacTuple/v1r0p0 	Make SVAC "tuple"

digi  		DIGI 	 	root  	$cookedRoot/grRoot  				Digi file
histogram 	histogram 	root 	$calibRoot/svacRoot/emRootv1r0p0 	SVAC histograms
jobOptions 	text 		jobOpt 	$calibRoot/svacRoot/emRootv1r0p0 	option file
recon 		RECON 		root 	$calibRoot/grRoot 			Recon file
script 		script 		csh 	$calibRoot/svacRoot/emRootv1r0p0 	script
svac	 	svac 		root 	$calibRoot/svacRoot/emRootv1r0p0 	SVAC "tuple"
EOT
