#!/usr/local/bin/perl

# Demonstration script.
# Submitted to batch by pipeline scheduler.
# You need only modify the last section...

use lib '/u/gl/dflath/glast/software/DPF/PDB/';
use DPFProc;

#####################################################
##
##  BEGIN:  DON'T TOUCH STUFF BETWEEN THESE COMMENTS
##
#####################################################

my $proc = new DPFProc(@ARGV);
my $inFiles = $proc->{'inFiles'};
my $outFiles = $proc->{'outFiles'};

#####################################################
##
##  END:  DON'T TOUCH STUFF BETWEEN THESE COMMENTS
##
#####################################################


#  Ok, this is your area to play, do as you wish from here on in:
#  Make sure you return the result of your processing in place of this perl
#  script's return code so that LSF records the correct ret code.
#  NOTE: This is done for you if you use the 'system' command as below.

# $inFiles{'DS_NAME'} is the filename of the instance of dataset 'DS_NAME'
# $outFiles{'DS_NAME'} is the filename of the instance of dataset 'DS_NAME'

# Configure your environment and run your processing, application, or script.
# Perl exposes the system environment thru the hash: 'ENV'


# ==============
#  For example:
# ==============

$ENV{'ldfFile'} = $ldfFile;
$ENV{'shellFile'} = $shellFile;
$ENV{'jobOptionFile'} = $jobOptionFile;
$ENV{'digiRootFile'}= $digiRootFile;
$ENV{'cmtPath'} = '/nfs/farm/g/glast/u05/builds/rh9_gcc32/EngineeringModel/EngineeringModel-v3r0402p16';
$ENV{'cmtDir'} = '/nfs/farm/g/glast/u06/chen/glast_mc/EngineeringModel_v3r0402p16/Em2/v0r0p0/cmt';
$ENV{'exe'} = '/nfs/farm/g/glast/u06/chen/glast_mc/EngineeringModel_v3r0402p16/Em2/v0r0p0/rh9_gcc32/Em2.exe';

system "ldfToDigi.pl";

