#!/usr/local/bin/perl

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

# Gotta get the run number in here somehow.
my $schema = $inFiles->{'schema'};
my $snapshot = $inFiles->{'snaphot'};

my $tarBall = $outFiles->{'tarBall'};

my $command = "ConfigTables.py $runName $schema $snapshot $tarBall";
my $extension = " | tee $logFile 2>&1 ";
my $syscmd = "$command $extension";

system $syscmd;

 
