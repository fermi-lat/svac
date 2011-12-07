#!/usr/local/bin/perl -w

use strict 'vars';
use vars qw{$dbh};
use DBI;
use DBI qw(:sql_types);

my $particleType = `$ENV{'svacPlLib'}/queryElogReportTable.pl $ARGV[0] particleType`;
chomp $particleType;


my $result;
if($particleType ne 'Cosmics' and $particleType ne 'Photons') {
    $result =  0;
}
else {
    $result = 1;
}
print "$result\n";

