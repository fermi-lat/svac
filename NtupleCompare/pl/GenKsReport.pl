#!/usr/local/bin/perl

use strict;

my $numArgs = $#ARGV + 1;

my $optionFile;

if($numArgs == 0) {
    $optionFile = "../src/ReportOption.dat";
}
else {
    $optionFile = $ARGV[0];
}

open(OPTFILE, "<$optionFile") || die "Can't open $optionFile for input, abortted!";

while(<OPTFILE>) {
    last if( ($_ =~ /\S+/) && ($_ !~ /^\/\//) );
}
my $nEvts = $_;
while(<OPTFILE>) {
    last if( ($_ =~ /\S+/) && ($_ !~ /^\/\//) );
}
my $reportDir = $_;
chop($reportDir);
while(<OPTFILE>) {
    last if( ($_ =~ /\S+/) && ($_ !~ /^\/\//) );
}
my $prefix = $_;
chop($prefix);
close(OPTFILE);

my $ksReportVersion = "v0";
my $texFile = 'refman.tex';
my $dviFile = 'refman.dvi';
my $psFile = 'refman.ps';
my $pdfFile = 'refman.pdf';
my $htmlFile = 'index.html';
my $pwd =  $ENV{PWD};

my $cmtPath = "/nfs/farm/g/glast/u06/chen/svac:/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0404p2";
my $cmtDir = "/nfs/farm/g/glast/u06/chen/svac/NtupleCompare/v0/cmt";
my $exeDir = "/nfs/farm/g/glast/u06/chen/svac/NtupleCompare/v0/rh9_gcc32";
my $doxyFile = "/nfs/farm/g/glast/u06/chen/svac/NtupleCompare/v0/src/ReportDoxyfile";
my $latexHeader = "/nfs/farm/g/glast/u06/chen/svac/NtupleCompare/v0/src/latexHeader.tex";

my $shellFile = $reportDir.'/'.$prefix.'_report.scr';
open(SHELLFILE, ">$shellFile") || die "Can't open $shellFile, abortted!";
print SHELLFILE qq{#!/bin/csh \n \n};
print SHELLFILE qq{unsetenv LD_LIBRARY_PATH \n};
print SHELLFILE qq{setenv CMTPATH $cmtPath \n};
print SHELLFILE qq{source $cmtDir/setup.csh \n};
print SHELLFILE qq{$exeDir/NtupleCompare.exe $optionFile \n};
print SHELLFILE qq{cd $reportDir \n};
print SHELLFILE qq{setenv latexHeader '$latexHeader' \n};
print SHELLFILE qq{setenv ksReportVersion '$ksReportVersion' \n};
print SHELLFILE qq{doxygen $doxyFile \n};
print SHELLFILE qq{cd latex \n};
print SHELLFILE qq{latex $texFile \n};
print SHELLFILE qq{latex $texFile \n};
print SHELLFILE qq{dvips -o $psFile $dviFile \n};
print SHELLFILE qq{ps2pdf $psFile $pdfFile \n};
print SHELLFILE qq{cd $pwd};
close(SHELLFILE);
system("chmod +rwx $shellFile");
system("$shellFile");
#    system("bsub -q medium -o $dumpFile $shellFile");



