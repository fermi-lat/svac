package MakeMeta;

use strict;

sub makeMeta {

=head1 makeMeta(taskDir, scriptBase1, [scriptBase2, ...])

This makes MetaWrappers.  It is used at install time.

The first argument is the Task directory.

Subsequent arguments are base parts of wrapper names.  For a base name foo, a
metawrapper named fooMetaWrapper.csh will be created (in the Task directory),
which will launch a pipeline wrapper named fooWrapper.pl (also in the Task
directory).

Return value is a hash containing the full path to the created metawrappers,
indexed by the input basenames.

=cut

my ($taskDir, @baseNames) = @_;

my %metaWrappers = ();
foreach my $script (@baseNames) {
	my $wrapperName = "${taskDir}/${script}Wrapper.pl";
	my $metaWrapperName = "${taskDir}/${script}MetaWrapper.csh";
	$metaWrappers{$script} = $metaWrapperName;
	my $metaWrapperText = 
"#!/bin/tcsh
setenv svacPlRoot $ENV{'svacPlRoot'}
exec $wrapperName \$*
";
	open FIELDS, '>', $metaWrapperName;
	print FIELDS $metaWrapperText;
	close FIELDS;
	system("chmod +x $metaWrapperName");
}

return %metaWrappers;

}

"Yes.";
