#!/usr/bin/perl -w

use strict;

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

my $batchgroup = $ENV{'batchgroup'};

# eLog
my $eLogDataDir = $ENV{'svacHead'};

my $updateElogDbXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/pipeline/pipeline.xsd\">
    <name>$ENV{'eLogTask'}</name>
    <type>Report</type>
    <dataset-base-path>$eLogDataDir</dataset-base-path>
    <run-log-path>/temp/</run-log-path>
        <executable name=\"populateElogDbWrapper\" version=\"$ENV{'eLogTaskVersion'}\">
            $ENV{'eLogTaskDir'}/populateElogDbWrapper.pl
        </executable>
        <executable name=\"LaunchDigiWrapper\" version=\"$ENV{'eLogTaskVersion'}\">
            $ENV{'eLogTaskDir'}/ldfTDLaunchWrapper.pl
        </executable>
        <executable name=\"LaunchConfRepWrapper\" version=\"$ENV{'eLogTaskVersion'}\">
            $ENV{'eLogTaskDir'}/ConfTLaunchWrapper.pl
        </executable>
        <batch-job-configuration name=\"express-job\" queue=\"express\" group\"$batchgroup\">
            <working-directory>$eLogDataDir</working-directory>
            <log-file-path>$eLogDataDir</log-file-path>
        </batch-job-configuration>
        <foreign-input-file name=\"rcReport\" pipeline=\"$ENV{'onlineTask'}\" file=\"rcReport\"/>
        <file name=\"script\" type=\"csh\" file-type=\"script\"/>
        <processing-step name=\"populateElogDb\" executable=\"populateElogDbWrapper\" batch-job-configuration=\"express-job\">
                        <input-file name=\"rcReport\"/>
                        <output-file name=\"script\"/>
        </processing-step>
        <processing-step name=\"LaunchDigi\" executable=\"LaunchDigiWrapper\" batch-job-configuration=\"express-job\">
                        <input-file name=\"ldf\"/>
        </processing-step>
        <processing-step name=\"LaunchConfRep\" executable=\"LaunchConfRepWrapper\" batch-job-configuration=\"express-job\">
                        <input-file name=\"schema\"/>
                        <input-file name=\"snapshot\"/>
        </processing-step>
</pipeline>
";

my $eLogXmlFileName = "$ENV{'eLogTask'}.xml";
open FIELDS, '>', $eLogXmlFileName;
print FIELDS $updateElogDbXml;
close FIELDS;

