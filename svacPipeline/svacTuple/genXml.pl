#!/usr/bin/perl -w

use strict;

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

my $urlUpdater = $ENV{'urlUpdateWrapper'};


# svacTuple
my $svacTupleDataDir = "$ENV{'calibRoot'}/svacRoot/$ENV{'svacTupleVersion'}";

my $svacTupleXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/pipeline/pipeline.xsd\">
    <name>$ENV{'svacTupleTask'}</name>
    <type>Analysis</type>
    <dataset-base-path>$svacTupleDataDir</dataset-base-path>
    <run-log-path>/temp/</run-log-path>
        <executable name=\"svacTupleWrapper\" version=\"$ENV{'svacTupleTaskVersion'}\">
            $ENV{'svacTupleTaskDir'}/RunRootAnalyzerWrapper.pl
        </executable>
        <executable name=\"svacRootFileWrapper\" version=\"$ENV{'svacPlLibVersion'}\">
            $urlUpdater
        </executable>
        <batch-job-configuration name=\"long-job\" queue=\"long\" group\"$batchgroup\">
            <working-directory>$svacTupleDataDir</working-directory>
            <log-file-path>$svacTupleDataDir</log-file-path>
        </batch-job-configuration>
        <batch-job-configuration name=\"express-job\" queue=\"express\" group\"$batchgroup\">
            <working-directory>$svacTupleDataDir</working-directory>
            <log-file-path>$svacTupleDataDir</log-file-path>
        </batch-job-configuration>
        <foreign-input-file name=\"digi\" pipeline=\"$ENV{'digitizationTask'}\" file=\"digi\"/>
        <foreign-input-file name=\"recon\" pipeline=\"$ENV{'reconTask'}\" file=\"recon\"/>
        <file name=\"histogram\" type=\"root\" file-type=\"histogram\"/>
        <file name=\"jobOptions\" type=\"jobOpt\" file-type=\"text\"/>
        <file name=\"script\" type=\"csh\" file-type=\"script\"/>
        <file name=\"svac\" type=\"root\" file-type=\"svac\"/>
        <processing-step name=\"svacTuple\" executable=\"svacTupleWrapper\" batch-job-configuration=\"long-job\">
                        <input-file name=\"digi\"/>
                        <input-file name=\"recon\"/>
                        <output-file name=\"histogram\"/>
                        <output-file name=\"svac\"/>
                        <output-file name=\"script\"/>
                        <output-file name=\"jobOptions\"/>
        </processing-step>
        <processing-step name=\"svacRootFile\" executable=\"svacRootFileWrapper\" batch-job-configuration=\"express-job\">
                        <input-file name=\"svac\"/>
        </processing-step>
</pipeline>

";

my $svacTupleXmlFileName = "$ENV{'svacTupleTask'}.xml";
open FIELDS, '>', $svacTupleXmlFileName;
print FIELDS $svacTupleXml;
close FIELDS;

