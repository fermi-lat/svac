package Input;

use Exporter;

our @ISA = ('Exporter');
our @EXPORT_OK = ('read_in_tower');

sub read_in_tower {
  my $tower = shift;
  my $fh = shift;

  while(<$fh>) {
    next if /^#/;

    if( /^START (.*)/ ) {
      $_ = $1;
      chomp;
      if( /Side Plane ((\+|-)(X|Y))/ ) { $process = create_proc($tower, 'sidewall', "\L$1"); }
      elsif( /Washer Plane ((\+|-)(X|Y))/ ) { $process = create_proc($tower, 'washer', "\L$1"); }
      elsif( /Flexure ([10]?[0-9].?$)/ ) { $process = create_proc($tower, 'flexure', $1); }
      elsif( /Flexure ([10]?[0-9])(-([10]?[0-9]))? Z/ ) { $process = create_proc($tower, 'flexurez', $1); }
      else { $process = create_proc('unknown'); }

      while(<$fh>) {
	if ( /^END/ ) { last; }
	chomp;
	$process->(split(/,/));
      }
    }
  }
}


sub create_proc {
  my $tower = shift;
  my $type = shift;
  my $loc = shift;
  my $ref;

  if( $type eq "sidewall" ) {
    $ref = sub {
      $tower->get_sidewall($loc)->add_point(@_);
    };
  } elsif ( $type eq "washer" ) {
    $ref = sub {
      $tower->get_washers($loc)->add_point(@_);
    };
  } elsif ( $type eq "flexure" ) {
    my $line = 0;
    $ref = sub {
      if( $line == 0 ) { $tower->get_cone($loc)->set_pierce(@_); }
      if( $line == 1 ) { $tower->get_cone($loc)->set_cone_vec(@_); }
      if( $line == 2 ) { $tower->get_cone($loc)->set_plane_vec(@_); }
      if( $line >= 3 ) { die "Undefined behavior" };

      $line++;
    };
  } elsif ( $type eq "flexurez" ) {
    $ref = sub {
      $tower->get_cone($loc)->set_z(@_);
    };
  } else {
    $ref = sub {
      return;
    }
  }

  $ref;
}
