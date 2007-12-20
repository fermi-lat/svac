#!/usr/bin/perl -w

use strict;

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

my $urlUpdater = $ENV{'urlUpdateWrapper'};

my $batchgroup = $ENV{'batchgroup'};

use MakeMeta;
my %metaWrappers = (MakeMeta::makeMeta($ENV{'configTaskDir'}, 
									   "GetConfigKey"),
					MakeMeta::makeMeta($ENV{'configTaskDir'}, 
									   "ConfigXml2Root"),
					MakeMeta::makeMeta($ENV{'configTaskDir'}, 
									   "DumpConfiguration"),
					MakeMeta::makeMeta($ENV{'svacPlLib'}, 
									   "url")
					);

my $configReportXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/Pipeline/schemas/1.1/pipeline.xsd\">

    <name>$ENV{'configReportTask'}</name>
    <type>Report</type>
    <dataset-base-path></dataset-base-path>
    <run-log-path>/temp/</run-log-path>

    <executable name=\"GetConfigKey\" version=\"$ENV{'configReportTaskVersion'}\">
        $metaWrappers{'GetConfigKey'}
    </executable>
     <executable name=\"ConfigXml2Root\" version=\"$ENV{'configReportTaskVersion'}\">
        $metaWrappers{'ConfigXml2Root'}
    </executable>
     <executable name=\"DumpConfiguration\" version=\"$ENV{'configReportTaskVersion'}\">
        $metaWrappers{'DumpConfiguration'}
    </executable>
   <executable name=\"urlWrapper\" version=\"$ENV{'svacVersion'}\">
       $metaWrappers{'url'}
    </executable>

    <batch-job-configuration name=\"express-job\" queue=\"express\" group=\"$batchgroup\">
        <working-directory>$ENV{'configTablesDataDirFull'}</working-directory>
        <log-file-path>$ENV{'configTablesDataDirFull'}</log-file-path>
    </batch-job-configuration>
    <batch-job-configuration name=\"medium-job\" queue=\"medium\" group=\"$batchgroup\">
        <working-directory>$ENV{'configTablesDataDirFull'}</working-directory>
        <log-file-path>$ENV{'configTablesDataDirFull'}</log-file-path>
    </batch-job-configuration>

    <file name=\"configRoot\"       file-type=\"root\"   type=\"ntuple\">
        <path>$ENV{'configTablesDataDirFull'}</path>
    </file>
    <file name=\"configDump\"       file-type=\"txt\"   type=\"text\">
        <path>$ENV{'configTablesDataDirFull'}</path>
    </file>
    <file name=\"digi\"       file-type=\"root\"   type=\"DIGI\">
        <path>$ENV{'digitizationDataDirFull'}</path>
    </file>
    <file name=\"key\"       file-type=\"txt\"   type=\"text\">
        <path>$ENV{'configTablesDataDirFull'}</path>
    </file>

    <processing-step name=\"GetConfigKey\" executable=\"GetConfigKey\" batch-job-configuration=\"express-job\">
                    <input-file name=\"digi\"/>
                    <output-file name=\"key\"/>
    </processing-step>
    <processing-step name=\"ConfigXml2Root\" executable=\"ConfigXml2Root\" batch-job-configuration=\"medium-job\">
                    <input-file name=\"key\"/>
                    <output-file name=\"configRoot\"/>
    </processing-step>
    <processing-step name=\"DumpConfiguration\" executable=\"DumpConfiguration\" batch-job-configuration=\"medium-job\">
                    <input-file name=\"key\"/>
                    <output-file name=\"configDump\"/>
    </processing-step>
    <processing-step name=\"configReportUrl\" executable=\"urlWrapper\" batch-job-configuration=\"express-job\">
                    <input-file name=\"configDump\"/>
    </processing-step>
</pipeline>

";

my $configReportXmlFileName = "$ENV{'configReportTask'}.xml";
open FIELDS, '>', $configReportXmlFileName;
print FIELDS $configReportXml;
close FIELDS;

