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
my $taskName = $proc->{'task_name'};

#####################################################
##
##  END:  DON'T TOUCH STUFF BETWEEN THESE COMMENTS
##
#####################################################

my $exe = 'TaskLaunch.pl';

my $newTask = 'ConfigReport';
my $schemaFile = $inFiles->{'schema'};
my $snapFile = $inFiles->{'snapshot'};
my $command = "$exe '$taskName' '$newTask' '$runName' '$schemaFile'' $snapFile'";
print "Running command :[$command]\n";
my $status = system("$command");

if ($status == 0) {
    exit 0;}
else {
    exit 1;}

