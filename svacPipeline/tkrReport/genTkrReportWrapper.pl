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

my $histoFile = $inFiles->{'histogram'};

my $tarBall = $outFiles->{'tarBall'};
my $tarBase = `basename $tarBall`;
chomp $tarBase;
my $workDir = `dirname $tarBall`;
chomp $workDir;

my $exe = $ENV{'tkrReportApp'};

my $command = "$exe '$histoFile' '$workDir' '$runName'";
print "Running command: [$command]\n";

my $ex = new Exec("$command");
my $rc = $ex->execute();

my $reportFileIn = "${workDir}/${runName}_report.html";
my $reportFileOut = "${workDir}/$ENV{'tkrReportUrl'}";
symlink($reportFileIn, $reportFileOut);

my $cmd;
my $keepers = "keepers.txt";
$cmd = "cd $workDir ; ls | egrep -v '^(tkrReport|core)' > $keepers";
print "$cmd\n";
system($cmd);
$cmd = "cd $workDir ; tar -c -z -f $tarBase -T $keepers";
print "$cmd\n";
system($cmd);

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
