#!/usr/local/bin/perl

use strict;

if ($#ARGV != 6) {
    die "Usage: $0 mcRootFile digiRootFile reconRootFile svacRootFile histFile optionFile shellFile";
}

my ($mcRootFile, $digiRootFile, $reconRootFile, $svacRootFile, $histFile, $optionFile, $shellFile) = @ARGV;

print <<EOT;
$0 running with:
  mcRootFile:    $mcRootFile
  digiRootFile:  $digiRootFile
  reconRootFile: $reconRootFile
  svacRootFile:  $svacRootFile
  histFile:      $histFile
  optionFile:    $optionFile
  shellFile:     $shellFile
EOT

my $cmtPath = "/nfs/slac/g/svac/common/builds/:/nfs/farm/g/glast/u10/builds/EngineeringModel/EngineeringModel-v3r0402p9/";
my $cmtDir = "/nfs/slac/g/svac/common/builds/EngineeringModelRoot/v1/cmt";
my $exeDir = "/nfs/slac/g/svac/common/builds/EngineeringModelRoot/v1/rh9_gcc32";

my $glastRoot = "/afs/slac.stanford.edu/g/glast";
my $glastScript = "$glastRoot/ground/scripts/user.cshrc";

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
# didn't help #print SHELLFILE qq{source $glastScript \n};
print SHELLFILE qq{unsetenv LD_LIBRARY_PATH \n};
print SHELLFILE qq{setenv CMTPATH $cmtPath \n};
print SHELLFILE qq{source $cmtDir/setup.csh \n};
print SHELLFILE qq{$exeDir/RunRootAnalyzer.exe $optionFile \n};
close(SHELLFILE);
system("chmod +rwx $shellFile");
exit(system("$shellFile"));

