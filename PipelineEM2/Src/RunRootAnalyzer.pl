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

my $cmtPath = $ENV{'CMTPATH'};
my $cmtDir = $ENV{'svacTupleCmt'};
my $exe = $ENV{'svacTupleApp'};

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
print SHELLFILE qq{source $glastScript \n};
print SHELLFILE qq{unsetenv LD_LIBRARY_PATH \n};
print SHELLFILE qq{setenv CMTPATH $cmtPath \n};
print SHELLFILE qq{source $cmtDir/setup.csh \n};
print SHELLFILE qq{$exe $optionFile \n};
close(SHELLFILE);
system("chmod +rwx $shellFile");

my $status = system("$shellFile");

if ($status == 0) {
    exit 0;}
else {
    exit 1;}
