#!/usr/bin/perl -w

use strict;

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

my $urlUpdater = $ENV{'urlUpdateWrapper'};

# eLog
my $eLogDataDir = $ENV{'svacHead'};

# configReport
my $configDataDir = "$ENV{'svacHead'}/configReport/$ENV{'configReportVersion'}";

# digitization
my $digiDataDir = "$ENV{'svacEmDir'}/grRoot";

# digiReport
my $digiReportDataDir = "$ENV{'svacEmDir'}/digiReport/$ENV{'digiReportVersion'}";

# recon
my $reconDataDir = "$ENV{'calibRoot'}/grRoot";

# reconReport
my $reconReportDataDir = "$ENV{'calibRoot'}/reconReport/$ENV{'reconReportVersion'}";

# svacTuple
my $svacTupleDataDir = "$ENV{'calibRoot'}/svacRoot/$ENV{'svacTupleVersion'}";

my $batchgroup = "glastdata";


#$ENV{''}


my $onlineXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/pipeline/pipeline.xsd\">
    <name>$ENV{'onlineTask'}</name>
    <type>Conversion</type>
    <dataset-base-path>$ENV{'onlineHead'}</dataset-base-path>
    <run-log-path>/temp/</run-log-path>
        <executable name=\"ldf2fitsWrapper\" version=\"onlineVersion\">
            $ENV{'onlineTaskDir'}/OnlineWrapper.pl
        </executable>
        <executable name=\"injectSVACWrapper\" version=\"$ENV{'svacOnlineVersion'}\">
            $ENV{'svacOnlineDir'}/SVACWrapper.pl
        </executable>
        <batch-job-configuration name=\"short-job\" queue=\"short\" group\"$batchgroup\">
            <working-directory>$ENV{'onlineHead'}</working-directory>
            <log-file-path>$ENV{'onlineHead'}</log-file-path>
        </batch-job-configuration>
        <file name=\"ldf\" type=\"fits\" file-type=\"LDF\"></file>
        <file name=\"rcReport\" type=\"xml\" file-type=\"rcReport\"></file>
        <file name=\"schema\" type=\"xml\" file-type=\"text\"></file>
        <file name=\"snapshot\" type=\"xml\" file-type=\"text\"></file>
        <processing-step name=\"ldf2fits\" executable=\"ldf2fitsWrapper\" batch-job-configuration=\"short-job\">
                        <output-file name=\"ldf\"/>
                        <output-file name=\"rcReport\"/>
                        <output-file name=\"schema\"/>
                        <output-file name=\"snapshot\"/>
        </processing-step>
        <processing-step name=\"injectSVAC\" executable=\"injectSVACWrapper\" batch-job-configuration=\"short-job\">
                        <input-file name=\"ldf\"/>
                        <input-file name=\"rcReport\"/>
                        <input-file name=\"schema\"/>
                        <input-file name=\"snapshot\"/>
        </processing-step>
</pipeline>

";

my $onlineFileName = "$ENV{'onlineTask'}.xml";
open FIELDS, '>', $onlineFileName;
print FIELDS $onlineXml;
close FIELDS;


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


my $configReportXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/pipeline/pipeline.xsd\">
    <name>$ENV{'configReportTask'}</name>
    <type>>Report</type>
    <dataset-base-path>$configDataDir</dataset-base-path>
    <run-log-path>/temp/</run-log-path>
        <executable name=\"ConfigTablesWrapper\" version=\"$ENV{'configReportTaskVersion'}\">
            $ENV{'configTaskDir'}/ConfigTablesWrapper.pl
        </executable>
        <executable name=\"configReportUrlWrapper\" version=\"$ENV{'svacPlLibVersion'}\">
            $urlUpdater
        </executable>
        <batch-job-configuration name=\"express-job\" queue=\"express\" group\"$batchgroup\">
            <working-directory>$configDataDir</working-directory>
            <log-file-path>$configDataDir</log-file-path>
        </batch-job-configuration>
        <batch-job-configuration name=\"short-job\" queue=\"short\" group\"$batchgroup\">
            <working-directory>$configDataDir</working-directory>
            <log-file-path>$configDataDir</log-file-path>
        </batch-job-configuration>
        <foreign-input-file name=\"snapshot\" pipeline=\"$ENV{'onlineTask'}\" name=\"snapshot\"/>
        <file name=\"tarBall\" type=\"tgz\" file-type=\"Analysis\"/>
        <processing-step name=\"ConfigTables\" executable=\"ConfigTablesWrapper\" batch-job-configuration=\"short-job\">
                        <input-file name=\"schema\"/>
                        <input-file name=\"snapshot\"/>
                        <output-file name=\"tarBall\"/>
        </processing-step>
        <processing-step name=\"configReportUrl\" executable=\"configReportUrlWrapper\" batch-job-configuration=\"express-job\">
                        <input-file name=\"tarBall\"/>
        </processing-step>
</pipeline>

";

my $configReportXmlFileName = "$ENV{'configReportTask'}.xml";
open FIELDS, '>', $configReportXmlFileName;
print FIELDS $configReportXml;
close FIELDS;


my $digitizationXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/pipeline/pipeline.xsd\">
    <name>$ENV{'digitizationTask'}</name>
    <type>Digitization</type>
    <dataset-base-path>$digiDataDir</dataset-base-path>
    <run-log-path>/temp/</run-log-path>
        <executable name=\"ConvertWrapper\" version=\"$ENV{'digitizationTaskVersion'}\">
            $ENV{'digitizationTaskDir'}/ldfToDigiWrapper.pl
        </executable>
        <executable name=\"LaunchReconWrapper\" version=\"$ENV{'digitizationTaskVersion'}\">
            $ENV{'digitizationTaskDir'}/recLaunchWrapper.pl
        </executable>
        <executable name=\"LaunchReportWrapper\" version=\"$ENV{'digitizationTaskVersion'}\">
            $ENV{'digitizationTaskDir'}/genDTRLaunchWrapper.pl
        </executable>
        <executable name=\"digiRootFileWrapper\" version=\"$ENV{'svacPlLibVersion'}\">
            $urlUpdater
        </executable>
        <batch-job-configuration name=\"express-job\" queue=\"express\" group\"$batchgroup\">
            <working-directory>$digiDataDir</working-directory>
            <log-file-path>$digiDataDir</log-file-path>
        </batch-job-configuration>
        <batch-job-configuration name=\"medium-job\" queue=\"medium\" group\"$batchgroup\">
            <working-directory>$digiDataDir</working-directory>
            <log-file-path>$digiDataDir</log-file-path>
        </batch-job-configuration>
        <foreign-input-file name=\"ldf\" pipeline=\"$ENV{'onlineTask'}\" name=\"ldf\"/>
        <file name=\"digi\" type=\"root\" file-type=\"DIGI\"/>
        <file name=\"jobOptions\" type=\"jobOpt\" file-type=\"text\"/>
        <file name=\"script\" type=\"csh\" file-type=\"script\"/>
        <processing-step name=\"Convert\" executable=\"ConvertWrapper\" batch-job-configuration=\"medium-job\">
                        <input-file name=\"ldf\"/>
                        <output-file name=\"digi\"/>
                        <output-file name=\"script\"/>
                        <output-file name=\"jobOptions\"/>
        </processing-step>
        <processing-step name=\"LaunchRecon\" executable=\"LaunchReconWrapper\" batch-job-configuration=\"express-job\">
                        <input-file name=\"digi\"/>
        </processing-step>
        <processing-step name=\"LaunchReport\" executable=\"LaunchReportWrapper\" batch-job-configuration=\"express-job\">
                        <input-file name=\"digi\"/>
        </processing-step>
        <processing-step name=\"digiRootFile\" executable=\"digiRootFileWrapper\" batch-job-configuration=\"express-job\">
                        <input-file name=\"digi\"/>
        </processing-step>
</pipeline>

";

my $digitizationXmlFileName = "$ENV{'digitizationTask'}.xml";
open FIELDS, '>', $digitizationXmlFileName;
print FIELDS $digitizationXml;
close FIELDS;


my $digiReportXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/pipeline/pipeline.xsd\">
    <name>$ENV{'digiReportTask'}</name>
    <type>Report</type>
    <dataset-base-path>$digiReportDataDir</dataset-base-path>
    <run-log-path>/temp/</run-log-path>
        <executable name=\"genReportWrapper\" version=\"$ENV{'digiReportTaskVersion'}\">
            $ENV{'digiReportTaskDir'}/genDigiTestReportWrapper.pl
        </executable>
        <executable name=\"digiReportUrlWrapper\" version=\"$ENV{'svacPlLibVersion'}\">
            $urlUpdater
        </executable>
        <batch-job-configuration name=\"medium-job\" queue=\"medium\" group\"$batchgroup\">
            <working-directory>$digiReportDataDir</working-directory>
            <log-file-path>$digiReportDataDir</log-file-path>
        </batch-job-configuration>
        <batch-job-configuration name=\"express-job\" queue=\"express\" group\"$batchgroup\">
            <working-directory>$digiReportDataDir</working-directory>
            <log-file-path>$digiReportDataDir</log-file-path>
        </batch-job-configuration>
        <foreign-input-file name=\"digi\" pipeline=\"$ENV{'digitizationTask'}\" file=\"digi\"/>
        <file name=\"jobOptions\" type=\"jobOpt\" file-type=\"text\"/>
        <file name=\"script\" type=\"csh\" file-type=\"script\"/>
        <file name=\"tarBall\" type=\"tgz\" file-type=\"Analysis\"/>
        <processing-step name=\"genReport\" executable=\"genReportWrapper\" batch-job-configuration=\"medium-job\">
                        <input-file name=\"digi\"/>
                        <output-file name=\"jobOptions\"/>
                        <output-file name=\"script\"/>
                        <output-file name=\"tarBall\"/>
        </processing-step>
        <processing-step name=\"digiReportUrl\" executable=\"digiReportUrlWrapper\" batch-job-configuration=\"express-job\">
                        <input-file name=\"tarBall\"/>
        </processing-step>
</pipeline>

";

my $digiReportXmlFileName = "$ENV{'digiReportTask'}.xml";
open FIELDS, '>', $digiReportXmlFileName;
print FIELDS $digiReportXml;
close FIELDS;


my $reconXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/pipeline/pipeline.xsd\">
    <name>$ENV{'reconTask'}</name>
    <type>Reconstruction</type>
    <dataset-base-path>$reconDataDir</dataset-base-path>
    <run-log-path>/temp/</run-log-path>
    <executable name=\"reconWrapper\" version=\"$ENV{'reconTaskVersion'}\">
        $ENV{'reconTaskDir'}/reconWrapper.pl
    </executable>
    <executable name=\"RunRALaunchWrapper\" version=\"$ENV{'reconTaskVersion'}\">
        $ENV{'reconTaskDir'}/RunRALaunchWrapper.pl
    </executable>
    <executable name=\"genRTRLaunchWrapper\" version=\"$ENV{'reconTaskVersion'}\">
        $ENV{'reconTaskDir'}/genRTRLaunchWrapper.pl
    </executable>
    <executable name=\"urlWrapper\" version=\"$ENV{'svacPlLibVersion'}\">
        $urlUpdater
    </executable>
    <batch-job-configuration name=\"xlong-job\" queue=\"xlong\" group\"$batchgroup\">
        <working-directory>$reconDataDir</working-directory>
        <log-file-path>$reconDataDir</log-file-path>
    </batch-job-configuration>
    <batch-job-configuration name=\"express-job\" queue=\"express\" group\"$batchgroup\">
        <working-directory>$reconDataDir</working-directory>
        <log-file-path>$reconDataDir</log-file-path>
    </batch-job-configuration>
    <foreign-input-file name=\"digi\" pipeline=\"$ENV{'digitizationTask'}\" file=\"digi\"/>
    <file name=\"jobOptions\" type=\"text\"   file-type=\"jobOpt\"/>
    <file name=\"merit\"      type=\"merit\"  file-type=\"root\"/>
    <file name=\"recon\"      type=\"RECON\"  file-type=\"root\"/>
    <file name=\"script\"     type=\"script\" file-type=\"csh\"/>
    <processing-step name=\"recon\" executable=\"reconWrapper\" batch-job-configuration=\"xlong-job\">
                    <input-file name=\"digi\"/>
                    <output-file name=\"jobOptions\"/>
                    <output-file name=\"merit\"/>
                    <output-file name=\"recon\"/>
                    <output-file name=\"script\"/>
    </processing-step>
    <processing-step name=\"LaunchSVAC\" executable=\"RunRALaunchWrapper\" batch-job-configuration=\"express-job\">
                    <input-file name=\"digi\"/>
                    <input-file name=\"recon\"/>
    </processing-step>
    <processing-step name=\"LaunchReport\" executable=\"genRTRLaunchWrapper\" batch-job-configuration=\"express-job\">
                    <input-file name=\"digi\"/>
                    <input-file name=\"recon\"/>
    </processing-step>
    <processing-step name=\"reconRootFile\" executable=\"urlWrapper\" batch-job-configuration=\"express-job\">
                    <input-file name=\"recon\"/>
    </processing-step>
    <processing-step name=\"meritRootFile\" executable=\"urlWrapper\" batch-job-configuration=\"express-job\">
                    <input-file name=\"merit\"/>
    </processing-step>
</pipeline>
";

my $reconXmlFileName = "$ENV{'reconTask'}.xml";
open FIELDS, '>', $reconXmlFileName;
print FIELDS $reconXml;
close FIELDS;


my $reconReportXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/pipeline/pipeline.xsd\">
    <name>$ENV{'reconReportTask'}</name>
    <type>Report</type>
    <dataset-base-path>$reconReportDataDir</dataset-base-path>
    <run-log-path>/temp/</run-log-path>
        <executable name=\"genReportWrapper\" version=\"$ENV{'reconReportTaskVersion'}\">
            $ENV{'reconReportTaskDir'}/genReconTestReportWrapper.pl
        </executable>
        <executable name=\"reconReportUrlWrapper\" version=\"$ENV{'svacPlLibVersion'}\">
            $urlUpdater
        </executable>
        <batch-job-configuration name=\"long-job\" queue=\"long\" group\"$batchgroup\">
            <working-directory>$reconReportDataDir</working-directory>
            <log-file-path>$reconReportDataDir</log-file-path>
        </batch-job-configuration>
        <batch-job-configuration name=\"express-job\" queue=\"express\" group\"$batchgroup\">
            <working-directory>$reconReportDataDir</working-directory>
            <log-file-path>$reconReportDataDir</log-file-path>
        </batch-job-configuration>
        <foreign-input-file name=\"digi\" pipeline=\"$ENV{'digitizationTask'}\" file=\"digi\"/>
        <foreign-input-file name=\"recon\" pipeline=\"$ENV{'reconTask'}\"/ file=\"recon\">
        <file name=\"jobOptions\" type=\"jobOpt\" file-type=\"text\"/>
        <file name=\"script\" type=\"csh\" file-type=\"script\"/>
        <file name=\"tarBall\" type=\"tgz\" file-type=\"Analysis\"/>
        <processing-step name=\"genReport\" executable=\"genReportWrapper\" batch-job-configuration=\"long-job\">
                        <input-file name=\"digi\"/>
                        <input-file name=\"recon\"/>
                        <output-file name=\"jobOptions\"/>
                        <output-file name=\"script\"/>
                        <output-file name=\"tarBall\"/>
        </processing-step>
        <processing-step name=\"reconReportUrl\" executable=\"reconReportUrlWrapper\" batch-job-configuration=\"express-job\">
                        <input-file name=\"tarBall\"/>
        </processing-step>
</pipeline>

";

my $reconReportXmlFileName = "$ENV{'reconReportTask'}.xml";
open FIELDS, '>', $reconReportXmlFileName;
print FIELDS $reconReportXml;
close FIELDS;


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

