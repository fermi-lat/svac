#!/usr/bin/perl -w

use strict;

use lib "$ENV{'svacPlRoot'}/lib-current";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup-current/svacPlSetup.cshrc");

my $urlUpdater = $ENV{'urlUpdateWrapper'};


my $batchgroup = $ENV{'batchgroup'};

# digitization
my $digiDataDir = "$ENV{'svacEmDir'}/grRoot";

my $digitizationXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/pipeline.xsd\">

    <name>$ENV{'digitizationTask'}</name>
    <type>Digitization</type>
    <dataset-base-path>$ENV{'dataHead'}</dataset-base-path>
    <run-log-path>/temp/</run-log-path>
        <executable name=\"Convert\" version=\"$ENV{'digitizationTaskVersion'}\">
            $ENV{'digitizationTaskDir'}/ldfToDigiWrapper.pl
        </executable>
        <executable name=\"LaunchRecon\" version=\"$ENV{'digitizationTaskVersion'}\">
            $ENV{'digitizationTaskDir'}/recLaunchWrapper.pl
        </executable>
        <executable name=\"LaunchReport\" version=\"$ENV{'digitizationTaskVersion'}\">
            $ENV{'digitizationTaskDir'}/genDTRLaunchWrapper.pl
        </executable>
        <executable name=\"digiRootFile\" version=\"$ENV{'svacPlLibVersion'}\">
            $urlUpdater
        </executable>

        <batch-job-configuration name=\"express-job\" queue=\"express\" group=\"$batchgroup\">
            <working-directory>$ENV{'digitizationDataDirFull'}</working-directory>
            <log-file-path>$ENV{'digitizationDataDirFull'}</log-file-path>
        </batch-job-configuration>
        <batch-job-configuration name=\"medium-job\" queue=\"medium\" group=\"$batchgroup\">
            <working-directory>$ENV{'digitizationDataDirFull'}</working-directory>
            <log-file-path>$ENV{'digitizationDataDirFull'}</log-file-path>
        </batch-job-configuration>

        <file name=\"ldf\"        file-type=\"fits\"   type=\"LDF\">$ENV{'onlineDataDir'}</file>
        <file name=\"digi\"       file-type=\"root\"   type=\"DIGI\">$ENV{'digitizationDataDir'}</file>
        <file name=\"jobOptions\" file-type=\"jobOpt\" type=\"text\">$ENV{'digitizationDataDir'}</file>
        <file name=\"script\"     file-type=\"csh\"    type=\"script\">$ENV{'digitizationDataDir'}</file>

        <processing-step name=\"Convert\" executable=\"Convert\" batch-job-configuration=\"medium-job\">
                        <input-file name=\"ldf\"/>
                        <output-file name=\"digi\"/>
                        <output-file name=\"script\"/>
                        <output-file name=\"jobOptions\"/>
        </processing-step>
        <processing-step name=\"LaunchRecon\" executable=\"LaunchRecon\" batch-job-configuration=\"express-job\">
                        <input-file name=\"digi\"/>
        </processing-step>
        <processing-step name=\"LaunchReport\" executable=\"LaunchReport\" batch-job-configuration=\"express-job\">
                        <input-file name=\"digi\"/>
        </processing-step>
        <processing-step name=\"digiRootFile\" executable=\"digiRootFile\" batch-job-configuration=\"express-job\">
                        <input-file name=\"digi\"/>
        </processing-step>
</pipeline>

";

my $digitizationXmlFileName = "$ENV{'digitizationTask'}.xml";
open FIELDS, '>', $digitizationXmlFileName;
print FIELDS $digitizationXml;
close FIELDS;

