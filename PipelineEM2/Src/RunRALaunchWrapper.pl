#!/usr/local/bin/perl

# Demonstration script.
# Submitted to batch by pipeline scheduler.
# You need only modify the last section...

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
my $taskName = $proc->{'task_name'};
my $runName = $proc->{'run_name'};

#####################################################
##
##  END:  DON'T TOUCH STUFF BETWEEN THESE COMMENTS
##
#####################################################

my $exe = './TaskLaunch.pl';

my $newTask = 'SVACTuple';
#my $mcRootFile = $inFiles->{'mc'};
my $digiRootFile = $inFiles->{'digi'};
my $reconRootFile = $inFiles->{'recon'};
#my $command = "$exe '$taskName' '$newTask' '$runName' '$mcRootFile' '$digiRootFile' '$reconRootFile'";
my $command = "$exe '$taskName' '$newTask' '$runName' '$digiRootFile' '$reconRootFile'";

print "Running command :[$command]\n";
my $status = system("$command");

if ($status == 0) {
    exit 0;}
else {
    exit 1;}

