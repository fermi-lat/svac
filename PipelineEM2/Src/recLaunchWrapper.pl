#!/usr/local/bin/perl

# Demonstration script.
# Submitted to batch by pipeline scheduler.
# You need only modify the last section...

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
my $taskName = $proc->{'task_name'};

#####################################################
##
##  END:  DON'T TOUCH STUFF BETWEEN THESE COMMENTS
##
#####################################################

my $exe = 'TaskLaunch.pl';

my $digiRootFile = $inFiles->{'digi'};
my $newTask = 'SVACTuple';
my $command = "$exe '$taskName' '$newTask' '$runName' '$digiRootFile'";

print "Running command :[$command]\n";
my $status = system("$command");

if ($status == 0) {
    exit 0;}
else {
    exit 1;}

