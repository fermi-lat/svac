# sidewall.pm
# FILENAME: sidewall.pm
# LATDOC: LAT-TD-xxxx
# REVISION: 1
# DATE: 20-SEP-04
# AUTHOR: Arthur K. Scholz
# DESCRIPTION: Sidewall library module.  Provides the base data type
# and access methods for a set of sidewalls.
#
# Sidewall Structure:
# Sidewall ->
#   points -> [
#               [x0 y0 z0]
#               [x1 y1 z1]
#               ...
#             ]
#   max    -> index to maximum point
#   inspec -> is the sidewall within spec

package Sidewall;

use Carp qw(croak);
use strict;

our %coord = ('x' => 0,
	      'y' => 1
	     );

our $max_tol = 186.250;

sub new {
  my $class = shift;
  $_ = shift;

  die "Unrecognized type" unless /^(\+|-)(x|y)$/;

  my $self = {
	      points => [],
	      max => 0,
	      inspec => 1,
	      type => $_,
	      outspec => {
			 }
	     };

  bless $self, $class;
}

sub add_point {
  $_[0]->{'type'} =~ /^(\+|-)(x|y)$/;
  my $sign = $1."1";
  my $coord = $coord{"$2"};

  --($_ = push @{$_[0]->{'points'}}, [@_[1..$#_]]);

  $_[0]->{'max'} = $sign * $_[0]->{'points'}->[$_]->[$coord] >
    $sign * $_[0]->{'points'}->[$_[0]->{'max'}]->[$coord] ?
      $_ : $_[0]->{'max'};

  $_[0]->check_inspec($coord) unless $_[0]->{'max'} != $_;

  $_;
}

sub get_point {
  @{$_[0]->{'points'}->[$_[1]]};
}

sub clear_points {
  $_[0]->{'points'} = [];
}

sub get_max {
  $_[0]->{'max'};
}

sub get_max_point {
  $_[0]->{'type'} =~ /^(\+|-)(x|y)$/;
  my $coord = $coord{"$2"};

  $_[0]->{'points'}->[$_[0]->{'max'}]->[$coord]
}

sub get_type {
  $_[0]->{'type'};
}

sub get_inspec {
  $_[0]->{'inspec'};
}

sub check_inspec {
  $_[0]->{'inspec'} = abs($_[0]->{'points'}->[$_[0]->{'max'}]->[$_[1]]) <= $max_tol;
}

1;

