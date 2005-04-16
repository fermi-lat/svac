#!/usr/local/bin/perl -w

use strict 'vars';
use vars qw{$dbh};
use DBI;
use DBI qw(:sql_types);

sub noRecon {
	print STDERR "Not reconstructing.\n";
	print "0\n";
	exit;
}

sub yesRecon {
	print STDERR "Reconstructing.\n";
	print "1\n";
	exit;
}

print STDERR "Determining reconstructability for run $ARGV[0]\n";


my $offline = `$ENV{'svacPlLib'}/queryElogReportTable.pl $ARGV[0] offline`;
chomp $offline;

my @badOffline = ('norecon', 'nodigi');
my @goodOffline = ('recon');

if (grep(/^$offline$/i, @goodOffline)) {
	print STDERR "Offline tag '$offline' says do it\n";
	yesRecon();
} elsif (grep(/^$offline$/i, @badOffline)) {
	print STDERR "Offline tag '$offline' says don't do it\n";
	noRecon();
} else {
	print STDERR "Offline tag '$offline' has no comment on the matter.\n";
}


my $particleType = `$ENV{'svacPlLib'}/queryElogReportTable.pl $ARGV[0] particleType`;
chomp $particleType;

my @reconPTypes = ('Cosmics', 'Photons', 'Am241');

if (grep(/^$particleType$/i, @reconPTypes)) {
	print STDERR "Particle type '$particleType' OK.\n";
    yesRecon();
}
else {
	print STDERR "Bad Particle type '$particleType'.\n";
    noRecon();
}

