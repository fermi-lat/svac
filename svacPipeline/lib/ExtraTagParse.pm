package ExtraTagParse;

use strict;

sub tagParse {

=head1 tagParse(AdditionFields, [tag])

This parses values out of the AdditionFields string.

If fed the string and a tag, it returns the value corresponding to the tag.

If fed just the string, it returns a hash containing the values associated
with each tag.

=cut

    #my ($pair, $scalar, $tag);
    my $scalar = 0;
    my $tag;
    my %hash = ();

    my $string = $_[0];
    if ($#_ > 0) {
        $tag = $_[1];
        $scalar = 1;
    }

    while ($string =~ /(.*?)\?\?\?(.*?)!!!/g) {
        if ($scalar) {
	  if ($1 eq $tag) {
	      return $2;
	  }
        } else {
	  $hash{$1} = $2;
        }
    }

    if ($scalar) {
        # we wouldn't have gotten here if the key were present
        return 0;
    } else {
        return \%hash;
    }
}


"Yeeha!";
