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
my $reconRootFile = $inFiles->{'recon'};
my $optionFile = $outFiles->{'jobOptions'};
my $shellFile = $outFiles->{'script'};
my $tarBall = $outFiles->{'tarBall'};

my $exe = '/nfs/slac/g/svac/common/pipeline/EM2/genReconTestReport.pl';

my $command = "$exe '$digiRootFile' '$reconRootFile' '$optionFile' '$shellFile' '$tarBall'";
print "Running command: [$command]\n";
system $command;
