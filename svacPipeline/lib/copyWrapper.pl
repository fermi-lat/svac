#!/usr/local/bin/perl -w

# This copies files.
#
# It should have one inFile, which should contain the name of a single file.
# It should have one outFile.
# The file named in the inFile will be copied to the outFile.

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

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

my @inFileNames = values %$inFiles;
die "Must have exactly one inFile!" unless scalar(@inFileNames) == 1;
my @inFile = inFileNames[0];

my @outFileNames = values %$outFiles;
die "Must have exactly one outFile!" unless scalar(@outFileNames) == 1;
my $outFile = $outFileNames[0];

open(INFILE, $inFile) or die "Can't open $inFile for input!";
my $sourceFile = <INFILE>;
chomp $sourceFile;

my $exe = "$ENV{'tryAFewTimes'} cp";

my $command = "$exe $sourceFile $outFile";
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
