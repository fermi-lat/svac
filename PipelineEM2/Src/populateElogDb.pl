#!/usr/local/bin/perl

use strict;

use lib '/u/gl/dflath/glast/software/DPF/PDB/';
use DPFProc;

#####################################################
##
##  BEGIN:  DON'T TOUCH STUFF BETWEEN THESE COMMENTS
##
#####################################################

my $proc = new DPFProc(@ARGV);
my $inFiles = $proc->{'inFiles'};
my $outFiles = $proc->{'outFiles'};

#####################################################
##
##  END:  DON'T TOUCH STUFF BETWEEN THESE COMMENTS
##
#####################################################

my $shellFile = $outFiles->{'script'}
my $rcReport = $inFiles->{'rcReport'};

# gotta compute this or get it from pieline DB
my $eLogFeederDir = $??;

#change to ftp protocol
my $rootUrl = '/glast.u01/temp/rootData/';

my $pwd = $ENV{PWD};

# check for eLogFeeder dir, quit if it does not exist 
if(! (-d $eLogFeederDir) ) {
   die "Directory $eLogFeederDir does not exist, abort!";
}

my $scriptDir = '/nfs/slac/g/svac/common/builds/eLogFeeder/v1r1';

#create a csh script to run update.py
open(SHELLFILE, ">$shellFile") || die "Can't open $shellFile, abortted!";
print SHELLFILE qq{#!/bin/csh \n \n};
print SHELLFILE qq{unsetenv LD_LIBRARY_PATH \n};
print SHELLFILE qq{cd $eLogFeederDir \n};
print SHELLFILE qq{cp $rcReport . \n};
print SHELLFILE qq{cp $scriptDir/report.xml . \n};
print SHELLFILE qq{source $scriptDir/setup.csh \n};
print SHELLFILE qq{$scriptDir/update.py $rootUrl \n};
print SHELLFILE qq{cd $pwd \n};
close(SHELLFILE);

system("chmod +rwx $shellFile");
system("$shellFile");
