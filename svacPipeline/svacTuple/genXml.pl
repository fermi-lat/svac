#!/usr/bin/perl -w

use strict;

use lib "$ENV{'svacPlRoot'}/lib-current";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup-current/svacPlSetup.cshrc");

my $urlUpdater = $ENV{'urlUpdateWrapper'};


my $batchgroup = $ENV{'batchgroup'};

# svacTuple
#my $svacTupleDataDir = "$ENV{'calibRoot'}/svacRoot/$ENV{'svacTupleVersion'}";

my $svacTupleXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/pipeline.xsd\">

    <name>$ENV{'svacTupleTask'}</name>
    <type>Analysis</type>
    <dataset-base-path>$ENV{'dataHead'}</dataset-base-path>
    <run-log-path>/temp/</run-log-path>
        <executable name=\"svacTuple\" version=\"$ENV{'svacTupleTaskVersion'}\">
            $ENV{'svacTupleTaskDir'}/RunRootAnalyzerWrapper.pl
        </executable>
        <executable name=\"svacRootFile\" version=\"$ENV{'svacPlLibVersion'}\">
            $urlUpdater
        </executable>

        <batch-job-configuration name=\"xlong-job\" queue=\"xlong\" group=\"$batchgroup\">
            <working-directory>$ENV{'svacTupleDataDirFull'}</working-directory>
            <log-file-path>$ENV{'svacTupleDataDirFull'}</log-file-path>
        </batch-job-configuration>
        <batch-job-configuration name=\"express-job\" queue=\"express\" group=\"$batchgroup\">
            <working-directory>$ENV{'svacTupleDataDirFull'}</working-directory>
            <log-file-path>$ENV{'svacTupleDataDirFull'}</log-file-path>
        </batch-job-configuration>

        <file name=\"histogram\"  file-type=\"root\"   type=\"histogram\">$ENV{'svacTupleDataDir'}</file>
        <file name=\"jobOptions\" file-type=\"jobOpt\" type=\"text\"     >$ENV{'svacTupleDataDir'}</file>
        <file name=\"script\"     file-type=\"csh\"    type=\"script\"   >$ENV{'svacTupleDataDir'}</file>
        <file name=\"svac\"       file-type=\"root\"   type=\"svac\"     >$ENV{'svacTupleDataDir'}</file>
        <file name=\"digi\"       file-type=\"root\"   type=\"DIGI\"     >$ENV{'digitizationDataDir'}</file>
        <file name=\"recon\"      file-type=\"root\"   type=\"RECON\"    >$ENV{'reconDataDir'}</file>

        <processing-step name=\"svacTuple\" executable=\"svacTuple\" batch-job-configuration=\"xlong-job\">
                        <input-file name=\"digi\"/>
                        <input-file name=\"recon\"/>
                        <output-file name=\"histogram\"/>
                        <output-file name=\"svac\"/>
                        <output-file name=\"script\"/>
                        <output-file name=\"jobOptions\"/>
        </processing-step>
        <processing-step name=\"svacRootFile\" executable=\"svacRootFile\" batch-job-configuration=\"express-job\">
                        <input-file name=\"svac\"/>
        </processing-step>
</pipeline>

";

my $svacTupleXmlFileName = "$ENV{'svacTupleTask'}.xml";
open FIELDS, '>', $svacTupleXmlFileName;
print FIELDS $svacTupleXml;
close FIELDS;

