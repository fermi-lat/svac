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


my $urlUpdater = $ENV{'urlUpdateWrapper'};

# eLog
my $eLogDataDir = $cookedRoot;

# configReport
my $configDataDir = "$cookedRoot/configReport/$ENV{'configReportVersion'}";

# digitization
my $digiDataDir = "$cookedRoot/grRoot";

# digiReport
my $digiReportDataDir = "$cookedRoot/digiReport/$ENV{'digiReportVersion'}";

# recon
my $reconDataDir = "$calibRoot/grRoot";

# reconReport
my $reconReportDataDir = "$calibRoot/reconReport/$ENV{'reconReportVersion'}";

# svacTuple
my $svacTupleDataDir = "$calibRoot/svacRoot/$ENV{'svacTupleVersion'}";


open FIELDS, '>', shift;
print FIELDS <<EOT;
## Machine-generated file, do not edit.

# This gives all the fields that must go in Navid's interface to set up the SVAC pipeline.
# The fields are:
#
# for a task:
# Name, Type, Base Path, Comment
#
# for a process:
# Name, Sequence, Application, Version, Command (the wrapper), batch Queue, Log directory, CWD (where the wrapper is run), Comment
# As far as I can tell, Application Version are basically comments.
#
# for a dataset:
# Name, Data Type, File Format, Path, Comment

# Datasets that are seen by more than one task are only shown in full for the first task that sees them.


$ENV{'eLogTask'}		Report		$ENV{'dataHead'}		Populate eLog database

populateElogDb	1	populateElogDb.pl	$ENV{'eLogTaskVersion'}	$ENV{'eLogTaskDir'}/populateElogDbWrapper.pl		short	$eLogDataDir	$eLogDataDir		Enter run in electronic logbook.
LaunchDigi	2	TaskLaunch.pl	$ENV{'eLogTaskVersion'}	$ENV{'eLogTaskDir'}/ldfTDLaunchWrapper.pl		short	$eLogDataDir	$eLogDataDir		Launch Digitization task 
LaunchConfRep	3	TaskLaunch.pl	$ENV{'eLogTaskVersion'}	$ENV{'eLogTaskDir'}/ConfTLaunchWrapper.pl		short	$eLogDataDir	$eLogDataDir		Launch configuration report task 
											
ldf	LDF	fits	$rawRoot		raw data in electronics space
rcReport	rcReport	xml	$rawRoot		rcreport
schema	text	xml	$rawRoot		schema file
script	script	csh	$eLogDataDir	script
snapshot	text	xml	$rawRoot		snapshot file



$ENV{'configReportTask'}	Report	$ENV{'dataHead'}		Make instrument configuration report

ConfigTables	1	ConfigTables.py	$ENV{'configReportTaskVersion'}	$ENV{'configTaskDir'}/ConfigTablesWrapper.pl	short	$configDataDir	$configDataDir		Create instrument configuration tables.
configReportUrl	2	updateUrl.py	$ENV{'configReportTaskVersion'}	$urlUpdater				short	$configDataDir	$configDataDir		Update URL for instrument configuration report.

schema
snapshot
tarBall	Analysis	tgz	$configDataDir		Tarball (.tgz) of configuration report directory



$ENV{'digitizationTask'}	Digitization	$ENV{'dataHead'}		Make digi file

Convert		1	ldfToDigi.pl	$ENV{'digitizationTaskVersion'}	$ENV{'digitizationTaskDir'}/ldfToDigiWrapper.pl		medium	$digiDataDir	$digiDataDir		Convert LDF to DIGI
LaunchRecon	2	TaskLaunch.pl	$ENV{'digitizationTaskVersion'}	$ENV{'digitizationTaskDir'}/recLaunchWrapper.pl		short	$digiDataDir	$digiDataDir		launch recon task
LaunchReport	3	TaskLaunch.pl	$ENV{'digitizationTaskVersion'}	$ENV{'digitizationTaskDir'}/genDTRLaunchWrapper.pl	short	$digiDataDir	$digiDataDir		launch digi report task
digiRootFile	4	updateUrl.py	$ENV{'digitizationTaskVersion'}	$urlUpdater					short	$digiDataDir	$digiDataDir		Update URL for digi file.

digi		DIGI	root	$digiDataDir	Raw data in detector space
jobOptions	text	jobOpt	$digiDataDir	config file
ldf
script		script	csh	$digiDataDir	script



$ENV{'digiReportTask'}	Report	$ENV{'dataHead'}		Report on contents of digi file

genReport		1	TestReport.exe	$ENV{'digiReportTaskVersion'}	$ENV{'digiReportTaskDir'}/genDigiTestReportWrapper.pl	short	$digiReportDataDir	$digiReportDataDir		Make report on digi file contents
digiReportUrl	2	updateUrl.py	$ENV{'digiReportTaskVersion'}	$urlUpdater					short	$digiReportDataDir	$digiReportDataDir		Update URL for digi report.

digi
jobOptions	text	jobOpt	$digiReportDataDir		output config file
script		script	csh	$digiReportDataDir		output script file
tarBall		Analysis	tgz	$digiReportDataDir		tarball of report directory



$ENV{'reconTask'}	Reconstruction	$ENV{'dataHead'}		Make recon and merit files

recon		1	recon.pl		$ENV{'reconTaskVersion'}	$ENV{'reconTaskDir'}/reconWrapper.pl		long	$reconDataDir	$reconDataDir		Make recon & merit files
LaunchSVAC	2	TaskLaunch.pl	$ENV{'reconTaskVersion'}	$ENV{'reconTaskDir'}/RunRALaunchWrapper.pl	short	$reconDataDir	$reconDataDir		Launch SVAC tuple creation task
LaunchReport	3	TaskLaunch.pl	$ENV{'reconTaskVersion'}	$ENV{'reconTaskDir'}/genRTRLaunchWrapper.pl	short	$reconDataDir	$reconDataDir		Launch recon report task
reconRootFile	4	updateUrl.py	$ENV{'reconTaskVersion'}	$urlUpdater				short	$reconDataDir	$reconDataDir		Update URL for recon file.
meritRootFile	5	updateUrl.py	$ENV{'reconTaskVersion'}	$urlUpdater				short	$reconDataDir	$reconDataDir		Update URL for merit file.

digi
jobOptions	text	jobOpt	$reconDataDir		options for recon
merit		merit	root	$reconDataDir		merit tuple
recon		RECON	root	$reconDataDir		recon file
script		script	sh	$reconDataDir		script



$ENV{'reconReportTask'}	Report	$ENV{'dataHead'}		Report on contents of recon & digi files

genReport		1	TestReport.exe	$ENV{'reconReportTaskVersion'}	$ENV{'reconReportTaskDir'}/genReconTestReportWrapper.pl	short	$reconReportDataDir		$reconReportDataDir		Create recon report
reconReportUrl	2	updateUrl.py	$ENV{'reconReportTaskVersion'}	$urlUpdater					short	$reconReportDataDir		$reconReportDataDir		Update URL for recon report.

digi
jobOptions	text	jobOpt	$reconReportDataDir		Option file
recon
script		script	csh	$reconReportDataDir		Script
tarBall		Analysis	tgz	$reconReportDataDir		tarball of report directory



$ENV{'svacTupleTask'}	Analysis	$ENV{'dataHead'}		Make SVAC "tuple"

svacTuple		1	RunRootAnalyzer.exe		$ENV{'svacTupleTaskVersion'}	$ENV{'svacTupleTaskDir'}/RunRootAnalyzerWrapper.pl	short	$svacTupleDataDir	$svacTupleDataDir		Make SVAC "tuple"
svacRootFile	2	updateUrl.py		$ENV{'svacTupleTaskVersion'}	$urlUpdater					short	$svacTupleDataDir	$svacTupleDataDir		Update URL for svac tuple file.

digi
histogram		histogram	root	$svacTupleDataDir		SVAC histograms
jobOptions	text	jobOpt	$svacTupleDataDir		option file
recon
script		script	csh	$svacTupleDataDir		script
svac		svac	root	$svacTupleDataDir		SVAC "tuple"
EOT
