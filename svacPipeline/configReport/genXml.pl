#!/usr/bin/perl -w

use strict;

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

my $urlUpdater = $ENV{'urlUpdateWrapper'};

my $batchgroup = $ENV{'batchgroup'};

use MakeMeta;
my %metaWrappers = (MakeMeta::makeMeta($ENV{'configTaskDir'}, 
									   "ConfigTables"),
					MakeMeta::makeMeta($ENV{'svacPlLib'}, 
									   "url")
					);

my $configReportXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/Pipeline/schemas/1.1/pipeline.xsd\">

    <name>$ENV{'configReportTaskLatte'}</name>
    <type>Report</type>
    <dataset-base-path></dataset-base-path>
    <run-log-path>/temp/</run-log-path>

    <executable name=\"ConfigTables\" version=\"$ENV{'configReportTaskVersion'}\">
        $metaWrappers{'ConfigTables'}
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

    <file file-type=\"xml\" name=\"snapshot\" type=\"text\"    >
        <path>$ENV{'onlineDataDirFull'}</path>
    </file>
    <file file-type=\"tgz\" name=\"tarBall\"  type=\"Analysis\">
        <path>$ENV{'configTablesDataDirFull'}</path>
    </file>

    <processing-step name=\"ConfigTables\" executable=\"ConfigTables\" batch-job-configuration=\"medium-job\">
                    <input-file name=\"snapshot\"/>
                    <output-file name=\"tarBall\"/>
    </processing-step>
    <processing-step name=\"configReportUrl\" executable=\"urlWrapper\" batch-job-configuration=\"express-job\">
                    <input-file name=\"tarBall\"/>
    </processing-step>
</pipeline>

";

my $configReportXmlFileName = "$ENV{'configReportTaskLatte'}.xml";
open FIELDS, '>', $configReportXmlFileName;
print FIELDS $configReportXml;
close FIELDS;


$configReportXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/Pipeline/schemas/1.1/pipeline.xsd\">

    <name>$ENV{'configReportTaskLicos'}</name>
    <type>Report</type>
    <dataset-base-path></dataset-base-path>
    <run-log-path>/temp/</run-log-path>

    <executable name=\"ConfigTables\" version=\"$ENV{'configReportTaskVersion'}\">
        $metaWrappers{'ConfigTables'}
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

    <file file-type=\"xml\" name=\"algorithm\" type=\"text\"    >
        <path>$ENV{'onlineDataDirFull'}/LICOS</path>
    </file>
    <file file-type=\"tgz\" name=\"tarBall\"  type=\"Analysis\">
        <path>$ENV{'configTablesDataDirFull'}</path>
    </file>

    <processing-step name=\"ConfigTables\" executable=\"ConfigTables\" batch-job-configuration=\"medium-job\">
                    <input-file name=\"algorithm\"/>
                    <output-file name=\"tarBall\"/>
    </processing-step>
    <processing-step name=\"configReportUrl\" executable=\"urlWrapper\" batch-job-configuration=\"express-job\">
                    <input-file name=\"tarBall\"/>
    </processing-step>
</pipeline>

";

$configReportXmlFileName = "$ENV{'configReportTaskLicos'}.xml";
open FIELDS, '>', $configReportXmlFileName;
print FIELDS $configReportXml;
close FIELDS;

