#!/usr/local/bin/perl

use strict;

my $ldfFile = $ENV{'ldfFile'};

my $shellFile = $ENV{'shellFile'};
my $jobOptionFile = $ENV{'jobOptionFile'};
my $digiRootFile = $ENV{'digiRootFile'};
my $cmtPath = $ENV{'cmtPath'};
my $cmtDir = $ENV{'cmtDir'};
my $exe = $ENV{'exe'};

print <<EOT;
$0 running with:
  ldfFile:       $ldfFile
  shellFile:     $shellFile
  jobOptionFile: $jobOptionFile
  digiRootFile:  $digiRootFile
  cmtPath:       $cmtPath
  cmtDir:        $cmtDir
  exe :          $exe
EOT

open(SHELLFILE, ">$shellFile") || die "Can't open $shellFile, abortted!";
print SHELLFILE "#!/bin/sh \n \n";
print SHELLFILE "unset LD_LIBRARY_PATH \n";
print SHELLFILE "CMTPATH=$cmtPath \n";
print SHELLFILE "export CMTPATH \n";
print SHELLFILE "pushd $cmtDir \n";
print SHELLFILE "source setup.sh \n";
print SHELLFILE "popd \n";
print SHELLFILE "pushd $cmtDir \n";
print SHELLFILE "cmt show uses \n";
print SHELLFILE "popd \n";

# convert ldf file to digi file
print SHELLFILE "JOBOPTIONS=$jobOptionFile \n";
print SHELLFILE "export JOBOPTIONS \n";
print SHELLFILE "$exe \n";

close(SHELLFILE);

# create option file for converting ebf files
open(JOBOPTIONFILE, ">$jobOptionFile") || die "Can't open $jobOptionFile, abortted!";
print JOBOPTIONFILE qq{ApplicationMgr.DLLs+= {"GaudiAlg", "GaudiAud"};\n};
print JOBOPTIONFILE qq{ApplicationMgr.ExtSvc += {"ChronoStatSvc"}; \n};
print JOBOPTIONFILE qq{AuditorSvc.Auditors = {"ChronoAuditor"}; \n};
print JOBOPTIONFILE qq{ApplicationMgr.DLLs += {"LdfConverter"}; \n};
print JOBOPTIONFILE qq{EventSelector.Instrument = "EM"; \n};
print JOBOPTIONFILE qq{ApplicationMgr.ExtSvc += {"LdfEventSelector/EventSelector" , "LdfCnvSvc/EventCnvSvc"}; \n};
print JOBOPTIONFILE qq{EventPersistencySvc.CnvServices = {"EventCnvSvc"};\n};
print JOBOPTIONFILE qq{ApplicationMgr.TopAlg = {"Sequencer/Top" }; \n};
print JOBOPTIONFILE qq{Generator.Members = {};\n};
print JOBOPTIONFILE qq{Digitization.Members = {};\n};
print JOBOPTIONFILE qq{Top.Members={"Sequencer/Output"}; \n};
print JOBOPTIONFILE qq{ApplicationMgr.DLLs += {"GlastSvc"}; \n};
print JOBOPTIONFILE qq{ApplicationMgr.ExtSvc += { "GlastDetSvc"}; \n};
print JOBOPTIONFILE qq{GlastDetSvc.xmlfile="\$(XMLGEODBSROOT)/xml/em2/em2SegVols.xml"; \n};
print JOBOPTIONFILE qq{GlastDetSvc.visitorMode="recon";\n };
print JOBOPTIONFILE qq{ApplicationMgr.DLLs +={"RootIo"}; \n};
print JOBOPTIONFILE qq{ApplicationMgr.ExtSvc += { "RootIoSvc" }; \n};
print JOBOPTIONFILE qq{digiRootWriterAlg.OutputLevel=3; \n};
print JOBOPTIONFILE qq{Output.Members = {"digiRootWriterAlg"}; \n};
print JOBOPTIONFILE qq{digiRootWriterAlg.digiRootFile = "$digiRootFile"; \n};
print JOBOPTIONFILE qq{EventSelector.StorageType = "LDFFILE"; \n};
print JOBOPTIONFILE qq{EventSelector.InputList = {"$ldfFile"}; \n};
print JOBOPTIONFILE qq{EventSelector.OutputLevel = 4; \n};
print JOBOPTIONFILE qq{MessageSvc.OutputLevel = 3; \n};
print JOBOPTIONFILE qq{ApplicationMgr.EvtMax  = 1000000000; \n};
close(JOBOPTIONFILE);

system("chmod +rwx $shellFile");
system("$shellFile");
 

