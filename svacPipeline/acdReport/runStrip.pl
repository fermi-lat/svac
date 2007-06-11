#!/usr/local/bin/perl -w

use strict;

if ($#ARGV != 1) {
    die "Usage: $0 digiRootFile acdTimeFile";
}

print STDERR "$0: svacPlRoot=[$ENV{'svacPlRoot'}]\n";

my ($digiRootFile, $acdTimeFile) = @ARGV;

print <<EOT;
$0 running with:
  digiRootFile: [$digiRootFile]
  acdTimeFile:   [$acdTimeFile]
EOT
	
my $setup = "$ENV{'monitorCmt'}/setup.sh";
my $exe = $ENV{'monitorApp'};
my $timeFile = "acd_time.root";
my $joFile = $ENV{'acdMonitorJo'};

my $cmd = "source $setup
$exe -j '$joFile' -d '$digiRootFile' || exit 1
mv '$timeFile' '$acdTimeFile'";

print STDERR "About to run [$cmd]\n.";

my $status = system($cmd);

if ($status == 0) {
    exit 0;}
else {
    exit 1;}
