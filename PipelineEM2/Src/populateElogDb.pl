#!/usr/local/bin/perl

use strict;

if ($#ARGV != 1) {
    die "Usage: $0 shellFile rcReport";
}

my ($shellFile, $rcReport) = @ARGV;

print <<EOT;
$0 running with:
  shellFile: $shellFile
  rcReport:  $rcReport
EOT

my $eLogFeederDir = `dirname $shellFile`;
chomp $eLogFeederDir;

#change to ftp protocol
my $rootUrl = '/glast.u01/temp/rootData/';

my $pwd = $ENV{PWD};

# check for eLogFeeder dir, quit if it does not exist 
if(! (-d $eLogFeederDir) ) {
   die "Directory $eLogFeederDir does not exist, abort!";
}

#my $scriptDir = '/nfs/slac/g/svac/common/builds/eLogFeeder/v1r1';
my $scriptDir = '/nfs/slac/g/svac/focke/test/eLogFeeder/v1r1';

#create a csh script to run update.py
open(SHELLFILE, ">$shellFile") || die "Can't open $shellFile, abortted!";
print SHELLFILE qq{#!/bin/csh \n \n};
print SHELLFILE qq{unsetenv LD_LIBRARY_PATH \n};
print SHELLFILE qq{cd $eLogFeederDir \n};
print SHELLFILE qq{source $scriptDir/setup.csh \n};
print SHELLFILE qq{$scriptDir/update.py $rcReport $rootUrl \n};
print SHELLFILE qq{cd $pwd \n};
close(SHELLFILE);

system("chmod +rwx $shellFile");

my $status = system("$shellFile");

if ($status == 0) {
    exit 0;}
else {
    exit 1;}
