#!/usr/bin/perl -w

use strict;

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

my $urlUpdater = $ENV{'urlUpdateWrapper'};

my $batchgroup = $ENV{'batchgroup'};

use MakeMeta;
my %metaWrappers = (MakeMeta::makeMeta($ENV{'reconTaskDir'}, 
									  "setupRecon", "doRecon", 
									  "cleanup"),
					MakeMeta::makeMeta($ENV{'svacPlLib'},
									   "copy", "delete",
									   "hadd", "url",
									   "Launch")
					);

my $reconXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/Pipeline/schemas/1.1/pipeline.xsd\">

    <name>$ENV{'reconTask'}</name>
    <type>Reconstruction</type>
    <dataset-base-path>$ENV{'dataHead'}</dataset-base-path>
    <run-log-path>/temp/</run-log-path>

    <executable name=\"setupRecon\" version=\"$ENV{'reconTaskVersion'}\">
        $metaWrappers{'setupRecon'}
    </executable>
    <executable name=\"doRecon\" version=\"$ENV{'reconTaskVersion'}\">
        $metaWrappers{'doRecon'}
    </executable>
    <executable name=\"copyWrapper\" version=\"$ENV{'svacVersion'}\">
        $metaWrappers{'copy'}
    </executable>
    <executable name=\"deleteWrapper\" version=\"$ENV{'svacVersion'}\">
        $metaWrappers{'delete'}
    </executable>
    <executable name=\"taskLauncher\" version=\"$ENV{'svacVersion'}\">
        $metaWrappers{'Launch'}
    </executable>
    <executable name=\"haddWrapper\" version=\"$ENV{'svacVersion'}\">
        $metaWrappers{'hadd'}
    </executable>
    <executable name=\"urlWrapper\" version=\"$ENV{'svacVersion'}\">
        $metaWrappers{'url'}
    </executable>
    <executable name=\"cleanup\" version=\"$ENV{'reconTaskVersion'}\">
        $metaWrappers{'cleanup'}
    </executable>

    <batch-job-configuration name=\"glastdataq-job\" queue=\"glastdataq\" group=\"$batchgroup\">
        <working-directory>$ENV{'reconDataDirFull'}</working-directory>
        <log-file-path>$ENV{'reconDataDirFull'}</log-file-path>
    </batch-job-configuration>
    <batch-job-configuration name=\"express-job\" queue=\"express\" group=\"$batchgroup\">
        <working-directory>$ENV{'reconDataDirFull'}</working-directory>
        <log-file-path>$ENV{'reconDataDirFull'}</log-file-path>
    </batch-job-configuration>

    <file name=\"cal\"         type=\"ntuple\" file-type=\"root\">
        <path>$ENV{'reconDataDir'}</path>
    </file>
    <file name=\"calChunks\"   type=\"text\"   file-type=\"txt\">
        <path>$ENV{'reconDataDir'}</path>
    </file>
    <file name=\"calStage\"   type=\"text\"   file-type=\"txt\">
        <path>$ENV{'reconDataDir'}</path>
    </file>
    <file name=\"merit\"       type=\"merit\"  file-type=\"root\">
        <path>$ENV{'reconDataDir'}</path>
    </file>
    <file name=\"meritChunks\" type=\"text\"   file-type=\"txt\">
        <path>$ENV{'reconDataDir'}</path>
    </file>
    <file name=\"meritStage\"   type=\"text\"   file-type=\"txt\">
        <path>$ENV{'reconDataDir'}</path>
    </file>
    <file name=\"recon\"       type=\"RECON\"  file-type=\"root\">
        <path>$ENV{'reconDataDir'}</path>
    </file>
    <file name=\"reconChunks\" type=\"text\"   file-type=\"txt\">
        <path>$ENV{'reconDataDir'}</path>
    </file>
     <file name=\"reconStage\"   type=\"text\"   file-type=\"txt\">
        <path>$ENV{'reconDataDir'}</path>
    </file>
   <file name=\"chunkJobs\"   type=\"text\"   file-type=\"txt\">
        <path>$ENV{'reconDataDir'}</path>
    </file>
    <file name=\"digi\"        type=\"DIGI\"   file-type=\"root\">
        <path>$ENV{'digitizationDataDir'}</path>
    </file>
    <file name=\"tarFile\"     type=\"log\"    file-type=\"tgz\">
        <path>$ENV{'reconDataDir'}</path>
    </file>
    <file name=\"keepers\"     type=\"text\"   file-type=\"txt\">
        <path>$ENV{'reconDataDir'}</path>
    </file>
    <file name=\"junkDirs\"    type=\"text\"   file-type=\"txt\">
        <path>$ENV{'reconDataDir'}</path>
    </file>

    <processing-step name=\"setupRecon\" executable=\"setupRecon\" batch-job-configuration=\"express-job\">
                    <input-file name=\"digi\"/>
                    <output-file name=\"calChunks\"/>
                    <output-file name=\"meritChunks\"/>
                    <output-file name=\"reconChunks\"/>
                    <output-file name=\"chunkJobs\"/>
                    <output-file name=\"keepers\"/>
                    <output-file name=\"junkDirs\"/>
    </processing-step>
    <processing-step name=\"doRecon\" executable=\"doRecon\" batch-job-configuration=\"glastdataq-job\">
                    <input-file name=\"chunkJobs\"/>
    </processing-step>
    <processing-step name=\"mergeRecon\" executable=\"haddWrapper\" batch-job-configuration=\"glastdataq-job\">
                    <input-file name=\"reconChunks\"/>
                    <output-file name=\"reconStage\"/>
    </processing-step>
    <processing-step name=\"deleteReconChunks\" executable=\"deleteWrapper\" batch-job-configuration=\"express-job\">
                    <input-file name=\"reconChunks\"/>
    </processing-step>
    <processing-step name=\"copyRecon\" executable=\"copyWrapper\" batch-job-configuration=\"glastdataq-job\">
                    <input-file name=\"reconStage\"/>
                    <output-file name=\"recon\"/>
    </processing-step>
    <processing-step name=\"deleteReconStage\" executable=\"deleteWrapper\" batch-job-configuration=\"express-job\">
                    <input-file name=\"reconStage\"/>
    </processing-step>
    <processing-step name=\"$ENV{'svacTupleTask'}\" executable=\"taskLauncher\" batch-job-configuration=\"express-job\">
                    <input-file name=\"digi\"/>
                    <input-file name=\"recon\"/>
    </processing-step>
    <processing-step name=\"$ENV{'reconReportTask'}\" executable=\"taskLauncher\" batch-job-configuration=\"express-job\">
                    <input-file name=\"digi\"/>
                    <input-file name=\"recon\"/>
    </processing-step>
    <processing-step name=\"mergeCal\" executable=\"haddWrapper\" batch-job-configuration=\"glastdataq-job\">
                    <input-file name=\"calChunks\"/>
                    <output-file name=\"calStage\"/>
    </processing-step>
    <processing-step name=\"deleteCalChunks\" executable=\"deleteWrapper\" batch-job-configuration=\"express-job\">
                    <input-file name=\"calChunks\"/>
    </processing-step>
    <processing-step name=\"copyCal\" executable=\"copyWrapper\" batch-job-configuration=\"glastdataq-job\">
                    <input-file name=\"calStage\"/>
                    <output-file name=\"cal\"/>
    </processing-step>
    <processing-step name=\"deleteCalStage\" executable=\"deleteWrapper\" batch-job-configuration=\"express-job\">
                    <input-file name=\"calStage\"/>
    </processing-step>
    <processing-step name=\"mergeMerit\" executable=\"haddWrapper\" batch-job-configuration=\"glastdataq-job\">
                    <input-file name=\"meritChunks\"/>
                    <output-file name=\"meritStage\"/>
    </processing-step>
    <processing-step name=\"deleteMeritChunks\" executable=\"deleteWrapper\" batch-job-configuration=\"express-job\">
                    <input-file name=\"meritChunks\"/>
    </processing-step>
    <processing-step name=\"copyMerit\" executable=\"copyWrapper\" batch-job-configuration=\"glastdataq-job\">
                    <input-file name=\"meritStage\"/>
                    <output-file name=\"merit\"/>
    </processing-step>
    <processing-step name=\"deleteMeritStage\" executable=\"deleteWrapper\" batch-job-configuration=\"express-job\">
                    <input-file name=\"meritStage\"/>
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


