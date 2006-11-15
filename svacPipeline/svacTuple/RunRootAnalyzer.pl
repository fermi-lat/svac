#!/usr/local/bin/perl -w

use strict;

use File::Copy;

if ($#ARGV != 7) {
    die "Usage: $0 mcRootFile digiRootFile reconRootFile svacRootFile histFile optionFile shellFile taskName";
}

print STDERR "$0: svacPlRoot=[$ENV{'svacPlRoot'}]\n";

my ($mcRootFile, $digiRootFile, $reconRootFile, $svacRootFile, $histFile, $optionFile, $shellFile, $taskName) = @ARGV;

my $reconDir = `dirname $reconRootFile`;
chomp $reconDir;
# remove leftover marker files
my $marker = "$reconDir/$ENV{'doneUsingRecon'}.$taskName";
unlink $marker;

my $cmtPath = $ENV{'CMTPATH'};
my $cmtDir = $ENV{'svacTupleCmt'};
my $exe = $ENV{'svacTupleApp'};
my $svacCmtConfig = $ENV{'SVAC_CMTCONFIG'};
my $svacGlastExt = $ENV{'SVAC_GLAST_EXT'};

print <<EOT;
$0 running with:
  mcRootFile:    $mcRootFile
  digiRootFile:  $digiRootFile
  reconRootFile: $reconRootFile
  svacRootFile:  $svacRootFile
  histFile:      $histFile
  optionFile:    $optionFile
  shellFile:     $shellFile
  taskName:      [$taskName]
EOT

# put .htaccess file in working directory to prevent HTTP downloads of 
# ROOT files
my $workDir = `dirname $svacRootFile`;
chomp $workDir;
copy($ENV{htAccess}, "$workDir/.htaccess");

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
print SHELLFILE "setenv CMTCONFIG $svacCmtConfig \n";
print SHELLFILE "setenv GLAST_EXT $svacGlastExt \n";
print SHELLFILE qq{setenv CMTPATH $cmtPath \n};
print SHELLFILE qq{source $cmtDir/setup.csh \n};
print SHELLFILE qq{$exe $optionFile || exit 1 \n};
close(SHELLFILE);
system("chmod +rwx $shellFile");

my $status = system("$shellFile");

if ($status == 0) {
    exit 0;}
else {
    exit 1;}
