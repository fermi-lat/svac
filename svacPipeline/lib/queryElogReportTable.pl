#!/usr/local/bin/perl -w

# a utility script to query one column from elogReport table
# usage: it takes two arguments. First argument is the runId of the run to be
# querid, second argument is the name of the column to be retrieved.
# The script simply print query results

use strict 'vars';
use vars qw{$dbh};
use DBI;
use DBI qw(:sql_types);

use lib "$ENV{'svacPlRoot'}/lib-current";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup-current/dbSetup.cshrc");

if($#ARGV+1 != 2) {
    die 'require two arguments: runId and columnName';
}

my $runId = $ARGV[0];
my $columnName = $ARGV[1];


$dbh = DBI->connect($ENV{'dbName'}, $ENV{'userName'}, $ENV{'passWd'}) or die 'connect db failed: '.$dbh->errstr;

# prepare to read in CLOB data
my $oldReadLen = $dbh->{LongReadLen};
$dbh->{LongReadLen} = 512 * 1024;
$dbh->{LongTruncOk} = 1;

my $sqlStr = "select $columnName from elogReport where runId = $runId";

my $sth = $dbh->prepare($sqlStr) or die 'prepare sql failed: '.$dbh->errstr;

$sth->execute() or die 'execute sql failed: '.$dbh->errstr;

my ($value) = $sth->fetchrow_array;

$sth->finish() or die 'finish sql failed: '.$dbh->errstr;

$dbh->{LongReadLen} = $oldReadLen;

$dbh->disconnect or die 'disconnect db failed: '.$dbh->errstr;

print "$value\n";
