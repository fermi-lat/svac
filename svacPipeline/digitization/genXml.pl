#!/usr/bin/perl -w

use strict;

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

my $urlUpdater = $ENV{'urlUpdateWrapper'};


my $batchgroup = $ENV{'batchgroup'};

# digitization
my $digiDataDir = "$ENV{'svacEmDir'}/grRoot";

my $digitizationXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/pipeline/pipeline.xsd\">
    <name>$ENV{'digitizationTask'}</name>
    <type>Digitization</type>
    <dataset-base-path>$digiDataDir</dataset-base-path>
    <run-log-path>/temp/</run-log-path>
        <executable name=\"ConvertWrapper\" version=\"$ENV{'digitizationTaskVersion'}\">
            $ENV{'digitizationTaskDir'}/ldfToDigiWrapper.pl
        </executable>
        <executable name=\"LaunchReconWrapper\" version=\"$ENV{'digitizationTaskVersion'}\">
            $ENV{'digitizationTaskDir'}/recLaunchWrapper.pl
        </executable>
        <executable name=\"LaunchReportWrapper\" version=\"$ENV{'digitizationTaskVersion'}\">
            $ENV{'digitizationTaskDir'}/genDTRLaunchWrapper.pl
        </executable>
        <executable name=\"digiRootFileWrapper\" version=\"$ENV{'svacPlLibVersion'}\">
            $urlUpdater
        </executable>
        <batch-job-configuration name=\"express-job\" queue=\"express\" group\"$batchgroup\">
            <working-directory>$digiDataDir</working-directory>
            <log-file-path>$digiDataDir</log-file-path>
        </batch-job-configuration>
        <batch-job-configuration name=\"medium-job\" queue=\"medium\" group\"$batchgroup\">
            <working-directory>$digiDataDir</working-directory>
            <log-file-path>$digiDataDir</log-file-path>
        </batch-job-configuration>
        <foreign-input-file name=\"ldf\" pipeline=\"$ENV{'onlineTask'}\" name=\"ldf\"/>
        <file name=\"digi\" type=\"root\" file-type=\"DIGI\"/>
        <file name=\"jobOptions\" type=\"jobOpt\" file-type=\"text\"/>
        <file name=\"script\" type=\"csh\" file-type=\"script\"/>
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

