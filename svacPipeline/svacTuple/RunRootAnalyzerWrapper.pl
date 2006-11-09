#!/usr/local/bin/perl -w

use strict;

use lib $ENV{'PDB_HOME'};
use DPFProc;
use Exec;

#####################################################
##
##  BEGIN:  DON'T TOUCH STUFF BETWEEN THESE COMMENTS
##
#####################################################

my $run_num=shift;
my $task_pk=shift;
my $taskProcess_name=shift;
print "$run_num, $task_pk, $taskProcess_name\n";
my $proc = new DPFProc($run_num, $task_pk, $taskProcess_name);

my $inFiles = $proc->{'inFiles'};
my $outFiles = $proc->{'outFiles'};
my $taskName = $proc->{'task_name'};
#####################################################
##
##  END:  DON'T TOUCH STUFF BETWEEN THESE COMMENTS
##
#####################################################

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

#my $mcRootFile = $inFiles->{'mc'};
my $mcRootFile = 'emptyFile';
system("touch $mcRootFile");

my $digiRootFile = $inFiles->{'digi'};
my $reconRootFile = $inFiles->{'recon'};

my $svacRootFile = $outFiles->{'svac'};
my $histFile = $outFiles->{'histogram'};
my $optionFile = $outFiles->{'jobOptions'};
my $shellFile = $outFiles->{'script'};

my $exe = $ENV{'svacTupleScript'};

my $command = "$exe '$mcRootFile' '$digiRootFile' '$reconRootFile' '$svacRootFile' '$histFile' '$optionFile' '$shellFile' '$taskName'";
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
