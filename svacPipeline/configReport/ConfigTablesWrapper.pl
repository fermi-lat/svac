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

my $snapshot = $inFiles->{'snapshot'};
my $split = $inFiles->{'splits'};
my $tarBall = $outFiles->{'tarBall'};

my $exe = $ENV{'configTablesScript'};

my $command = "$exe '$runName' '$snapshot' '$split' '$tarBall'";
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
