#!/usr/local/bin/perl

use strict;

use lib '/u/gl/dflath/glast/software/DPF/PDB/';
use DPFProc;

#####################################################
##
##  BEGIN:  DON'T TOUCH STUFF BETWEEN THESE COMMENTS
##
#####################################################

my $proc = new DPFProc(@ARGV);
my $inFiles = $proc->{'inFiles'};
my $outFiles = $proc->{'outFiles'};

#####################################################
##
##  END:  DON'T TOUCH STUFF BETWEEN THESE COMMENTS
##
#####################################################

my $ldfFile = $inFiles->{'ldf'};
my $shellFile = $outFiles->{'script'};
my $jobOptionFile = $outFiles->{'jobOptions'};
my $digiRootFile = $outFiles->{'digi'};

$ENV{'ldfFile'} = $ldfFile;
$ENV{'shellFile'} = $shellFile;
$ENV{'jobOptionFile'} = $jobOptionFile;
$ENV{'digiRootFile'}= $digiRootFile;
$ENV{'cmtPath'} = '/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0402p16';
$ENV{'cmtDir'} = '/nfs/farm/g/glast/u06/chen/glast_mc/EngineeringModel_v3r0402p16/Em2/v0r0p0/cmt';
$ENV{'exe'} = '/nfs/farm/g/glast/u06/chen/glast_mc/EngineeringModel_v3r0402p16/Em2/v0r0p0/rh9_gcc32/Em2.exe';

my $command = "ldfToDigi.pl";

system $command;

