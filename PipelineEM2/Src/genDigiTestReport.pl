#!/usr/local/bin/perl

use strict;

if ($#ARGV != 4) {
    die "Usage: $0 digiRootFile optionFile shellFile tarBall";
}

my ($runName, $digiRootFile, $optionFile, $shellFile, $tarBall) = @ARGV;

print <<EOT;
$0 running with:
  runName:      [$runName]
  digiRootFile: [$digiRootFile]
  optionFile:   [$optionFile]
  shellFile:    [$shellFile]
  tarBall:      [$tarBall]
EOT

my $reconRootFile = 'noSuchFile';

my $reportDir = `dirname $tarBall`;
chomp $reportDir;

my $texFile = 'refman.tex';
my $dviFile = 'refman.dvi';
my $psFile = 'refman.ps';
my $pdfFile = 'refman.pdf';
my $htmlFile = 'index.html';
my $pwd =  $ENV{PWD};

my $cmtPath = '/nfs/slac/g/svac/common/builds/:/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0402p16';
my $cmtDir = '/nfs/slac/g/svac/common/builds/TestReport/v2r0/cmt';
my $exeDir = '/nfs/slac/g/svac/common/builds/TestReport/v2r0/rh9_gcc32';
my $doxyFile = '/nfs/slac/g/svac/common/builds/TestReport/v2r0/src/ReportDoxyfile';

open(OPTFILE, ">$optionFile") || die "Can't open $optionFile for input, abortted!";
print OPTFILE qq{$digiRootFile \n};
print OPTFILE qq{$reconRootFile \n};
print OPTFILE qq{$reportDir \n};
print OPTFILE qq{$runName \n};
close(OPTFILE);

open(SHELLFILE, ">$shellFile") || die "Can't open $shellFile, abortted!";
print SHELLFILE qq{#!/bin/csh \n \n};
print SHELLFILE qq{unsetenv LD_LIBRARY_PATH \n};
print SHELLFILE qq{setenv CMTPATH $cmtPath \n};
print SHELLFILE qq{source $cmtDir/setup.csh \n};
print SHELLFILE qq{$exeDir/TestReport.exe $optionFile \n};
print SHELLFILE qq{cd $reportDir \n};
print SHELLFILE qq{doxygen $doxyFile \n};
print SHELLFILE qq{cd latex \n};
print SHELLFILE qq{latex $texFile \n};
print SHELLFILE qq{dvips -o $psFile $dviFile \n};
print SHELLFILE qq{ps2pdf $psFile $pdfFile \n};
print SHELLFILE qq{cd $reportDir \n};
print SHELLFILE qq{tar cf $tarBall . \n};
print SHELLFILE qq{cd $pwd};
close(SHELLFILE);
system("chmod +rwx $shellFile");

my $status = system("$shellFile");

if ($status == 0) {
    exit 0;}
else {
    exit 1;}
