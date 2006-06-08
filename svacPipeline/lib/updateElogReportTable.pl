#!/usr/local/bin/perl -w

# a utility script to update one column in the elogReport table 
# usage: it takes three arguments. First argument is the runId of the run to be
# updated, second argument is the name of the column to be updated, third 
# argument is the value to be put into the column.
# Note at the moment it can only update a column which contain a string.

use strict 'vars';
use vars qw{$dbh};
use DBI;
use DBI qw(:sql_types);

use lib "$ENV{'beamtestPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'beamtestPlRoot'}/setup/dbSetup10.cshrc");

if($#ARGV+1 != 3) {
    die 'require three arguments: runId, columnName, value';
}

my $runId = $ARGV[0];
my $columnName = $ARGV[1];
my $value = $ARGV[2];

print STDERR "Run: [$runId], Column: [$columnName], Value: [$value]\n";

if ($ENV{'eLogTestOnly'}) {
	print STDERR "Running in test mode, not updating eLog.\n";
	exit 0;
}

$dbh = DBI->connect($ENV{'dbName'}, $ENV{'userName'}, $ENV{'passWd'}) or die 'connect db failed: '.$dbh->errstr;

my $sqlStr = "update elogReport set $columnName='$value' where runId = $runId";

my $sth = $dbh->prepare($sqlStr) or die 'prepare sql failed: '.$dbh->errstr;

$sth->execute() or die 'execute sql failed: '.$dbh->errstr;

$sth->finish() or die 'finish sql failed: '.$dbh->errstr;

$dbh->disconnect or die 'disconnect db failed: '.$dbh->errstr;


