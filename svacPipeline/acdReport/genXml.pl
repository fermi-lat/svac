#!/usr/bin/perl -w

use strict;

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

my $urlUpdater = $ENV{'urlUpdateWrapper'};

my $batchgroup = $ENV{'batchgroup'};

use MakeMeta;
my %metaWrappers = MakeMeta::makeMeta($ENV{'acdReportTaskDir'}, 
									  "runStrip", "alarmHandler");

my $xmlData = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/Pipeline/schemas/1.1/pipeline.xsd\">

    <name>$ENV{'acdReportTask'}</name>
    <type>Analysis</type>
    <dataset-base-path>$ENV{'dataHead'}</dataset-base-path>
    <run-log-path>/temp/</run-log-path>

    <executable name=\"runStrip\" version=\"$ENV{'acdReportTaskVersion'}\">
        $metaWrappers{'runStrip'}
    </executable>
    <executable name=\"alarmHandler\" version=\"$ENV{'acdReportTaskVersion'}\">
        $metaWrappers{'alarmHandler'}
    </executable>

    <batch-job-configuration name=\"medium-job\" queue=\"medium\" group=\"$batchgroup\">
        <working-directory>$ENV{'acdReportDataDirFull'}</working-directory>
        <log-file-path>$ENV{'acdReportDataDirFull'}</log-file-path>
    </batch-job-configuration>
    <batch-job-configuration name=\"express-job\" queue=\"express\" group=\"$batchgroup\">
        <working-directory>$ENV{'acdReportDataDirFull'}</working-directory>
        <log-file-path>$ENV{'acdReportDataDirFull'}</log-file-path>
    </batch-job-configuration>

    <file name=\"acdAlarm\"       file-type=\"xml\"   type=\"text\">
        <path>$ENV{'acdReportDataDir'}</path>
    </file>
    <file name=\"acdTime\"       file-type=\"root\"   type=\"histogram\">
        <path>$ENV{'acdReportDataDir'}</path>
    </file>
    <file name=\"digi\"       file-type=\"root\"   type=\"DIGI\">
        <path>$ENV{'digitizationDataDir'}</path>
    </file>


    <processing-step name=\"runStrip\" executable=\"runStrip\" batch-job-configuration=\"medium-job\">
                    <input-file name=\"digi\"/>
                    <output-file name=\"acdTime\"/>
    </processing-step>
    <processing-step name=\"alarmHandler\" executable=\"alarmHandler\" batch-job-configuration=\"medium-job\">
                    <input-file name=\"acdTime\"/>
                    <output-file name=\"acdAlarm\"/>
    </processing-step>


</pipeline>

";

my $xmlFileName = "$ENV{'acdReportTask'}.xml";
open FIELDS, '>', $xmlFileName;
print FIELDS $xmlData;
close FIELDS;

$xmlData = 
"<?xml version=\"1.0\" ?>
<!-- job optin file for runMuonCalib_ped.exe -->

<ifile cvs_Header=\"\$Header$\" cvs_Revision=\"\$Revision$\" >

  <section name=\"parameters\"> input parameters for ACD pedestal and gain calibration
    <item name=\"outputPrefix\" value=\"acd\"> output file prefix </item>
    <item name=\"configFile\" value=\"$ENV{monitorDir}/src/monconfigacd.xml\"> output file prefix </item>
    <item name=\"htmlFile\" value=\"alarms.html\"> html output file </item>
  </section>
</ifile>
";

$xmlFileName = $ENV{'acdMonitorJo'};
open FIELDS, '>', $xmlFileName;
print FIELDS $xmlData;
close FIELDS;

