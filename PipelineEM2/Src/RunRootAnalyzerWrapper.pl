#!/usr/local/bin/perl

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
#####################################################
##
##  END:  DON'T TOUCH STUFF BETWEEN THESE COMMENTS
##
#####################################################

#my $mcRootFile = $inFiles->{'mc'};
my $mcRootFile = 'emptyFile';
system("touch $mcRootFile");

my $digiRootFile = $inFiles->{'digi'};
my $reconRootFile = $inFiles->{'recon'};

my $svacRootFile = $outFiles->{'svac'};
my $histFile = $outFiles->{'histogram'};
my $optionFile = $outFiles->{'jobOptions'};
my $shellFile = $outFiles->{'script'};

my $exe = './RunRootAnalyzer.pl';

my $command = "source setup.sh ; $exe '$mcRootFile' '$digiRootFile' '$reconRootFile' '$svacRootFile' '$histFile' '$optionFile' '$shellFile'";
print "Running command: [$command]\n";


my $ex = new Exec("$command");

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
