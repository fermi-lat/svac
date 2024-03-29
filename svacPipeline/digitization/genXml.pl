#!/usr/bin/perl -w

use strict;

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

my $urlUpdater = $ENV{'urlUpdateWrapper'};

my $batchgroup = $ENV{'batchgroup'};

use MakeMeta;
my %metaWrappers = (MakeMeta::makeMeta($ENV{'digitizationTaskDir'}, 
									   "ldfToDigi", "retDefToDigi",
									   "setEvents"),
					MakeMeta::makeMeta($ENV{'svacPlLib'}, 
									   "Launch", "LaunchReconstructable", 
									   "url", "delete")
					);


my $digitizationXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/Pipeline/schemas/1.1/pipeline.xsd\">

    <name>$ENV{'digitizationTask'}</name>
    <type>Digitization</type>
    <dataset-base-path></dataset-base-path>
    <run-log-path>/temp/</run-log-path>

    <executable name=\"Convert\" version=\"$ENV{'digitizationTaskVersion'}\">
        $metaWrappers{'retDefToDigi'}
    </executable>
    <executable name=\"SetEvents\" version=\"$ENV{'digitizationTaskVersion'}\">
        $metaWrappers{'setEvents'}
    </executable>
    <executable name=\"launchRecon\" version=\"$ENV{'digitizationTaskVersion'}\">
        $metaWrappers{'LaunchReconstructable'}
    </executable>
    <executable name=\"taskLauncher\" version=\"$ENV{'svacVersion'}\">
        $metaWrappers{'Launch'}
    </executable>
    <executable name=\"urlWrapper\" version=\"$ENV{'svacVersion'}\">
        $metaWrappers{'url'}
    </executable>
    <executable name=\"deleteWrapper\" version=\"$ENV{'svacVersion'}\">
        $metaWrappers{'delete'}
    </executable>

    <batch-job-configuration name=\"express-job\" queue=\"express\" group=\"$batchgroup\">
        <working-directory>$ENV{'digitizationDataDirFull'}</working-directory>
        <log-file-path>$ENV{'digitizationDataDirFull'}</log-file-path>
    </batch-job-configuration>
    <batch-job-configuration name=\"glastdataq-job\" queue=\"glastdataq\" group=\"$batchgroup\">
        <working-directory>$ENV{'digitizationDataDirFull'}</working-directory>
        <log-file-path>$ENV{'digitizationDataDirFull'}</log-file-path>
    </batch-job-configuration>

    <file name=\"RetDef\"     file-type=\"evt\"   type=\"RetDef\">
        <path>$ENV{'onlineDataDirFull'}</path>
    </file>
    <file name=\"digi\"       file-type=\"root\"   type=\"DIGI\">
        <path>$ENV{'digitizationDataDirFull'}</path>
    </file>
    <file name=\"jobOptions\" file-type=\"jobOpt\" type=\"text\">
        <path>$ENV{'digitizationDataDirFull'}</path>
    </file>
    <file name=\"script\"     file-type=\"csh\"    type=\"script\">
        <path>$ENV{'digitizationDataDirFull'}</path>
    </file>
    <file name=\"evtList\" type=\"text\"   file-type=\"txt\">
        <path>$ENV{'digitizationDataDirFull'}</path>
    </file>

    <processing-step name=\"Convert\" executable=\"Convert\" batch-job-configuration=\"glastdataq-job\">
                    <input-file name=\"RetDef\"/>
                    <output-file name=\"digi\"/>
                    <output-file name=\"script\"/>
                    <output-file name=\"jobOptions\"/>
                    <output-file name=\"evtList\"/>
    </processing-step>
    <processing-step name=\"SetEvents\" executable=\"SetEvents\" batch-job-configuration=\"express-job\">
                    <input-file name=\"digi\"/>
    </processing-step>
    <processing-step name=\"$ENV{'reconTask'}\" executable=\"launchRecon\" batch-job-configuration=\"express-job\">
                    <input-file name=\"digi\"/>
    </processing-step>
    <processing-step name=\"$ENV{'digiReportTask'}\" executable=\"taskLauncher\" batch-job-configuration=\"express-job\">
                    <input-file name=\"digi\"/>
    </processing-step>
    <processing-step name=\"$ENV{'acdReportTask'}\" executable=\"taskLauncher\" batch-job-configuration=\"express-job\">
                    <input-file name=\"digi\"/>
    </processing-step>
    <processing-step name=\"$ENV{'configReportTask'}\" executable=\"taskLauncher\" batch-job-configuration=\"express-job\">
                    <input-file name=\"digi\"/>
    </processing-step>
    <processing-step name=\"digiRootFile\" executable=\"urlWrapper\" batch-job-configuration=\"express-job\">
                    <input-file name=\"digi\"/>
    </processing-step>
    <processing-step name=\"deleteEvt\" executable=\"deleteWrapper\" batch-job-configuration=\"express-job\">
                    <input-file name=\"evtList\"/>
    </processing-step>
</pipeline>

";

my $digitizationXmlFileName = "$ENV{'digitizationTask'}.xml";
open FIELDS, '>', $digitizationXmlFileName;
print FIELDS $digitizationXml;
close FIELDS;

