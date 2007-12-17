#!/usr/local/bin/perl -w

use strict 'vars';
use vars qw{$dbh};
use DBI;
use DBI qw(:sql_types);

print STDERR "$0: svacPlRoot=[$ENV{'svacPlRoot'}]\n";

if ($#ARGV != 1) {
	die "Usage: $0 runId tkrHistFile";
}
my ($run, $tkrHistFile) = @ARGV;

my $query = $ENV{'eLogQuery'};

sub noCopy {
	print STDERR "Not Copying.\n";
	exit;
}

sub yesCopy {
	print STDERR "Copying.\n";
	my $dest = $ENV{'tkrHistDir'};
	system("ln -s $tkrHistFile $dest");
	exit;
}

print STDERR "Determining copyability for run $run:\n";

my $particleType = `$query $run particleType`;
chomp $particleType;

my @noCopyPTypes = ('Charge Injection');

if (grep(/^$particleType$/i, @noCopyPTypes)) {
	print STDERR "Bad Particle type '$particleType'.\n";
    noCopy();
}
else {
	print STDERR "Particle type '$particleType' OK.\n";
}

my $runLength = `$query $run ElapsedTime`;
unless (length($runLength)) {
        die("Can't get run length!\n");
}
print STDERR "Run length for $run was $runLength\n";
if ($runLength <= $ENV{'tkrCopyLimit'}) {
	noCopy();
}

yesCopy();
