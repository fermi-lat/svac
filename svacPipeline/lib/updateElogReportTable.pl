#!/usr/local/bin/perl

# a utility script to update one column in the elogReport table 
# usage: it takes three arguments. First argument is the runId of the run to be
# updated, second argument is the name of the column to be updated, third 
# argument is the value to be put into the column.
# Note at the moment it can only update a column which contain a string.

use strict 'vars';
use vars qw{$dbh};
use DBI;
use DBI qw(:sql_types);

if($#ARGV+1 != 3) {
    die 'require three arguments: runId, columnName, value';
}

my $runId = $ARGV[0];
my $columnName = $ARGV[1];
my $value = $ARGV[2];

$ENV{'TWO_TASK'}='SLAC_TCP';
$ENV{'ORACLE_HOME'} = "/afs/slac/package/oracle/8.1.6/sun4x_56";
$ENV{'TNS_ADMIN'} = "/afs/slac/package/oracle/8.1.6/sun4x_56/network/admin/tnsnames.ora";
$ENV{'LIBHOME'} = "/afs/slac/package/oracle/8.1.6/sun4x_56/lib";


$dbh = DBI->connect('DBI:Oracle:SLAC_TCP', 'GLAST_CAL', '9square#') or die 'connect db failed: '.$dbh->errstr;

my $sqlStr = "update elogReport set $columnName='$value' where runId = $runId";

my $sth = $dbh->prepare($sqlStr) or die 'prepare sql failed: '.$dbh->errstr;

$sth->execute() or die 'execute sql failed: '.$dbh->errstr;

$sth->finish() or die 'finish sql failed: '.$dbh->errstr;

$dbh->disconnect or die 'disconnect db failed: '.$dbh->errstr;


