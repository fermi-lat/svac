#!/usr/bin/perl -w

use strict;

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

my $batchgroup = $ENV{'batchgroup'};

my $eLogDataDir = $ENV{'svacHead'};

use MakeMeta;
my %metaWrappers = (MakeMeta::makeMeta($ENV{'eLogTaskDir'}, 
									  "populateElogDb"),
					MakeMeta::makeMeta($ENV{'svacPlLib'}, 
									   "Launch")
					);

my $updateElogDbXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/Pipeline/schemas/1.1/pipeline.xsd\">

    <name>$ENV{'eLogTaskLatte'}</name>
    <type>Report</type>
    <dataset-base-path></dataset-base-path>
    <run-log-path>/temp/</run-log-path>

    <executable name=\"populateElogDb\" version=\"$ENV{'eLogTaskVersion'}\">
        $metaWrappers{'populateElogDb'}
    </executable>
    <executable name=\"taskLauncher\" version=\"$ENV{'svacVersion'}\">
        $metaWrappers{'Launch'}
    </executable>

    <batch-job-configuration name=\"express-job\" queue=\"express\" group=\"$batchgroup\">
        <working-directory>$ENV{'eLogDataDirFull'}</working-directory>
        <log-file-path>$ENV{'eLogDataDirFull'}</log-file-path>
    </batch-job-configuration>

    <file file-type=\"xml\"  name=\"snapshot\" type=\"text\"    >
        <path>$ENV{'onlineDataDirFull'}</path>
    </file>
    <file file-type=\"fits\" name=\"ldf\"      type=\"LDF\"     >
        <path>$ENV{'onlineDataDirFull'}</path>
    </file>
    <file file-type=\"xml\"  name=\"rcReport\" type=\"rcReport\">
        <path>$ENV{'onlineDataDirFull'}</path>
    </file>
    <file file-type=\"csh\"  name=\"script\"   type=\"script\"  >
        <path>$ENV{'eLogDataDirFull'}</path>
    </file>

    <processing-step name=\"populateElogDb\" executable=\"populateElogDb\" batch-job-configuration=\"express-job\">
                    <input-file name=\"rcReport\"/>
                    <output-file name=\"script\"/>
    </processing-step>
    <processing-step name=\"$ENV{'digitizationTaskLatte'}\" executable=\"taskLauncher\" batch-job-configuration=\"express-job\">
                    <input-file name=\"ldf\"/>
    </processing-step>
    <processing-step name=\"$ENV{'configReportTaskLatte'}\" executable=\"taskLauncher\" batch-job-configuration=\"express-job\">
                    <input-file name=\"snapshot\"/>
    </processing-step>
</pipeline>
";

my $eLogXmlFileName = "$ENV{'eLogTaskLatte'}.xml";
open FIELDS, '>', $eLogXmlFileName;
print FIELDS $updateElogDbXml;
close FIELDS;


$updateElogDbXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/Pipeline/schemas/1.1/pipeline.xsd\">

    <name>$ENV{'eLogTaskLicos'}</name>
    <type>Report</type>
    <dataset-base-path></dataset-base-path>
    <run-log-path>/temp/</run-log-path>

    <executable name=\"populateElogDb\" version=\"$ENV{'eLogTaskVersion'}\">
        $metaWrappers{'populateElogDb'}
    </executable>
    <executable name=\"taskLauncher\" version=\"$ENV{'svacVersion'}\">
        $metaWrappers{'Launch'}
    </executable>

    <batch-job-configuration name=\"express-job\" queue=\"express\" group=\"$batchgroup\">
        <working-directory>$ENV{'eLogDataDirFull'}</working-directory>
        <log-file-path>$ENV{'eLogDataDirFull'}</log-file-path>
    </batch-job-configuration>

    <file file-type=\"xml\"  name=\"algorithm\" type=\"text\"    >
        <path>$ENV{'onlineDataDirFull'}/LICOS</path>
    </file>
    <file file-type=\"evt\"  name=\"RetDef\"   type=\"RetDef\"  >
        <path>$ENV{'onlineDataDirFull'}</path>
    </file>
    <file file-type=\"xml\"  name=\"rcReport\" type=\"rcReport\">
        <path>$ENV{'onlineDataDirFull'}/LICOS</path>
    </file>
    <file file-type=\"csh\"  name=\"script\"   type=\"script\"  >
        <path>$ENV{'eLogDataDirFull'}</path>
    </file>

    <processing-step name=\"populateElogDb\" executable=\"populateElogDb\" batch-job-configuration=\"express-job\">
                    <input-file name=\"rcReport\"/>
                    <output-file name=\"script\"/>
    </processing-step>
    <processing-step name=\"$ENV{'digitizationTaskLicos'}\" executable=\"taskLauncher\" batch-job-configuration=\"express-job\">
                    <input-file name=\"RetDef\"/>
    </processing-step>
    <processing-step name=\"$ENV{'configReportTaskLicos'}\" executable=\"taskLauncher\" batch-job-configuration=\"express-job\">
                    <input-file name=\"algorithm\"/>
    </processing-step>
</pipeline>
";

$eLogXmlFileName = "$ENV{'eLogTaskLicos'}.xml";
open FIELDS, '>', $eLogXmlFileName;
print FIELDS $updateElogDbXml;
close FIELDS;

