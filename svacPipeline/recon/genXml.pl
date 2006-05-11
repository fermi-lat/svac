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

    <executable name=\"setupRecon\" version=\"$ENV{'reconTaskVersion'}\">
        $ENV{'reconTaskDir'}/setupReconWrapper.pl
    </executable>
    <executable name=\"doRecon\" version=\"$ENV{'reconTaskVersion'}\">
        $ENV{'reconTaskDir'}/doReconWrapper.pl
    </executable>
    <executable name=\"mergeRecon\" version=\"$ENV{'reconTaskVersion'}\">
        $ENV{'reconTaskDir'}/mergeReconWrapper.pl
    </executable>
    <executable name=\"RunRALaunch\" version=\"$ENV{'reconTaskVersion'}\">
        $ENV{'reconTaskDir'}/RunRALaunchWrapper.pl
    </executable>
    <executable name=\"genRTRLaunch\" version=\"$ENV{'reconTaskVersion'}\">
        $ENV{'reconTaskDir'}/genRTRLaunchWrapper.pl
    </executable>
    <executable name=\"mergeMerit\" version=\"$ENV{'reconTaskVersion'}\">
        $ENV{'reconTaskDir'}/mergeMeritWrapper.pl
    </executable>
    <executable name=\"mergeCal\" version=\"$ENV{'reconTaskVersion'}\">
        $ENV{'reconTaskDir'}/mergeCalWrapper.pl
    </executable>
    <executable name=\"urlWrapper\" version=\"$ENV{'svacVersion'}\">
        $urlUpdater
    </executable>
    <executable name=\"cleanup\" version=\"$ENV{'reconTaskVersion'}\">
        $ENV{'reconTaskDir'}/cleanupWrapper.pl
    </executable>

    <batch-job-configuration name=\"xlong-job\" queue=\"xlong\" group=\"$batchgroup\">
        <working-directory>$ENV{'reconDataDirFull'}</working-directory>
        <log-file-path>$ENV{'reconDataDirFull'}</log-file-path>
    </batch-job-configuration>
    <batch-job-configuration name=\"express-job\" queue=\"express\" group=\"$batchgroup\">
        <working-directory>$ENV{'reconDataDirFull'}</working-directory>
        <log-file-path>$ENV{'reconDataDirFull'}</log-file-path>
    </batch-job-configuration>

    <file name=\"cal\"         type=\"ntuple\" file-type=\"root\">$ENV{'reconDataDir'}</file>
    <file name=\"calChunks\"   type=\"text\"   file-type=\"txt\">$ENV{'reconDataDir'}</file>
    <file name=\"merit\"       type=\"merit\"  file-type=\"root\">$ENV{'reconDataDir'}</file>
    <file name=\"meritChunks\" type=\"text\"   file-type=\"txt\">$ENV{'reconDataDir'}</file>
    <file name=\"recon\"       type=\"RECON\"  file-type=\"root\">$ENV{'reconDataDir'}</file>
    <file name=\"reconChunks\" type=\"text\"   file-type=\"txt\">$ENV{'reconDataDir'}</file>
    <file name=\"chunkJobs\"   type=\"text\"   file-type=\"txt\">$ENV{'reconDataDir'}</file>
    <file name=\"digi\"        type=\"DIGI\"   file-type=\"root\">$ENV{'digitizationDataDir'}</file>
    <file name=\"tarFile\"     type=\"log\"    file-type=\"tgz\">$ENV{'reconDataDir'}</file>
    <file name=\"keepers\"     type=\"text\"   file-type=\"txt\">$ENV{'reconDataDir'}</file>
    <file name=\"junkDirs\"    type=\"text\"   file-type=\"txt\">$ENV{'reconDataDir'}</file>

    <processing-step name=\"setupRecon\" executable=\"setupRecon\" batch-job-configuration=\"express-job\">
                    <input-file name=\"digi\"/>
                    <output-file name=\"calChunks\"/>
                    <output-file name=\"meritChunks\"/>
                    <output-file name=\"reconChunks\"/>
                    <output-file name=\"chunkJobs\"/>
                    <output-file name=\"keepers\"/>
                    <output-file name=\"junkDirs\"/>
    </processing-step>
    <processing-step name=\"doRecon\" executable=\"doRecon\" batch-job-configuration=\"xlong-job\">
                    <input-file name=\"chunkJobs\"/>
    </processing-step>
    <processing-step name=\"mergeRecon\" executable=\"mergeRecon\" batch-job-configuration=\"xlong-job\">
                    <input-file name=\"reconChunks\"/>
                    <output-file name=\"recon\"/>
    </processing-step>
    <processing-step name=\"LaunchSVAC\" executable=\"RunRALaunch\" batch-job-configuration=\"express-job\">
                    <input-file name=\"digi\"/>
                    <input-file name=\"recon\"/>
    </processing-step>
    <processing-step name=\"LaunchReport\" executable=\"genRTRLaunch\" batch-job-configuration=\"express-job\">
                    <input-file name=\"digi\"/>
                    <input-file name=\"recon\"/>
    </processing-step>
    <processing-step name=\"mergeMerit\" executable=\"mergeMerit\" batch-job-configuration=\"xlong-job\">
                    <input-file name=\"meritChunks\"/>
                    <output-file name=\"merit\"/>
    </processing-step>
    <processing-step name=\"mergeCal\" executable=\"mergeCal\" batch-job-configuration=\"xlong-job\">
                    <input-file name=\"calChunks\"/>
                    <output-file name=\"cal\"/>
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
    <processing-step name=\"cleanup\" executable=\"cleanup\" batch-job-configuration=\"express-job\">
                    <input-file name=\"keepers\"/>
                    <input-file name=\"junkDirs\"/>
                    <output-file name=\"tarFile\"/>
    </processing-step>
</pipeline>
";

my $reconXmlFileName = "$ENV{'reconTask'}.xml";
open FIELDS, '>', $reconXmlFileName;
print FIELDS $reconXml;
close FIELDS;


