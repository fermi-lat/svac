#!/usr/local/bin/perl -w

use strict;

if ($#ARGV != 5) {
    die "Usage: $0 digiRootFile shellFile jobOptionFile reconRootFile meritRootFile runId";
}

my ($digiRootFile, $shellFile, $jobOptionFile, $reconRootFile, $meritRootFile, $runId) = @ARGV; 

print <<EOT;
$0 running with:
  digiRootFile:  $digiRootFile
  shellFile:     $shellFile
  jobOptionFile: $jobOptionFile
  reconRootFile: $reconRootFile
  meritRootFile: $meritRootFile
  runId: $runId
EOT

my $tkrSerNo = `$ENV{'svacPlLib'}/queryElogReportTable.pl $runId tkr_ser_no`;
$tkrSerNo =~ s/\?//g;
my $calSerNo = `$ENV{'svacPlLib'}/queryElogReportTable.pl $runId cal_ser_no`;
$calSerNo =~ s/\?//g;

my $em = 0;
if($tkrSerNo =~ /Mini/ || $calSerNo =~ /EM2/) {
    $em = 1;
}

#build instrument type used to select appropriate constants
my $instrumentType = '';

my $schemaFile = `$ENV{'svacPlLib'}/queryElogReportTable.pl $runId SCHEMACONFIGFILE`;

if($schemaFile =~ /grid/i) {
    $instrumentType = 'LAT';
}
elsif($em) {
    $instrumentType = 'EM';
}
elsif($tkrSerNo && !$calSerNo) {
    $instrumentType = $tkrSerNo;
}
elsif(!$tkrSerNo && $calSerNo) {
    $instrumentType = 'Cal'.$calSerNo;
}
elsif($tkrSerNo && $calSerNo) {
    $instrumentType = $tkrSerNo.':Cal'.$calSerNo;
}


my $cmtPath = $ENV{'CMTPATH'};
my $cmtDir = $ENV{'reconCmt'};
my $exe = $ENV{'reconApp'};
my $svacCmtConfig = $ENV{'SVAC_CMTCONFIG'};
my $svacGlastExt = $ENV{'SVAC_GLAST_EXT'};
my $latCalibRoot = $ENV{'LATCalibRoot'};

open(SHELLFILE, ">$shellFile") || die "Can't open $shellFile, abortted!";
print SHELLFILE "#!/bin/csh \n \n";
print SHELLFILE "unsetenv LD_LIBRARY_PATH \n";
print SHELLFILE "setenv CMTCONFIG $svacCmtConfig \n";
print SHELLFILE "setenv GLAST_EXT $svacGlastExt \n";
print SHELLFILE "setenv CMTPATH $cmtPath \n";
print SHELLFILE "setenv LATCalibRoot $latCalibRoot \n";
print SHELLFILE "pushd $cmtDir \n";
print SHELLFILE "source setup.csh \n";
print SHELLFILE "cmt show uses \n";
print SHELLFILE "popd \n";
print SHELLFILE "setenv JOBOPTIONS $jobOptionFile \n";
print SHELLFILE "$exe || exit 1 \n";
close(SHELLFILE);

my $geoFile = '$(XMLGEODBSROOT)/xml/flight/flightSegVols.xml';;
if($em) {
$geoFile = '$(XMLGEODBSROOT)/xml/em2/em2SegVols.xml';
}

open(JOBOPTIONFILE, ">$jobOptionFile") || die "Can't open $jobOptionFile, abortted!";
print JOBOPTIONFILE <<EOF;
#include "\$LATINTEGRATIONROOT/src/jobOptions/pipeline/readigi_runrecon.txt"
GlastDetSvc.xmlfile = "$geoFile";
digiRootReaderAlg.digiRootFile = "$digiRootFile";
RootTupleSvc.filename = "$meritRootFile";
reconRootWriterAlg.reconRootFile = "$reconRootFile";
EOF
close(JOBOPTIONFILE);
system("chmod +rwx $shellFile");

my $status = system("$shellFile");

if ($status == 0) {
    exit 0;}
else {
    exit 1;}


