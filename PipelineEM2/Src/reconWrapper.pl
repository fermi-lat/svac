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

my $digiRootFile = $inFiles->{'digi'};
my $shellFile = $outFiles->{'script'};
my $jobOptionFile = $outFiles->{'jobOptions'};
my $reconRootFile = $outFiles->{'recon'};
my $meritRootFile = $outFiles->{'merit'};

my $exe = 'recon.pl';

my $command = "$exe '$digiRootFile' '$shellFile' '$jobOptionFile' '$reconRootFile' '$meritRootFile'";
print "Running command: [$command]\n";
exit(system($command));
