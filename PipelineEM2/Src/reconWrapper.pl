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

my $digiRootFile = $inFiles->{'digi'};
my $shellFile = $outFiles->{'script'};
my $jobOptionFile = $outFiles->{'jobOptions'};
my $reconRootFile = $outFiles->{'recon'};
my $meritRootFile = $outFiles->{'merit'};

my $exe = '/nfs/slac/g/svac/common/pipeLine/EM2/recon.pl';

system("$exe '$digiRootFile' '$shellFile' '$jobOptionFile' '$reconRootFile' '$meritRootFile'");
