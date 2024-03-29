#!/usr/local/bin/perl

use strict;

if ($#ARGV != 1) {
    die "Usage: $0 shellFile rcReport";
}

my ($shellFile, $rcReport) = @ARGV;

print <<EOT;
$0 running with:
  shellFile: [$shellFile]
  rcReport:  [$rcReport]
EOT

my $eLogFeederDir = `dirname $shellFile`;
chomp $eLogFeederDir;

#change to ftp protocol
my $rootUrl = $ENV{'rootUrl'};

# check for eLogFeeder dir, quit if it does not exist 
if(! (-d $eLogFeederDir) ) {
   die "Directory $eLogFeederDir does not exist, abort!";
}

my $scriptDir = $ENV{'eLogDir'};

#create a csh script to run update.py
open(SHELLFILE, ">$shellFile") || die "Can't open $shellFile, abortted!";
print SHELLFILE qq{#!/bin/csh \n \n};
print SHELLFILE qq{unsetenv LD_LIBRARY_PATH \n};
print SHELLFILE qq{pushd $eLogFeederDir \n};
print SHELLFILE qq{source $scriptDir/setup.csh \n};
print SHELLFILE qq{$scriptDir/update.py $rcReport $rootUrl \n};
close(SHELLFILE);

system("chmod +rwx $shellFile");

my $status = system("$shellFile");

if ($status == 0) {
    exit 0;}
else {
    exit 1;}
