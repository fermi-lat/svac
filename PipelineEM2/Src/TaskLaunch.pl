#!/usr/local/bin/perl -w

use strict;

my ($oldTask, $newTask, $runName, @files) = @ARGV;

foreach $oldFile (@files) {
    my $newFile = $oldFile;
    $newFile =~ s/$oldTask/$newTask/;
    link $oldFile $newFile;
}

my $command = "CreateRun.pl $newTask $runName";

my $status = system($command);
if ($status == 0) {
    exit 0;}
else {
    exit 1;}

