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

#####################################################
##
##  END:  DON'T TOUCH STUFF BETWEEN THESE COMMENTS
##
#####################################################

my $digiRootFile = $inFiles->{'digi'};
my $optionFile = $outFiles->{'jobOptions'};
my $shellFile = $outFiles->{'script'};
my $tarBall = $outFiles->{'tarBall'};

my $exe = '/nfs/slac/g/svac/common/pipeline/EM2/genDigiTestReport.pl';

my $command = "$exe '$digiRootFile' '$optionFile' '$shellFile' '$tarBall'";
print "Running command: [$command]\n";
system $command;
