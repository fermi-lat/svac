#!/usr/local/bin/perl

use strict;

use lib $ENV{'PDB_HOME'};
use DPFProc;


#####################################################
##
##  BEGIN:  DON'T TOUCH STUFF BETWEEN THESE COMMENTS
##
#####################################################

my $run_num=shift;
my $task_pk=shift;
my $taskProcess_name=shift;
print "$run_num, $task_pk, $taskProcess_name\n";
my $proc = new DPFProc($run_num, $task_pk, $taskProcess_name);

my $inFiles = $proc->{'inFiles'};
my $outFiles = $proc->{'outFiles'};
#####################################################
##
##  END:  DON'T TOUCH STUFF BETWEEN THESE COMMENTS
##
#####################################################

my $mcRootFile = $inFiles->{'mc'};
my $digiRootFile = $inFiles->{'digi'};
my $reconRootFile = $inFiles->{'recon'};

my $svacRootFile = $outFiles->{'svac'};
my $histFile = $outFiles->{'histogram'};
my $optionFile = $outFiles->{'jobOptions'};
my $shellFile = $outFiles->{'script'};

my $exe = 'RunRootAnalyzer.pl';

my $command = "$exe '$mcRootFile' '$digiRootFile' '$reconRootFile' '$svacRootFile' '$histFile' '$optionFile' '$shellFile'";
print "Running command: [$command]\n";
system($command);
