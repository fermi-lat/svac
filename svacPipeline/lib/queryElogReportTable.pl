#!/usr/local/bin/perl -w

# a utility script to query one column from elogReport table
# usage: it takes two arguments. First argument is the runId of the run to be
# querid, second argument is the name of the column to be retrieved.
# The script simply print query results

use strict 'vars';
use vars qw{$dbh};
use DBI;
use DBI qw(:sql_types);

if($#ARGV+1 != 2) {
    die 'require two arguments: runId and columnName';
}

my $runId = $ARGV[0];
my $columnName = $ARGV[1];

$ENV{'TWO_TASK'}='SLAC_TCP';
$ENV{'ORACLE_HOME'} = "/afs/slac/package/oracle/8.1.6/sun4x_56";
$ENV{'TNS_ADMIN'} = "/afs/slac/package/oracle/8.1.6/sun4x_56/network/admin/tnsnames.ora";
$ENV{'LIBHOME'} = "/afs/slac/package/oracle/8.1.6/sun4x_56/lib";


$dbh = DBI->connect('DBI:Oracle:SLAC_TCP', 'GLAST_CAL', '9square#') or die 'connect db failed: '.$dbh->errstr;

my $sqlStr = "select $columnName from elogReport where runId = $runId";

my $sth = $dbh->prepare($sqlStr) or die 'prepare sql failed: '.$dbh->errstr;

$sth->execute() or die 'execute sql failed: '.$dbh->errstr;

my ($value) = $sth->fetchrow_array;

$sth->finish() or die 'finish sql failed: '.$dbh->errstr;

$dbh->disconnect or die 'disconnect db failed: '.$dbh->errstr;

print $value;
