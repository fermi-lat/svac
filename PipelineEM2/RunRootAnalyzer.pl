#!/usr/local/bin/perl

use strict;
my($jobFile, $optionFile, $rootFile, $rootDir, $mcRootFile, $digiRootFile, 
$reconRootFile, $svacRootFile, $dumpFile, $shellFile);

my $numArgs = $#ARGV + 1;

if($numArgs == 0) {
    die "Missing run id as input argument";
}

my $runId = $ARGV[0];

my $rootDataDir = '/nfs/farm/g/glast/u01/temp/rootData/';

my $cmtPath = "/nfs/farm/g/glast/u06/chen/svac/:/nfs/farm/g/glast/u10/builds/EngineeringModel/EngineeringModel-v3r0402p9/";
my $cmtDir = "/nfs/farm/g/glast/u06/chen/svac/EngineeringModelRoot/v0r2/cmt";
my $exeDir = "/nfs/farm/g/glast/u06/chen/svac/EngineeringModelRoot/v0r2/rh9_gcc32";
my $mcRootDir = $rootDataDir.'/'.$runId.'/rootFile/';
my $digiRootDir = $mcRootDir;
my $reconRootDir = $mcRootDir;
my $svacRootDir = $mcRootDir;

$mcRootFile = $mcRootDir.$runId."_mc.root";
$digiRootFile = $digiRootDir.$runId."_digi.root";
$reconRootFile = $reconRootDir.$runId."_recon.root";
$svacRootFile = $svacRootDir.$runId."_svac.root";
my $histFile = $svacRootDir.$runId."_hist.root";
$dumpFile = $svacRootDir.$runId.".dump";

#create option file for Main.exe
$optionFile = $svacRootDir.$runId."_svac.dat";
open(OPTIONFILE, ">$optionFile") || die "Can't open $optionFile for input, abortted!";
print OPTIONFILE $mcRootFile."\n";
print OPTIONFILE $digiRootFile."\n";
print OPTIONFILE $reconRootFile."\n";
print OPTIONFILE $svacRootFile."\n";
print OPTIONFILE $histFile."\n";
close(OPTIONFILE);

#create shell file to execute Main.exe
$shellFile = $svacRootDir.$runId."_svac.scr";
open(SHELLFILE, ">$shellFile") || die "Can't open $shellFile for input, abortted!";
print SHELLFILE qq{#!/bin/csh \n \n};
print SHELLFILE qq{unsetenv LD_LIBRARY_PATH \n};
print SHELLFILE qq{setenv CMTPATH $cmtPath \n};
print SHELLFILE qq{source $cmtDir/setup.csh \n};
print SHELLFILE qq{$exeDir/RunRootAnalyzer.exe $optionFile \n};
close(SHELLFILE);
system("chmod +rwx $shellFile");
system("$shellFile");

