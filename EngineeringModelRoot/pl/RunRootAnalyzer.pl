#!/usr/local/bin/perl

use strict;
my($jobFile, $optionFile, $rootFile, $rootDir, $mcRootFile, $digiRootFile, 
$reconRootFile, $svacRootFile, $dumpFile, $shellFile);

$jobFile = "../src/job.dat";


my $cmtPath = "/nfs/farm/g/glast/u06/chen/svac/:/nfs/farm/g/glast/u10/builds/EngineeringModel/EngineeringModel-v3r0402p9/";
my $cmtDir = "/nfs/farm/g/glast/u06/chen/svac/EngineeringModelRoot/v0r2/cmt";
my $exeDir = "/nfs/farm/g/glast/u06/chen/svac/EngineeringModelRoot/v0r2/rh9_gcc32";
my $mcRootDir = '/nfs/farm/g/glast/u01/svac_workshop/em_v3r0402p9/mc/TwoTowers/cr/batch/';
my $digiRootDir = $mcRootDir;
my $reconRootDir = $mcRootDir;
#my $mcRootDir = '/nfs/farm/g/glast/u01/mc/em_v3r0402p9/oneTower/';
#my $digiRootDir = '/nfs/farm/g/glast/u01/svac_workshop/em_v3r0402p9/mc/OneTower/cr/digi/';
#my $reconRootDir = '/nfs/farm/g/glast/u01/svac_workshop/em_v3r0402p9/mc/OneTower/cr/recon/';
my $svacRootDir = $mcRootDir;

open(JOBFILE, "<$jobFile") || die "Can't open $jobFile for input, abortted!";
while(<JOBFILE>) {
    ($rootFile) = split;
    if( $rootFile eq "") { last; }

    $mcRootFile = $mcRootDir.$rootFile."_mc.root";
    $digiRootFile = $digiRootDir.$rootFile."_digi.root";
    $reconRootFile = $reconRootDir.$rootFile."_recon.root";
    $svacRootFile = $svacRootDir.$rootFile."_svac.root";
    my $histFile = $svacRootDir.$rootFile."_hist.root";
    $dumpFile = $svacRootDir.$rootFile.".dump";

#create option file for Main.exe
    $optionFile = $svacRootDir.$rootFile."_svac.dat";
    open(OPTIONFILE, ">$optionFile") || 
	die "Can't open $optionFile for input, abortted!";
    print OPTIONFILE $mcRootFile."\n";
    print OPTIONFILE $digiRootFile."\n";
    print OPTIONFILE $reconRootFile."\n";
    print OPTIONFILE $svacRootFile."\n";
    print OPTIONFILE $histFile."\n";
    close(OPTIONFILE);

#create shell file to execute Main.exe
    $shellFile = $svacRootDir.$rootFile."_svac.scr";
    open(SHELLFILE, ">$shellFile") || 
	die "Can't open $shellFile for input, abortted!";
    print SHELLFILE qq{#!/bin/csh \n \n};
    print SHELLFILE qq{unsetenv LD_LIBRARY_PATH \n};
    print SHELLFILE qq{setenv CMTPATH $cmtPath \n};
    print SHELLFILE qq{source $cmtDir/setup.csh \n};
    print SHELLFILE qq{$exeDir/RunRootAnalyzer.exe $optionFile \n};
    close(SHELLFILE);
    system("chmod +rwx $shellFile");
#    system("$shellFile");
    system("bsub -q medium -o $dumpFile $shellFile");
}

close(JOBFILE);
