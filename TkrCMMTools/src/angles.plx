#! /usr/bin/perl

# FILENAME: angles.pmx
# AUTHOR: Arthur K. Scholz
# DESCRIPTION: Stand alone angle calculation program

use AngTool ('cal_ang');
use Math::Trig('pi');

unless ($#ARGV == 2) {
  $0 =~ /([^\\\/]*)$/; # remove path
  print "Usage: $1 x_offset y_offset eccentricity";
  exit;
}

$angtool::e = $ARGV[2]; # set eccentricity

my ($alpha, $beta);

eval { 
  ($alpha, $beta) = cal_ang($ARGV[0], $ARGV[1]);
};

if($@ =~ /Out of range:/) {
  print STDERR "Range error: Offsets provided excede range.  Check if offsets and eccentricity are in the same units";
  exit 0;
}

$alpha *= 180/pi;
$beta  *= 180/pi;

printf "alpha:%6d\nbeta:%7d", $alpha, $beta;
