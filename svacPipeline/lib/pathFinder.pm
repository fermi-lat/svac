package pathFinder;

use strict;

sub findPath {
	my $task = shift;
	$task =~ s/-/\//g;
	my $taskPath = "$ENV{'svacPlRoot'}/$task";
	return $taskPath;
}


"true";
