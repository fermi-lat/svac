#!/usr/bin/perl -w

use strict;

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

my $urlUpdater = $ENV{'urlUpdateWrapper'};


my $batchgroup = $ENV{'batchgroup'};

# configReport
my $configDataDir = "$ENV{'svacHead'}/configReport/$ENV{'configReportVersion'}";


my $configReportXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/pipeline/pipeline.xsd\">
    <name>$ENV{'configReportTask'}</name>
    <type>>Report</type>
    <dataset-base-path>$configDataDir</dataset-base-path>
    <run-log-path>/temp/</run-log-path>
        <executable name=\"ConfigTablesWrapper\" version=\"$ENV{'configReportTaskVersion'}\">
            $ENV{'configTaskDir'}/ConfigTablesWrapper.pl
        </executable>
        <executable name=\"configReportUrlWrapper\" version=\"$ENV{'svacPlLibVersion'}\">
            $urlUpdater
        </executable>
        <batch-job-configuration name=\"express-job\" queue=\"express\" group=\"$batchgroup\">
            <working-directory>$configDataDir</working-directory>
            <log-file-path>$configDataDir</log-file-path>
        </batch-job-configuration>
        <batch-job-configuration name=\"short-job\" queue=\"short\" group=\"$batchgroup\">
            <working-directory>$configDataDir</working-directory>
            <log-file-path>$configDataDir</log-file-path>
        </batch-job-configuration>
        <foreign-input-file name=\"snapshot\" pipeline=\"$ENV{'onlineTask'}\" name=\"snapshot\"/>
        <file name=\"tarBall\" type=\"tgz\" file-type=\"Analysis\"/>
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

