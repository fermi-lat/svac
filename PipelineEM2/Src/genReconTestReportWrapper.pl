#!/usr/local/bin/perl

use strict;

use lib $ENV{'PDB_HOME'};
use DPFProc;

#####################################################
##
##  BEGIN:  DON'T TOUCH STUFF BETWEEN THESE COMMENTS
##
#####################################################

my $proc = new DPFProc(@ARGV);
my $inFiles = $proc->{'inFiles'};
my $outFiles = $proc->{'outFiles'};
my $runName = $proc->{'run_name'};

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

my $exe = './genReconTestReport.pl';

my $command = "$exe '$runName' '$digiRootFile' '$reconRootFile' '$optionFile' '$shellFile' '$tarBall'";
print "Running command: [$command]\n";
exit(system($command));
