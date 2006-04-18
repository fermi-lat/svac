#!/usr/local/bin/perl -w

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
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

my $urlKey = $taskProcessName;
my @inFileNames = values %$inFiles;

my $scriptDir = $ENV{'eLogDir'};
environmentalizer::sourceCsh("$scriptDir/setup.csh");

my $exe = $ENV{'urlUpdateScript'};

foreach (@inFileNames) {
# construct a command, print it to the log file, and run it:
    my $inFile = $_;

    if (! -e $_) {
        print "File [$_] does not exist, not updating its URL\n";
        exit(1);
    }

    my $cmd = "$exe $runName $urlKey $inFile";
    print "cmd is [$cmd]\n";

    my $ex = new Exec("$cmd");
    
    my $rc = $ex->execute();

	if ( defined($rc) ) {
		if ( $rc == 0 ) {
			#terminated successfully
			exit(0);
		} else {
			#your app failed, interpret return code
			#and then exit non-zero
			
			#(do some stuff here if you want)
			exit($rc);         
		}
    } else {
        if (( !$ex->{'success'} ) && ( !defined($ex->{'signal_number'}) )) {
	  # Your app is not present!!!
	  # ie, system can't find your app or script
	  print "\n\n***** APPLICATION NOT FOUND *******\n\n";
        } else {
	  if ($ex->{'core_dump'}) {
	      #your app core dumped
	  }
	  if (defined($ex->{'signal_number'})) {
	      #your app terminated with a signal
	      my $signal_number = $ex->{'signal_number'};
	  }
        }

        #exit non-zero:
        exit(255);
    }
}
