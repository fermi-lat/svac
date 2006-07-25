#!/usr/bin/perl -w

use strict;

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

my $urlUpdater = $ENV{'urlUpdateWrapper'};

my $batchgroup = $ENV{'batchgroup'};

my $xmlData = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/Pipeline/schemas/1.1/pipeline.xsd\">

    <name>$ENV{'tkrReportTask'}</name>
    <type>Analysis</type>
    <dataset-base-path>$ENV{'dataHead'}</dataset-base-path>
    <run-log-path>/temp/</run-log-path>
        <executable name=\"tkrReportWrapper\" version=\"$ENV{'tkrReportTaskVersion'}\">
            $ENV{'tkrReportTaskDir'}/genTkrReportWrapper.pl
        </executable>
        <executable name=\"tkrReportUrlWrapper\" version=\"$ENV{'svacVersion'}\">
            $urlUpdater
        </executable>

        <batch-job-configuration name=\"medium-job\" queue=\"medium\" group=\"$batchgroup\">
            <working-directory>$ENV{'tkrReportDataDirFull'}</working-directory>
            <log-file-path>$ENV{'tkrReportDataDirFull'}</log-file-path>
        </batch-job-configuration>
        <batch-job-configuration name=\"express-job\" queue=\"express\" group=\"$batchgroup\">
            <working-directory>$ENV{'tkrReportDataDirFull'}</working-directory>
            <log-file-path>$ENV{'tkrReportDataDirFull'}</log-file-path>
        </batch-job-configuration>

        <file name=\"svac\"       file-type=\"root\"   type=\"svac\"     >
            <path>$ENV{'svacTupleDataDir'}</path>
        </file>
        <file name=\"tarBall\"       file-type=\"tgz\"   type=\"Analysis\"     >
            <path>$ENV{'tkrReportDataDir'}</path>
        </file>

        <processing-step name=\"genReport\" executable=\"tkrReportWrapper\" batch-job-configuration=\"medium-job\">
                        <input-file name=\"svac\"/>
                        <output-file name=\"tarBall\"/>
        </processing-step>
        <processing-step name=\"tkrReportUrl\" executable=\"tkrReportUrlWrapper\" batch-job-configuration=\"express-job\">
                        <input-file name=\"tarBall\"/>
        </processing-step>
</pipeline>

";

my $xmlFileName = "$ENV{'tkrReportTask'}.xml";
open FIELDS, '>', $xmlFileName;
print FIELDS $xmlData;
close FIELDS;

