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

my $shellFile = $outFiles->{'script'};
my $rcReport = $inFiles->{'rcReport'};

my $exe = './populateElogDb.pl';

my $command = "$exe '$shellFile' '$rcReport'";
print "Running command: [$command]\nIn $ENV{'PWD'}\n";

my $status = system($command);

if ($status == 0) {
    exit 0;}
else {
    exit 1;}
