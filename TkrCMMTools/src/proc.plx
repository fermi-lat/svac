#! /usr/bin/perl

use CGI::Pretty;
use CGI::Carp;
use FileHandle;
use Input ('read_in_tower');

use Tower;

my $query = new CGI;

our $cmd = 0;

if($ARGV[0]) {
  $cmd = 1;

  print "Command Line\n";
}

print $query->header;
print $query->start_html("Tower Alignment CMM Data Processing Tools");
print $query->h1("Tower Alignment CMM Data Processing Tools");
print $query->hr;

print_prompt($query);
print $query->hr;
do_work($query);

print $query->end_html;

sub print_prompt {
  my $query = shift;

  print $query->start_multipart_form();
  print "Enter the file to process: ";
  print $query->filefield(-name=>'fh',
			  -default=>'no default',
			  -size=>45,
			 );
  print $query->h4("Report Type");
  print $query->radio_group(-name => 'report_type',
			    -values => ['0', '1', '2'],
			    -default => 'Simple',
			    -labels => {'0' => 'Simple',
					'1' => 'Detailed',
					'2' => 'Tolerance'
				       }
			   );
  print $query->br;
  print $query->br;
  print $query->reset;
  print $query->submit('submit','Process File');
  print $query->end_form;
}

sub do_work {
  my $query = shift;

  unless ($cmd) {
    return unless ($query->param('submit'));
  }

  my $fh = $query->param('fh');

  if($cmd) {
    my $fh = new FileHandle;
    $fh->open(@ARGV[0]);
  }

  my $detail = $query->param('report_type');

  my $tower = Tower->new("00000");

  read_in_tower($tower,$fh);

  print $query->h1(Report);
  print print_sidewalls($query,$tower,$detail);
  print $query->br();
  print print_washers($query,$tower,$detail);
  print $query->br();
  print print_cones($query,$tower,$detail);

  print $query->br;

  print $query->table({-border=>'',
		       -cellspacing => '0',
		       -cellpadding =>'5'},
	    $query->Tr({-align=>LEFT, -valign=>TOP},
		       [
			$query->th(['Reference Flex Cone',
				    'alpha', 'beta']),
			$query->td(['2',
				    sprintf("%2d",
					    $tower->get_cone('2')->get_alpha()),
				    sprintf("%2d",
					    $tower->get_cone('2')->get_beta()),
				   ]
				  ),
			$query->td(['8',
				    sprintf("%2d",$tower->get_cone('8')->get_alpha()),
				    sprintf("%2d",$tower->get_cone('8')->get_beta()),
				   ]
				  ),
			$query->td(['11',
				    sprintf("%2d",$tower->get_cone('11')->get_alpha()),
				    sprintf("%2d",$tower->get_cone('11')->get_beta()),
				   ]
				  )
		       ]
		      )
		     );
}

sub print_sidewalls {
  my $query = shift;
  my $tower = shift;
  my $detailed = shift;

  my @td_array;

  my @header = ('Tower Half Width', 'Status');
  push @header, ('Max') if $detailed;

  @td_array = ($query->th(\@header));

  foreach (sort($tower->list_sidewalls)) {
    my $color;
    my $value;
    my $td_string;

    $td_string = $query->td(["\U$_"]);

    if($tower->get_sidewall($_)->get_inspec) {
      $color = 'lime';
      $value = 'passed';
    } else {
      $color = 'red';
      $value = 'failed';
    }

    $td_string .= $query->td({-bgcolor => $color}, [$value]);
    $td_string .= $query->td({-align => 'RIGHT'},
			     [sprintf "%.3f",
			      $tower->get_sidewall($_)->get_max_point()])
      if $detailed;

    push @td_array, $td_string;
  }

  @header = ('Tower Full Width', 'Status');
  push @header, ('Max') if $detailed;
  push @td_array, $query->th(\@header);

  @_ = ('x', 'y');

  foreach (@_) {
    my $td_string = $query->td(["\U$_"]);

    if($tower->check_width('sidewall',$_)) {
      $color = 'lime';
      $value = 'passed';
    } else {
      $color = 'red';
      $value = 'failed';
    }

    $td_string .= $query->td({-bgcolor => $color}, [$value]);
    $td_string .= $query->td({-align => 'RIGHT'},
			     [sprintf "%.3f",
			      $tower->get_width('sidewall',$_)])
      if $detailed;

    push @td_array, $td_string;
  }

  $query->table({-border => '', -cellspacing => '0', -cellpadding => '5'},
		$query->Tr({ -align => 'LEFT', -valign => 'TOP' },
			   \@td_array)
	       );
}

sub print_washers {
  my $query = shift;
  my $tower = shift;
  my $detailed = shift;

  my @td_array;

  my @header = ('Washer Plane', 'Status');
  push @header, ('Max') if $detailed;

  @td_array = ($query->th(\@header));

  foreach (sort($tower->list_washers)) {
    my $color;
    my $value;
    my $td_string;

    $td_string = $query->td(["\U$_"]);

    if($tower->get_washers($_)->get_inspec) {
      $color = 'lime';
      $value = 'passed';
    } else {
      $color = 'red';
      $value = 'failed';
    }

    $td_string .= $query->td({-bgcolor => $color}, [$value]);
    $td_string .= $query->td({-align => 'RIGHT'},
			     [sprintf "%.3f",
			      $tower->get_washers($_)->get_max_point()])
      if $detailed;

    push @td_array, $td_string;
  }

  @header = ('Tower Full Width', 'Status');
  push @header, ('Max') if $detailed;
  push @td_array, $query->th(\@header);

  @_ = ('x', 'y');

  foreach (@_) {
    my $td_string = $query->td(["\U$_"]);

    if($tower->check_width('washers',$_)) {
      $color = 'lime';
      $value = 'passed';
    } else {
      $color = 'red';
      $value = 'failed';
    }

    $td_string .= $query->td({-bgcolor => $color}, [$value]);
    $td_string .= $query->td({-align => 'RIGHT'},
			     [sprintf "%.3f",
			      $tower->get_width('washers',$_)])
      if $detailed;

    push @td_array, $td_string;
  }

  $query->table({-border => '', -cellspacing => '0', -cellpadding => '5'},
		$query->Tr({ -align => 'LEFT', -valign => 'TOP' },
			   \@td_array)
	       );
}

sub print_cones {
  my $query = shift;
  my $tower = shift;
  my $detailed = shift;

  my @td_array;

  my @header = ('Flexure Cone', 'Status');
  push @header, ('Theta',
		 'Phi',
		 'Gamma',
		 'Z',
		 'Radial Offset',
		 'FCS X Offset',
		 'FCS Y Offset',
		 'Alpha',
		 'Beta'
		)
    if $detailed;

  @td_array = ($query->th(\@header));

  foreach ($tower->list_cones) {
    my $color;
    my $value;
    my $td_string;

    $td_string = $query->td(["\U$_"]);

    if($tower->get_cone($_)->get_inspec) {
      $color = 'lime';
      $value = 'passed';
    } else {
      $color = 'red';
      $value = 'failed';
    }

    $td_string .= $query->td({-bgcolor => $color}, [$value]);

    if($detailed) {
      $td_string .= 
	$query->td({-align => 'RIGHT'},
		   [
		    sprintf("%.3f", $tower->get_cone($_)->get_theta()),
		    sprintf("%.3f",$tower->get_cone($_)->get_phi()),
		    sprintf("%.3f",$tower->get_cone($_)->get_gamma()),
		    sprintf("%.3f",$tower->get_cone($_)->get_z()),
		    sprintf("%.3f",$tower->get_cone($_)->get_dist()),
		    sprintf("%.3f",$tower->get_cone($_)->get_x()),
		    sprintf("%.3f",$tower->get_cone($_)->get_y()),
		    sprintf("%3d",$tower->get_cone($_)->get_alpha()),
		    sprintf("%3d",$tower->get_cone($_)->get_beta())
		   ]);
    }

    push @td_array, $td_string;
  }

  $query->table({-border => '',
		 -cellspacing => '0',
		 -cellpadding => '5'},
		$query->Tr({ -align => 'LEFT',
			     -valign => 'TOP' },
			   \@td_array)
	       );
}

sub dump_tower {
  $tower = shift;

  foreach (keys %{$tower->{'sidewall'}}) {
    if($tower->get_sidewall($_)->get_inspec()) {
      print "Sidewall $_: Passed\n<BR>";
    }
    else {
      my $max;

      print "Sidewall $_: Failed\n<BR>";
      print "Max Point: ",
	$max = $tower->get_sidewall($_)->get_max(),
	  "<BR>";
      my @point = $tower->get_sidewall($_)->get_point($max);
      print "Value: @point",
	  "<BR>";
    }
  }

  foreach (keys %{$tower->{'washers'}}) {
    if($tower->get_washers($_)->get_inspec()) {
      print "Washers $_: Passed\n<BR>";
    }
    else {
      print "Washers $_: Failed\n<BR>";
    }
  }
}
