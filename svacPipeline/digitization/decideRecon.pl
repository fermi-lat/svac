#!/usr/local/bin/perl -w

use strict 'vars';
use vars qw{$dbh};
use DBI;
use DBI qw(:sql_types);

my $run = shift;

my $query = $ENV{'eLogQuery'};

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

print STDERR "Determining reconstructability for run $run:\n";


my $offline = `$query $run offline`;
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


my $particleType = `$query $run particleType`;
chomp $particleType;

my @reconPTypes = ('Cosmics', 'Photons', 'Am241');

if (grep(/^$particleType$/i, @reconPTypes)) {
	print STDERR "Particle type '$particleType' OK.\n";
}
else {
	print STDERR "Bad Particle type '$particleType'.\n";
    noRecon();
}


my @serials = (`$query $run CAL_SER_NO`, `$query $run TKR_SER_NO`);
if (grep(/mini|em/i, @serials)) {
	print STDERR "Weird old hardware, not reconstructing.\n";
	noRecon();
}

yesRecon();
