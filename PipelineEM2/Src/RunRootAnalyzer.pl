#!/usr/local/bin/perl

use strict;

use lib '/u/gl/dflath/glast/software/DPF/PDB/';
use DPFProc;


#####################################################
##
##  BEGIN:  DON'T TOUCH STUFF BETWEEN THESE COMMENTS
##
#####################################################

my $run_num=shift;
my $task_pk=shift;
my $taskProcess_name=shift;
print "$run_num, $task_pk, $taskProcess_name\n";
my $proc = new DPFProc($run_num, $task_pk, $taskProcess_name);

my $inFiles = $proc->{'inFiles'};
my $outFiles = $proc->{'outFiles'};
#####################################################
##
##  END:  DON'T TOUCH STUFF BETWEEN THESE COMMENTS
##
#####################################################

my $mcRootFile = $inFiles->{'mc'};
my $digiRootFile = $inFiles->{'digi'};
my $reconRootFile = $inFiles->{'recon'};

my $svacRootFile = $outFiles->{'svac'};
my $histFile = $outFiles->{'histogram'};
my $optionFile = $outFiles->{'jobOptions'};
my $shellFile = $outFiles->{'script'};

my $cmtPath = "/nfs/farm/g/glast/u06/chen/svac/:/nfs/farm/g/glast/u10/builds/EngineeringModel/EngineeringModel-v3r0402p9/";
my $cmtDir = "/nfs/farm/g/glast/u06/chen/svac/EngineeringModelRoot/v0r2/cmt";
my $exeDir = "/nfs/farm/g/glast/u06/chen/svac/EngineeringModelRoot/v0r2/rh9_gcc32";

#create option file for Main.exe
open(OPTIONFILE, ">$optionFile") || die "Can't open $optionFile for input, abortted!";
print OPTIONFILE $mcRootFile."\n";
print OPTIONFILE $digiRootFile."\n";
print OPTIONFILE $reconRootFile."\n";
print OPTIONFILE $svacRootFile."\n";
print OPTIONFILE $histFile."\n";
close(OPTIONFILE);

#create shell file to execute Main.exe
open(SHELLFILE, ">$shellFile") || die "Can't open $shellFile for input, abortted!";
print SHELLFILE qq{#!/bin/csh \n \n};
print SHELLFILE qq{unsetenv LD_LIBRARY_PATH \n};
print SHELLFILE qq{setenv CMTPATH $cmtPath \n};
print SHELLFILE qq{source $cmtDir/setup.csh \n};
print SHELLFILE qq{$exeDir/RunRootAnalyzer.exe $optionFile \n};
close(SHELLFILE);
system("chmod +rwx $shellFile");
system("$shellFile");

