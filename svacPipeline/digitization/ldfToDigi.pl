#!/usr/local/bin/perl

use strict;

my $ldfFile = $ENV{'ldfFile'};

my $shellFile = $ENV{'shellFile'};
my $jobOptionFile = $ENV{'jobOptionFile'};
my $digiRootFile = $ENV{'digiRootFile'};

my $cmtPath = $ENV{'CMTPATH'};
my $cmtDir = $ENV{'ldfToDigiCmt'};
my $exe = $ENV{'ldfToDigiApp'};
my $ldfFileType = $ENV{'ldfFileType'};

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

if (-z $ldfFile) {
    print "LDF file [$ldfFile] has zero size.\n";
    exit 0;
}

open(SHELLFILE, ">$shellFile") || die "Can't open $shellFile, abortted!";
print SHELLFILE "#!/bin/csh \n \n";
#print SHELLFILE "unsetenv LD_LIBRARY_PATH \n";
#print SHELLFILE "source $glastScript \n";
print SHELLFILE "setenv CMTPATH $cmtPath \n";
print SHELLFILE "pushd $cmtDir \n";
print SHELLFILE "source setup.csh \n";
print SHELLFILE "popd \n";
print SHELLFILE "pushd $cmtDir \n";
print SHELLFILE "cmt show uses \n";
print SHELLFILE "popd \n";

# convert ldf file to digi file
print SHELLFILE "setenv JOBOPTIONS $jobOptionFile \n";
print SHELLFILE "$exe || exit 1\n";

close(SHELLFILE);

# create option file for converting ebf files
open(JOBOPTIONFILE, ">$jobOptionFile") || die "Can't open $jobOptionFile, abortted!";
print JOBOPTIONFILE <<EOF;
ApplicationMgr.DLLs+= { "GaudiAlg", "GaudiAud"};
ApplicationMgr.ExtSvc += {"ChronoStatSvc"};
AuditorSvc.Auditors = {"ChronoAuditor"};
ApplicationMgr.DLLs += {"LdfConverter"};
//EventSelector.Instrument = "EM";
ApplicationMgr.ExtSvc += { 
    "LdfEventSelector/EventSelector" , 
    "LdfCnvSvc/EventCnvSvc"
    };
EventPersistencySvc.CnvServices = {"EventCnvSvc"};
ApplicationMgr.TopAlg = {
      "Sequencer/Top" };
Generator.Members = {};
Digitization.Members = {};
Top.Members={
    "Sequencer/Trigger",
    "Sequencer/Output" 
};
ApplicationMgr.DLLs += {"GlastSvc"};
ApplicationMgr.ExtSvc += { "GlastDetSvc"};
//GlastDetSvc.xmlfile="\$(XMLGEODBSROOT)/xml/em2/em2SegVols.xml";
GlastDetSvc.visitorMode="recon";
ApplicationMgr.DLLs +={ 
    "Trigger", "RootIo"
}; 
Trigger.Members = {"TriggerAlg"};
TriggerAlg.mask = 0;

ApplicationMgr.ExtSvc += { "RootIoSvc" };
digiRootWriterAlg.OutputLevel=3;
Output.Members = {
    "digiRootWriterAlg"
};
digiRootWriterAlg.digiRootFile = "$digiRootFile";
EventSelector.StorageType = "$ldfFileType";
EventSelector.InputList = {"$ldfFile"};
EventSelector.OutputLevel = 4;
MessageSvc.OutputLevel = 3;
ApplicationMgr.EvtMax  = 100000000;
EOF
close(JOBOPTIONFILE);

system("chmod +rwx $shellFile");

my $status = system("$shellFile");
 
if ($status == 0) {
    exit 0;}
else {
    exit 1;}
