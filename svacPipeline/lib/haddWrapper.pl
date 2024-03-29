#!/usr/local/bin/perl -w

# This merges tuples using haddMerge.
#
# It expects a single inFile, containing a list of the chunk files.
# It produces a single outFile, containing the name of the merged file.

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
die "Must have exactly one inFile!" unless scalar(@inFileNames) == 1;
my $inFile = $inFileNames[0];

my @outFileNames = values %$outFiles;
die "Must have exactly one outFile!" unless scalar(@outFileNames) == 1;
my $outFile = $outFileNames[0];

my $exe = $ENV{'haddMerge'};

my $command = "$exe '$inFile' '$outFile' '$runId'";
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
