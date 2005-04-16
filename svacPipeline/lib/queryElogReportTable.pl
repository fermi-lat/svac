#!/usr/local/bin/perl -w

# a utility script to query one field from elogReport table
# usage: it takes two arguments. First argument is the runId of the run to be
# querid, second argument is the name of the field to be retrieved.
# Note the field does not have to be stored as a column in the elogReport 
# table, it could be stored in the additionFields column.
# The script simply print query results

use strict 'vars';
use vars qw{$dbh};
use DBI;
use DBI qw(:sql_types);

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/dbSetup.cshrc");

if($#ARGV+1 != 2) {
    die 'require two arguments: runId and fieldName';
}

my $runId = $ARGV[0];
my $fieldName = $ARGV[1];


$dbh = DBI->connect($ENV{'dbName'}, $ENV{'userName'}, $ENV{'passWd'}) or die 'connect db failed: '.$dbh->errstr;


# check whether the field is stored as a column in the table
my $sqlStr = "select column_name from USER_TAB_COLUMNS where upper(column_name)=upper('$fieldName') and upper(table_name) = upper('eLogReport')";

my $isColumn = queryTable($sqlStr);

if(defined($isColumn)) {

    my $sqlStr = "select $fieldName from elogReport where runId = $runId";

    my $value = queryTable($sqlStr);

    print "$value\n";

    exit 0;

}

# the field could be saved in additionFields column
# prepare to read in CLOB data
my $oldReadLen = $dbh->{LongReadLen};
$dbh->{LongReadLen} = 512 * 1024;
$dbh->{LongTruncOk} = 1;

my $columnName = 'additionFields';

$sqlStr = "select $columnName from elogReport where runId = $runId";

my $additionFields = queryTable($sqlStr);

$dbh->{LongReadLen} = $oldReadLen;

$dbh->disconnect or die 'disconnect db failed: '.$dbh->errstr;

my $result;
foreach my $item (split(/!!!/, $additionFields)) {

    my ($tag, $value) = split(/\?\?\?/, $item);
    if($tag eq $fieldName) {
	$result = $value;
	last;
    }
}
print "$result\n";

exit 0;


# this routine assumes query only returns maximally 1 row of data
sub queryTable {

    my($sqlStr) = @_;

    my $sth = $dbh->prepare($sqlStr) or die 'prepare sql failed: '.$dbh->errstr;

    $sth->execute() or die "execute sql failed: $sqlStr".$dbh->errstr;

    my ($result) = $sth->fetchrow_array;

    $sth->finish() or die 'finish sql failed: '.$dbh->errstr;

    return $result;

}
