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

my $schema = $inFiles->{'schema'};
my $snapshot = $inFiles->{'snapshot'};

my $tarBall = $outFiles->{'tarBall'};

my $command = "./ConfigTables.py '$runName' '$schema' '$snapshot' '$tarBall'";
print "Running command: [$command]\n";

my $status = system($command);

if ($status == 0) {
    exit 0;}
else {
    exit 1;}
