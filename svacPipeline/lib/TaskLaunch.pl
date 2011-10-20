#!/usr/local/bin/perl -w

use strict;

use File::Basename;

my $oldFile;
my ($oldTask, $newTask, $runName, @files) = @ARGV;

# could also use "ln" or "cp"
my $linker = "ln -s";

my $status = 0;

my $command = "$ENV{'PDB_HOME'}/createRun.pl $newTask $runName";

$status |= system($command);

if ($status == 0) {
    exit 0;}
else {
    exit 1;}

