# angtool.pm
# FILENAME: angtool.pm
# LATDOC: LAT TD-xxxx
# REVISION: 1
# DATE: 15-SEP-04
# AUTHOR: Arthur K. Scholz
# DESCRIPTION: Converts FCS offsets to cone installation angles.  
# Refer to Alignment Plan (LAT-DS-xxxx) for definitions of these 
# coordinate systems

package AngTool;

use Math::Trig ('acos', 'asin', 'pi');
use Exporter;

@ISA = ('Exporter');
@EXPORT_OK = ('cal_ang', 'check_ang');

our $tol = 10**-6;
our $e = 0;

sub cal_ang {
  my ($x, $y) = @_;
  my $r;
  my $alpha = 0;
  my $beta = 0;
  my $ca = 0;
  my $cb = 0;

  $r = $x**2 + $y**2;

  die "Out of range: $r > 2*$e^2" if $r > 2*$e**2 + $tol;

  return ($alpha, $beta) if $r == 0;

  $alpha = acos(1 - $r/(2*$e**2));

  $ca = $e * (1-cos($alpha));
  $cb = $e * sin($alpha);

  $beta = acos(($ca*$x+$cb*$y)/$r);
  $beta = -$beta unless check_ang($alpha, $beta, $x, $y);
  die "Could not verify values" unless
    check_ang($alpha, $beta, $x, $y);

  return ($alpha, $beta);
}

sub check_ang {
  my ($alpha, $beta, $x, $y) = @_;

  $x1 = $e*(cos($beta)-cos($alpha-$beta));
  $y1 = $e*(sin($beta)+sin($alpha-$beta));

  return 0 unless
    (equals($x1,$x) &&
     equals($y1,$y));

  return 1;
}

sub equals {
  my ($a, $b) = @_;

  return 0 unless (abs($a - $b) < $tol);
  return 1;
}

return 1;
