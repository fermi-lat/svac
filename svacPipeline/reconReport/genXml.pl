#!/usr/bin/perl -w

use strict;

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

my $urlUpdater = $ENV{'urlUpdateWrapper'};


my $batchgroup = $ENV{'batchgroup'};

# reconReport
my $reconReportDataDir = "$ENV{'calibRoot'}/reconReport/$ENV{'reconReportVersion'}";

my $reconReportXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/pipeline/pipeline.xsd\">
    <name>$ENV{'reconReportTask'}</name>
    <type>Report</type>
    <dataset-base-path>$reconReportDataDir</dataset-base-path>
    <run-log-path>/temp/</run-log-path>
        <executable name=\"genReportWrapper\" version=\"$ENV{'reconReportTaskVersion'}\">
            $ENV{'reconReportTaskDir'}/genReconTestReportWrapper.pl
        </executable>
        <executable name=\"reconReportUrlWrapper\" version=\"$ENV{'svacPlLibVersion'}\">
            $urlUpdater
        </executable>
        <batch-job-configuration name=\"long-job\" queue=\"long\" group=\"$batchgroup\">
            <working-directory>$reconReportDataDir</working-directory>
            <log-file-path>$reconReportDataDir</log-file-path>
        </batch-job-configuration>
        <batch-job-configuration name=\"express-job\" queue=\"express\" group=\"$batchgroup\">
            <working-directory>$reconReportDataDir</working-directory>
            <log-file-path>$reconReportDataDir</log-file-path>
        </batch-job-configuration>
        <foreign-input-file name=\"digi\" pipeline=\"$ENV{'digitizationTask'}\" file=\"digi\"/>
        <foreign-input-file name=\"recon\" pipeline=\"$ENV{'reconTask'}\"/ file=\"recon\">
        <file name=\"jobOptions\" type=\"jobOpt\" file-type=\"text\"/>
        <file name=\"script\" type=\"csh\" file-type=\"script\"/>
        <file name=\"tarBall\" type=\"tgz\" file-type=\"Analysis\"/>
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

