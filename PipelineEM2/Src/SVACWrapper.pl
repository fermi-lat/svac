#!/usr/local/bin/perl -w

# Pipeline interface to launch SVAC pipeline tasks

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
my $taskName = $proc->{'task_name'};
my $taskProcessName = $proc->{'taskProcess_name'};

#####################################################
##
##  END:  DON'T TOUCH STUFF BETWEEN THESE COMMENTS
##
#####################################################

my $exe = './SVACLaunch.pl';

my $rcReport = $inFiles->{'rcReport'};
my $schema = $inFiles->{'schema'};
my $snapshot = $inFiles->{'snapshot'};
my $ldfFile = $inFiles->{'ldf'};

my $cmd = "$exe '$taskName' '$runName' '$rcReport' '$schema' '$snapshot' '$ldfFile'";

print "cmd is [$cmd]\n";
my $status = system("$cmd");

if ($status == 0) {
    exit 0;}
else {
    exit 1;}

