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

my $proc = new DPFProc(@ARGV);
my $inFiles = $proc->{'inFiles'};
my $outFiles = $proc->{'outFiles'};
my $runName = $proc->{'run_name'};

#####################################################
##
##  END:  DON'T TOUCH STUFF BETWEEN THESE COMMENTS
##
#####################################################

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

my $ldfFile = $inFiles->{'ldf'};
my $shellFile = $outFiles->{'script'};
my $jobOptionFile = $outFiles->{'jobOptions'};
my $digiRootFile = $outFiles->{'digi'};

my $exe = $ENV{'digitizationScript'};
my $command = "$exe '$runName' '$ldfFile' '$shellFile' '$jobOptionFile' '$digiRootFile'";
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