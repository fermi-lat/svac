#!/usr/local/bin/perl -w

use strict;

print STDERR "$0: svacPlRoot=[$ENV{'svacPlRoot'}]\n";

my ($cmd, $marker, $task);

my ($taskName, $runName, $reconRootFile) = @ARGV;

my $reconDir = `dirname $reconRootFile`;
chomp $reconDir;

# make a marker file saying we are done
$marker = "$reconDir/$ENV{'doneUsingRecon'}.$taskName";
$cmd = "touch $marker";
print STDERR "Running command [$cmd]\n";
system($cmd);

# check if this run was taken with one of the scripts that
# we don't want to save recon for
my @junkScripts = (
				   'intSeApp_e2e_LAT-22x',
				   'intSeApp_e2e_LAT-22x_0.50hr',
				   'intSeApp_e2e_LAT-71x_0.50hr',
				   'intSeApp_e2e_LAT-20xMIPThruNoPer_0.50hr', 
				   'intSeApp_e2e_LAT-22xGammaThruNoPer_0.50hr', 
				   'intSeAppLrs_e2e_Other-LightTight2_0.01hr',
				   );
my $testScript = `$ENV{'eLogQuery'} $runName testname`;
chomp $testScript;
if (grep(/^$testScript$/, @junkScripts)) {
	print STDERR "Script [$testScript] is not a keeper, deleting recon file.\n";
} else {
	print STDERR "Script [$testScript] is a keeper, not deleting recon file.\n";
	exit 0;
}

# check if everyone has made their marker file
my @tasksUsingRecon = ($ENV{'reconReportTask'}, $ENV{'svacTupleTask'});
foreach $task (@tasksUsingRecon) {
	$marker = "$reconDir/$ENV{'doneUsingRecon'}.$task";
	if (not stat($marker)) {
		print STDERR "Task [$task] is not done, not deleting recon file.\n";
		exit 0;
	}
}

# do the cleanup
# recon file is really a symlink
my $realReconFile = $reconDir . '/' . readlink($reconRootFile);
print STDERR "Deleting file [$realReconFile], which is linked from [$reconRootFile]\n";
if ($ENV{'svacTestMode'}) {
	print STDERR "Running in test mode, not deleting file.\n";
} else {
	# delete recon file
	unlink($realReconFile);
}
# clear link in eLog
system("$ENV{'eLogUpdate'} $runName reconrootfile ''");

