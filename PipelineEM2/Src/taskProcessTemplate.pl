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


#  Ok, this is your area to play, do as you wish from here on in:
#  Make sure you return the result of your processing in place of this perl
#  script's return code so that LSF records the correct ret code.
#  NOTE: This is done for you if you use the 'system' command as below.

# $inFiles{'DS_NAME'} is the filename of the instance of dataset 'DS_NAME'
# $outFiles{'DS_NAME'} is the filename of the instance of dataset 'DS_NAME'

# Configure your environment and run your processing, application, or script.
# Perl exposes the system environment thru the hash: 'ENV'


# ==============
#  For example:
# ==============

# add current working directory to system path, just for fun:
$ENV->{'PATH'} = `pwd` . ":" . $ENV->{'PATH'};

# construct a command, print it to the log file, and run it:
my $cmd = "cp $inFiles->{'CopyIn'} $outFiles->{'CopyOut'}";
print "cmd is [$cmd]\n";

exit(system("$cmd"));

