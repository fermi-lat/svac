#!/usr/bin/perl -w

use strict;

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

my $urlUpdater = $ENV{'urlUpdateWrapper'};

my $batchgroup = $ENV{'batchgroup'};

use MakeMeta;
my %metaWrappers = (MakeMeta::makeMeta($ENV{'reconReportTaskDir'}, 
									   "genReconTestReport"),
					MakeMeta::makeMeta($ENV{'svacPlLib'}, 
									   "url", "finalCleanup")
					);

my $reconReportXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/Pipeline/schemas/1.1/pipeline.xsd\">

    <name>$ENV{'reconReportTask'}</name>
    <type>Report</type>
    <dataset-base-path>$ENV{'dataHead'}</dataset-base-path>
    <run-log-path>/temp/</run-log-path>

    <executable name=\"genReport\" version=\"$ENV{'reconReportTaskVersion'}\">
        $metaWrappers{'genReconTestReport'}
    </executable>
    <executable name=\"urlWrapper\" version=\"$ENV{'svacVersion'}\">
        $metaWrappers{'url'}
    </executable>
    <executable name=\"finalCleanup\" version=\"$ENV{'svacVersion'}\">
        $metaWrappers{'finalCleanup'}
    </executable>

    <batch-job-configuration name=\"glastdataq-job\" queue=\"glastdataq\" group=\"$batchgroup\">
        <working-directory>$ENV{'reconReportDataDirFull'}</working-directory>
        <log-file-path>$ENV{'reconReportDataDirFull'}</log-file-path>
    </batch-job-configuration>
    <batch-job-configuration name=\"express-job\" queue=\"express\" group=\"$batchgroup\">
        <working-directory>$ENV{'reconReportDataDirFull'}</working-directory>
        <log-file-path>$ENV{'reconReportDataDirFull'}</log-file-path>
    </batch-job-configuration>

    <file name=\"jobOptions\" file-type=\"jobOpt\" type=\"text\">
        <path>$ENV{'reconReportDataDir'}</path>
    </file>
    <file name=\"script\"     file-type=\"csh\"    type=\"script\">
        <path>$ENV{'reconReportDataDir'}</path>
    </file>
    <file name=\"tarBall\"    file-type=\"tgz\"    type=\"Analysis\">
        <path>$ENV{'reconReportDataDir'}</path>
    </file>
    <file name=\"digi\"       file-type=\"root\"   type=\"DIGI\">
        <path>$ENV{'digitizationDataDir'}</path>
    </file>
    <file name=\"recon\"      file-type=\"root\"   type=\"RECON\">
        <path>$ENV{'reconDataDir'}</path>
    </file>

    <processing-step name=\"genReport\" executable=\"genReport\" batch-job-configuration=\"glastdataq-job\">
                    <input-file name=\"digi\"/>
                    <input-file name=\"recon\"/>
                    <output-file name=\"jobOptions\"/>
                    <output-file name=\"script\"/>
                    <output-file name=\"tarBall\"/>
    </processing-step>
    <processing-step name=\"reconReportUrl\" executable=\"urlWrapper\" batch-job-configuration=\"express-job\">
                    <input-file name=\"tarBall\"/>
    </processing-step>
    <processing-step name=\"finalCleanup\" executable=\"finalCleanup\" batch-job-configuration=\"express-job\">
                    <input-file name=\"recon\"/>
    </processing-step>
</pipeline>

";

my $reconReportXmlFileName = "$ENV{'reconReportTask'}.xml";
open FIELDS, '>', $reconReportXmlFileName;
print FIELDS $reconReportXml;
close FIELDS;

