package environmentalizer;

use strict;

sub sourceCsh {
    my $evFile = shift;
    foreach(`tcsh -f -c 'source $evFile ; setenv'`) {
	$ENV{$1} = $2 if /^(\S+)=(\S*)$/;
    }
}


'YOW!';
