#!/usr/local/bin/perl -w

use strict;

print STDERR "$0: svacPlRoot=[$ENV{'svacPlRoot'}]\n";

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

#doesn't work, as $query fails if asked about an absent field, 
#and offline is often absent
# unless (length($offline)) {
# 	die("Can't get offline tag!\n");
# }

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
unless (length($nEvents)) {
	die("Can't get event count!\n");
}
$nEvents = int($nEvents);
print STDERR "Run $run has $nEvents events.\n";
# LICOS runs will appear to have negative events at this point, try to digitize them all
# LATTE runs appear to have 2 more events (sweep) than they really do (if they have any)
if (0 <= $nEvents && $nEvents <= 2) {
	noDigi();
}

yesDigi();
