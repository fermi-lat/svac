#!/usr/bin/perl -w

use strict;

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

my $run = '$(RUN_NAME)';

my $raw = 'rawData';
my $cooked = 'rootData';

my $rawRoot = "$raw/$run";
my $rawRootFull = "$ENV{'dataHead'}/$rawRoot";
my $cookedRoot = "$cooked/$run";
my $cookedRootFull = "$ENV{'dataHead'}/$cookedRoot";

#my $calibRoot = "$cookedRoot/$ENV{'calibVersion'}";
my $calibRoot = "$ENV{'calibVersion'}";
my $calibRootFull = "$cookedRootFull/$calibRoot";

my $urlUpdater = $ENV{'urlUpdateWrapper'};

# eLog
my $eLogDataDir = $cookedRoot;

# configReport
#my $configDataDir = "$cookedRoot/configReport/$ENV{'configReportVersion'}";
my $configDataDir = "configReport/$ENV{'configReportVersion'}";
my $configDataDirFull = "$cookedRootFull/$configDataDir";

# digitization
#my $digiDataDir = "$cookedRoot/grRoot";
my $digiDataDir = "grRoot";

# digiReport
#my $digiReportDataDir = "$cookedRoot/digiReport/$ENV{'digiReportVersion'}";
my $digiReportDataDir = "digiReport/$ENV{'digiReportVersion'}";

# recon
my $reconDataDir = "$calibRoot/grRoot";
my $reconDataDirFull = "$cookedRootFull/$reconDataDir";

# reconReport
my $reconReportDataDir = "$calibRoot/reconReport/$ENV{'reconReportVersion'}";

# svacTuple
my $svacTupleDataDir = "$calibRoot/svacRoot/$ENV{'svacTupleVersion'}";

my $batchgroup = "glastdata";

my $rcReportLine = "rcReport	rcReport	xml	$rawRoot		rcreport";
my $ldfLine = "ldf	LDF	fits	$rawRoot		raw data in electronics space";
my $schemaLine = "schema	text	xml	$rawRoot		schema file";
my $snapshotLine = "snapshot	text	xml	$rawRoot		snapshot file";
my $digiLine = "digi		DIGI	root	$digiDataDir	Raw data in detector space";
my $reconLine = "recon		RECON	root	$reconDataDir		recon file";
my $meritLine = "merit		merit	root	$reconDataDir		merit tuple";
my $svacTupleLine = "svac		svac	root	$svacTupleDataDir		SVAC tuple";
my $svacHistLine = "histogram		histogram	root	$svacTupleDataDir		SVAC histograms";


open FIELDS, '>', 'junk';
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
# As far as I can tell, Application and Version are basically comments.
#
# for a dataset:
# Name, Data Type, File Format, Path, Comment



EM2OnlineV01	Conversion	$ENV{'dataHead'}		Convert LDF files to FITS

injectSVAC	2	TaskLaunch.pl	$ENV{'svacOnlineVersion'}	$ENV{'svacOnlineDir'}/SVACWrapper.pl	short	/afs/slac.stanford.edu/u/gl/glast/onlinePipeline/log/	$rawRoot		Launch SVAC tasks

$ldfLine
$rcReportLine
$schemaLine
$snapshotLine



$ENV{'eLogTask'}		Report		$ENV{'dataHead'}		Populate eLog database

populateElogDb	1	populateElogDb.pl	$ENV{'eLogTaskVersion'}	$ENV{'eLogTaskDir'}/populateElogDbWrapper.pl		short	$eLogDataDir	$eLogDataDir		Enter run in electronic logbook.
LaunchDigi	2	TaskLaunch.pl	$ENV{'eLogTaskVersion'}	$ENV{'eLogTaskDir'}/ldfTDLaunchWrapper.pl		short	$eLogDataDir	$eLogDataDir		Launch Digitization task 
LaunchConfRep	3	TaskLaunch.pl	$ENV{'eLogTaskVersion'}	$ENV{'eLogTaskDir'}/ConfTLaunchWrapper.pl		short	$eLogDataDir	$eLogDataDir		Launch configuration report task 
											
$ldfLine
$rcReportLine
$schemaLine
script	script	csh	$eLogDataDir	script
$snapshotLine



$ENV{'configReportTask'}	Report	$ENV{'dataHead'}		Make instrument configuration report

ConfigTables	1	ConfigTables.py	$ENV{'configReportTaskVersion'}	$ENV{'configTaskDir'}/ConfigTablesWrapper.pl	short	$configDataDir	$configDataDir		Create instrument configuration tables.
configReportUrl	2	updateUrl.py	$ENV{'configReportTaskVersion'}	$urlUpdater				short	$configDataDir	$configDataDir		Update URL for instrument configuration report.

$schemaLine
$snapshotLine
tarBall	Analysis	tgz	$configDataDir		Tarball (.tgz) of configuration report directory



$ENV{'digitizationTask'}	Digitization	$ENV{'dataHead'}		Make digi file

Convert		1	ldfToDigi.pl	$ENV{'digitizationTaskVersion'}	$ENV{'digitizationTaskDir'}/ldfToDigiWrapper.pl		medium	$digiDataDir	$digiDataDir		Convert LDF to DIGI
LaunchRecon	2	TaskLaunch.pl	$ENV{'digitizationTaskVersion'}	$ENV{'digitizationTaskDir'}/recLaunchWrapper.pl		short	$digiDataDir	$digiDataDir		launch recon task
LaunchReport	3	TaskLaunch.pl	$ENV{'digitizationTaskVersion'}	$ENV{'digitizationTaskDir'}/genDTRLaunchWrapper.pl	short	$digiDataDir	$digiDataDir		launch digi report task
digiRootFile	4	updateUrl.py	$ENV{'digitizationTaskVersion'}	$urlUpdater					short	$digiDataDir	$digiDataDir		Update URL for digi file.

$digiLine
jobOptions	text	jobOpt	$digiDataDir	config file
$ldfLine
script		script	csh	$digiDataDir	script



$ENV{'digiReportTask'}	Report	$ENV{'dataHead'}		Report on contents of digi file

genReport		1	TestReport.exe	$ENV{'digiReportTaskVersion'}	$ENV{'digiReportTaskDir'}/genDigiTestReportWrapper.pl	short	$digiReportDataDir	$digiReportDataDir		Make report on digi file contents
digiReportUrl	2	updateUrl.py	$ENV{'digiReportTaskVersion'}	$urlUpdater					short	$digiReportDataDir	$digiReportDataDir		Update URL for digi report.

$digiLine
jobOptions	text	jobOpt	$digiReportDataDir		output config file
script		script	csh	$digiReportDataDir		output script file
tarBall		Analysis	tgz	$digiReportDataDir		tarball of report directory



$ENV{'reconTask'}	Reconstruction	$ENV{'dataHead'}		Make recon and merit files

recon		1	recon.pl		$ENV{'reconTaskVersion'}	$ENV{'reconTaskDir'}/reconWrapper.pl		long	$reconDataDir	$reconDataDir		Make recon & merit files
LaunchSVAC	2	TaskLaunch.pl	$ENV{'reconTaskVersion'}	$ENV{'reconTaskDir'}/RunRALaunchWrapper.pl	short	$reconDataDir	$reconDataDir		Launch SVAC tuple creation task
LaunchReport	3	TaskLaunch.pl	$ENV{'reconTaskVersion'}	$ENV{'reconTaskDir'}/genRTRLaunchWrapper.pl	short	$reconDataDir	$reconDataDir		Launch recon report task
reconRootFile	4	updateUrl.py	$ENV{'reconTaskVersion'}	$urlUpdater				short	$reconDataDir	$reconDataDir		Update URL for recon file.
meritRootFile	5	updateUrl.py	$ENV{'reconTaskVersion'}	$urlUpdater				short	$reconDataDir	$reconDataDir		Update URL for merit file.

$digiLine
jobOptions	text	jobOpt	$reconDataDir		options for recon
$meritLine
$reconLine
script		script	sh	$reconDataDir		script



$ENV{'reconReportTask'}	Report	$ENV{'dataHead'}		Report on contents of recon & digi files

genReport		1	TestReport.exe	$ENV{'reconReportTaskVersion'}	$ENV{'reconReportTaskDir'}/genReconTestReportWrapper.pl	short	$reconReportDataDir		$reconReportDataDir		Create recon report
reconReportUrl	2	updateUrl.py	$ENV{'reconReportTaskVersion'}	$urlUpdater					short	$reconReportDataDir		$reconReportDataDir		Update URL for recon report.

$digiLine
jobOptions	text	jobOpt	$reconReportDataDir		Option file
$reconLine
script		script	csh	$reconReportDataDir		Script
tarBall		Analysis	tgz	$reconReportDataDir		tarball of report directory



$ENV{'svacTupleTask'}	Analysis	$ENV{'dataHead'}		Make SVAC "tuple"

svacTuple		1	RunRootAnalyzer.exe		$ENV{'svacTupleTaskVersion'}	$ENV{'svacTupleTaskDir'}/RunRootAnalyzerWrapper.pl	short	$svacTupleDataDir	$svacTupleDataDir		Make SVAC "tuple"
svacRootFile	2	updateUrl.py		$ENV{'svacTupleTaskVersion'}	$urlUpdater					short	$svacTupleDataDir	$svacTupleDataDir		Update URL for svac tuple file.

$digiLine
$svacHistLine
jobOptions	text	jobOpt	$svacTupleDataDir		option file
$reconLine
script		script	csh	$svacTupleDataDir		script
$svacTupleLine
EOT

close FIELDS;

#$ENV{''}


my $onlineXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/pipeline/pipeline.xsd\">
    <name>$ENV{'onlineTask'}</name>
    <type>Conversion</type>
    <dataset-base-path>/nfs/farm/g/glast/u12/EM2</dataset-base-path>
    <run-log-path>/temp/</run-log-path>
        <executable name=\"ldf2fitsWrapper\" version=\"onlineVersion\">
            /nfs/slac/g/svac/common/pipeline/EM2/onlinePipeline/OnlineWrapper.pl
        </executable>
        <executable name=\"injectSVACWrapper\" version=\"$ENV{'svacOnlineVersion'}\">
            $ENV{'svacOnlineDir'}/SVACWrapper.pl
        </executable>
        <batch-job-configuration name=\"short-job\" queue=\"short\" group\"$batchgroup\">
            <working-directory>/nfs/slac/g/svac/common/pipeline/EM2/onlinePipeline/log</working-directory>
            <log-file-path>/nfs/farm/g/glast/u12/EM2/rawData/$(RUN_NAME)</log-file-path>
        </batch-job-configuration>
        <file name=\"ldf\" type=\"fits\" file-type=\"LDF\"></file>
        <file name=\"rcReport\" type=\"xml\" file-type=\"rcReport\"></file>
        <file name=\"schema\" type=\"xml\" file-type=\"text\"></file>
        <file name=\"snapshot\" type=\"xml\" file-type=\"text\"></file>
        <processing-step name=\"ldf2fits\" executable=\"ldf2fitsWrapper\" batch-job-configuration=\"short-job\">
                        <output-file name=\"ldf\"/>
                        <output-file name=\"rcReport\"/>
                        <output-file name=\"schema\"/>
                        <output-file name=\"snapshot\"/>
        </processing-step>
        <processing-step name=\"injectSVAC\" executable=\"injectSVACWrapper\" batch-job-configuration=\"short-job\">
                        <input-file name=\"ldf\"/>
                        <input-file name=\"rcReport\"/>
                        <input-file name=\"schema\"/>
                        <input-file name=\"snapshot\"/>
        </processing-step>
</pipeline>

";

my $onlineFileName = "$ENV{'onlineTask'}.xml";
open FIELDS, '>', $onlineFileName;
print FIELDS $onlineXml;
close FIELDS;


my $updateElogDbXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/pipeline/pipeline.xsd\">

    <name>$ENV{'eLogTask'}</name>
    <type>Report</type>
    <dataset-base-path>$eLogDataDir</dataset-base-path>
    <run-log-path>$eLogDataDir</run-log-path>
        <executable name=\"populateElogDbWrapper\" version=\"$ENV{'eLogTaskVersion'}\">
            $ENV{'eLogTaskDir'}/populateElogDbWrapper.pl
        </executable>
        <executable name=\"LaunchDigiWrapper\" version=\"$ENV{'eLogTaskVersion'}\">
            $ENV{'eLogTaskDir'}/ldfTDLaunchWrapper.pl
        </executable>
        <executable name=\"LaunchConfRepWrapper\" version=\"$ENV{'eLogTaskVersion'}\">
            $ENV{'eLogTaskDir'}/ConfTLaunchWrapper.pl
        </executable>
        <batch-job-configuration name=\"express-job\" queue=\"express\" group\"$batchgroup\">
            <working-directory>$eLogDataDir</working-directory>
            <log-file-path>$eLogDataDir</log-file-path>
        </batch-job-configuration>
        <file name=\"ldf\" type=\"fits\" file-type=\"LDF\"></file>
        <file name=\"rcReport\" type=\"xml\" file-type=\"rcReport\" pipeline=\"$ENV{'onlineTask'}\"></file>
        <file name=\"schema\" type=\"xml\" file-type=\"text\" pipeline=\"$ENV{'onlineTask'}\"></file>
        <file name=\"script\" type=\"csh\" file-type=\"script\"></file>
        <file name=\"snapshot\" type=\"xml\" file-type=\"text\" pipeline=\"$ENV{'onlineTask'}\"></file>
        <processing-step name=\"populateElogDb\" executable=\"populateElogDbWrapper\" batch-job-configuration=\"express-job\">
                        <input-file name=\"rcReport\"/>
                        <output-file name=\"script\"/>
        </processing-step>
        <processing-step name=\"LaunchDigi\" executable=\"LaunchDigiWrapper\" batch-job-configuration=\"express-job\">
                        <input-file name=\"ldf\"/>
        </processing-step>
        <processing-step name=\"LaunchConfRep\" executable=\"LaunchConfRepWrapper\" batch-job-configuration=\"express-job\">
                        <input-file name=\"schema\"/>
                        <input-file name=\"snapshot\"/>
        </processing-step>
</pipeline>
";

my $eLogXmlFileName = "$ENV{'eLogTask'}.xml";
open FIELDS, '>', $eLogXmlFileName;
print FIELDS $updateElogDbXml;
close FIELDS;


my $configReportXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/pipeline/pipeline.xsd\">
    <name>configReport-EM2-v1r0</name>
    <type>Digitization</type>
    <dataset-base-path>/nfs/farm/g/glast/u12/EM2</dataset-base-path>
    <run-log-path>/temp/</run-log-path>
        <executable name=\"ConfigTablesWrapper\" version=\"v1r0\">
            /nfs/slac/g/svac/common/pipeline/EM2/svacPipeline/configReport/v1r0/ConfigTablesWrapper.pl
        </executable>
        <executable name=\"configReportUrlWrapper\" version=\"v1r0\">
            /nfs/slac/g/svac/common/pipeline/EM2/svacPipeline/lib/urlWrapper.pl
        </executable>
        <batch-job-configuration name=\"express-job\" queue=\"express\" group\"$batchgroup\">
            <working-directory>/nfs/farm/g/glast/u12/EM2/rootData/$(RUN_NAME)/configReport/v1r0p0</working-directory>
            <log-file-path>/nfs/farm/g/glast/u12/EM2/log//$(RUN_NAME)/</log-file-path>
        </batch-job-configuration>
        <batch-job-configuration name=\"short-job\" queue=\"short\" group\"$batchgroup\">
            <working-directory>/nfs/farm/g/glast/u12/EM2/rootData/$(RUN_NAME)/configReport/v1r0p0</working-directory>
            <log-file-path>/nfs/farm/g/glast/u12/EM2/log//$(RUN_NAME)/</log-file-path>
        </batch-job-configuration>
        <file name=\"schema\" type=\"xml\" file-type=\"text\">rawData/$(RUN_NAME)</file>
        <file name=\"snapshot\" type=\"xml\" file-type=\"text\">rawData/$(RUN_NAME)</file>
        <file name=\"tarBall\" type=\"tgz\" file-type=\"Analysis\">rootData/$(RUN_NAME)/configReport/v1r0p0</file>
        <processing-step name=\"ConfigTables\" executable=\"ConfigTablesWrapper\" batch-job-configuration=\"short-job\">
                        <input-file name=\"schema\"/>
                        <input-file name=\"snapshot\"/>
                        <output-file name=\"tarBall\"/>
        </processing-step>
        <processing-step name=\"configReportUrl\" executable=\"configReportUrlWrapper\" batch-job-configuration=\"express-job\">
                        <input-file name=\"tarBall\"/>
        </processing-step>
</pipeline>

";

my $configReportXmlFileName = "$ENV{'configReportTask'}.xml";
open FIELDS, '>', $configReportXmlFileName;
print FIELDS $configReportXml;
close FIELDS;


my $digitizationXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/pipeline/pipeline.xsd\">
    <name>digitization-EM2-v1r0</name>
    <type>Digitization</type>
    <dataset-base-path>/nfs/farm/g/glast/u12/EM2</dataset-base-path>
    <run-log-path>/temp/</run-log-path>
        <executable name=\"ConvertWrapper\" version=\"v1r0\">
            /nfs/slac/g/svac/common/pipeline/EM2/svacPipeline/digitization/v1r0/ldfToDigiWrapper.pl
        </executable>
        <executable name=\"LaunchReconWrapper\" version=\"v1r0\">
            /nfs/slac/g/svac/common/pipeline/EM2/svacPipeline/digitization/v1r0/recLaunchWrapper.pl
        </executable>
        <executable name=\"LaunchReportWrapper\" version=\"v1r0\">
            /nfs/slac/g/svac/common/pipeline/EM2/svacPipeline/digitization/v1r0/genDTRLaunchWrapper.pl
        </executable>
        <executable name=\"digiRootFileWrapper\" version=\"v1r0\">
            /nfs/slac/g/svac/common/pipeline/EM2/svacPipeline/lib/urlWrapper.pl
        </executable>
        <batch-job-configuration name=\"express-job\" queue=\"express\" group\"$batchgroup\">
            <working-directory>/nfs/farm/g/glast/u12/EM2/rootData/$(RUN_NAME)/grRoot</working-directory>
            <log-file-path>/nfs/farm/g/glast/u12/EM2/log//$(RUN_NAME)/</log-file-path>
        </batch-job-configuration>
        <batch-job-configuration name=\"medium-job\" queue=\"medium\" group\"$batchgroup\">
            <working-directory>/nfs/farm/g/glast/u12/EM2/rootData/$(RUN_NAME)/grRoot</working-directory>
            <log-file-path>/nfs/farm/g/glast/u12/EM2/log//$(RUN_NAME)/</log-file-path>
        </batch-job-configuration>
        <file name=\"digi\" type=\"root\" file-type=\"DIGI\">rootData/$(RUN_NAME)/grRoot</file>
        <file name=\"jobOptions\" type=\"jobOpt\" file-type=\"text\">rootData/$(RUN_NAME)/grRoot</file>
        <file name=\"ldf\" type=\"fits\" file-type=\"LDF\">rawData/$(RUN_NAME)</file>
        <file name=\"script\" type=\"csh\" file-type=\"script\">rootData/$(RUN_NAME)/grRoot</file>
        <processing-step name=\"Convert\" executable=\"ConvertWrapper\" batch-job-configuration=\"medium-job\">
                        <input-file name=\"ldf\"/>
                        <output-file name=\"digi\"/>
                        <output-file name=\"script\"/>
                        <output-file name=\"jobOptions\"/>
        </processing-step>
        <processing-step name=\"LaunchRecon\" executable=\"LaunchReconWrapper\" batch-job-configuration=\"express-job\">
                        <input-file name=\"digi\"/>
        </processing-step>
        <processing-step name=\"LaunchReport\" executable=\"LaunchReportWrapper\" batch-job-configuration=\"express-job\">
                        <input-file name=\"digi\"/>
        </processing-step>
        <processing-step name=\"digiRootFile\" executable=\"digiRootFileWrapper\" batch-job-configuration=\"express-job\">
                        <input-file name=\"digi\"/>
        </processing-step>
</pipeline>

";

my $digitizationXmlFileName = "$ENV{'digitizationTask'}.xml";
open FIELDS, '>', $digitizationXmlFileName;
print FIELDS $digitizationXml;
close FIELDS;


my $digiReportXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/pipeline/pipeline.xsd\">
    <name>digiReport-EM2-v1r0</name>
    <type>Report</type>
    <dataset-base-path>/nfs/farm/g/glast/u12/EM2</dataset-base-path>
    <run-log-path>/temp/</run-log-path>
        <executable name=\"genReportWrapper\" version=\"v1r0\">
            /nfs/slac/g/svac/common/pipeline/EM2/svacPipeline/digiReport/v1r0/genDigiTestReportWrapper.pl
        </executable>
        <executable name=\"digiReportUrlWrapper\" version=\"v1r0\">
            /nfs/slac/g/svac/common/pipeline/EM2/svacPipeline/lib/urlWrapper.pl
        </executable>
        <batch-job-configuration name=\"medium-job\" queue=\"medium\" group\"$batchgroup\">
            <working-directory>/nfs/farm/g/glast/u12/EM2/rootData/$(RUN_NAME)//digiReport/v1r0p0</working-directory>
            <log-file-path>/nfs/farm/g/glast/u12/EM2/log//$(RUN_NAME)/</log-file-path>
        </batch-job-configuration>
        <batch-job-configuration name=\"express-job\" queue=\"express\" group\"$batchgroup\">
            <working-directory>/nfs/farm/g/glast/u12/EM2/rootData/$(RUN_NAME)//digiReport/v1r0p0</working-directory>
            <log-file-path>/nfs/farm/g/glast/u12/EM2/log//$(RUN_NAME)/</log-file-path>
        </batch-job-configuration>
        <file name=\"digi\" type=\"root\" file-type=\"DIGI\">rootData/$(RUN_NAME)/grRoot</file>
        <file name=\"jobOptions\" type=\"jobOpt\" file-type=\"text\">rootData/$(RUN_NAME)/digiReport/v1r0p0</file>
        <file name=\"script\" type=\"csh\" file-type=\"script\">rootData/$(RUN_NAME)/digiReport/v1r0p0</file>
        <file name=\"tarBall\" type=\"tgz\" file-type=\"Analysis\">rootData/$(RUN_NAME)/digiReport/v1r0p0</file>
        <processing-step name=\"genReport\" executable=\"genReportWrapper\" batch-job-configuration=\"medium-job\">
                        <input-file name=\"digi\"/>
                        <output-file name=\"jobOptions\"/>
                        <output-file name=\"script\"/>
                        <output-file name=\"tarBall\"/>
        </processing-step>
        <processing-step name=\"digiReportUrl\" executable=\"digiReportUrlWrapper\" batch-job-configuration=\"express-job\">
                        <input-file name=\"tarBall\"/>
        </processing-step>
</pipeline>

";

my $digiReportXmlFileName = "$ENV{'digiReportTask'}.xml";
open FIELDS, '>', $digiReportXmlFileName;
print FIELDS $digiReportXml;
close FIELDS;


my $reconXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
  xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
  xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
  xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/pipeline/pipeline.xsd\">

  <name>$ENV{'reconTask'}</name>
  <type>Reconstruction</type>
  <dataset-base-path>$cookedRootFull</dataset-base-path>
  <run-log-path>/temp/</run-log-path>

  <executable name=\"reconWrapper\" version=\"$ENV{'reconTaskVersion'}\">
    $ENV{'reconTaskDir'}/reconWrapper.pl
  </executable>

  <executable name=\"RunRALaunchWrapper\" version=\"$ENV{'reconTaskVersion'}\">
    $ENV{'reconTaskDir'}/RunRALaunchWrapper.pl
  </executable>

  <executable name=\"genRTRLaunchWrapper\" version=\"$ENV{'reconTaskVersion'}\">
    $ENV{'reconTaskDir'}/genRTRLaunchWrapper.pl
  </executable>

  <executable name=\"urlWrapper\" version=\"$ENV{'reconTaskVersion'}\">
    $urlUpdater
  </executable>

  <batch-job-configuration name=\"xlong-job\" queue=\"xlong\" group\"$batchgroup\">
    <working-directory>$reconDataDirFull</working-directory>
    <log-file-path>$reconDataDirFull</log-file-path>
  </batch-job-configuration>

  <batch-job-configuration name=\"express-job\" queue=\"express\" group\"$batchgroup\">
    <working-directory>$reconDataDirFull</working-directory>
    <log-file-path>$reconDataDirFull</log-file-path>
  </batch-job-configuration>

  <file name=\"digi\"       type=\"DIGI\"   file-type=\"root\">$digiDataDir</file>
  <file name=\"jobOptions\" type=\"text\"   file-type=\"jobOpt\">$reconDataDir</file>
  <file name=\"merit\"      type=\"merit\"  file-type=\"root\">$reconDataDir</file>
  <file name=\"recon\"      type=\"RECON\"  file-type=\"root\">$reconDataDir</file>
  <file name=\"script\"     type=\"script\" file-type=\"csh\">$reconDataDir</file>

  <processing-step name=\"recon\" executable=\"reconWrapper\" batch-job-configuration=\"xlong-job\">
    <input-file name=\"digi\"/>
    <output-file name=\"jobOptions\"/>
    <output-file name=\"merit\"/>
    <output-file name=\"recon\"/>
    <output-file name=\"script\"/>
  </processing-step>

  <processing-step name=\"LaunchSVAC\" executable=\"RunRALaunchWrapper\" batch-job-configuration=\"express-job\">
    <input-file name=\"digi\"/>
    <input-file name=\"recon\"/>
  </processing-step>

  <processing-step name=\"LaunchReport\" executable=\"genRTRLaunchWrapper\" batch-job-configuration=\"express-job\">
    <input-file name=\"digi\"/>
    <input-file name=\"recon\"/>
  </processing-step>

  <processing-step name=\"reconRootFile\" executable=\"urlWrapper\" batch-job-configuration=\"express-job\">
    <input-file name=\"recon\"/>
  </processing-step>

  <processing-step name=\"meritRootFile\" executable=\"urlWrapper\" batch-job-configuration=\"express-job\">
    <input-file name=\"merit\"/>
  </processing-step>

</pipeline>
";

my $reconXmlFileName = "$ENV{'reconTask'}.xml";
open FIELDS, '>', $reconXmlFileName;
print FIELDS $reconXml;
close FIELDS;


my $reconReportXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/pipeline/pipeline.xsd\">
    <name>reconReport-EM2-v1r0</name>
    <type>Report</type>
    <dataset-base-path>/nfs/farm/g/glast/u12/EM2</dataset-base-path>
    <run-log-path>/temp/</run-log-path>
        <executable name=\"genReportWrapper\" version=\"v1r0\">
            /nfs/slac/g/svac/common/pipeline/EM2/svacPipeline/reconReport/v1r0/genReconTestReportWrapper.pl
        </executable>
        <executable name=\"reconReportUrlWrapper\" version=\"v1r0\">
            /nfs/slac/g/svac/common/pipeline/EM2/svacPipeline/lib/urlWrapper.pl
        </executable>
        <batch-job-configuration name=\"long-job\" queue=\"long\" group\"$batchgroup\">
            <working-directory>/nfs/farm/g/glast/u12/EM2/rootData/$(RUN_NAME)/calib-v1r0/reconReport/v1r0p0</working-directory>
            <log-file-path>/nfs/farm/g/glast/u12/EM2/log//$(RUN_NAME)/</log-file-path>
        </batch-job-configuration>
        <batch-job-configuration name=\"express-job\" queue=\"express\" group\"$batchgroup\">
            <working-directory>/nfs/farm/g/glast/u12/EM2/rootData/$(RUN_NAME)/calib-v1r0/reconReport/v1r0p0</working-directory>
            <log-file-path>/nfs/farm/g/glast/u12/EM2/log//$(RUN_NAME)/</log-file-path>
        </batch-job-configuration>
        <file name=\"digi\" type=\"root\" file-type=\"DIGI\">rootData/$(RUN_NAME)/grRoot</file>
        <file name=\"jobOptions\" type=\"jobOpt\" file-type=\"text\">rootData/$(RUN_NAME)/calib-v1r0/reconReport/v1r0p0</file>
        <file name=\"recon\" type=\"root\" file-type=\"RECON\">rootData/$(RUN_NAME)/calib-v1r0/grRoot</file>
        <file name=\"script\" type=\"csh\" file-type=\"script\">rootData/$(RUN_NAME)/calib-v1r0/reconReport/v1r0p0</file>
        <file name=\"tarBall\" type=\"tgz\" file-type=\"Analysis\">rootData/$(RUN_NAME)/calib-v1r0/reconReport/v1r0p0</file>
        <processing-step name=\"genReport\" executable=\"genReportWrapper\" batch-job-configuration=\"long-job\">
                        <input-file name=\"digi\"/>
                        <input-file name=\"recon\"/>
                        <output-file name=\"jobOptions\"/>
                        <output-file name=\"script\"/>
                        <output-file name=\"tarBall\"/>
        </processing-step>
        <processing-step name=\"reconReportUrl\" executable=\"reconReportUrlWrapper\" batch-job-configuration=\"express-job\">
                        <input-file name=\"tarBall\"/>
        </processing-step>
</pipeline>

";

my $reconReportXmlFileName = "$ENV{'reconReportTask'}.xml";
open FIELDS, '>', $reconReportXmlFileName;
print FIELDS $reconReportXml;
close FIELDS;


my $svacTupleXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/pipeline/pipeline.xsd\">
    <name>svacTuple-EM2-v1r0</name>
    <type>Analysis</type>
    <dataset-base-path>/nfs/farm/g/glast/u12/EM2</dataset-base-path>
    <run-log-path>/temp/</run-log-path>
        <executable name=\"svacTupleWrapper\" version=\"v1r0\">
            /nfs/slac/g/svac/common/pipeline/EM2/svacPipeline/svacTuple/v1r0/RunRootAnalyzerWrapper.pl
        </executable>
        <executable name=\"svacRootFileWrapper\" version=\"v1r0\">
            /nfs/slac/g/svac/common/pipeline/EM2/svacPipeline/lib/urlWrapper.pl
        </executable>
        <batch-job-configuration name=\"long-job\" queue=\"long\" group\"$batchgroup\">
            <working-directory>/nfs/farm/g/glast/u12/EM2/rootData/$(RUN_NAME)/calib-v1r0/svacRoot/emRootv0r0</working-directory>
            <log-file-path>/nfs/farm/g/glast/u12/EM2/log//$(RUN_NAME)/</log-file-path>
        </batch-job-configuration>
        <batch-job-configuration name=\"express-job\" queue=\"express\" group\"$batchgroup\">
            <working-directory>/nfs/farm/g/glast/u12/EM2/rootData/$(RUN_NAME)/calib-v1r0/svacRoot/emRootv0r0</working-directory>
            <log-file-path>/nfs/farm/g/glast/u12/EM2/log//$(RUN_NAME)/</log-file-path>
        </batch-job-configuration>
        <file name=\"digi\" type=\"root\" file-type=\"DIGI\">rootData/$(RUN_NAME)/grRoot</file>
        <file name=\"histogram\" type=\"root\" file-type=\"histogram\">rootData/$(RUN_NAME)/calib-v1r0/svacRoot/emRootv0r0</file>
        <file name=\"jobOptions\" type=\"jobOpt\" file-type=\"text\">rootData/$(RUN_NAME)/calib-v1r0/svacRoot/emRootv0r0</file>
        <file name=\"recon\" type=\"root\" file-type=\"RECON\">rootData/$(RUN_NAME)/calib-v1r0/grRoot</file>
        <file name=\"script\" type=\"csh\" file-type=\"script\">rootData/$(RUN_NAME)/calib-v1r0/svacRoot/emRootv0r0</file>
        <file name=\"svac\" type=\"root\" file-type=\"svac\">rootData/$(RUN_NAME)/calib-v1r0/svacRoot/emRootv0r0</file>
        <processing-step name=\"svacTuple\" executable=\"svacTupleWrapper\" batch-job-configuration=\"long-job\">
                        <input-file name=\"digi\"/>
                        <input-file name=\"recon\"/>
                        <output-file name=\"histogram\"/>
                        <output-file name=\"svac\"/>
                        <output-file name=\"script\"/>
                        <output-file name=\"jobOptions\"/>
        </processing-step>
        <processing-step name=\"svacRootFile\" executable=\"svacRootFileWrapper\" batch-job-configuration=\"express-job\">
                        <input-file name=\"svac\"/>
        </processing-step>
</pipeline>

";

my $svacTupleXmlFileName = "$ENV{'svacTupleTask'}.xml";
open FIELDS, '>', $svacTupleXmlFileName;
print FIELDS $svacTupleXml;
close FIELDS;

