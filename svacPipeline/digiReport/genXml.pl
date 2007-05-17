#!/usr/bin/perl -w

use strict;

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

my $urlUpdater = $ENV{'urlUpdateWrapper'};

my $batchgroup = $ENV{'batchgroup'};

use MakeMeta;
my %metaWrappers = (MakeMeta::makeMeta($ENV{'digiReportTaskDir'}, 
									   "genDigiTestReport"),
					MakeMeta::makeMeta($ENV{'svacPlLib'}, 
									   "url")
					);

my $digiReportXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/Pipeline/schemas/1.1/pipeline.xsd\">

    <name>$ENV{'digiReportTask'}</name>
    <type>Report</type>
    <dataset-base-path>$ENV{'dataHead'}</dataset-base-path>
    <run-log-path>/temp/</run-log-path>

    <executable name=\"genReport\" version=\"$ENV{'digiReportTaskVersion'}\">
        $metaWrappers{'genDigiTestReport'}
    </executable>
    <executable name=\"urlWrapper\" version=\"$ENV{'svacVersion'}\">
        $metaWrappers{'url'}
    </executable>

    <batch-job-configuration name=\"glastdataq-job\" queue=\"glastdataq\" group=\"$batchgroup\">
        <working-directory>$ENV{'digiReportDataDirFull'}</working-directory>
        <log-file-path>$ENV{'digiReportDataDirFull'}</log-file-path>
    </batch-job-configuration>
    <batch-job-configuration name=\"express-job\" queue=\"express\" group=\"$batchgroup\">
        <working-directory>$ENV{'digiReportDataDirFull'}</working-directory>
        <log-file-path>$ENV{'digiReportDataDirFull'}</log-file-path>
    </batch-job-configuration>

    <file name=\"jobOptions\" file-type=\"jobOpt\" type=\"text\">
        <path>$ENV{'digiReportDataDir'}</path>
    </file>
    <file name=\"script\"     file-type=\"csh\"    type=\"script\">
        <path>$ENV{'digiReportDataDir'}</path>
    </file>
    <file name=\"histogram\"    file-type=\"root\"    type=\"histogram\">
        <path>$ENV{'digiReportDataDir'}</path>
    </file>
    <file name=\"tarBall\"    file-type=\"tgz\"    type=\"Analysis\">
        <path>$ENV{'digiReportDataDir'}</path>
    </file>
    <file name=\"digi\"       file-type=\"root\"   type=\"DIGI\">
        <path>$ENV{'digitizationDataDir'}</path>
    </file>

    <processing-step name=\"genReport\" executable=\"genReport\" batch-job-configuration=\"glastdataq-job\">
                    <input-file name=\"digi\"/>
                    <output-file name=\"jobOptions\"/>
                    <output-file name=\"script\"/>
                    <output-file name=\"histogram\"/>
                    <output-file name=\"tarBall\"/>
    </processing-step>
    <processing-step name=\"$ENV{'tkrReportTask'}\" executable=\"taskLauncher\" batch-job-configuration=\"express-job\">
                    <input-file name=\"histogram\"/>
    </processing-step>
    <processing-step name=\"digiReportUrl\" executable=\"urlWrapper\" batch-job-configuration=\"express-job\">
                    <input-file name=\"tarBall\"/>
    </processing-step>
</pipeline>

";

my $digiReportXmlFileName = "$ENV{'digiReportTask'}.xml";
open FIELDS, '>', $digiReportXmlFileName;
print FIELDS $digiReportXml;
close FIELDS;
