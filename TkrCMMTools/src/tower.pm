# tower.pm
# FILENAME: tower.pm
# LATDOC: LAT-TD-xxxx
# REVISION: 1
# DATE: 20-SEP-04
# AUTHOR: Arthur K. Scholz
# DESCRIPTION: Tower library module.  Provides the base data type 
# and access methods for a tower.
#
# Tower Data Structure:
# Tower ->
#   id        -> tower id number
#   statu     -> flight status
#   sidewalls -> +x -> sidewall structure
#                +y -> sidewall structure
#                -x -> sidewall structure
#                -y -> sidewall structure
#   cones     ->  0 -> side flexure
#                 1 -> side flexure
#                 2 -> corner flexure
#                 3 -> side flexure
#                 4 -> side flexure
#                 5 -> corner flexure
#                 6 -> side flexure
#                 7 -> side flexure
#                 8 -> corner flexure
#                 9 -> side flexure
#                10 -> side flexure
#                11 -> corner flexure
#   washers   -> +x -> washer structure
#                +y -> washer structure
#                -x -> washer structure
#                -y -> washer structure

package Tower;

use Exporter;
use Carp qw(croak);
use strict;

use Sidewall;
use Washer;
use Cone;

our @ISA = 'Exporter';

our $default_id = "00000";

our $max_width_wash = 373.500;
our $max_width_side = 372.500;

sub new {
  my $class = shift;
  my $tower_id = shift;
  $tower_id = $default_id unless $tower_id;

  my $self = {
	      id       => $tower_id,
	      status   => 'non-flight',
	      sidewall => {
			   '+x' => Sidewall->new('+x'),
			   '+y' => Sidewall->new('+y'),
			   '-x' => Sidewall->new('-x'),
			   '-y' => Sidewall->new('-y')
			  },
	      cone     => [
			   Cone->new('0'), # 0
			   Cone->new('1'), # 1
			   Cone->new('2'), # 2
			   Cone->new('3'), # 3
			   Cone->new('4'), # 4
			   Cone->new('5'), # 5
			   Cone->new('6'), # 6
			   Cone->new('7'), # 7
			   Cone->new('8'), # 8
			   Cone->new('9'), # 9
			   Cone->new('10'), # 10
			   Cone->new('11')  # 11
			  ],
	      washers  => {
			   '+x' => Washer->new('+x'),
			   '+y' => Washer->new('+y'),
			   '-x' => Washer->new('-x'),
			   '-y' => Washer->new('-y')
			  },
	      outspec  => {
			  }
	     };

  bless $self, $class;
}

sub get_id {
  $_[0]->{'id'};
}

sub set_id {
  # Add ID format checking

  $_[0]->{'id'} = $_[1];
}

sub get_status {
  $_[0]->{'status'};
}

sub set_status {
  # Add status format checking

  $_[0]->{'status'} = $_[1];
}

sub list_sidewalls {
  keys %{$_[0]->{'sidewall'}}
}

sub get_sidewall {
  $_[0]->{'sidewall'}->{$_[1]};
}

sub set_sidewall {
  # Add sidewall name checking

  $_[0]->{'sidewall'}->{$_[1]} = $_[2];
}

sub remove_sidewall {
  $_[0]->{'sidewall'}->{$_[1]} = {};
}

sub list_cones {
  my @tmp;

  foreach (@{$_[0]->{'cone'}}) {
    push @tmp, $_->get_id();
  }

  @tmp;
}

sub get_cone {
  $_[0]->{'cone'}->[$_[1]];
}

sub remove_cone {
  $_[0]->{'cone'}->[0] = {};
}

sub list_washers {
  keys %{$_[0]->{'washers'}};
}

sub get_washers {
  $_[0]->{'washers'}->{$_[1]};
}

sub set_washers {
  # Add washer name checking
  $_[0]->{'washers'}->{$_[1]} = $_[2];
}

sub remove_washers{
  $_[0]->{'washers'}->{$_[1]} = {};
}

sub get_width {
  my $id = shift;
  my $type = shift;
  my $axis = shift;

  if( $type eq 'sidewall' ) {
    $id->get_sidewall("+$axis")->get_max_point() - $id->get_sidewall("-$axis")->get_max_point();
  } elsif( $type eq 'washers' ) {
    $id->get_washers("+$axis")->get_max_point() - $id->get_washers("-$axis")->get_max_point();
  }
}

sub check_width {
  my $id = shift;
  my $type = shift;
  my $axis = shift;

  my $max_width = ($type =~ /sidewall/) ? $max_width_side : $max_width_wash;

  $id->get_width($type, $axis) < $max_width;
}

1;
