#!/usr/bin/perl -w

use strict;

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

my $urlUpdater = $ENV{'urlUpdateWrapper'};

my $batchgroup = $ENV{'batchgroup'};

my $reconXml = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<pipeline
    xmlns=\"http://glast-ground.slac.stanford.edu/pipeline\"
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
    xsi:schemaLocation=\"http://glast-ground.slac.stanford.edu/pipeline http://glast-ground.slac.stanford.edu/pipeline.xsd\">

    <name>$ENV{'reconTask'}</name>
    <type>Reconstruction</type>
    <dataset-base-path>$ENV{'dataHead'}</dataset-base-path>
    <run-log-path>/temp/</run-log-path>

    <executable name=\"recon\" version=\"$ENV{'reconTaskVersion'}\">
        $ENV{'reconTaskDir'}/reconWrapper.pl
    </executable>
    <executable name=\"RunRALaunch\" version=\"$ENV{'reconTaskVersion'}\">
        $ENV{'reconTaskDir'}/RunRALaunchWrapper.pl
    </executable>
    <executable name=\"genRTRLaunch\" version=\"$ENV{'reconTaskVersion'}\">
        $ENV{'reconTaskDir'}/genRTRLaunchWrapper.pl
    </executable>
    <executable name=\"urlWrapper\" version=\"$ENV{'svacVersion'}\">
        $urlUpdater
    </executable>

    <batch-job-configuration name=\"xlong-job\" queue=\"xlong\" group=\"$batchgroup\">
        <working-directory>$ENV{'reconDataDirFull'}</working-directory>
        <log-file-path>$ENV{'reconDataDirFull'}</log-file-path>
    </batch-job-configuration>
    <batch-job-configuration name=\"express-job\" queue=\"express\" group=\"$batchgroup\">
        <working-directory>$ENV{'reconDataDirFull'}</working-directory>
        <log-file-path>$ENV{'reconDataDirFull'}</log-file-path>
    </batch-job-configuration>

    <file name=\"cal\"        type=\"ntuple\" file-type=\"root\">$ENV{'reconDataDir'}</file>
    <file name=\"merit\"      type=\"merit\"  file-type=\"root\">$ENV{'reconDataDir'}</file>
    <file name=\"recon\"      type=\"RECON\"  file-type=\"root\">$ENV{'reconDataDir'}</file>
    <file name=\"digi\"       type=\"DIGI\"   file-type=\"root\">$ENV{'digitizationDataDir'}</file>
    <file name=\"tarFile\"    type=\"log\"    file-type=\"tgz\">$ENV{'reconDataDir'}</file>

    <processing-step name=\"recon\" executable=\"recon\" batch-job-configuration=\"xlong-job\">
                    <input-file name=\"digi\"/>
                    <output-file name=\"cal\"/>
                    <output-file name=\"merit\"/>
                    <output-file name=\"recon\"/>
                    <output-file name=\"tarFile\"/>
    </processing-step>
    <processing-step name=\"LaunchSVAC\" executable=\"RunRALaunch\" batch-job-configuration=\"express-job\">
                    <input-file name=\"digi\"/>
                    <input-file name=\"recon\"/>
    </processing-step>
    <processing-step name=\"LaunchReport\" executable=\"genRTRLaunch\" batch-job-configuration=\"express-job\">
                    <input-file name=\"digi\"/>
                    <input-file name=\"recon\"/>
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
</pipeline>
";

my $reconXmlFileName = "$ENV{'reconTask'}.xml";
open FIELDS, '>', $reconXmlFileName;
print FIELDS $reconXml;
close FIELDS;


# write the csh script that does recon on one chunk
my $reconScript = 
"#!/bin/csh
unsetenv LD_LIBRARY_PATH
setenv CMTCONFIG $ENV{'SVAC_CMTCONFIG'}
setenv GLAST_EXT $ENV{'SVAC_GLAST_EXT'}
setenv CMTPATH $ENV{'CMTPATH'}
setenv LATCalibRoot $ENV{'LATCalibRoot'}
pushd $ENV{'reconCmt'}
source setup.csh ''
cmt show uses
popd
setenv JOBOPTIONS \$1
set digiFile=\$2

set stageDir=\$runStageDir
set localDir=$ENV{'localDisk'}

alias run 'echo \\!* ; date ; \\!*'

if ( { test -d \$localDir } ) then
    set relocate=1

	set myLocal=\$localDir/\$\$
	test -d \$myLocal || run mkdir \$myLocal

    setenv inDir \$myLocal
    setenv procDir \$myLocal

    set digiBase=`basename \$digiFile`
    set reconFile=`awk -F'\"' '/RECON\\.root/{print \$2}' \$JOBOPTIONS`
    set reconBase=`basename \$reconFile`
    set meritFile=`awk -F'\"' '/merit\\.root/{print \$2}' \$JOBOPTIONS`
    set meritBase=`basename \$meritFile`
    set calFile=`awk -F'\"' '/calTuple\\.root/{print \$2}' \$JOBOPTIONS`
    set calBase=`basename \$calFile`

    run cp \$digiFile \$inDir && set unDone=0 || set unDone=1
	while (\$unDone)
		sleep 17
		run cp \$digiFile \$inDir && set unDone=0 || set unDone=1
	end

else
    set relocate=0
    setenv procDir \$stageDir
    setenv inDir `dirname \$digiFile`
endif
echo Reading digi file from \$inDir
echo Writing chunk files to \$procDir

$ENV{'reconApp'} || exit 1

if ( \$relocate ) then
    echo Relocating chunk files from \$procDir to \$stageDir
    pushd \$procDir
    run mv \$reconBase \$meritBase \$calBase \$stageDir
    cd \$inDir
    run rm \$digiBase
    popd
	run rmdir \$myLocal 
endif
";
my $scriptName = "$ENV{'reconOneScript'}";
open(SHELLFILE, ">$scriptName") || die "Can't open $scriptName for writing!\n";
print SHELLFILE $reconScript;
close(SHELLFILE);
system("chmod +rx $scriptName");
