#!/usr/bin/perl -w

use strict;

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

my $urlUpdater = $ENV{'urlUpdateWrapper'};


my $batchgroup = $ENV{'batchgroup'};

# digiReport
my $digiReportDataDir = "$ENV{'svacEmDir'}/digiReport/$ENV{'digiReportVersion'}";

my $digiReportXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/pipeline.xsd\">

    <name>$ENV{'digiReportTask'}</name>
    <type>Report</type>
    <dataset-base-path>$digiReportDataDir</dataset-base-path>
    <run-log-path>/temp/</run-log-path>
        <executable name=\"genReportWrapper\" version=\"$ENV{'digiReportTaskVersion'}\">
            $ENV{'digiReportTaskDir'}/genDigiTestReportWrapper.pl
        </executable>
        <executable name=\"digiReportUrlWrapper\" version=\"$ENV{'svacPlLibVersion'}\">
            $urlUpdater
        </executable>

        <batch-job-configuration name=\"medium-job\" queue=\"medium\" group=\"$batchgroup\">
            <working-directory>$digiReportDataDir</working-directory>
            <log-file-path>$digiReportDataDir</log-file-path>
        </batch-job-configuration>
        <batch-job-configuration name=\"express-job\" queue=\"express\" group=\"$batchgroup\">
            <working-directory>$digiReportDataDir</working-directory>
            <log-file-path>$digiReportDataDir</log-file-path>
        </batch-job-configuration>

        <file name=\"jobOptions\" type=\"jobOpt\" file-type=\"text\"/>
        <file name=\"script\" type=\"csh\" file-type=\"script\"/>
        <file name=\"tarBall\" type=\"tgz\" file-type=\"Analysis\"/>

        <foreign-input-file name=\"digi\" pipeline=\"$ENV{'digitizationTask'}\" file=\"digi\"/>

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
