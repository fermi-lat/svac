#!/usr/local/bin/perl -w

use strict;

if ($#ARGV != 4) {
    die "Usage: $0 runName ldfFile shellFile jobOptionFile digiRootFile";
}

my ($runName, $ldfFile, $shellFile, $jobOptionFile, $digiRootFile) = @ARGV;

my $cmtPath = $ENV{'CMTPATH'};
my $cmtDir = $ENV{'ldfToDigiCmt'};
my $exe = $ENV{'ldfToDigiApp'};
my $ldfFileType = $ENV{'ldfFileType'};
my $svacCmtConfig = $ENV{'SVAC_CMTCONFIG'};
my $svacGlastExt = $ENV{'SVAC_GLAST_EXT'};

print <<EOT;
$0 running with options:
  ldfFile:       $ldfFile
  shellFile:     $shellFile
  jobOptionFile: $jobOptionFile
  digiRootFile:  $digiRootFile
  cmtPath:       $cmtPath
  cmtDir:        $cmtDir
  exe :          $exe
EOT
    
#my $glastRoot = "/afs/slac.stanford.edu/g/glast";
#my $glastScript = "$glastRoot/ground/scripts/user.cshrc";

# put ldfFITS file in eLog
my $eLogCmd = "$ENV{'svacPlLib'}/updateElogReportTable.pl '$runName' FitsFile '$ldfFile'";
print "Running command [$eLogCmd]\n";
system($eLogCmd);

if (-z $ldfFile) {
    print "LDF file [$ldfFile] has zero size.\n";
    exit 0;
}

open(SHELLFILE, ">$shellFile") || die "Can't open $shellFile, abortted!";
print SHELLFILE "#!/bin/csh \n \n";
print SHELLFILE "unsetenv LD_LIBRARY_PATH \n";
#print SHELLFILE "source $glastScript \n";
print SHELLFILE "setenv CMTCONFIG $svacCmtConfig \n";
print SHELLFILE "setenv GLAST_EXT $svacGlastExt \n";
print SHELLFILE "setenv CMTPATH $cmtPath \n";
print SHELLFILE "pushd $cmtDir \n";
print SHELLFILE "source setup.csh \n";
print SHELLFILE "popd \n";
print SHELLFILE "pushd $cmtDir \n";
print SHELLFILE "cmt show uses \n";
print SHELLFILE "popd \n";

# convert ldf file to digi file
print SHELLFILE "setenv JOBOPTIONS $jobOptionFile \n";
print SHELLFILE "$exe || exit 1 \n";

close(SHELLFILE);

# create option file for converting ebf files
open(JOBOPTIONFILE, ">$jobOptionFile") || die "Can't open $jobOptionFile, abortted!";
print JOBOPTIONFILE <<EOF;
ApplicationMgr.DLLs   += {"GaudiAlg",
                          "GaudiAud"};
ApplicationMgr.ExtSvc += {"ChronoStatSvc"};
AuditorSvc.Auditors    = {"ChronoAuditor"};
ApplicationMgr.TopAlg = {"Sequencer/Top"};
Top.Members = {"Sequencer/Triggered"};
Triggered.Members = {"Sequencer/Trigger",
                     "Sequencer/Output"};
ApplicationMgr.DLLs    += {"GlastSvc"};
ApplicationMgr.ExtSvc  += {"GlastDetSvc"};
GlastDetSvc.topVolume   = "LAT"; 
GlastDetSvc.visitorMode = "recon";
ApplicationMgr.DLLs += {"Trigger"};
Trigger.Members      = {"TriggerAlg"};
TriggerAlg.mask = 0; 
ApplicationMgr.DLLs += {"RootIo"}; 
Output.Members       = {"digiRootWriterAlg"};
ApplicationMgr.DLLs   += {"LdfConverter"};
ApplicationMgr.ExtSvc += {"LdfEventSelector/EventSelector","LdfCnvSvc/EventCnvSvc"};
EventPersistencySvc.CnvServices = {"EventCnvSvc"};
EventSelector.Instrument = "LAT";
MessageSvc.OutputLevel = 3;
ApplicationMgr.EvtMax = 10000000;
GlastDetSvc.xmlfile = "\$(XMLGEODBSROOT)/xml/flight/flightSegVols.xml";
EventSelector.StorageType = "$ldfFileType";
EventSelector.InputList = {"$ldfFile"};
digiRootWriterAlg.digiRootFile = "$digiRootFile";
EOF

close(JOBOPTIONFILE);

system("chmod +rwx $shellFile");

my $status = system("$shellFile");
 
if ($status == 0) {
    exit 0;}
else {
    exit 1;}
