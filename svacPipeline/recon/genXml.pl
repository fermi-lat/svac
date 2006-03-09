#!/usr/bin/perl -w

use strict;

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

my $urlUpdater = $ENV{'urlUpdateWrapper'};

my $batchgroup = $ENV{'batchgroup'};

my $reconXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/pipeline.xsd\">

    <name>$ENV{'reconTask'}</name>
    <type>Reconstruction</type>
    <dataset-base-path>$ENV{'dataHead'}</dataset-base-path>
    <run-log-path>/temp/</run-log-path>

    <executable name=\"recon\" version=\"$ENV{'reconTaskVersion'}\">
        $ENV{'reconTaskDir'}/reconWrapper.pl
    </executable>
    <executable name=\"RunRALaunch\" version=\"$ENV{'reconTaskVersion'}\">
        $ENV{'reconTaskDir'}/RunRALaunchWrapper.pl
    </executable>
    <executable name=\"genRTRLaunch\" version=\"$ENV{'reconTaskVersion'}\">
        $ENV{'reconTaskDir'}/genRTRLaunchWrapper.pl
    </executable>
    <executable name=\"urlWrapper\" version=\"$ENV{'svacVersion'}\">
        $urlUpdater
    </executable>

    <batch-job-configuration name=\"xlong-job\" queue=\"xlong\" group=\"$batchgroup\">
        <working-directory>$ENV{'reconDataDirFull'}</working-directory>
        <log-file-path>$ENV{'reconDataDirFull'}</log-file-path>
    </batch-job-configuration>
    <batch-job-configuration name=\"express-job\" queue=\"express\" group=\"$batchgroup\">
        <working-directory>$ENV{'reconDataDirFull'}</working-directory>
        <log-file-path>$ENV{'reconDataDirFull'}</log-file-path>
    </batch-job-configuration>

    <file name=\"cal\"        type=\"ntuple\" file-type=\"root\">$ENV{'reconDataDir'}</file>
    <file name=\"merit\"      type=\"merit\"  file-type=\"root\">$ENV{'reconDataDir'}</file>
    <file name=\"recon\"      type=\"RECON\"  file-type=\"root\">$ENV{'reconDataDir'}</file>
    <file name=\"digi\"       type=\"DIGI\"   file-type=\"root\">$ENV{'digitizationDataDir'}</file>
    <file name=\"tarFile\"    type=\"log\"    file-type=\"tgz\">$ENV{'reconDataDir'}</file>

    <processing-step name=\"recon\" executable=\"recon\" batch-job-configuration=\"xlong-job\">
                    <input-file name=\"digi\"/>
                    <output-file name=\"cal\"/>
                    <output-file name=\"merit\"/>
                    <output-file name=\"recon\"/>
                    <output-file name=\"tarFile\"/>
    </processing-step>
    <processing-step name=\"LaunchSVAC\" executable=\"RunRALaunch\" batch-job-configuration=\"express-job\">
                    <input-file name=\"digi\"/>
                    <input-file name=\"recon\"/>
    </processing-step>
    <processing-step name=\"LaunchReport\" executable=\"genRTRLaunch\" batch-job-configuration=\"express-job\">
                    <input-file name=\"digi\"/>
                    <input-file name=\"recon\"/>
    </processing-step>
    <processing-step name=\"reconRootFile\" executable=\"urlWrapper\" batch-job-configuration=\"express-job\">
                    <input-file name=\"recon\"/>
    </processing-step>
    <processing-step name=\"meritRootFile\" executable=\"urlWrapper\" batch-job-configuration=\"express-job\">
                    <input-file name=\"merit\"/>
    </processing-step>
    <processing-step name=\"calRootFile\" executable=\"urlWrapper\" batch-job-configuration=\"express-job\">
                    <input-file name=\"cal\"/>
    </processing-step>
</pipeline>
";

my $reconXmlFileName = "$ENV{'reconTask'}.xml";
open FIELDS, '>', $reconXmlFileName;
print FIELDS $reconXml;
close FIELDS;


