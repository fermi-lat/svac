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
ApplicationMgr.DLLs   += {"GaudiAlg","GaudiAud"};
ApplicationMgr.ExtSvc += {"ChronoStatSvc"};
AuditorSvc.Auditors = {"ChronoAuditor"};
ApplicationMgr.ExtSvc = {"GlastEventSelector/EventSelector" , 
                         "EventCnvSvc"};
EventPersistencySvc.CnvServices = {"EventCnvSvc"};
EventSelector.Input = "NONE";
ApplicationMgr.TopAlg = {"Sequencer/Top"};
Top.Members = {"Sequencer/Calibration",
               "Sequencer/Digitization",
               "Sequencer/Triggered",
               "Sequencer/Integrity",
               "Sequencer/Output"};
Top.StopOverride = true;
Calibration.Members = {"TkrCalibAlg"};
Digitization.Members = {"digiRootReaderAlg"};
Triggered.Members = {"Sequencer/Trigger"};
Trigger.Members   = {"TriggerAlg"};
ApplicationMgr.DLLs += {"Trigger"};
TriggerAlg.mask = 0;
ApplicationMgr.DLLs += {"EventIntegrity"};
Integrity.Members    = {"EventIntegrityAlg",
                        "Sequencer/Reconstruction"};
ApplicationMgr.DLLs   += {"GlastSvc"};
ApplicationMgr.ExtSvc += {"GlastDetSvc"};
GlastDetSvc.topVolume   = "LAT"; 
GlastDetSvc.visitorMode = "recon";
ApplicationMgr.ExtSvc += {"GlastRandomSvc"};
ApplicationMgr.DLLs   += {"G4Generator","G4Propagator"};
ApplicationMgr.ExtSvc += {"G4GeometrySvc"};
ApplicationMgr.DLLs += {"CalUtil", "CalXtalResponse"};
ApplicationMgr.ExtSvc += {"GlastPropagatorSvc"};
ApplicationMgr.DLLs += {"CalibSvc",
                        "TkrUtil",
                        "CalRecon",
                        "TkrRecon"};
Reconstruction.Members = {"Sequencer/Cal1", 
                          "Sequencer/Tkr",
                          "Sequencer/Cal2",
                          "Sequencer/TkrIter",
                          "Sequencer/Acd"};
Cal1.Members    = {"CalXtalRecAlg", 
                   "CalClustersAlg/first"};
Tkr.Members     = {"TkrReconAlg/FirstPass"};
Cal2.Members    = {"CalClustersAlg/second"};
TkrIter.Members = {"TkrReconAlg/Iteration"};
second.OutputLevel = 5;  
ApplicationMgr.DLLs += {"AcdRecon"};
Acd.Members = {"AcdReconAlg"};
Output.Members  = {"meritAlg"};
Output.Members += {"reconRootWriterAlg"};
ApplicationMgr.ExtSvc += {"TkrGeometrySvc"};
ApplicationMgr.ExtSvc += {"TkrInitSvc"};
ApplicationMgr.ExtSvc += {"CalibDataSvc"};
ApplicationMgr.ExtSvc += {"CalibMySQLCnvSvc", "CalibXmlCnvSvc" };
DetectorPersistencySvc.CnvServices += {"CalibMySQLCnvSvc"};
CalibMySQLCnvSvc.DbName = "calib";
DetectorPersistencySvc.CnvServices += {"CalibXmlCnvSvc"};
CalibDataSvc.CalibInstrumentName = "$instrumentType";
CalibDataSvc.CalibStorageType = 14;
CalibDataSvc.CalibRootName = "Calib";
CalibDataSvc.CalibTimeSource = "data";
ApplicationMgr.ExtSvc += {"CalCalibSvc"};
CalCalibSvc.DefaultFlavor = "vanilla";
ApplicationMgr.ExtSvc += {"CalibRootCnvSvc"};                            
DetectorPersistencySvc.CnvServices += {"CalibRootCnvSvc"};
CalibDataSvc.CalibFlavorList = {"ideal", "vanilla"};
ApplicationMgr.ExtSvc += {"CalFailureModeSvc"};
ApplicationMgr.DLLs   += {"AnalysisNtuple","ntupleWriterSvc","merit"};
ApplicationMgr.ExtSvc += {"RootTupleSvc"};
MeritAlg.IM_filename = ""; 
MeritAlg.cuts        = "LnA";
ApplicationMgr.DLLs   += {"RootIo"};
ApplicationMgr.ExtSvc += {"RootIoSvc"}; 
ApplicationMgr.Runable = "RootIoSvc"; 
MessageSvc.OutputLevel = 3;
ApplicationMgr.EvtMax = 10000000;
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


