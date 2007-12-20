#!/usr/local/bin/perl -w

# Launch SVAC pipeline.

use strict;

print STDERR "$0: svacPlRoot=[$ENV{'svacPlRoot'}]\n";

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

print STDERR "$0: svacPlRoot=[$ENV{'svacPlRoot'}]\n";

#environmentalizer::sourceCsh("$ENV{SVAC_PDB_CONFIG}");

my $runName = $ARGV[0];

die "You must suppy a runId!" if not $runName;

my $onlineDataDir = "$ENV{'onlineHead'}/$ENV{'onlineSubDir'}/$runName";
my $licosDir = $onlineDataDir . '/LICOS';

die "Directory $licosDir does not exist.\n" unless -d $licosDir;

my $launcher = "$ENV{'PDB_HOME'}/createRun.pl";

my $status = 0;

my $nextTask = $ENV{'eLogTask'};

my $rcReportBase = "${nextTask}_${runName}_rcReport_rcReport.xml";
my $RetDefBase = "${nextTask}_${runName}_RetDef_RetDef.evt";

my $rcReportIn = $licosDir . '/' . 'rcReport.out';
my $RetDefIn = $onlineDataDir . '/' . $runName . '.evt';

my @inFiles = ($rcReportIn, $rcReportIn, $RetDefIn);

my $rcReportOut = $licosDir . '/' . $rcReportBase;
my $rcReportXml = $licosDir . '/' . $runName . '_rcReport.xml';
my $RetDefOut = $onlineDataDir . '/' . $RetDefBase;
my @outFiles = ($rcReportOut, $rcReportXml, $RetDefOut);

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
