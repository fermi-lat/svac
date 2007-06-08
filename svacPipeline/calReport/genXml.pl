#!/usr/bin/perl -w

use strict;

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

my $urlUpdater = $ENV{'urlUpdateWrapper'};

my $batchgroup = $ENV{'batchgroup'};

use MakeMeta;
my %metaWrappers = MakeMeta::makeMeta($ENV{'calReportTaskDir'}, 
									  "calPed", "calAnal");

my $xmlData = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/Pipeline/schemas/1.1/pipeline.xsd\">

    <name>$ENV{'calReportTask'}</name>
    <type>Analysis</type>
    <dataset-base-path>$ENV{'dataHead'}</dataset-base-path>
    <run-log-path>/temp/</run-log-path>

    <executable name=\"calPed\" version=\"$ENV{'calReportTaskVersion'}\">
        $metaWrappers{'calPed'}
    </executable>
    <executable name=\"calAnal\" version=\"$ENV{'calReportTaskVersion'}\">
        $metaWrappers{'calAnal'}
    </executable>

    <batch-job-configuration name=\"express-job\" queue=\"express\" group=\"$batchgroup\">
        <working-directory>$ENV{'calReportDataDirFull'}</working-directory>
        <log-file-path>$ENV{'calReportDataDirFull'}</log-file-path>
    </batch-job-configuration>
    <batch-job-configuration name=\"medium-job\" queue=\"medium\" group=\"$batchgroup\">
        <working-directory>$ENV{'calReportDataDirFull'}</working-directory>
        <log-file-path>$ENV{'calReportDataDirFull'}</log-file-path>
    </batch-job-configuration>
    <batch-job-configuration name=\"glastdataq-job\" queue=\"glastdataq\" group=\"$batchgroup\">
        <working-directory>$ENV{'calReportDataDirFull'}</working-directory>
        <log-file-path>$ENV{'calReportDataDirFull'}</log-file-path>
    </batch-job-configuration>

    <file name=\"calHist\"       file-type=\"root\"   type=\"histogram\">
        <path>$ENV{'calReportDataDir'}</path>
    </file>
    <file name=\"calReport\"       file-type=\"ps\"   type=\"Analysis\">
        <path>$ENV{'calReportDataDir'}</path>
    </file>
    <file name=\"digi\"       file-type=\"root\"   type=\"DIGI\">
        <path>$ENV{'digitizationDataDir'}</path>
    </file>


    <processing-step name=\"calPed\" executable=\"calPed\" batch-job-configuration=\"glastdataq-job\">
                    <input-file name=\"digi\"/>
                    <output-file name=\"calHist\"/>
    </processing-step>
    <processing-step name=\"calAnal\" executable=\"calAnal\" batch-job-configuration=\"medium-job\">
                    <input-file name=\"calHist\"/>
                    <output-file name=\"calReport\"/>
    </processing-step>


</pipeline>

";

my $xmlFileName = "$ENV{'calReportTask'}.xml";
open FIELDS, '>', $xmlFileName;
print FIELDS $xmlData;
close FIELDS;
