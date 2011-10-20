#!/usr/bin/perl -w

use strict;

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

my $urlUpdater = $ENV{'urlUpdateWrapper'};

my $batchgroup = $ENV{'batchgroup'};

# recon
my $reconDataDir = "$ENV{'calibRoot'}/grRoot";

my $reconXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/pipeline/pipeline.xsd\">
    <name>$ENV{'reconTask'}</name>
    <type>Reconstruction</type>
    <dataset-base-path>$reconDataDir</dataset-base-path>
    <run-log-path>/temp/</run-log-path>
    <executable name=\"reconWrapper\" version=\"$ENV{'reconTaskVersion'}\">
        $ENV{'reconTaskDir'}/reconWrapper.pl
    </executable>
    <executable name=\"RunRALaunchWrapper\" version=\"$ENV{'reconTaskVersion'}\">
        $ENV{'reconTaskDir'}/RunRALaunchWrapper.pl
    </executable>
    <executable name=\"genRTRLaunchWrapper\" version=\"$ENV{'reconTaskVersion'}\">
        $ENV{'reconTaskDir'}/genRTRLaunchWrapper.pl
    </executable>
    <executable name=\"urlWrapper\" version=\"$ENV{'svacPlLibVersion'}\">
        $urlUpdater
    </executable>
    <batch-job-configuration name=\"xlong-job\" queue=\"xlong\" group\"$batchgroup\">
        <working-directory>$reconDataDir</working-directory>
        <log-file-path>$reconDataDir</log-file-path>
    </batch-job-configuration>
    <batch-job-configuration name=\"express-job\" queue=\"express\" group\"$batchgroup\">
        <working-directory>$reconDataDir</working-directory>
        <log-file-path>$reconDataDir</log-file-path>
    </batch-job-configuration>
    <foreign-input-file name=\"digi\" pipeline=\"$ENV{'digitizationTask'}\" file=\"digi\"/>
    <file name=\"jobOptions\" type=\"text\"   file-type=\"jobOpt\"/>
    <file name=\"merit\"      type=\"merit\"  file-type=\"root\"/>
    <file name=\"recon\"      type=\"RECON\"  file-type=\"root\"/>
    <file name=\"script\"     type=\"script\" file-type=\"csh\"/>
    <processing-step name=\"recon\" executable=\"reconWrapper\" batch-job-configuration=\"xlong-job\">
                    <input-file name=\"digi\"/>
                    <output-file name=\"jobOptions\"/>
                    <output-file name=\"merit\"/>
                    <output-file name=\"recon\"/>
                    <output-file name=\"script\"/>
    </processing-step>
    <processing-step name=\"LaunchSVAC\" executable=\"RunRALaunchWrapper\" batch-job-configuration=\"express-job\">
                    <input-file name=\"digi\"/>
                    <input-file name=\"recon\"/>
    </processing-step>
    <processing-step name=\"LaunchReport\" executable=\"genRTRLaunchWrapper\" batch-job-configuration=\"express-job\">
                    <input-file name=\"digi\"/>
                    <input-file name=\"recon\"/>
    </processing-step>
    <processing-step name=\"reconRootFile\" executable=\"urlWrapper\" batch-job-configuration=\"express-job\">
                    <input-file name=\"recon\"/>
    </processing-step>
    <processing-step name=\"meritRootFile\" executable=\"urlWrapper\" batch-job-configuration=\"express-job\">
                    <input-file name=\"merit\"/>
    </processing-step>
</pipeline>
";

my $reconXmlFileName = "$ENV{'reconTask'}.xml";
open FIELDS, '>', $reconXmlFileName;
print FIELDS $reconXml;
close FIELDS;
