#!/usr/local/bin/perl -w

use strict;

my $newTask = 'SVACTuple';

my ($oldTask, $runName, $mcFile, $digiFile, $reconFile) = @ARGV;

foreach $oldFile ($mcFile, $digiFile, $reconFile) {
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

