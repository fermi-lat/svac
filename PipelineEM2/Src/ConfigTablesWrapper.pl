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
my $runName = $proc->{'run_name'};

#####################################################
##
##  END:  DON'T TOUCH STUFF BETWEEN THESE COMMENTS
##
#####################################################

my $schema = $inFiles->{'schema'};
my $snapshot = $inFiles->{'snapshot'};

my $tarBall = $outFiles->{'tarBall'};

my $command = "ConfigTables.py '$runName' '$schema' '$snapshot' '$tarBall'";
print "Running command: [$command]\n";
system $command;

 
