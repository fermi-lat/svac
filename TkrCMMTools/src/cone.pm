# cone.pm
# FILENAME: cone.pm
# LATDOC: LAT-TD-xxxx
# REVISION: 1
# DATE: 20-SEP-04
# AUTHOR: Arthur K. Scholz
# DESCRIPTION: Cone library module.  Provides the base data type
# and access methods for a set of cones.
#
# Cone Structure:
# Cone ->
#   pierce -> [x y z]
#   cone   -> [i j k]
#   face   -> [i j k]
#   inspec -> is it in spec?
#   theta  -> axial angle
#   phi    -> pitch angle
#   gamma  -> cone axis angle
#   alpha  -> inner cone angle
#   beta   -> outer cone angle
#   disp   -> displacement


package Cone;

use Math::Trig ('acos', 'pi', 'asin');
use AngTool ('cal_ang');

our $cone_z = -30.17;
our $e = .5334;
$AngTool::e = $e;

our $theta = 0;
our $delta_theta = 0.404;

our $phi = 0;
our $delta_phi = 0.483;

our $gamma = 0;
our $delta_gamma = .404;

our $max_dist = .870;

our $nom_z = -37.42;
our $min_z = -37.67;
our $max_z = -34.00;

our $max_y = 1;
our $min_s_y = -.350;
our $min_c_y = -.690;

our @normal = ( [ 1, 0, 0 ], # 0  Side
		[ 1, 0, 0 ], # 1  Side
		[ sqrt(2)/2, sqrt(2)/2, 0 ], # 2  Corner
		[ 0, 1, 0 ], # 3  Side
		[ 0, 1, 0 ], # 4  Side
		[ -sqrt(2)/2, sqrt(2)/2, 0 ], # 5  Corner
		[ -1, 0, 0 ], # 6  Side
		[ -1, 0, 0 ], # 7  Side
		[ -sqrt(2)/2, -sqrt(2)/2, 0 ], # 8  Corner
		[ 0, -1, 0 ], # 9  Side
		[ 0, -1, 0 ], # 10 Side
		[ sqrt(2)/2, -sqrt(2)/2, 0 ]  # 11 Corner
	      );

our @nom_offset  = ( 19,
		     -19,
		     0,
		     19,
		     -19,
		     0,
		     31,
		     -31,
		     0,
		     31,
		     -31,
		     0
		   );

sub new {
  my $class = shift;
  my $self  = { 'id' => shift,
		'pierce'    => [],
		'cone_vec'  => [],
		'plane_vec' => [],
		'inspec'    => 1,
		'theta'     => 0,
		'phi'       => 0,
		'gamma'     => 0,
		'alpha'     => 0,
		'beta'      => 0,
		'disp'      => 0,
		'z'         => 0,
		'x'         => 0,
		'y'         => 0,
		'outspec'   => {
			       }
	      };

  bless $self, $class;
}

sub set_pierce {
  $_[0]->{'pierce'} = [@_[1..$#_]];
  $_[0]->calc_ab();
}

sub set_cone_vec {
  $_[0]->{'cone_vec'} = [@_[1..$#_]];
  $_[0]->calc_gamma();
}

sub set_plane_vec {
  $_[0]->{'plane_vec'} = [@_[1..$#_]];
  $_[0]->calc_theta();
  $_[0]->calc_phi();
}

sub get_pierce {
  $_[0]->{'pierce'};
}

sub get_cone_vec {
  $_[0]->{'cone_vec'};
}

sub get_plane_vec {
  $_[0]->{'plane_vec'}
}

sub dot {
  my $a = shift;
  my $b = shift;
  my $total;

  die "Vector matchup error: $#{$a} does not match $#{$b}" unless ($#{$a} == $#{$b});

  foreach (0 .. $#{$a}) {
    $total += ${$a}[$_] * ${$b}[$_];
  }

  $total;
}

sub dist {
  my $total;
  foreach (@_) {
    $total += ($_ * $_);
  }

  sqrt($total);
}

sub calc_theta {
  my @v = @{$_[0]->{'plane_vec'}};
  $v[2] = 0;

  $_[0]->{'theta'} = (180/pi) * 
    acos( dot(\@v, $normal[$_[0]->{'id'}])
	  / dist(@v)
	);

  ($_[0]->{'inspec'} = 0) unless (abs($_[0]->{'theta'}-$theta) < $delta_theta);
}

sub calc_phi {
  my @v = @{$_[0]->{'plane_vec'}};

  $_[0]->{'phi'} = (180/pi) * atan2( $v[2],
				     dot( \@v, $normal[$_[0]->{'id'}])
				   );

  ($_[0]->{'inspec'} = 0) unless (abs($_[0]->{'phi'}-$phi) < $delta_phi);
}

sub calc_gamma {
  my @v = @{$_[0]->{'cone_vec'}};
  my @n = @{$normal[$_[0]->{'id'}]};

  @n = (-$n[0], -$n[1], 0);

  $_[0]->{'gamma'} = (180/pi) * acos( dot( \@v, \@n ) );

  ($_[0]->{'inspec'} = 0) unless (abs($_[0]->{'gamma'}-$gamma) < $delta_gamma);
}


sub calc_ab {
  my @v = @{$_[0]->{'pierce'}};
  my @n = @{$normal[$_[0]->{'id'}]};
  my @r = ($n[1], -$n[0], 0);

  $v[2] = $v[2] - $cone_z;

  my $d = dot( \@v, \@n );

  my @d = ( @v[0] - $d * $n[0], @v[1] - $d * $n[1], @v[2] );
  $_[0]->{'x'} = dot( \@d, \@r ) - $nom_offset[$_[0]->{'id'}];
  $_[0]->{'y'} = $v[2];

  $_[0]->{'dist'} = dist($_[0]->{'x'}, $_[0]->{'y'});

  unless ($_[0]->{'dist'} >= 2*$e) {
    my @tmp = AngTool::cal_ang(-$_[0]->{'x'}, -$_[0]->{'y'});
    ( $_[0]->{'alpha'}, $_[0]->{'beta'} ) = ( (180/pi) * @tmp[0], (180/pi) * @tmp[1]);
  } else {
    ( $_[0]->{'alpha'}, $_[0]->{'beta'} ) = ("Out of spec", "Out of spec");
    $_[0]->{'inspec'} = 0;
  }

  my $min_y = ($_[0]->{'id'} =~ /^([258]|11)$/) ? $min_c_y : $min_s_y;

  ($_[0]->{'inspec'} = 0) unless ($_[0]->{'dist'} <= $max_dist);
  ($_[0]->{'inspec'} = 0) unless (($_[0]->{'y'} <= $max_y) && ($_[0]->{'y'} >= $min_y));
}

sub set_z {
  $_[0]->{'z'}=@_[1];

  ($_[0]->{'inspec'} = 0) unless (($_[0]->{'z'} <= $max_z) && ($_[0]->{'z'} >= $min_z));
}

sub get_z {
  $_[0]->{'z'};
}

sub get_alpha {
  $_[0]->{'alpha'};
}

sub get_beta {
  $_[0]->{'beta'};
}

sub get_gamma {
  $_[0]->{'gamma'};
}

sub get_phi {
  $_[0]->{'phi'};
}

sub get_theta {
  $_[0]->{'theta'};
}

sub get_dist {
  $_[0]->{'dist'};
}

sub get_x {
  $_[0]->{'x'};
}

sub get_y {
  $_[0]->{'y'};
}

sub get_inspec {
  $_[0]->{'inspec'};
}

sub get_id {
  $_[0]->{'id'};
}

1;
