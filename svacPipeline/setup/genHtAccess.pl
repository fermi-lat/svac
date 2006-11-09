#! /usr/bin/env perl

use strict;

use lib "$ENV{'svacPlRoot'}/lib";
use environmentalizer;
environmentalizer::sourceCsh("$ENV{'svacPlRoot'}/setup/svacPlSetup.cshrc");

my $htaData = 
"AuthType Basic
AuthName 'Please use FTP.'
AuthUserFile $ENV{svacPlRoot}/setup/passwords
Require user glast
";

my $htaName = "$ENV{'svacPlRoot'}/setup/htaccess";
open HTA, '>', $htaName;
print HTA $htaData;
close HTA;
