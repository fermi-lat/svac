#!/usr/local/bin/perl -w

use strict;

if ($#ARGV != 5) {
    die "Usage: $0 runId digiRootFile optionFile shellFile histoFile tarBall";
}

print STDERR "$0: svacPlRoot=[$ENV{'svacPlRoot'}]\n";

my ($runName, $digiRootFile, $optionFile, $shellFile, $histoFile, $tarBall) = @ARGV;

print <<EOT;
$0 running with:
  runName:      [$runName]
  digiRootFile: [$digiRootFile]
  optionFile:   [$optionFile]
  shellFile:    [$shellFile]
  histoFile:    [$histoFile]
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

my $cmtPath = $ENV{'CMTPATH'};
my $cmtDir = $ENV{'digiReportCmt'};
my $exe = $ENV{'digiReportApp'};
my $digiReportVersion = $ENV{'digiReportVersion'};
my $EngineeringModelVersion = $ENV{'EngineeringModelVersion'};
my $tkrCalibSerNo = $ENV{'tkrCalibSerNo'};
my $calCalibSerNo = $ENV{'calCalibSerNo'};
my $latexHeaderFile = $ENV{'latexHeaderFile'};
my $doxyFile = $ENV{'digiRepDoxyFile'};
my $testReportVersion = $ENV{'TestReportVersion'};

my $histOrig = $runName . '_hist.root';

open(OPTFILE, ">$optionFile") || die "Can't open $optionFile for input, abortted!";
print OPTFILE qq{$digiRootFile \n};
print OPTFILE qq{$reconRootFile \n};
print OPTFILE qq{$reportDir \n};
print OPTFILE qq{$runName \n};
print OPTFILE qq{$digiReportVersion \n};
print OPTFILE qq{$EngineeringModelVersion \n};
print OPTFILE qq{$tkrCalibSerNo \n};
print OPTFILE qq{$calCalibSerNo \n};
close(OPTFILE);

open(SHELLFILE, ">$shellFile") || die "Can't open $shellFile, abortted!";
print SHELLFILE qq{#!/bin/csh \n \n};
print SHELLFILE qq{unsetenv LD_LIBRARY_PATH \n};
print SHELLFILE qq{setenv CMTPATH $cmtPath \n};
print SHELLFILE "setenv CMTCONFIG $ENV{'SVAC_CMTCONFIG'} \n";
print SHELLFILE "setenv GLAST_EXT $ENV{'SVAC_GLAST_EXT'} \n";
print SHELLFILE qq{source $cmtDir/setup.csh \n};
print SHELLFILE qq{$exe $optionFile || exit 1 \n};
print SHELLFILE qq{cd $reportDir \n};
print SHELLFILE qq{mv $histOrig $histoFile \n};
print SHELLFILE qq{ln -s $histoFile $histOrig \n};
print SHELLFILE qq{setenv latexHeader '$latexHeaderFile' \n};
print SHELLFILE qq{setenv testReportVersion '$testReportVersion' \n};
print SHELLFILE qq{doxygen $doxyFile \n};
print SHELLFILE qq{mv *.eps latex/ \n};
print SHELLFILE qq{cd latex \n};
print SHELLFILE qq{latex $texFile \n};
print SHELLFILE qq{dvips -o $psFile $dviFile \n};
print SHELLFILE qq{ps2pdf $psFile $pdfFile \n};
print SHELLFILE qq{cd $reportDir \n};
print SHELLFILE qq{tar cf $tarBall . \n};
print SHELLFILE qq{cd $pwd \n};
close(SHELLFILE);
system("chmod +rwx $shellFile");

my $status = system("$shellFile");

if ($status == 0) {
    exit 0;}
else {
    exit 1;}
