#!/usr/local/bin/perl -w

# This launches Tasks, only if the run is reconstructable.
#
# The name of the TP that uses this must  be the same as the name of 
# the Task that it launches.

use strict;

use lib $ENV{'PDB_HOME'};
use DPFProc;
use Exec;

#####################################################
##
##  BEGIN:  DON'T TOUCH STUFF BETWEEN THESE COMMENTS
##
#####################################################

my $proc = new DPFProc(@ARGV);
my $inFiles = $proc->{'inFiles'};
my $runId = $proc->{'run_name'};
my $taskName = $proc->{'task_name'};
my $procName = $proc->{'taskProcess_name'};

#####################################################
##
##  END:  DON'T TOUCH STUFF BETWEEN THESE COMMENTS
##
#####################################################

print STDERR "$0: svacPlRoot=[$ENV{'svacPlRoot'}]\n";

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

print STDERR "$0: svacPlRoot=[$ENV{'svacPlRoot'}]\n";

my $exe = $ENV{'taskLauncher'};

my $oldTask = $taskName;
my $newTask = $procName;

my @inFileNames = values %$inFiles;

my $command = "$exe '$oldTask' '$newTask' '$runId'";
my $inFile;
foreach $inFile (@inFileNames) {
	$command .= " '$inFile'";
}

my $doRecon = `$ENV{'decideReconScript'} $runId`;
chomp $doRecon;
if ($doRecon eq '1') {
    print "Reconstructable run, status: $doRecon\n";
} elsif ($doRecon eq '0') {
    print "This is not a reconstructable run, status: $doRecon\n";
    exit(0);
} else {
	print "Bad result from decideRecon.\n";
	exit(1);
}

print "Running command: [$command]\n";

my $ex = new Exec("$command");

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
