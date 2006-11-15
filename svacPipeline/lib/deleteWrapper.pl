#!/usr/local/bin/perl -w

# This deletes files.
#
# It is assumed that all infiles contain lists of files to delete, one per line.

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
my $outFiles = $proc->{'outFiles'};
my $runId = $proc->{'run_name'};
my $taskName = $proc->{'task_name'};

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

my @inFileNames = values %$inFiles;

my $exe = 'rm -f';

my $ex;
my $rc = 0;
my $status = 0;
foreach (@inFileNames) {
	print STDERR "Reading files to delete from $_\n";
	open(INFILE, $_) or die "Couldn't open $_ for input!\n";
	
	while (<INFILE>) {
		chomp;
		
		my $command = "$exe '$_'";
		print STDERR "Running command: [$command]\n";
		
		$ex = new Exec("$command");
		
		if ($ENV{'svacTestMode'}) {
			print STDERR "Running in test mode, not deleting file.\n";
		} else {
			$status = $ex->execute();
			$rc |= $status;
		}
	}
}

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
