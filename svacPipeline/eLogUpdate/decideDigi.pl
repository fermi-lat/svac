#!/usr/local/bin/perl -w

use strict;

my $run = shift;
my $ldfFile = shift;

my $query = $ENV{'eLogQuery'};

sub noDigi {
	print STDERR "Not digitizing.\n";
	print "0\n";
	exit;
}

sub yesDigi {
	print STDERR "Digitizing.\n";
	print "1\n";
	exit;
}

print STDERR "Determining digitizability for run $run:\n";


my @badOffline = ('nodigi');

my $offline = `$query $run offline`;
chomp $offline;

if (grep(/^$offline$/i, @badOffline)) {
	print STDERR "Offline tag '$offline' says don't do it.\n";
	noDigi();
}

if ((! -e $ldfFile) || (-z $ldfFile)) {
	print STDERR "File $ldfFile is nonexistent or empty.\n";
	noDigi();
}

my $command = "$query $run EventCount";
my $nEvents = `$command`;
chomp $nEvents;
$nEvents = int($nEvents);
print STDERR "Run $run has $nEvents events.\n";
if ($nEvents <= 2) {
	noDigi();
}

yesDigi();
