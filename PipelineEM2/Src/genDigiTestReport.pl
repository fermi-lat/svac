#!/usr/local/bin/perl

use strict;

my $numArgs = $#ARGV + 1;

if($numArgs == 0) {
    die "Missing run id as input argument";
}

my $runId = $ARGV[0];

my $rootDataDir = '/nfs/farm/g/glast/u01/temp/rootData/';

my $reportDir = $rootDataDir.$runId.'/report';
# create report dir under rootDataDir if it does not exist 
if(! (-d $reportDir) ) {
    mkdir($reportDir) || die "can not make dir $reportDir, abort!";
}

my $runRootDir = $rootDataDir.$runId.'/rootFile';

#search digi/recon root file
opendir(DIR, $runRootDir) || die "can not find $runRootDir, abort!";
my @files = readdir(DIR);
my $timeStamp;
foreach my $file (@files) {
    if($file =~ /\_digi.root/ ) {
	$timeStamp = substr($file, 0, length($file)-10);
	last;
    }
}

if(! defined($timeStamp)) {
    die "digi root file can not be found, abort!";
}

my $digiRootFile = $runRootDir.'/'.$timeStamp.'_digi.root';
my $reconRootFile = $runRootDir.'/'.$timeStamp.'_recon.root';
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

my $optionFile = $reportDir.'/GentestReport_'.$timeStamp.'.txt';
open(OPTFILE, ">$optionFile") || die "Can't open $optionFile for input, abortted!";
print OPTFILE qq{$digiRootFile \n};
print OPTFILE qq{$reconRootFile \n};
print OPTFILE qq{$reportDir \n};
print OPTFILE qq{$timeStamp \n};
close(OPTFILE);

my $shellFile = $reportDir.'/GenTestReport_'.$timeStamp.'.scr';
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
print SHELLFILE qq{cd $pwd};
close(SHELLFILE);
system("chmod +rwx $shellFile");
system("$shellFile");
