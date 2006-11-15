#!/usr/local/bin/perl -w

use strict;

use File::Basename;

print STDERR "$0: svacPlRoot=[$ENV{'svacPlRoot'}]\n";

my $oldFile;
my ($oldTask, $newTask, $runName, @files) = @ARGV;

# could also use "ln" or "cp"
my $linker = "ln -s";

my $status = 0;

foreach $oldFile (@files) {
    my $newFile = $oldFile;
    $newFile =~ s/$oldTask/$newTask/;
    # make a relative symlink, not absolute
    my ($target, $path) = fileparse($oldFile);
    #
    $status |= system("test -e $newFile || $linker $target $newFile");
}

my $command = "$ENV{'PDB_HOME'}/createRun.pl $newTask $runName";

$status |= system($command);

if ($status == 0) {
    exit 0;}
else {
    exit 1;}

