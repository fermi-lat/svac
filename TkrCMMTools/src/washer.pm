# washer.pm
# FILENAME: washer.pm
# LATDOC: LAT-TD-xxxx
# REVISION: 1
# DATE: 20-SEP-04
# AUTHOR: Arthur K. Scholz
# DESCRIPTION: Washer library module.  Provides the base data type
# and access methods for a set of washers.
#
# Washers behave essentially like sidewalls for now.  They can
# inherit the same access methods and data structures for now.

package Washer;
@ISA = ('Sidewall');

our $max_tol = 186.750;

sub check_inspec {
  $_[0]->{'inspec'} = abs($_[0]->{'points'}->[$_[0]->{'max'}]->[$_[1]]) <= $max_tol;
}
