#!/usr/local/bin/perl -w

use strict;

if ($#ARGV != 2) {
    die "Usage: $0 acdTimeFile acdAlarmFile acdLogFile";
}

print STDERR "$0: svacPlRoot=[$ENV{'svacPlRoot'}]\n";

my ($acdTimeFile, $acdAlarmFile, $acdLogFile) = @ARGV;

print <<EOT;
$0 running with:
  acdTimeFile:   [$acdTimeFile]
  acdAlarmFile:   [$acdAlarmFile]
  acdLogFile:   [$acdLogFile]
EOT
   
my $exe = $ENV{'dataMonitoringApp'};
my $joFile = $ENV{'acdAlarmJo'};

my $dest = $ENV{'acdReportDestination'};

my $cmd = "
python $exe -c '$joFile' -o '$acdAlarmFile' -l 1 '$acdTimeFile' > $acdLogFile || exit 1
cp '$acdTimeFile' '$dest'
cp '$acdLogFile' '$dest'
";

print STDERR "About to run [$cmd]\n.";

my $status = system($cmd);

if ($status == 0) {
    exit 0;}
else {
    exit 1;}
