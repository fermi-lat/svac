#!/usr/local/bin/perl

use strict;

my $numArgs = $#ARGV + 1;

if($numArgs == 0) {
    die "Missing run id as input argument";
}

my $runId = $ARGV[0];

my $rawDataDir = '/nfs/farm/g/glast/u01/temp/rawData/';
my $rootDataDir = '/nfs/farm/g/glast/u01/temp/rootData/';

#change to ftp protocol
my $rootUrl = '/glast.u01/temp/rootData/';

my $pwd = $ENV{PWD};

# create run dir under rootDataDir if it does not exist 
my $runRootDir = $rootDataDir.$runId;
if(! (-d $runRootDir) ) {
    mkdir($runRootDir) || die "can not make dir $runRootDir, abort!";
}
my $runRawDir = $rawDataDir.$runId;

# create eLogFeeder dir under runRootDir if it does not exist 
my $eLogFeederDir = $runRootDir.'/eLogFeeder';
if(! (-d $eLogFeederDir) ) {
    mkdir($eLogFeederDir) || die "can not make dir $eLogFeederDir, abort!";
}

my $scriptDir = '/nfs/slac/g/svac/common/builds/eLogFeeder/v1r1';

#create a csh script to run update.py
my $shellFile = $eLogFeederDir.'/updateElog.scr';
open(SHELLFILE, ">$shellFile") || die "Can't open $shellFile, abortted!";
print SHELLFILE qq{#!/bin/csh \n \n};
print SHELLFILE qq{unsetenv LD_LIBRARY_PATH \n};
print SHELLFILE qq{cd $eLogFeederDir \n};
print SHELLFILE qq{cp $runRawDir/rcReport.out . \n};
print SHELLFILE qq{cp $scriptDir/report.xml . \n};
print SHELLFILE qq{source $scriptDir/setup.csh \n};
print SHELLFILE qq{$scriptDir/update.py $rootUrl \n};
print SHELLFILE qq{cd $pwd \n};
close(SHELLFILE);

system("chmod +rwx $shellFile");
system("$shellFile");
