#!/usr/local/bin/perl -w

use strict 'vars';
use vars qw{$dbh};
use DBI;
use DBI qw(:sql_types);

$ENV{'TWO_TASK'}='SLAC_TCP';
$ENV{'ORACLE_HOME'} = "/afs/slac/package/oracle/8.1.6/sun4x_56";
$ENV{'TNS_ADMIN'} = "/afs/slac/package/oracle/8.1.6/sun4x_56/network/admin/tnsnames.ora";
$ENV{'LIBHOME'} = "/afs/slac/package/oracle/8.1.6/sun4x_56/lib";

my $result = &isParticleRun($ARGV[0]);
print $result;

sub isParticleRun {

    my ($runId) = @_;

    $dbh = DBI->connect('DBI:Oracle:SLAC_TCP', 'GLAST_CAL', '9square#') or die 'failed: '.$dbh->errstr;

    my $sth = $dbh->prepare(qq{select particletype from elogreport where runid=$runId}) or die $dbh->errstr;

    $sth->execute() or die $dbh->errstr;

    my($particleType) = $sth->fetchrow_array;

    if($particleType ne 'Cosmics' and $particleType ne 'Photons') {
	return 0;
    }
    else {
	return 1;
    }
 
    $dbh->disconnect;
}
