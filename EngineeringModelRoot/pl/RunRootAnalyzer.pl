#!/usr/local/bin/perl

use strict;
my($jobFile, $optionFile, $rootFile, $rootDir, $mcRootFile, $digiRootFile, 
$reconRootFile, $svacRootFile, $dumpFile, $shellFile);

$jobFile = "../src/job.dat";


my $cmtPath = "/nfs/farm/g/glast/u06/chen/glast_mc/:/nfs/farm/g/glast/u10/builds/EngineeringModel/EngineeringModel-v1r0401p9/";
my $cmtDir = "/nfs/farm/g/glast/u06/chen/glast_mc/EngineeringModelRoot/v1r0401p9/cmt";
my $exeDir = "/nfs/farm/g/glast/u06/chen/glast_mc/EngineeringModelRoot/v1r0401p9/rh9_gcc32";
my $digiRootDir = '/nfs/farm/g/glast/u01/mc/em_v1r0401p9/oneTower/';
my $svacRootDir = $digiRootDir;

open(JOBFILE, "<$jobFile") || die "Can't open $jobFile for input, abortted!";
while(<JOBFILE>) {
    ($rootFile) = split;
    if( $rootFile eq "") { last; }

    $mcRootFile = $digiRootDir.$rootFile."_mc.root";
    $digiRootFile = $digiRootDir.$rootFile."_digi.root";
    $reconRootFile = $svacRootDir.$rootFile."_recon.root";
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
    print SHELLFILE qq{setenv CMTPATH $cmtPath \n};
    print SHELLFILE qq{source $cmtDir/setup.csh \n};
    print SHELLFILE qq{$exeDir/RunRootAnalyzer.exe $optionFile \n};
    close(SHELLFILE);
    system("chmod +rwx $shellFile");
#    system("$shellFile");
    system("bsub -q medium -o $dumpFile $shellFile");
}

close(JOBFILE);
