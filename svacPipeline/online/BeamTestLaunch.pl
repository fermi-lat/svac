#!/usr/local/bin/perl -w

# Launch SVAC pipeline.

use strict;

use lib "$ENV{'beamtestPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'beamtestPlRoot'}/setup/svacPlSetup.cshrc");

#environmentalizer::sourceCsh("$ENV{SVAC_PDB_CONFIG}");

my $runName = $ARGV[0];

my $onlineDataDir = "$ENV{'onlineHead'}/$ENV{'onlineSubDir'}/$runName";

my $launcher = "$ENV{'PDB_HOME'}/createRun.pl";

my $status = 0;

my $nextTask = $ENV{'eLogTaskLatte'};

my $baseHead = "${nextTask}_${runName}";
my $rcReportBase = "${baseHead}_rcReport_rcReport.xml";
my $ldfBase = "${baseHead}_ldf_LDF.ldf";
my $snapBase = "${baseHead}_snapshot_text.xml";

my $timestamp;
my $ldfFile;
my $nLdf = 0;
foreach (<$onlineDataDir/*.ldf>) {
	if (/\/([0-9]*)\.ldf$/) {
		$timestamp = $1;
		$ldfFile = $_;
		$nLdf++;
	}
}
if ($nLdf == 0) {
	die "Couldn't find LDF file!";
} elsif ($nLdf > 1) {
	die "Too many LDF files!";
}

my $rcReportIn = $onlineDataDir . '/' . 'rcReport.out';
my $ldfIn = $ldfFile;
my $snapIn = $onlineDataDir . '/' . 'rsb' . $timestamp . '.xml';
my @inFiles = ($rcReportIn, $ldfIn, $snapIn);

my $rcReportOut = $onlineDataDir . '/' . $rcReportBase;
my $ldfOut = $onlineDataDir . '/' . $ldfBase;
my $snapOut = $onlineDataDir . '/' . $snapBase;
my @outFiles = ($rcReportOut, $ldfOut, $snapOut);

for (my $ii=0; $ii<=$#inFiles; $ii++) {
	my $inFile = $inFiles[$ii];
	my $outFile = $outFiles[$ii];
	if (-e $inFile) {
		link($inFile, $outFile);
	} else {
		print "$inFile does not exist, creating empty $outFile.\n";
		system("touch $outFile");
	}
}

# launch eLog task
my $eLogCommand = "$launcher '$nextTask' '$runName'";

my @commands = ('date', $eLogCommand);

my $command;
foreach $command (@commands) {
    print "Running command [$command]\n";
    $status |= system($command);}

if ($status == 0) {
    exit 0;}
else {
    exit 1;}
