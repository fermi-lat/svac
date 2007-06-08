#!/usr/local/bin/perl -w

use strict;

use File::Basename;

if ($#ARGV != 2) {
    die "Usage: $0 runId digiRootFile calHistFile";
}

print STDERR "$0: svacPlRoot=[$ENV{'svacPlRoot'}]\n";

my ($runId, $digiRootFile, $calHistFile) = @ARGV;

print <<EOT;
$0 running with:
  runId:        [$runId]
  digiRootFile: [$digiRootFile]
  calHistFile:  [$calHistFile]
EOT
	
my $setup = "$ENV{'calReportCmt'}/setup.sh";
my $exe = $ENV{'calPedApp'};
my $joFile = $ENV{'calPedConfig'};
my $binWidth = $ENV{'calReportBinWidth'};
my $nBins = $ENV{'calReportNBins'};

my ($base, $path) = fileparse($digiRootFile);
# This is hardcoded into the app :-(
my $histFile = 'muonPeds.' . $base;

my $cmd = "
source $setup
$exe '$joFile' '$digiRootFile' '$binWidth' '$nBins' || exit 1
mv '$histFile' '$calHistFile'
";

print STDERR "About to run [$cmd]\n.";

my $status = system($cmd);

if ($status == 0) {
    exit 0;}
else {
    exit 1;}
