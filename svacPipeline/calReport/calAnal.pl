#!/usr/local/bin/perl -w

use strict;

use File::Basename;

if ($#ARGV != 2) {
    die "Usage: $0 runId calHistFile calReportFile";
}

print STDERR "$0: svacPlRoot=[$ENV{'svacPlRoot'}]\n";

my ($runId, $calHistFile, $calReportFile) = @ARGV;

print <<EOT;
$0 running with:
  runId:         [$runId]
  calHistFile:   [$calHistFile]
  calReportFile: [$calReportFile]
EOT
   
my $setup = "$ENV{'calReportCmt'}/setup.sh";
my $exe = $ENV{'calAnalApp'};
my $binWidth = $ENV{'calReportBinWidth'};
my $version = $ENV{'calReportTaskVersion'};

my ($calHistFileRelative, $junk) = fileparse($calHistFile);

# This is hardcoded into the app :-(
my $histFile = 'muonPeds.digitization-licos-' . $ENV{'calReportTaskVersion'} . '_' . $runId . '_digi_DIGI.root';
# So is this.
my $reportFile = 'EMI_report_' . $runId . '.ps';

my $dest = $ENV{'calReportDesination'};

my $cmd = "
source $setup
ln -s $calHistFileRelative $histFile
$exe '$runId' '$binWidth' '$version' || exit 1
cp '$reportFile' '$dest'
mv '$reportFile' '$calReportFile'
";

print STDERR "About to run [$cmd]\n.";

my $status = system($cmd);

if ($status == 0) {
    exit 0;}
else {
    exit 1;}
