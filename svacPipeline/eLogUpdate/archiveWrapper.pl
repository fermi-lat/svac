#!/usr/local/bin/perl -w

# This is not actually used in the current pipeline

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

use lib "$ENV{'beamtestPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'beamtestPlRoot'}/setup/svacPlSetup.cshrc");

my $tarBall = $outFiles->{'tarBall'};
my $command = "tar czf $tarBall LICOS";

my $tbList = `ls *tarball*RAW.tgz`;
if (length($tbList)) {
	die("tarball already exists.");
}

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

#        <executable name=\"Archive\" version=\"$ENV{'eLogTaskVersion'}\">
#            $ENV{'eLogTaskDir'}/archiveWrapper.pl
#        </executable>
#        <batch-job-configuration name=\"short-job\" queue=\"short\" group=\"$batchgroup\">
#            <working-directory>$ENV{'onlineDataDirFull'}</working-directory>
#            <log-file-path>$ENV{'onlineDataDirFull'}</log-file-path>
#        </batch-job-configuration>
#        <file file-type=\"tgz\"  name=\"tarball\"   type=\"RAW\"  >
#            <path>$ENV{'eLogDataDirFull'}</path>
#        </file>
#        <processing-step name=\"archive\" executable=\"Archive\" batch-job-configuration=\"short-job\">
#                        <output-file name=\"tarBall\"/>
#        </processing-step>
