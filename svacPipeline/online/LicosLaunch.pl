#!/usr/local/bin/perl -w

# Launch SVAC pipeline.

use strict;

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

#environmentalizer::sourceCsh("$ENV{SVAC_PDB_CONFIG}");

my $runName = $ARGV[0];

my $onlineDataDir = "$ENV{'onlineHead'}/$ENV{'onlineSubDir'}/$runName";
my $licosDir = $onlineDataDir . '/LICOS';

my $launcher = "$ENV{'PDB_HOME'}/createRun.pl";

my $status = 0;

# launch eLog task
my $nextTask = $ENV{'eLogTaskLicos'};
my $eLogCommand = "$launcher '$nextTask' '$runName'";

my $rcReportBase = "${nextTask}_${runName}_rcReport_rcReport.xml";
my $RetDefBase = "${nextTask}_${runName}_RetDef_RetDef.evt";
# my $algBase = "${nextTask}_${runName}_snapshot_text.xml";

# my $algPat = $licosDir . '/' . 'e2e*.xml';
# my @algFiles = glob($algPat);
# my $algFileIn = $algFiles[0]; 

my $rcReportIn = $licosDir . '/' . 'rcReport.out';
my $RetDefIn = $onlineDataDir . '/' . $runName . '.evt';
# my @inFiles = ($rcReportIn, $rcReportIn, $RetDefIn, $algFileIn);
my @inFiles = ($rcReportIn, $rcReportIn, $RetDefIn);

my $rcReportOut = $licosDir . '/' . $rcReportBase;
my $rcReportXml = $licosDir . '/' . $runName . '_rcReport.xml';
my $RetDefOut = $onlineDataDir . '/' . $RetDefBase;
# my $algFileOut = $onlineDataDir . '/' . $algBase;
# my @outFiles = ($rcReportOut, $rcReportXml, $RetDefOut, $algFileOut);
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

my @commands = ('date', $eLogCommand);

my $command;
foreach $command (@commands) {
    print "Running command [$command]\n";
    $status |= system($command);}

if ($status == 0) {
    exit 0;}
else {
    exit 1;}
