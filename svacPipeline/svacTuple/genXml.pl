#!/usr/bin/perl -w

use strict;

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

my $urlUpdater = $ENV{'urlUpdateWrapper'};

my $batchgroup = $ENV{'batchgroup'};

use MakeMeta;
my %metaWrappers = (MakeMeta::makeMeta($ENV{'svacTupleTaskDir'}, 
									   "RunRootAnalyzer"),
					MakeMeta::makeMeta($ENV{'svacPlLib'}, 
									   "url", "finalCleanup", 'copyTkr')
					);

my $svacTupleXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/Pipeline/schemas/1.1/pipeline.xsd\">

    <name>$ENV{'svacTupleTask'}</name>
    <type>Analysis</type>
    <dataset-base-path>$ENV{'dataHead'}</dataset-base-path>
    <run-log-path>/temp/</run-log-path>

    <executable name=\"svacTuple\" version=\"$ENV{'svacTupleTaskVersion'}\">
        $metaWrappers{'RunRootAnalyzer'}
    </executable>
    <executable name=\"urlWrapper\" version=\"$ENV{'svacVersion'}\">
        $metaWrappers{'url'}
    </executable>
    <executable name=\"finalCleanup\" version=\"$ENV{'svacVersion'}\">
        $metaWrappers{'finalCleanup'}
    </executable>
    <executable name=\"copyTkr\" version=\"$ENV{'svacVersion'}\">
        $metaWrappers{'copyTkr'}
    </executable>

    <batch-job-configuration name=\"glastdataq-job\" queue=\"glastdataq\" group=\"$batchgroup\">
        <working-directory>$ENV{'svacTupleDataDirFull'}</working-directory>
        <log-file-path>$ENV{'svacTupleDataDirFull'}</log-file-path>
    </batch-job-configuration>
    <batch-job-configuration name=\"express-job\" queue=\"express\" group=\"$batchgroup\">
        <working-directory>$ENV{'svacTupleDataDirFull'}</working-directory>
        <log-file-path>$ENV{'svacTupleDataDirFull'}</log-file-path>
    </batch-job-configuration>

    <file name=\"histogram\"  file-type=\"root\"   type=\"histogram\">
        <path>$ENV{'svacTupleDataDir'}</path>
    </file>
    <file name=\"jobOptions\" file-type=\"jobOpt\" type=\"text\"     >
        <path>$ENV{'svacTupleDataDir'}</path>
    </file>
    <file name=\"script\"     file-type=\"csh\"    type=\"script\"   >
        <path>$ENV{'svacTupleDataDir'}</path>
    </file>
    <file name=\"svac\"       file-type=\"root\"   type=\"svac\"     >
        <path>$ENV{'svacTupleDataDir'}</path>
    </file>
    <file name=\"digi\"       file-type=\"root\"   type=\"DIGI\"     >
        <path>$ENV{'digitizationDataDir'}</path>
    </file>
    <file name=\"recon\"      file-type=\"root\"   type=\"RECON\"    >
        <path>$ENV{'reconDataDir'}</path>
    </file>

    <processing-step name=\"svacTuple\" executable=\"svacTuple\" batch-job-configuration=\"glastdataq-job\">
                    <input-file name=\"digi\"/>
                    <input-file name=\"recon\"/>
                    <output-file name=\"histogram\"/>
                    <output-file name=\"svac\"/>
                    <output-file name=\"script\"/>
                    <output-file name=\"jobOptions\"/>
    </processing-step>
    <processing-step name=\"svacRootFile\" executable=\"urlWrapper\" batch-job-configuration=\"express-job\">
                    <input-file name=\"svac\"/>
    </processing-step>
    <processing-step name=\"finalCleanup\" executable=\"finalCleanup\" batch-job-configuration=\"express-job\">
                    <input-file name=\"recon\"/>
    </processing-step>
    <processing-step name=\"copyTkr\" executable=\"copyTkr\" batch-job-configuration=\"express-job\">
                    <input-file name=\"svac\"/>
    </processing-step>
</pipeline>

";

my $svacTupleXmlFileName = "$ENV{'svacTupleTask'}.xml";
open FIELDS, '>', $svacTupleXmlFileName;
print FIELDS $svacTupleXml;
close FIELDS;

