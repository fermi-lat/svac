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


# eLog
my $eLogTaskDir = "$ENV{'svacPlRoot'}/eLogUpdate/$ENV{'eLogTaskVersion'}";

# configReport
my $configTaskDir = "$ENV{'svacPlRoot'}/configReport/$ENV{'configReportTaskVersion'}";
my $configDataDir = "$cookedRoot/configReport/$ENV{'configReportVersion'}";

# digitization
my $digiTaskDir = "$ENV{'svacPlRoot'}/digitization/$ENV{'digitizationTaskVersion'}";
my $digiDataDir = "$cookedRoot/grRoot";

# digiReport
my $digiReportTaskDir = "$ENV{'svacPlRoot'}/digiReport/$ENV{'digiReportTaskVersion'}";
my $digiReportDataDir = "$cookedRoot/digiReport/$ENV{'digiReportVersion'}";

# recon
my $reconTaskDir = "$ENV{'svacPlRoot'}/recon/$ENV{'reconTaskVersion'}";
my $reconDataDir = "$calibRoot/grRoot";

# reconReport
my $reconReportTaskDir = "$ENV{'svacPlRoot'}/reconReport/$ENV{'reconReportTaskVersion'}";
my $reconReportDataDir = "$calibRoot/reconReport/$ENV{'reconReportVersion'}";

# svacTuple
my $svacTupleTaskDir = "$ENV{'svacPlRoot'}/svacTuple/$ENV{'svacTupleTaskVersion'}";
my $svacTupleDataDir = "$calibRoot/svacRoot/$ENV{'svacTupleVersion'}";


open FIELDS, '>', shift;
print FIELDS <<EOT;
$ENV{'eLogTask'}		Report		$ENV{'dataHead'}		Populate eLog database

populateElogDb	1	populateElogDb.pl	$ENV{'eLogTaskVersion'}	$eLogTaskDir/populateElogDbWrapper.pl		short	$cookedRoot	$eLogTaskDir		Enter run in electronic logbook.
LaunchDigi	2	TaskLaunch.pl	$ENV{'eLogTaskVersion'}	$eLogTaskDir/ldfTDLaunchWrapper.pl		short	$cookedRoot	$eLogTaskDir		Launch Digitization task 
LaunchConfRep	3	TaskLaunch.pl	$ENV{'eLogTaskVersion'}	$eLogTaskDir/ConfTLaunchWrapper.pl		short	$cookedRoot	$eLogTaskDir		Launch configuration report task 
											
ldf	LDF	fits	$rawRoot		raw data in electronics space
rcReport	rcReport	xml	$rawRoot		rcreport
schema	text	xml	$rawRoot		schema file
script	script	csh	$cookedRoot	script
snapshot	text	xml	$rawRoot		snapshot file



$ENV{'configReportTask'}	Report	$ENV{'dataHead'}		Make instrument configuration report

ConfigTables	1	ConfigTables.py	$ENV{'configReportTaskVersion'}	$configTaskDir/ConfigTablesWrapper.pl	short	$configDataDir	$ENV{'svacCmt'}/ConfigTables/$ENV{'configReportVersion'}/Src		Create instrument configuration tables.

schema	text	xml	$rawRoot			XML schema file
snapshot	text	xml	$rawRoot			XML snapshot file
tarBall	Analysis	tgz	$configDataDir		Tarball (.tgz) of configuration report directory



$ENV{'digitizationTask'}	Digitization	$ENV{'dataHead'}		Make digi file

Convert		1	ldfToDigi.pl	$ENV{'digitizationTaskVersion'}	$digiTaskDir/ldfToDigiWrapper.pl	medium	$digiDataDir	$digiTaskDir		Convert LDF to DIGI
LaunchRecon	2	TaskLaunch.pl	$ENV{'digitizationTaskVersion'}	$digiTaskDir/recLaunchWrapper.pl	short	$digiDataDir	$digiTaskDir		launch recon task
LaunchReport	3	TaskLaunch.pl	$ENV{'digitizationTaskVersion'}	$digiTaskDir/genDTRLaunchWrapper.pl	short	$digiDataDir	$digiTaskDir		launch digi report task

digi		DIGI	root	$digiDataDir	Raw data in detector space
jobOptions	text	jobOpt	$digiDataDir	config file
ldf		LDF	fits	$rawRoot		Raw data in electronics space
script		script	csh	$digiDataDir	script



$ENV{'digiReportTask'}	Report	$ENV{'dataHead'}		Report on contents of digi file

genReport		1	TestReport.exe	$ENV{'digiReportTaskVersion'}	$digiReportTaskDir/genDigiTestReportWrapper.pl	short	$digiReportDataDir	$digiReportTaskDir		Make report on digi file contents

digi		DIGI	root	$digiDataDir		input digi file
jobOptions	text	jobOpt	$digiReportDataDir		output config file
script		script	csh	$digiReportDataDir		output script file
tarBall		Analysis	tgz	$digiReportDataDir		tarball of report directory



$ENV{'reconTask'}	Reconstruction	$ENV{'dataHead'}		Make recon and merit files

recon		1	recon.pl		$ENV{'reconTaskVersion'}	$reconTaskDir/reconWrapper.pl		long	$reconDataDir	$reconTaskDir		Make recon & merit files
LaunchSVAC	2	TaskLaunch.pl	$ENV{'reconTaskVersion'}	$reconTaskDir/RunRALaunchWrapper.pl	short	$reconDataDir	$reconTaskDir		Launch SVAC tuple creation task
LaunchReport	3	TaskLaunch.pl	$ENV{'reconTaskVersion'}	$reconTaskDir/genRTRLaunchWrapper.pl	short	$reconDataDir	$reconTaskDir		Launch recon report task

digi		DIGI	root	$digiDataDir		digi file
jobOptions	text	jobOpt	$reconDataDir		options for recon
merit		merit	root	$reconDataDir		merit tuple
recon		RECON	root	$reconDataDir		recon file
script		script	sh	$reconDataDir		script



$ENV{'reconReportTask'}	Report	$ENV{'dataHead'}		Report on contents of recon & digi files

genReport		1	TestReport.exe	$ENV{'reconReportTaskVersion'}	$reconReportTaskDir/genReconTestReportWrapper.pl	short	$reconReportDataDir		$reconReportTaskDir		Create recon report

digi		DIGI	root	$digiDataDir		Digi file
jobOptions	text	jobOpt	$reconReportDataDir		Option file
recon		RECON	root	$reconDataDir		Recon file
script		script	csh	$reconReportDataDir		Script
tarBall		Analysis	tgz	$reconReportDataDir		tarball of report directory



$ENV{'svacTupleTask'}	Analysis	$ENV{'dataHead'}		Make SVAC "tuple"

svacTuple		1	RunRootAnalyzer.exe		$ENV{'svacTupleTaskVersion'}	$svacTupleTaskDir/RunRootAnalyzerWrapper.pl	short	$svacTupleDataDir	$svacTupleTaskDir		Make SVAC "tuple"

digi		DIGI	root	$digiDataDir		Digi file
histogram		histogram	root	$svacTupleDataDir		SVAC histograms
jobOptions	text	jobOpt	$svacTupleDataDir		option file
recon		RECON	root	$reconDataDir		Recon file
script		script	csh	$svacTupleDataDir		script
svac		svac	root	$svacTupleDataDir		SVAC "tuple"
EOT
