#!/usr/local/bin/perl -w

use strict;

my $run = shift;
my $ldfFile = shift;

if ((! -e $ldfFile) || (-z $ldfFile)) {
	print STDERR "File $ldfFile is nonexistent or empty, not digitizing.\n";
	print "0\n";
	exit;
}

my $command = "queryElogReportTable.pl $run EventCount";
my $nEvents = `$command`;
chomp $nEvents;
if (!$nEvents) {
	print STDERR "Run $run has no events, not digitizing.\n";
	print "0\n";
	exit;
}

print STDERR "Run $run looks OK to digitize.\n";
print "1\n";
