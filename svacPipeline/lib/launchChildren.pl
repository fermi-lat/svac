#!/usr/local/bin/perl -w

# Demonstration script.
# Submitted to batch by pipeline scheduler.
# You need only modify the last section...

use strict;

my ($oldTask, $runName, $ldfFile) = @ARGV;

my ($newTask, $command);
my $status = 0;

my $linker = $ENV{'taskLinker'};
my $launcher = 'createRun.pl'

# launch digitization
$newTask = $ENV{'digitizationTask'};
if ((! -e $ldfFile) || (-z $ldfFile)) {
    print "LDF file [$ldfFile] does not exist or has zero size, not launching digitization task.\n";
} else {
    $command = "$linker '$taskName' '$newTask' '$ldfFile'";
    print "Running command: [$command]\n";
    $status |= system($command);
    $command = "$launcher '$taskName' '$runName'";
    print "Running command: [$command]\n";
    $status |= system($command);
}

# launch configReport
$newTask = $ENV{'configReportTask'};
$command = "$launcher '$newTask' '$runName'";
print "Running command: [$command]\n";
$status |= system($command);

if ($status) { # failure
    exit 1;
} else {       # success
    exit 0;
}

