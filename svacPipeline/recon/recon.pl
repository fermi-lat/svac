#!/usr/local/bin/perl -w

use strict;

if ($#ARGV != 4) {
    die "Usage: $0 digiRootFile shellFile jobOptionFile reconRootFile meritRootFile";
}

my ($digiRootFile, $shellFile, $jobOptionFile, $reconRootFile, $meritRootFile) = @ARGV; 

print <<EOT;
$0 running with:
  digiRootFile:  $digiRootFile
  shellFile:     $shellFile
  jobOptionFile: $jobOptionFile
  reconRootFile: $reconRootFile
  meritRootFile: $meritRootFile
EOT

my $cmtPath = $ENV{'CMTPATH'};
my $cmtDir = $ENV{'reconCmt'};
my $exe = $ENV{'reconApp'};

open(SHELLFILE, ">$shellFile") || die "Can't open $shellFile, abortted!";
print SHELLFILE 
"#!/bin/csh

unsetenv LD_LIBRARY_PATH
setenv CMTPATH $cmtPath
pushd $cmtDir
source setup.csh
cmt show uses
popd
setenv JOBOPTIONS $jobOptionFile
$exe || exit 1
";
close(SHELLFILE);

open(JOBOPTIONFILE, ">$jobOptionFile") || die "Can't open $jobOptionFile, abortted!";
print JOBOPTIONFILE 
"#include \"\$GLEAMROOT/src/basicOptions.txt\"
Digitization.Members = {\"digiRootReaderAlg\"};
\\\\EventSelector.Instrument = \"EM\";
\\\\GlastDetSvc.xmlfile=\"\$(XMLGEODBSROOT)/xml/em2/em2SegVols.xml\";
GlastDetSvc.visitorMode  = \"recon\";
\\\\ mask = 0 means not filtering out any events
TriggerAlg.mask = 0;

ApplicationMgr.DLLs += {\"ntupleWriterSvc\"};
ApplicationMgr.ExtSvc += {\"RootTupleSvc\"};

meritAlg.EventTreeName=\"MeritTuple\";
meritAlg.PointingTreeName=\"Exposure\";
RootTupleSvc.TreeName=\"MeritTuple\";
RootTupleSvc.filename=\"$meritRootFile\";

Generator.Members = {} ;
Digitization.Members = {\"digiRootReaderAlg\"};
digiRootReaderAlg.digiRootFile=\"$digiRootFile\";
reconRootWriterAlg.reconRootFile = \"$reconRootFile\";
Output.Members = {\"reconRootWriterAlg\"};
CalClustersAlg.OutputLevel=4;
ApplicationMgr.EvtMax = 100000000;
MessageSvc.OutputLevel      =3;

\\\\ApplicationMgr.ExtSvc += {\"TkrFailureModeSvc\"};
\\\\TkrFailureModeSvc.layerList = {\"0_0_0\", \"0_0_1\"};

\\\\ these two lines are added so that number of events will be registered in the root file
ApplicationMgr.ExtSvc += { \"RootIoSvc\" };
ApplicationMgr.Runable= \"RootIoSvc\";

\\\\ read in CAL calibraton constants
\\\\CalXtalRecAlg.startTime = \"2003-9-5 11:00\";
\\\\CalXtalRecAlg.calibFlavor=\"chen\";
\\\\ApplicationMgr.ExtSvc += {\"CalibDataSvc\"};
\\\\ApplicationMgr.ExtSvc += {\"CalibMySQLCnvSvc\", \"CalibXmlCnvSvc\" };
\\\\DetectorPersistencySvc.CnvServices += {\"CalibMySQLCnvSvc\"};
\\\\DetectorPersistencySvc.CnvServices += {\"CalibXmlCnvSvc\"};
\\\\CalibDataSvc.CalibInstrumentName = \"EM\";
\\\\CalibDataSvc.CalibFlavorList = {\"ideal\", \"chen\"};
";

close(JOBOPTIONFILE);
system("chmod +rwx $shellFile");

my $status = system("$shellFile");

if ($status == 0) {
    exit 0;}
else {
    exit 1;}


