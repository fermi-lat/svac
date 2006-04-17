#!/usr/local/bin/perl -w

# Launch SVAC pipeline.

use strict;

my ($oldTask, $runName, $rcReport, $snapshot, $ldfFile) = @ARGV;

my $launcher = $ENV{'taskLauncher'};

my $status = 0;

# launch eLog task
my $nextTask = $ENV{'eLogTask'};
my $eLogCommand = "$launcher '$oldTask' '$nextTask' '$runName' '$rcReport' '$snapshot' '$ldfFile'";

my @commands = ($eLogCommand);

my $command;
foreach $command (@commands) {
    print "Running command [$command]\n";
    $status |= system($command);}

if ($status == 0) {
    exit 0;}
else {
    exit 1;}