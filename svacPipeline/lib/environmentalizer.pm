package environmentalizer;

use strict;

sub sourceCsh {
    my $evFile = shift;
    foreach(`tcsh -c 'source $evFile ; setenv'`) {
	$ENV{$1} = $2 if /^(\S+)=(\S*)$/;
    }
}


'YOW!';
