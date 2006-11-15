#!/usr/local/bin/perl -w

# a utility script to query one field from elogReport table
# usage: it takes two arguments. First argument is the runId of the run to be
# querid, second argument is the name of the field to be retrieved.
# Note the field does not have to be stored as a column in the elogReport 
# table, it could be stored in the additionFields column.
# The script simply print query results. It exits with exited code 1 if the
# value is not stored in the database. Note if you use system() to call this
# utility script, the return code is the exit code shifted to left by eight,
# so exit code 1 would become 256.


use strict 'vars';
use vars qw{$dbh};
use DBI;
use DBI qw(:sql_types);

print STDERR "$0: svacPlRoot=[$ENV{'svacPlRoot'}]\n";

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/dbSetup10.cshrc");

print STDERR "$0: svacPlRoot=[$ENV{'svacPlRoot'}]\n";

if($#ARGV+1 != 2) {
    die 'require two arguments: runId and fieldName';
}

my $runId = $ARGV[0];
my $fieldName = $ARGV[1];


$dbh = DBI->connect($ENV{'dbName'}, $ENV{'userName'}, $ENV{'passWd'}) or dbErr('connect db failed: '.$dbh->errstr);


# check whether the field is stored as a column in the table
my $sqlStr = "select column_name from USER_TAB_COLUMNS where upper(column_name)=upper('$fieldName') and upper(table_name) = upper('eLogReport')";

my $isColumn = queryTable($sqlStr);

if(defined($isColumn)) {

    my $sqlStr = "select $fieldName from elogReport where runId = $runId";

    my $value = queryTable($sqlStr);

    if(defined($value)) {
	print "$value\n";
	exit 0;
    }
    else {
	exit(1);
    }
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

$dbh->disconnect or dbErr('disconnect db failed: '.$dbh->errstr);

my $result;
foreach my $item (split(/!!!/, $additionFields)) {

    my ($tag, $value) = split(/\?\?\?/, $item);
    if($tag eq $fieldName) {
	$result = $value;
	last;
    }
}

if(defined($result)) {
    print "$result\n";
    exit 0;
}
else {
    exit(1);
}

# this routine assumes query only returns maximally 1 row of data
sub queryTable {

    my($sqlStr) = @_;

    my $sth = $dbh->prepare($sqlStr) or dbErr("prepare sql failed: $sqlStr ".$dbh->errstr);

    $sth->execute() or dbErr("execute sql failed: $sqlStr ".$dbh->errstr);

    my ($result) = $sth->fetchrow_array;

    $sth->finish() or dbErr("finish sql failed: $sqlStr ".$dbh->errstr);

    return $result;

}

sub dbErr {
    my ($errStr) = @_;

    print $errStr;;

    exit(1);
}
