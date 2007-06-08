#!/usr/local/bin/perl -w

use strict;

if ($#ARGV != 1) {
    die "Usage: $0 acdTimeFile acdAlarmFile";
}

print STDERR "$0: svacPlRoot=[$ENV{'svacPlRoot'}]\n";

my ($acdTimeFile, $acdAlarmFile) = @ARGV;

print <<EOT;
$0 running with:
  acdTimeFile:   [$acdTimeFile]
  acdAlarmFile:   [$acdAlarmFile]
EOT
   
my $exe = $ENV{'dataMonitoringApp'};
my $joFile = $ENV{'acdAlarmJo'};

my $dest = $ENV{'acdReportDestination'};

my $cmd = "python $exe -c '$joFile' -o '$acdAlarmFile' -l 1 '$acdTimeFile' || exit 1
cp '$acdTimeFile' '$dest'
cp '$acdAlarmFile' '$dest'";

print STDERR "About to run [$cmd]\n.";

my $status = system($cmd);

if ($status == 0) {
    exit 0;}
else {
    exit 1;}
