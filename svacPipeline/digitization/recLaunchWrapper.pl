#!/usr/local/bin/perl -w

# Demonstration script.
# Submitted to batch by pipeline scheduler.
# You need only modify the last section...

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
my $taskName = $proc->{'task_name'};
my $runName = $proc->{'run_name'};

#####################################################
##
##  END:  DON'T TOUCH STUFF BETWEEN THESE COMMENTS
##
#####################################################

use lib "$ENV{'svacPlRoot'}/lib-current";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup-current/svacPlSetup.cshrc");

my $exe = $ENV{'taskLauncher'};

my $newTask = $ENV{'reconTask'};
my $digiRootFile = $inFiles->{'digi'};
my $command = "$exe '$taskName' '$newTask' '$runName' '$digiRootFile'";

if (! -e $digiRootFile) {
    print "Digi file [$digiRootFile] does not exist, not launching recon task.\n";
    exit(0);
}

my $doRecon = `$ENV{'decideReconScript'} $runName`;
chomp $doRecon;
if ($doRecon == 1) {
    print "Reconstructable run, status: $doRecon\n";
} else {
    print "This is not a reconstructable run, status: $doRecon\n";
    exit(0)
}

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
