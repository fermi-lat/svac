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

#####################################################
##
##  END:  DON'T TOUCH STUFF BETWEEN THESE COMMENTS
##
#####################################################

my $mcRootFile = $inFiles->{'mc'};
my $digiRootFile = $inFiles->{'digi'};
my $reconRootFile = $inFiles->{'recon'};

my $exe = 'RunRALaunch.pl';

my $command = "$exe $taskName $runName $mcRootFile $digiRootFile $reconRootFile";
print "Running command :[$command]\n";
my $status = system("$command");

if ($status == 0) {
    exit 0;}
else {
    exit 1;}

