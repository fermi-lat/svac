#!/usr/local/bin/perl -w

use strict;
use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/dbSetup.cshrc");

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
my $rawUrl = $ENV{'rawUrl'};

# check for eLogFeeder dir, quit if it does not exist 
if(! (-d $eLogFeederDir) ) {
   die "Directory $eLogFeederDir does not exist, abort!";
}

my $scriptDir = $ENV{'eLogDir'};

#create a csh script to run update.py
open(SHELLFILE, ">$shellFile") || die "Can't open $shellFile, abortted!";
print SHELLFILE <<EOF;
#!/bin/csh 
unsetenv LD_LIBRARY_PATH 
pushd $eLogFeederDir
source /usr/local/bin/coraenvp
setenv TWO_TASK $ENV{'TWO_TASK'}
setenv ORACLE_HOME $ENV{'ORACLE_HOME'}
setenv LD_LIBRARY_PATH .:$ENV{'ORACLE_LD_PATH'}
$scriptDir/update.py $rcReport $rootUrl $rawUrl 
EOF
close(SHELLFILE);

system("chmod +rwx $shellFile");

my $status = system("$shellFile");

if ($status == 0) {
    exit 0;}
else {
    exit 1;}
