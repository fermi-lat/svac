#!/usr/local/bin/perl

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

my $glastRoot = "/afs/slac.stanford.edu/g/glast";
my $glastScript = "$glastRoot/ground/scripts/user.cshrc";

open(SHELLFILE, ">$shellFile") || die "Can't open $shellFile, abortted!";
print SHELLFILE "#!/bin/csh \n \n";
print SHELLFILE "unsetenv LD_LIBRARY_PATH \n";
print SHELLFILE "source $glastScript \n";
print SHELLFILE "setenv CMTPATH $cmtPath \n";
print SHELLFILE "pushd $cmtDir \n";
print SHELLFILE "source setup.csh \n";
print SHELLFILE "cmt show uses \n";
print SHELLFILE "popd \n";
print SHELLFILE "setenv JOBOPTIONS $jobOptionFile \n";
print SHELLFILE "$exe \n";
close(SHELLFILE);

open(JOBOPTIONFILE, ">$jobOptionFile") || die "Can't open $jobOptionFile, abortted!";
print JOBOPTIONFILE "#include \"\$GLEAMROOT/src/basicOptions.txt\" \n";
print JOBOPTIONFILE qq(Digitization.Members = {"digiRootReaderAlg"}; \n);
#print JOBOPTIONFILE qq(EventSelector.Instrument = "EM"; \n);
#print JOBOPTIONFILE qq(GlastDetSvc.xmlfile="\$(XMLGEODBSROOT)/xml/em2/em2SegVols.xml"; \n);
print JOBOPTIONFILE qq(GlastDetSvc.visitorMode  = "recon";);

# mask = 0 means not filtering out any events
print JOBOPTIONFILE qq(TriggerAlg.mask = 0; \n);

print JOBOPTIONFILE qq(ApplicationMgr.DLLs += {"ntupleWriterSvc"}; \n);
print JOBOPTIONFILE qq(ApplicationMgr.ExtSvc += {"RootTupleSvc"}; \n);

print JOBOPTIONFILE qq{meritAlg.EventTreeName="MeritTuple"; \n};
print JOBOPTIONFILE qq{meritAlg.PointingTreeName="Exposure"; \n};
print JOBOPTIONFILE qq{RootTupleSvc.TreeName="MeritTuple"; \n};
print JOBOPTIONFILE qq{RootTupleSvc.filename="$meritRootFile"; \n};

print JOBOPTIONFILE qq(Generator.Members = {} ; \n);

print JOBOPTIONFILE qq(Digitization.Members = {"digiRootReaderAlg"}; \n);

print JOBOPTIONFILE qq(digiRootReaderAlg.digiRootFile="$digiRootFile"; \n);

print JOBOPTIONFILE qq(reconRootWriterAlg.reconRootFile = "$reconRootFile"; \n);

print JOBOPTIONFILE qq(Output.Members = {"reconRootWriterAlg"}; \n);

print JOBOPTIONFILE qq(CalClustersAlg.OutputLevel=4; \n);

print JOBOPTIONFILE qq(ApplicationMgr.EvtMax = 100000000; \n);

print JOBOPTIONFILE qq(MessageSvc.OutputLevel      =3; \n);

#print JOBOPTIONFILE qq(ApplicationMgr.ExtSvc += {"TkrFailureModeSvc"}; \n);
#print JOBOPTIONFILE qq(TkrFailureModeSvc.layerList = {"0_0_0", "0_0_1"}; \n);

# these two lines are added so that number of events will be registered in the root file
print JOBOPTIONFILE qq(ApplicationMgr.ExtSvc += { "RootIoSvc" }; \n);
print JOBOPTIONFILE qq(ApplicationMgr.Runable= "RootIoSvc"; \n);

# read in CAL calibraton constants
print JOBOPTIONFILE qq(CalXtalRecAlg.startTime = "2003-9-5 11:00"; \n);
print JOBOPTIONFILE qq(CalXtalRecAlg.calibFlavor="chen"; \n);

print JOBOPTIONFILE qq(ApplicationMgr.ExtSvc += {"CalibDataSvc"}; \n);

print JOBOPTIONFILE qq(ApplicationMgr.ExtSvc += {"CalibMySQLCnvSvc", "CalibXmlCnvSvc" }; \n);

print JOBOPTIONFILE qq(DetectorPersistencySvc.CnvServices += {"CalibMySQLCnvSvc"}; \n);
print JOBOPTIONFILE qq(DetectorPersistencySvc.CnvServices += {"CalibXmlCnvSvc"}; \n);

print JOBOPTIONFILE qq(CalibDataSvc.CalibInstrumentName = "EM"; \n);
print JOBOPTIONFILE qq(CalibDataSvc.CalibFlavorList = {"ideal", "chen"}; \n);

close(JOBOPTIONFILE);
system("chmod +rwx $shellFile");

my $status = system("$shellFile");

if ($status == 0) {
    exit 0;}
else {
    exit 1;}


