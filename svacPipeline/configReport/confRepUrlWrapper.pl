#!/usr/local/bin/perl

# Demonstration script.
# Submitted to batch by pipeline scheduler.
# You need only modify the last section...

#use lib '/u/gl/dflath/glast/software/DPF/PDB/';
use lib $ENV{'PDB_HOME'};
use Exec;
use DPFProc;
use strict;

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

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

# construct a command, print it to the log file, and run it:
my $cmd = "";
print "cmd is [$cmd]\n";

my $ex = new Exec("$cmd");

my $rc = $ex->execute();

if ($rc == 0) {
    #terminated successfully:
    exit(0);
} elsif ( defined($rc) ) {
    #your app failed, interpret return code
    #and then exit non-zero
    
    #(do some stuff here if you want)
    exit($rc);
} else {
    if (( !$ex->{'success'} ) && ( !defined($ex->{'signal_number'}) )) {
	# Your app is not present!!!
	# ie, system can't find your app or script
	print "\n\n***** APPLICATION NOT FOUND *******\n\n";
    } else {
	if ($ex->{'core_dump'}) {
	    #your app core dumped
	}
	if ($ex->{'signal_number'} != undef) {
	    #your app terminated with a signal
	    my $signal_number = $ex->{'signal_number'};
	}
    }

    #exit non-zero:
    exit(255);
}
