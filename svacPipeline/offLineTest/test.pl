#!/usr/local/bin/perl -w

use strict;

use lib $ENV{'PDB_HOME'};
use DPFProc;
use Exec;

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

my $runName = '306000163';
my $digiRootFile = '/nfs/farm/g/glast/u06/chen/temp/em_v3r0404p2/306000163/041008101639_digi.root';
my $splitInfoFile = '/nfs/farm/g/glast/u06/chen/temp/em_v3r0404p2/306000163/digiReport/tkrSplit.dat';
my $optionFile = '/nfs/farm/g/glast/u06/chen/temp/em_v3r0404p2/306000163/digiReport/'.$runName.'_option.dat';
my $shellFile = '/nfs/farm/g/glast/u06/chen/temp/em_v3r0404p2/306000163/digiReport/'.$runName.'_report.scr';
my $tarBall = '/nfs/farm/g/glast/u06/chen/temp/em_v3r0404p2/306000163/digiReport/'.$runName.'_report.tar';

my $exe = $ENV{'digiReportScript'};

my $command = "$exe '$runName' '$digiRootFile' '$splitInfoFile' '$optionFile' '$shellFile' '$tarBall'";
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
