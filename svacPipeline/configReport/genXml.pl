#!/usr/bin/perl -w

use strict;

use lib "$ENV{'svacPlRoot'}/lib-current";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup-current/svacPlSetup.cshrc");

my $urlUpdater = $ENV{'urlUpdateWrapper'};


my $batchgroup = $ENV{'batchgroup'};

# configReport
#my $configDataDir = "$ENV{'svacHead'}/configReport/$ENV{'configReportVersion'}";


my $configReportXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/pipeline.xsd\">

    <name>$ENV{'configReportTask'}</name>
    <type>Report</type>
    <dataset-base-path>$ENV{'dataHead'}</dataset-base-path>
    <run-log-path>/temp/</run-log-path>
        <executable name=\"ConfigTables\" version=\"$ENV{'configReportTaskVersion'}\">
            $ENV{'configTaskDir'}/ConfigTablesWrapper.pl
        </executable>
        <executable name=\"configReportUrl\" version=\"$ENV{'svacPlLibVersion'}\">
            $urlUpdater
        </executable>

        <batch-job-configuration name=\"express-job\" queue=\"express\" group=\"$batchgroup\">
            <working-directory>$ENV{'configTablesDataDirFull'}</working-directory>
            <log-file-path>$ENV{'configTablesDataDirFull'}</log-file-path>
        </batch-job-configuration>
        <batch-job-configuration name=\"short-job\" queue=\"short\" group=\"$batchgroup\">
            <working-directory>$ENV{'configTablesDataDirFull'}</working-directory>
            <log-file-path>$ENV{'configTablesDataDirFull'}</log-file-path>
        </batch-job-configuration>

        <file file-type=\"xml\" name=\"snapshot\" type=\"text\"    >$ENV{'onlineDataDir'}</file>
        <file file-type=\"xml\" name=\"schema\"   type=\"text\"    >$ENV{'onlineDataDir'}</file>
        <file file-type=\"tgz\" name=\"tarBall\"  type=\"Analysis\">$ENV{'configTablesDataDir'}</file>

        <processing-step name=\"ConfigTables\" executable=\"ConfigTables\" batch-job-configuration=\"short-job\">
                        <input-file name=\"schema\"/>
                        <input-file name=\"snapshot\"/>
                        <output-file name=\"tarBall\"/>
        </processing-step>
        <processing-step name=\"configReportUrl\" executable=\"configReportUrl\" batch-job-configuration=\"express-job\">
                        <input-file name=\"tarBall\"/>
        </processing-step>
</pipeline>

";

my $configReportXmlFileName = "$ENV{'configReportTask'}.xml";
open FIELDS, '>', $configReportXmlFileName;
print FIELDS $configReportXml;
close FIELDS;

