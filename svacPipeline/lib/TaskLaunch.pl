#!/usr/local/bin/perl -w

use strict;

my $oldFile;
my ($oldTask, $newTask, $runName, @files) = @ARGV;

# could also use "ln" or "cp"
my $linker = "ln -s";

my $status = 0;

foreach $oldFile (@files) {
    my $newFile = $oldFile;
    $newFile =~ s/$oldTask/$newTask/;
    $status |= system("test -e $newFile || $linker $oldFile $newFile");
}

my $command = "$ENV{'PDB_HOME'}/createRun.pl $newTask $runName";

$status |= system($command);

if ($status == 0) {
    exit 0;}
else {
    exit 1;}

