#include <iostream>
#include <cstdio>
#include <strings.h>
#include <stdexcept>
#include "TROOT.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TPostScript.h"
#include "TestReport.h"
#include "ToString.h"
#include "TStyle.h"
#include "TLine.h"
#include "TFrame.h"
#include "TLatex.h"
#include "Geo.h"

using std::cout;
using std::endl;
using std::string;

Float_t TestReport::efficDivide(TH1& top, const TH1& bot, Bool_t inEffic) {

  Int_t nt = top.GetNbinsX();
  Int_t nb = bot.GetNbinsX();
  if ( nt != nb ) return -1.;

  Float_t iT(0.);
  Float_t iB(0.);

  for ( UInt_t i(1); i <= nt; i++ ) {
    Float_t vT = top.GetBinContent(i);
    Float_t n = bot.GetBinContent(i);
    iT += vT;
    iB += n;
    if ( vT > n ) return -2.;
    if ( n == 0 )  {
      top.SetBinContent(i,0.0);
      top.SetBinError(i,0.0);
      continue;
    }
    // sneak in 1/2 an event to distinguish perfect channels from channels w/ no data.
    if ( vT < 0.5 ) {
      vT = 0.5;
    }
    Float_t p = vT / n;
    Float_t q = 1. - p;
    Float_t npq = n*p*q;
    Float_t err = TMath::Sqrt(npq) / n;
    top.SetBinContent(i, inEffic ? q : p);
    top.SetBinError(i,err);
  }

  top.SetMinimum(0.);
  top.SetMaximum(1.);
  
  return fabs(iB) > 1e-9 ? iT / iB : 0.;
}

TestReport::TestReport(const char* dir, const char* prefix, 
		       const char* version, const char* emVersion,
		       const char*tkrCalibSerNo, const char* calCalibSerNo)
  : m_dir(dir), m_prefix(prefix), m_version(version), m_emVersion(emVersion),
    m_tkrCalibSerNo(tkrCalibSerNo), m_calCalibSerNo(calCalibSerNo), 
    m_outputFile(0), m_mcFile(0), m_mcTree(0),
    m_mcBranch(0), m_mcEvent(0), m_reconFile(0), m_reconTree(0), 
    m_reconBranch(0), m_reconEvent(0), m_digiFile(0), m_digiTree(0),
    m_digiBranch(0), m_digiEvent(0), m_trigger(0), m_nBadEvts(0), 
    m_nTrgParityErrors(0), m_nPacketErrors(0), m_nTemErrors(0), m_isLATTE(0),
    m_nEvent(0),
    m_nTkrTrigger(0), m_nEventBadStrip(0), m_nEventMoreStrip(0), 
    m_nEventSatTot(0), m_nEventZeroTot(0), m_nEvtInvalidTot(0), m_nEvtOverlapTriggerTot(0),
    m_nEventBadTot(0), m_startTime(0),
    m_endTime(0), m_nDigi(0), m_nAcdOddParityError(0), m_nAcdHeaderParityError(0),
    m_AcdTileIdOnePMT(0), m_AcdTileIdOneVeto(0),
    m_AcdHitMap(0), m_AcdVetoMap(0),
    m_AcdPhaMapA(0), m_AcdPhaMapB(0),
    m_AcdEfficMap(0),m_AcdInEfficMap(0),
    m_AcdMissMapTop(0), 
    m_AcdMissMapMinusX(0), m_AcdMissMapMinusY(0),
    m_AcdMissMapPlusX(0), m_AcdMissMapPlusY(0)
{ 
  // initialize ROOT
  if(gROOT == 0) {
    static TROOT g_root("report", "report");
  }
  gROOT->SetBatch();  // initialize ROOT
  if(gROOT == 0) {
    static TROOT g_root("report", "report");
  }
  gROOT->SetBatch();

  string f(dir);
  f += '/';
  f += prefix;
  f += "_report.doxygen";
  m_report = new ofstream(f.c_str());
  m_report->precision(2);

  string r(dir);
  r += '/';
  r += prefix;
  r += "_hist.root";
  m_outputFile = new TFile(r.c_str(), "RECREATE");

  std::fill((int*) m_nFec, ((int*) m_nFec)+g_nTower*g_nLayer*g_nView*2, 12);

  m_trigger = new TH1F("trigger", "Trigger distribution", 32, -0.5, 31.5);
  HistAttribute att("Trigger word", "Number of events");
  setHistParameters(m_trigger, att);

  m_condSummary = new TH1F("condSummary", "Condition summary distribution", 32, -0.5, 31.5);
  att.m_xTitle = "GEM Condition summary word";
  setHistParameters(m_condSummary, att);

  m_tkrPerTower = new TH1F("tkrPerTower","Number of TKR triggers per tower",32,0,16);
  att.set("Tower number","Number of TKR triggers");
  setHistParameters(m_tkrPerTower, att);

  m_calLoPerTower = new TH1F("calLoPerTower","Number of CAL LO triggers per tower",32,0,16);
  att.set("Tower number","Number of CAL LO triggers");
  setHistParameters(m_calLoPerTower, att);

  m_calHiPerTower = new TH1F("calHiPerTower","Number of CAL Hi triggers per tower",32,0,16);
  att.set("Tower number","Number of CAL HI triggers");
  setHistParameters(m_calHiPerTower, att);

  for(int i = 0; i != 7; ++i) {
    m_nEventDigi[i] = 0;
  }

  m_nHit2D = new TH2F("nHit2D", "nhits distribution", 36, -0.5, 35.5, 16, -0.5, 15.5);
  att.set("Plane", "Tower");
  setHistParameters(m_nHit2D, att);

  m_nZeroHit2D = new TH2F("nZeroHit2D", "no. of events with zero strip hit in a particular TKR plane", 72, 0, 36, 16, -0.5, 15.5);
  att.set("Plane", "Tower");
  setHistParameters(m_nZeroHit2D, att);

  for(int i = 0; i != g_nTower; ++i) {
    char name[] = "nHitss00";
    sprintf(name, "nHitss%02d", i);
    char xTitle[] = "Number of strip hits in tower 00";
    sprintf(xTitle, "Number of strip hits in tower %02d", i);
    m_nHit[i] = new TH1F(name, xTitle, 20, 0., 20.);
    att.set(xTitle, "Number of events", 0.1, 0.07, 0.6, 0.4);
    setHistParameters(m_nHit[i], att);
 
    char name1[] = "nLayer00";
    sprintf(name1, "nLayer%02d", i);
    char xTitle1[] = "Number of hit planes in tower 00";
    sprintf(xTitle1, "Number of hit planes in tower %02d", i);
    m_nLayer[i] = new TH1F(name1, xTitle1, 37, -0.5, 36.5);
    att.set(xTitle1, "Number of events", 0.1, 0.07, 0.6, 0.4);
    setHistParameters(m_nLayer[i], att);

    m_nTkrEvent[i] = 0;
    m_nTkrBadEvent[i] = 0;

    for(int j = 0; j != g_nPlane; ++j) {
      m_nHitPlane[i][j] = 0;
      m_nEvtPlane[i][j] = 0;
      m_nEvtHitPlane[i][j][0] = 0;
      m_nEvtHitPlane[i][j][1] = 0;
      for(int k = 0; k != 2; ++k) {
	char name[] = "tot00000";
	sprintf(name, "tot%02d%02d%1d", i, j, k);
	m_tot[i][j][k] = new TH1F(name, name, g_satTot, 0, g_satTot);
      }
    }

    for(int j = 0; j != g_nCalLayer; ++j) {
      m_calEneLayer[i][j] = 0;
      m_nCalEneLayer[i][j] = 0;
      m_nCalHit[i][j] = 0;
      m_nEvtCalHit[i][j] = 0;
    }
  }

  for(int i = 0; i != enums::number_of_trigger_bits; ++i) {
    m_nEvtGltTrigger[i] = 0; 
  }

  for(int i = 0; i != enums::GEM_offset; ++i) {
    m_nEvtGemTrigger[i] = 0;
  }

  m_nCalHit2D = new TH2F("nCalHit2D", "nhits distribution", 8, -0.5, 7.5, 16, -0.5, 15.5);
  att.set("Layer", "Tower");
  setHistParameters(m_nCalHit2D, att);

  m_nZeroCalHit2D = new TH2F("nZeroCalHit2D", "ratio of events with no hit in a particular CAL layer", 8, -0.5, 7.5, 16, -0.5, 15.5);
  att.set("Layer", "Tower");
  setHistParameters(m_nZeroCalHit2D, att);

  m_totZero2D = new TH2F("totZero2D", "Zerot tot distribution", 72, 0., 36., 16, -0.5, 15.5);
  att.set("Plane", "Tower");
  setHistParameters(m_totZero2D, att);

  m_totNoise2D = new TH2F("totNoise2D", "Noise tot distribution", 72, 0., 36., 16, -0.5, 15.5);
  att.set("Plane", "Tower");
  setHistParameters(m_totNoise2D, att);

  m_totSat2D = new TH2F("totSat2D", "Tot distribution", 72, 0, 36, 16, -0.5, 15.5);
  att.set("Plane", "Tower");
  setHistParameters(m_totSat2D, att);

  m_totAve2D = new TH2F("totAve2D", "Tot distribution", 72, 0, 36, 16, -0.5, 15.5);
  att.set("Plane", "Tower");
  setHistParameters(m_totAve2D, att);

  m_nTkrTrack = new TH1F("nTkrTrack", "Number of reconstructed tracks", 11, -0.5, 10.5);
  att.set("Number of reconstructed tracks", "Number of events");
  att.m_canRebin = false;
  setHistParameters(m_nTkrTrack, att);

  m_reconDirXY = new TH2F("reconDirXY", "Reconstructed dir xy distribution", 100, -1, 1, 100, -1, 1);
  att.set("Reconstructed x direction", "Reconstructed Y direction");
  setHistParameters(m_reconDirXY, att);

  m_reconDirZ = new TH1F("reconDirZ", "Reconstructed dir Z distribution", 100, -1, 0.);
  att.set("Reconstructed z direction", "Number of events");
  setHistParameters(m_reconDirZ, att);

  m_reconPosXY = new TH2F("reconPosXY", "Reconstructed dir XY position", 100, -1000, 1000, 100, -1000, 1000);
  att.set("Reconstructed x position", "Reconstructed y position");
  att.m_canRebin = false;
  att.m_use2DStat = 1;
  setHistParameters(m_reconPosXY, att);

  m_reconPosZ = new TH1F("reconPosZ", "Reconstructed dir Z position", 100, -100, 750.);
  att.set("Reconstructed z position", "Number of events");
  att.m_canRebin = false;
  setHistParameters(m_reconPosZ, att);

  m_reconEne = new TH1F("reconEne", "Reconstructed energy", 100, 0., 400.);
  att.set("Reconstructed energy(MeV)", "Number of events");
  att.m_canRebin = false;
  setHistParameters(m_reconEne, att);

  m_calSumEne = new TH1F("calSumEne", "Cal energy", 100, 0., 400.);
  att.set("Sum of crystal crystal energies in the CAL cluster(MeV).", "Number of events");
  att.m_canRebin = false;
  setHistParameters(m_calSumEne, att);

  m_calEneLayer2D = new TH2F("calEneLayer", "Energy in each CAL layer(MeV)", 8, -0.5, 7.5, 16, -0.5, 15.5);
  att.set("Layer", "Tower");
  setHistParameters(m_calEneLayer2D, att);

  m_zeroCalEneLayer2D = new TH2F("zeroCalEneLayer", "Ratio of events with zero energy measured in a particular CAL layer(MeV)", 8, -0.5, 7.5, 16, -0.5, 15.5);
  att.set("Layer", "Tower");
  setHistParameters(m_zeroCalEneLayer2D, att);

  m_gemDiscarded = new TH1F("gemDiscarded","Number of GEM discarded events between two successive read out events",40,0,20);
  att.set("Number of GEM discarded events","Number of events");
  setHistParameters(m_gemDiscarded,att);

  m_gemDiscardedTime = new TH1F("gemDiscardedTime","Time between the previous read out event and the last discarded event in system clock ticks (nominally 50 ns)",100,0,530);
  att.set("Time of last discarded event (nominally 50 ns ticks)","Number of events");
  setHistParameters(m_gemDiscardedTime,att);

  m_timeInterval = new TH1F("timeInterval", "Time interval between adjacent event in mill second", 100, 0., 3.);
  att.set("Time interval between adjacent events(ms)", "Number of events");
  setHistParameters(m_timeInterval, att);

  m_timeIntervalCut = new TH1F("timeIntervalCut", "Time interval between adjacent event in millseconds with a cut of 1 millsecond", 100, 0., 1.);
  att.set("Time interval between adjacent events(ms)", "Number of events");
  att.m_canRebin = false;
  setHistParameters(m_timeIntervalCut, att);

  m_timeIntervalGem = new TH1F("timeIntervalGem", "Time interval between adjacent event in milliseconds, the time is measured by GEM", 100, 0., 3.);
  att.set("Time interval between adjacent events(ms)", "Number of events");
  setHistParameters(m_timeIntervalGem, att);

  m_timeIntervalGemZoom = new TH1F("timeIntervalGemZoom", "Time interval between adjacent event in milliseconds with a cut of 1 millsecond. The time is measured by GEM", 100, 0., 1.);
  att.set("Time interval between adjacent events(ms)", "Number of events");
  setHistParameters(m_timeIntervalGemZoom, att);

  m_alignCalTkr = new TH1F("alignCalTkr", "Distance between the reconstructed CAL cluster XY coordinates and the XY coordinates extrapolated from TKR", 50, 0., 100.);
  att.set("Difference(mm)", "Number of events");
  att.m_canRebin = false;
  setHistParameters(m_alignCalTkr, att);

  m_nAcdDigis = new TH1F("nAcdDigis","Number of ACD digis",100,-0.5,99.5);
  att.set("Number of ACD digis","Number of events");
  att.m_canRebin = false;
  setHistParameters(m_nAcdDigis,att);

  m_AcdTileIdOnePMT = new TH1F("AcdTileIdOnePMT","ACD tile ID for single PMT digis",128,-0.5,127.5);
  att.set("ACD GEM ID","Fraction of events w/ only 1 PMT fired");
  att.m_canRebin = false;
  setHistParameters(m_AcdTileIdOnePMT,att);

  m_AcdTileIdOneVeto = new TH1F("AcdTileIdOneVeto","ACD tile ID for single Veto digis",128,-0.5,127.5);
  att.set("ACD GEM ID","Fraction of events w/ only 1 Veto signal");
  att.m_canRebin = false;
  setHistParameters(m_AcdTileIdOneVeto,att);

  m_AcdHitMap = new TH1F("AcdHitMap","ACD GEM ID for Hits",128,-0.5,127.5);
  att.set("ACD GEM ID","Number of events");
  att.m_canRebin = false;
  setHistParameters(m_AcdHitMap,att);
 
  m_AcdVetoMap = new TH1F("AcdVetoMap","ACD GEM ID for Vetos",128,-0.5,127.5);
  att.set("ACD GEM ID","Fraction of events above Veto threshold");
  att.m_canRebin = false;
  setHistParameters(m_AcdVetoMap,att);
  
  m_AcdPhaMapA = new TH2F("AcdPhaMapA","ACD GEM ID vs PHA for A PMT",128,-0.5,127.5,256,0,4096);
  att.set("ACD GEM ID","PHA counts");
  att.m_canRebin = false;
  setHistParameters(m_AcdPhaMapA,att);

  m_AcdPhaMapB = new TH2F("AcdPhaMapB","ACD GEM ID vs PHA for B PMT",128,-0.5,127.5,256,0,4096);
  att.set("ACD GEM ID","PHA counts");
  att.m_canRebin = false;
  setHistParameters(m_AcdPhaMapB,att);

  m_AcdEfficMap = new TH1F("AcdEfficMap","ACD Effic by Tile ID",128,-0.5,127.5); 
  att.set("ACD GEM ID","Number of events");
  att.m_canRebin = false;
  setHistParameters(m_AcdEfficMap,att);

  m_AcdInEfficMap = new TH1F("AcdInEfficMap","ACD InEffic by Tile ID",128,-0.5,127.5); 
  att.set("ACD GEM ID","Fraction on expected hits that are missing");
  att.m_canRebin = false;
  setHistParameters(m_AcdInEfficMap,att);
  
  m_AcdMissMapTop = new TH2F("AcdMissMapTop","ACD X-Y location for misses",200,-800.,800.,200,-800.,800.);
  att.set("X (mm)","Y (mm)");
  att.m_canRebin = false;
  setHistParameters(m_AcdMissMapTop,att);

  m_AcdMissMapMinusX = new TH2F("AcdMissMapMinusX","ACD Y-Z location for misses",200,-800.,800.,200,0.,800.);
  att.set("Y (mm)","Z (mm)");
  att.m_canRebin = false;
  setHistParameters(m_AcdMissMapMinusX,att);

  m_AcdMissMapMinusY = new TH2F("AcdMissMapMinusY","ACD X-Z location for misses",200,-800.,800.,200,0.,800.);
  att.set("X (mm)","Z (mm)");
  att.m_canRebin = false;
  setHistParameters(m_AcdMissMapMinusY,att);

  m_AcdMissMapPlusX = new TH2F("AcdMissMapPlusX","ACD Y-Z location for misses",200,-800.,800.,200,0.,800.);
  att.set("Y (mm)","Z (mm)");
  att.m_canRebin = false;
  setHistParameters(m_AcdMissMapPlusX,att);

  m_AcdMissMapPlusY = new TH2F("AcdMissMapPlusY","ACD X-Z location for misses",200,-800.,800.,200,0.,800.);
  att.set("X (mm)","Z (mm)");
  att.m_canRebin = false;
  setHistParameters(m_AcdMissMapPlusY,att);
  
}

TestReport::~TestReport()
{
  if(m_outputFile) {
    m_outputFile->cd();
    m_outputFile->Write(0, TObject::kOverwrite);
    m_outputFile->Close();

    // when the file is deleted, all trees and histograms associated with it
    // also get deleted. So they should not be manually deleted again
    delete m_outputFile;
  }

  delete m_mcFile;
  delete m_digiFile;
  delete m_reconFile;
  delete m_report;
}

void TestReport::setHistParameters(TH1* h, const HistAttribute& att)
{
  assert(h != 0);

  h->SetXTitle(att.m_xTitle.c_str());
  h->SetYTitle(att.m_yTitle.c_str());
  h->SetTitle("");
  h->SetFillColor(2);
  h->SetLineWidth(1);
  h->SetLabelSize(att.m_axisLabelSize, "X");
  h->SetLabelSize(att.m_axisLabelSize, "Y");
  h->GetXaxis()->SetTitleSize(att.m_axisTitleSize);
  h->GetYaxis()->SetTitleSize(att.m_axisTitleSize);
  h->GetXaxis()->SetTitleOffset(att.m_xTitleOffset);
  h->GetYaxis()->SetTitleOffset(att.m_yTitleOffset);

  if(att.m_canRebin) h->SetBit(TH1::kCanRebin); 

  if(TH2F* h2 = dynamic_cast<TH2F*>(h)) {
    if (att.m_use2DStat) {
      h2->SetStats(kTRUE);
    } else {
      h2->SetStats(kFALSE);
    }
  }
}

void TestReport::setGraphParameters(TGraph* h, const GraphAttribute& att)
{
  assert(h != 0);

  h->GetXaxis()->SetTitle(att.m_xTitle.c_str());
  h->GetYaxis()->SetTitle(att.m_yTitle.c_str());
  h->SetTitle("");
  h->GetXaxis()->SetLabelSize(att.m_axisLabelSize);
  h->GetYaxis()->SetLabelSize(att.m_axisLabelSize);
  h->GetXaxis()->SetTitleSize(att.m_axisTitleSize);
  h->GetYaxis()->SetTitleSize(att.m_axisTitleSize);
  h->GetXaxis()->SetTitleOffset(att.m_xTitleOffset);
  h->GetYaxis()->SetTitleOffset(att.m_yTitleOffset);

  h->SetMarkerSize(att.m_markerSize);
}


UShort_t TestReport::getGemId(UInt_t id) {
  UInt_t face = id / 100;
  UInt_t row = (id % 100 ) / 10;
  UInt_t col = (id % 10 );
  switch ( face ) {
  case 0:  return 64 + 5*row + col;  // top:      64 - 89
  case 1:  return 32 + 5*row + col;  // -x side:  32 - 47
  case 2:  return      5*row + col;  // -y side    0 - 15
  case 3:  return 48 + 5*row + col;  // +x side   48 - 63
  case 4:  return 16 + 5*row + col;  // +y side   16 - 31
  case 5:                                   // x ribbons 96 - 99
    return 96 + col;
  case 6:                                   // y ribbons 100- 103
    return 100 + col;
  }
  return 0xFFFF;
}

void TestReport::analyzeTrees(const char* mcFileName="mc.root",
			      const char* digiFileName="digi.root",
			      const char* reconFileName="recon.root")
{
  //open 3 root files

  if(mcFileName) m_mcFile = new TFile(mcFileName, "READ");
  // check whether file exists
  if(m_mcFile && m_mcFile->IsZombie()) m_mcFile = 0;
  if(m_mcFile) {
    m_mcTree = (TTree*) m_mcFile->Get("Mc");
    m_mcEvent = 0;  
    m_mcBranch = m_mcTree->GetBranch("McEvent");
    // what is stored in the root tree is actually a pointer rather than
    // mc event
    m_mcBranch->SetAddress(&m_mcEvent);
  }

  if(reconFileName) m_reconFile = new TFile(reconFileName, "READ");
  if(m_reconFile && m_reconFile->IsZombie()) m_reconFile = 0;
  if(m_reconFile) {
    m_reconTree = (TTree*) m_reconFile->Get("Recon");
    m_reconEvent = 0;
    m_reconBranch = m_reconTree->GetBranch("ReconEvent");
    m_reconBranch->SetAddress(&m_reconEvent);
  }

  if(digiFileName) m_digiFile = new TFile(digiFileName, "READ");
  if(m_digiFile && m_digiFile->IsZombie()) m_digiFile = 0;
  if(m_digiFile) {
    m_digiTree = (TTree*) m_digiFile->Get("Digi");
    m_digiEvent = 0;
    m_digiBranch = m_digiTree->GetBranch("DigiEvent");
    m_digiBranch->SetAddress(&m_digiEvent);
  }

  int nMc, nRecon, nDigi;
  if(m_mcFile) {
    nMc = (int) m_mcTree->GetEntries();
    std::cout << "No of events in " << mcFileName << " : " << nMc << endl;
    m_nEvent = nMc;
  }
  if(m_reconFile) {
    nRecon = (int) m_reconTree->GetEntries();
    std::cout << "No of events in " << reconFileName << " : " << nRecon << endl;
    m_nEvent = nRecon;
  }
  if(m_digiFile) {
    nDigi = (int) m_digiTree->GetEntries();
    std::cout << "No of events in " << digiFileName << " : " << nDigi << endl;
    m_nEvent = nDigi;
  }

  // For testing:
  //int nEvent = 1000;
  //m_nEvent = nEvent;

  // For GEM discarded events:
  int previousGemDiscarded = 0;

  for(int iEvent = 0; iEvent != m_nEvent; ++iEvent) {

    if ( iEvent % 1000 == 0 ) {
      cout << iEvent << endl;
    }

    if(m_mcEvent) m_mcEvent->Clear();
    if(m_digiEvent) m_digiEvent->Clear();
    if(m_reconEvent) m_reconEvent->Clear();

    if(m_mcFile) {
      m_mcBranch->GetEntry(iEvent);
      analyzeMcTree();
    }

    if(m_digiFile) {
      m_digiBranch->GetEntry(iEvent);

      analyzeDigiTree();


      // GEM discarded events:
      int thisGemDiscarded = m_digiEvent->getGem().getDiscarded();

      int thisGemDeltaEventTime       = m_digiEvent->getGem().getDeltaEventTime();
      int thisGemWDeltaWindowOpenTime = m_digiEvent->getGem().getDeltaWindowOpenTime();

      if (iEvent > 0) {
        // Gem discarded delta wrt the previous event:
        float delta = thisGemDiscarded - previousGemDiscarded;
        m_gemDiscarded->Fill(delta);

        // Fill time histo for non-saturated events:
        if (thisGemWDeltaWindowOpenTime<65500 && thisGemDeltaEventTime<65500) {

          // Get time quantity we want to look at:
          int deltaTime = thisGemDeltaEventTime - thisGemWDeltaWindowOpenTime;

          // Fill histogram:
          m_gemDiscardedTime->Fill(deltaTime);
        }
      }
      previousGemDiscarded = thisGemDiscarded;


      UInt_t uPpcT = m_digiEvent->getEbfUpperPpcTimeBase();
      UInt_t lPpcT = m_digiEvent->getEbfLowerPpcTimeBase();
      static UInt_t prevUPpcT = uPpcT;
      static UInt_t prevLPpcT = lPpcT;

 
      //     cout << "uPpcT = " << uPpcT << " lPpcT = " << lPpcT
      //      << " good = " << m_digiEvent->getEventSummaryData().goodEvent()
      //   << endl;

      //
      // Time from Mission elapsed time to Unix time and then from PDT to GMT:
      //
      int deltaTimeUgly = 978307200 + 25200; 

      if(iEvent == 0) {
        if (m_isLATTE == 1) {
	  m_startTime = m_digiEvent->getEbfTimeSec();
        } else {
          m_startTime = m_digiEvent->getTimeStamp() + deltaTimeUgly;
	}
      else {
	// convert 16 MHZ clock to ms
	
	assert(uPpcT >= prevUPpcT);

	double interval;

// note a long can only hold 32 bit
	static const long temp = 256*256*256*255;

	if(lPpcT < prevLPpcT) { // roll over
	  interval = double(uPpcT - prevUPpcT - 1) * 268435.456 + 
	  double(temp - prevLPpcT + lPpcT + 256*256*256) / 16000.;
	}
	else {
	  interval = double(uPpcT - prevUPpcT) * 268435.456 + 
	    double_t(lPpcT - prevLPpcT) / 16000.;
	}

	//if ( interval < 500. ) {
	  m_timeInterval->Fill(interval);
	  //}
        if ( interval < 1. ) {
 	  m_timeIntervalCut->Fill(interval);
	}
	prevUPpcT = uPpcT;
	prevLPpcT = lPpcT;
      }

      if(iEvent == m_nEvent-1) {
        if (m_isLATTE == 1) { 
	  m_endTime = m_digiEvent->getEbfTimeSec();
	} else {
          m_endTime = m_digiEvent->getTimeStamp() + deltaTimeUgly;
	}
      }
    }

    if(m_reconFile) {
      m_reconBranch->GetEntry(iEvent);
      analyzeReconTree();
    }

  }  
  
  if(m_mcFile) m_mcFile->Close();
  if(m_reconFile) m_reconFile->Close();
  if(m_digiFile) m_digiFile->Close();
}

void TestReport::analyzeReconTree()
{
  TkrRecon* tkrRecon = m_reconEvent->getTkrRecon();

  bool tkrReconSucceed = false;
  bool muonThroughCal = false;
 
  TVector3 pos, dir;

  Int_t nTk = 0;

  if(tkrRecon) {
    nTk = tkrRecon->getTrackCol()->GetLast()+1;
    m_nTkrTrack->Fill(tkrRecon->getTrackCol()->GetLast()+1);

    TObjArray* vertices = tkrRecon->getVertexCol();
    if(tkrRecon->getVertexCol()->GetLast() >= 0) {
      tkrReconSucceed = true;
      TkrVertex* tkrVertex = dynamic_cast<TkrVertex*>(vertices->At(0));
      if(tkrVertex) {
	pos = tkrVertex->getPosition();
	dir = tkrVertex->getDirection();
	m_reconDirXY->Fill(dir.X(), dir.Y());
	m_reconDirZ->Fill(dir.Z());
	m_reconPosXY->Fill(pos.X(), pos.Y());
	m_reconPosZ->Fill(pos.Z());
	m_reconEne->Fill(tkrVertex->getEnergy());
      }
    }
  }

  CalRecon* calRecon = m_reconEvent->getCalRecon();

  TVector3 calPos;

  if(calRecon) {

    TObjArray* calClusterCol = calRecon->getCalClusterCol();
    if(calClusterCol) {
      // currently there is just one cluster in CAL
      CalCluster* calCluster = dynamic_cast<CalCluster*>(calClusterCol->At(0));
      if(calCluster) {
	if(calCluster->getParams().getEnergy() > 50)  muonThroughCal = true;
	m_calSumEne->Fill(calCluster->getParams().getEnergy());
	calPos = calCluster->getParams().getCentroid();
      }
    }

    //condition variables to indicate whether a CAL layer had nonzero energy
    bool hasEne[g_nTower][g_nCalLayer];
    bzero(hasEne, g_nTower*g_nCalLayer*sizeof(bool));

    TObjArray* calXtalCol = calRecon->getCalXtalRecCol();
    if(calXtalCol) {
      for(int i = 0; i <= calXtalCol->GetLast(); ++i) {
	if(CalXtalRecData* p = 
	   dynamic_cast<CalXtalRecData*>(calXtalCol->At(i))) {
	  CalXtalId id = p->getPackedId();
	  int tower = id.getTower();
	  int layer = id.getLayer();
	  m_calEneLayer[tower][layer] += p->getEnergy();
	  hasEne[tower][layer] = 1;
	}
      }

      for(int i = 0; i != g_nTower; ++i) {
	for(int j = 0; j != g_nCalLayer; ++j) {
	  if(hasEne[i][j]) ++m_nCalEneLayer[i][j];
	}
      }
    }
  }

  if(tkrReconSucceed && muonThroughCal) {

    double x = dir.x()/dir.z()*(calPos.z()-pos.z()) + pos.x();
    double y = dir.y()/dir.z()*(calPos.z()-pos.z()) + pos.y();
    double distance = sqrt((x-calPos.x())*(x-calPos.x()) + (y-calPos.y())*(y-calPos.y()));

    m_alignCalTkr->Fill(distance);
  }

  AcdRecon* acdRecon = m_reconEvent->getAcdRecon();
  if ( acdRecon && nTk == 1) {
    UInt_t nAcdInter = acdRecon->nAcdIntersections();
    for ( UInt_t iAcdInter(0); iAcdInter < nAcdInter; iAcdInter++ ) {
      const AcdTkrIntersection* acdInter = acdRecon->getAcdTkrIntersection(iAcdInter);
      if ( acdInter->getTrackIndex() != 0 ) continue;
      if ( acdInter->getArcLengthToIntersection() < 0 ) continue;
      UShort_t acdGemId = getGemId( acdInter->getTileId().getId() );
      if ( acdInter->tileHit() ) {
	m_AcdEfficMap->Fill( acdGemId );
      } else {
	m_AcdInEfficMap->Fill( acdGemId );
	const TVector3& missPos = acdInter->getGlobalPosition();
	UInt_t face = acdInter->getTileId().getFace();
	switch ( face ) {
	case 0:
	  m_AcdMissMapTop->Fill( missPos.X(), missPos.Y() );
	  break;
	case 1:
	  m_AcdMissMapMinusX->Fill( missPos.Y(), missPos.Z() );
	  break;
	case 2: 
	  m_AcdMissMapMinusY->Fill( missPos.X(), missPos.Z() );
	  break;
	case 3:
	  m_AcdMissMapPlusX->Fill( missPos.Y(), missPos.Z() );
	  break;
	case 4: 
	  m_AcdMissMapPlusY->Fill( missPos.X(), missPos.Z() );
	  break;
	}
      }
    }
  }
}


void TestReport::analyzeDigiTree()
{
  unsigned int word = m_digiEvent->getL1T().getTriggerWord();
  unsigned bitMask = 0;
  int ibit = enums::number_of_trigger_bits;
  while(ibit--) { bitMask |= 1<<ibit; }
  int trigger = word & bitMask;
  m_trigger->Fill(trigger);
  for(int i = 0; i != enums::number_of_trigger_bits; ++i) {
    if( (trigger >> i) & 1) ++m_nEvtGltTrigger[i];
  }

  // LATTE run?
  m_isLATTE = 0;
  if (m_digiEvent->getEventSummaryData().oswLength() > 0) m_isLATTE = 1;

  if(m_digiEvent->getEventSummaryData().badEvent()) ++m_nBadEvts;

  if (m_digiEvent->getEventSummaryData().packetError())       ++m_nPacketErrors;
  if (m_digiEvent->getEventSummaryData().trgParityError())    ++m_nTrgParityErrors;
  if (m_digiEvent->getEventSummaryData().errorEventSummary()) ++m_nTemErrors;

  int cond = m_digiEvent->getGem().getConditionSummary();
  m_condSummary->Fill(cond);
  for(int i = 0; i != enums::GEM_offset; ++i) {
    if( (cond >> i) & 1) {
      ++m_nEvtGemTrigger[i];
    }
  }

  // Triggers per tower:
  for (int i = 0; i != g_nTower; ++i) {
    m_tkrPerTowerArray[i]   = 0;
    m_calLoPerTowerArray[i] = 0;
    m_calHiPerTowerArray[i] = 0;
  }

  int gemTkrVector   = m_digiEvent->getGem().getTkrVector();
  int gemCalLoVector = m_digiEvent->getGem().getCalLeVector();
  int gemCalHiVector = m_digiEvent->getGem().getCalHeVector();

  for (int i = 0; i != g_nTower; ++i) {
    if ((gemTkrVector >> i)   & 1 ) ++m_tkrPerTowerArray[i];
    if ((gemCalLoVector >> i) & 1 ) ++m_calLoPerTowerArray[i];
    if ((gemCalHiVector >> i) & 1 ) ++m_calHiPerTowerArray[i];
  }
  for (int i = 0; i != g_nTower; ++i) {
    if (m_tkrPerTowerArray[i] > 0) {
      m_tkrPerTower->Fill(i);
    }
    if (m_calLoPerTowerArray[i] > 0) {
      m_calLoPerTower->Fill(i);
    }
    if (m_calHiPerTowerArray[i] > 0) {
      m_calHiPerTower->Fill(i);
    }
  }


  // 1 count = 50 ns
  UInt_t deltaT = m_digiEvent->getGem().getDeltaEventTime();
  m_timeIntervalGem->Fill(0.00005*deltaT);

  if ((0.00005*deltaT) < 1.0) {
    m_timeIntervalGemZoom->Fill(0.00005*deltaT);
  }

  int tkrVector = m_digiEvent->getGem().getTkrVector();

  // 3 in a row TKR trigger
  bool tkrTrigger;
  if(cond & 2) {
    ++m_nTkrTrigger;
    tkrTrigger = true;

    for(int i = 0; i != g_nTower; ++i) {
      if( (tkrVector >> i) & 1 ) ++m_nTkrEvent[i];
    }
  }
  else {
    tkrTrigger = false;
  }

  int nTkrDigis = m_digiEvent->getTkrDigiCol()->GetLast()+1;

  int nHit[g_nTower], nPlane[g_nTower], nDigi[g_nTower];
  for(int i = 0; i != g_nTower; ++i) {
    nHit[i] = 0;
    nPlane[i] = 0;
    nDigi[i] = 0;
  }

  bool badStrip = false, moreStrip = false;
  bool satTot = false, zeroTot = false, badTot = false;

  for(int i = 0; i != nTkrDigis; ++i) {

    const TkrDigi* tkrDigi = m_digiEvent->getTkrDigi(i);
    assert(tkrDigi != 0); 

    int tower = tkrDigi->getTower().id();
    int biLayer = tkrDigi->getBilayer();
    GlastAxis::axis view = tkrDigi->getView();
    int iView = (view == GlastAxis::X) ? 0 : 1;
    int plane = Geo::instance()->getPlane(biLayer, iView);

    ++nDigi[tower];

    ++nPlane[tower];

    nHit[tower] += tkrDigi->getNumHits();

    m_nHitPlane[tower][plane] += tkrDigi->getNumHits();
    if(m_nHitPlane[tower][plane] > 0) ++m_nEvtPlane[tower][plane];

    int lowCount = 0, highCount = 0;
    int nStrips = tkrDigi->getNumHits();

    int lastController0Strip = tkrDigi->getLastController0Strip();

    for(int i = 0; i != nStrips; ++i) {
      int stripId = tkrDigi->getStrip(i);

      if(stripId < 0 || stripId >= g_nStrip) {
	badStrip = true;
      }
      else { 
	(stripId<=lastController0Strip) ? ++lowCount : ++highCount;
      }
    }

    if(lowCount > 0) ++m_nEvtHitPlane[tower][plane][0];
    if(highCount > 0) ++m_nEvtHitPlane[tower][plane][1];

    if(lowCount > 64 || highCount > 64) {
      moreStrip = true;
    }

    int tot0 = tkrDigi->getToT(0);
    int tot1 = tkrDigi->getToT(1);

    if((tot0>0 && lowCount==0)|| (tot1>0 && highCount==0)) badTot = true;
    if((tot0==0 && lowCount>0)|| (tot1==0 && highCount>0)) zeroTot = true;
    
    if (tot0<0 || tot0>g_overlapTot || tot1<0 || tot1>g_overlapTot) ++m_nEvtInvalidTot; 
    if (tot0>g_satTot && tot0!=g_overlapTot) ++m_nEvtInvalidTot; 
    if (tot1>g_satTot && tot1!=g_overlapTot) ++m_nEvtInvalidTot; 

    if(tot0==g_satTot || tot1==g_satTot) ++m_nEvtOverlapTriggerTot; 

    if(tot0 == 0){
      m_totZero2D->Fill(plane+0.25, tower, 1./m_nEvent);
      if(lowCount > 0) m_totNoise2D->Fill(plane+0.25, tower);
    }
    if(tot1 == 0){
      m_totZero2D->Fill(plane+0.75, tower, 1./m_nEvent);
      if(highCount > 0) m_totNoise2D->Fill(plane+0.75, tower);
    }

    if(tot0 == g_satTot){
      satTot = true;
      m_totSat2D->Fill(plane+0.25, tower);
    }
    if(tot1 == g_satTot){
      satTot = true;
      m_totSat2D->Fill(plane+0.75, tower);
    }

    if(tot0>0 && tot0<g_satTot) {
      m_tot[tower][plane][0]->Fill(tot0);
    }
    if(tot1>0 && tot1<g_satTot) {
      m_tot[tower][plane][1]->Fill(tot1);
    }

  }

  if(badStrip) ++m_nEventBadStrip;
  if(moreStrip) ++m_nEventMoreStrip;
  if(badTot) ++m_nEventBadTot;
  if(zeroTot) ++m_nEventZeroTot;
  if(satTot) ++m_nEventSatTot;

  int maxNDigi = 0;
  for(int i = 0; i != g_nTower; ++i) {
    m_nHit[i]->Fill(nHit[i]);
    m_nLayer[i]->Fill(nPlane[i]);
    if(nDigi[i] > maxNDigi) maxNDigi = nDigi[i];
    if( ((tkrVector >> i) & 1) && nDigi[i] < 6) ++m_nTkrBadEvent[i];
  }

  if(tkrTrigger) {
    (maxNDigi >= 6) ? ++m_nEventDigi[6] : ++m_nEventDigi[maxNDigi];
  }

  // condition variables to indicate whether a particular layer has any hits
  int isHit[g_nTower][g_nCalLayer];
  bzero(isHit, g_nTower*g_nCalLayer*sizeof(int));

  //  int nCalDigis = m_digiEvent->getCalDigiCol()->GetLast()+1;
  const TClonesArray* calDigiCol = m_digiEvent->getCalDigiCol();
  for(int i = 0; i <= calDigiCol->GetLast(); ++i) {
    if(CalDigi* p = dynamic_cast<CalDigi*>(calDigiCol->At(i))) {
      int tower = p->getPackedId().getTower();
      int layer = p->getPackedId().getLayer();

      ++m_nCalHit[tower][layer];
      isHit[tower][layer] = 1;
    }
  }

  for(int i = 0; i != g_nTower; ++i) {
    for(int j = 0; j != g_nCalLayer; ++j) {
      if(isHit[i][j]) ++m_nEvtCalHit[i][j];
    }
  }


  //
  // ACD digis:
  //
  int tmpAcdOddParityError    = 0;
  int tmpAcdHeaderParityError = 0;

  const TObjArray* acdDigiCol = m_digiEvent->getAcdDigiCol();
  assert(acdDigiCol != 0);

  int nAcdDigis = acdDigiCol->GetLast()+1;
  m_nAcdDigis->Fill(nAcdDigis);

  for(int iDigi = 0; iDigi != nAcdDigis; ++iDigi) {

    const AcdDigi* acdDigi = dynamic_cast<const AcdDigi*>(acdDigiCol->At(iDigi));
    assert(acdDigi != 0);

    int AcdGemID = getGemId ( acdDigi->getId().getId() );

    // add to hit map
    m_AcdHitMap->Fill(AcdGemID);

    // Get the hit map & veto flags
    Bool_t hitPmtA = acdDigi->getLowDiscrim(AcdDigi::A);
    Bool_t hitPmtB = acdDigi->getLowDiscrim(AcdDigi::B);
    Bool_t singlePmt = (hitPmtA && ! hitPmtB) || (!hitPmtA && hitPmtB);
    Bool_t vetoA = acdDigi->getVeto(AcdDigi::A);
    Bool_t vetoB = acdDigi->getVeto(AcdDigi::B);
    Bool_t singleVeto = (vetoA && !vetoB) || (!vetoA && vetoB);

    if ( singlePmt ) m_AcdTileIdOnePMT->Fill(AcdGemID);
    if ( singleVeto ) m_AcdTileIdOneVeto->Fill(AcdGemID);
    if ( vetoA || vetoB ) m_AcdVetoMap->Fill(AcdGemID);

    if (acdDigi->getRange(AcdDigi::A) == 0 ) m_AcdPhaMapA->Fill(AcdGemID, acdDigi->getPulseHeight(AcdDigi::A) );
    if (acdDigi->getRange(AcdDigi::B) == 0 ) m_AcdPhaMapB->Fill(AcdGemID, acdDigi->getPulseHeight(AcdDigi::B) );      
    
    if (acdDigi->getOddParityError(AcdDigi::A)) ++tmpAcdOddParityError;
    if (acdDigi->getOddParityError(AcdDigi::B)) ++tmpAcdOddParityError;

    if (acdDigi->getHeaderParityError(AcdDigi::A)) ++tmpAcdHeaderParityError;
    if (acdDigi->getHeaderParityError(AcdDigi::B)) ++tmpAcdHeaderParityError;
  }

  if (tmpAcdOddParityError)    ++m_nAcdOddParityError;
  if (tmpAcdHeaderParityError) ++m_nAcdHeaderParityError;

}

void TestReport::generateReport()
{
  writeHeader();

  (*m_report) << "@section purpose Purpose" << endl;
  (*m_report) << "This report is used in offline data analyses to identify apparent problems in cosmic ray muon and VDG data. <b>Warning! Results from other tests(such as charge injection) should be interpreted with care.</b>" << endl;

  (*m_report) << "@section version Software Version" << endl;
  (*m_report) << "@li EngineeringModel: @b " << m_emVersion << endl;
  (*m_report) << "@li TestReport: @b " << m_version << endl;
  /*
  (*m_report) << "@section calibversion Serial no. of calibration constants (-9999 means no constants were used.)" << endl;
  (*m_report) << "@li TKR: @b " << m_tkrCalibSerNo << endl;
  (*m_report) << "@li CAL: @b " << m_calCalibSerNo << endl;
  */
  (*m_report) << "@section summary Summary" << endl;
  if(m_nEvent == 0) {
    (*m_report) << "<b> There are no events in this run! </b>" << endl;
    return;
  } 

  (*m_report) << "In the digi file @em " << m_digiFile->GetName() << endl;

  if (m_isLATTE == 1) {
    (*m_report) << "@li There are @b " << m_nEvent << " triggers. This run was taken with LATTE so there will be " << m_nEvent+2 << " events recorded in the eLog database since LATTE adds two additional events in the process which are not triggered events." << endl;
  } else {
    (*m_report) << "@li There are @b " << m_nEvent << " triggers." << endl;
  }

  (*m_report) << "@li There are @b " << m_nBadEvts << " bad events " << endl;

  (*m_report) << "@li There are @b " << m_nTrgParityErrors << " events with Trigger Parity errors " << endl;
  (*m_report) << "@li There are @b " << m_nPacketErrors << " events with Packet errors " << endl;
  (*m_report) << "@li There are @b " << m_nTemErrors << " events with TEM errors " << endl;

  (*m_report) << "@li There are @b " << m_nAcdOddParityError    << " events with ACD Odd Parity errors " << endl;
  (*m_report) << "@li There are @b " << m_nAcdHeaderParityError << " events with ACD 'Header Parity errors'.  (Should always be zero)." << endl;

  (*m_report) << "@li Time of the first trigger: <b>" << ctime((time_t*) (&m_startTime)) << " (GMT) </b>";
  (*m_report) << "@li Time of the last trigger: <b>" << ctime((time_t*) (&m_endTime)) << " (GMT) </b>";
  (*m_report) << "@li Duration: <b>" << m_endTime - m_startTime << " seconds" << "</b>" << endl;
  (*m_report) << "@li Rate: <b>" << double(m_nEvent)/(m_endTime - m_startTime) << " hz" << "</b>" << endl;

  if(m_reconFile) {
    (*m_report) << "<p>The Recon file is: @em " << m_reconFile->GetName() << "</p>" << endl;
    generateReconReport();
  }

  if(m_digiFile) generateDigiReport();
 
  writeTail(); 
}

void TestReport::generateDigiReport()
{
  (*m_report) << "@section trigger Trigger" << endl;

  // print condition summary plots
  string file = m_prefix;
  file += "_condSummary";
  PlotAttribute att(file.c_str(), "GEM condition summary word. The word is deduced by combining bit patterns from the table shown below. For example, an event with both the TKR trigger bit and the CAL low trigger bit set in GEM has the condition summary word of @latex $2^{2} + 2^{1} = 6$ @endlatex @html 2<sup>2</sup> + 2<sup>1</sup> = 6 @endhtml", "condSummary", 1);
  producePlot(m_condSummary, att);
  insertPlot(att);
  *(m_report) << "@latexonly \\nopagebreak @endlatexonly" << endl;
  printCondSummaryTable();

  // print trigger plots
  file = m_prefix;
  file += "_trigger";
  att.set(file.c_str(), "Trigger word calculated by triggerAlg. The word is deduced by combining bit patterns from the table shown below. For example, an event with both the TKR trigger bit and the CAL Low trigger bit set has the GLT word of @latex $2^{1} + 2^{2} = 6$ @endlatex @html 2<sup>1</sup> + 2<sup>2</sup> = 6 @endhtml.", "trigger", 1);
  producePlot(m_trigger, att);
  insertPlot(att);
  *(m_report) << "@latexonly \\nopagebreak @endlatexonly" << endl;
  printGltTriggerTable();

  // Trigger per tower:
  produceTriggerPerTowerPlot();

  // GEM discarded events:
  (*m_report) << "@section gemDiscarded GEM Discarded Events" << endl;
  produceGemDiscardedPlot();

  (*m_report) << "@section timeInfo Time Info" << endl;

  if (m_isLATTE == 1) {
    produceTimeIntervalPlotSBC();
  }
  produceTimeIntervalPlotGEM();


  (*m_report) << "@section tkrDigi TKR Digitization" << endl;

  *(m_report) << "@subsection nDigi nDigi" << endl;
  *(m_report) << "@latexonly \\nopagebreak @endlatexonly" << endl;
  printNDigiTable();
  *(m_report) << "@latexonly \\nopagebreak @endlatexonly" << endl;
  printNDigiTowerTable();
  *(m_report) << "@latexonly \\pagebreak @endlatexonly" << endl;
  *(m_report) << "@latexonly \\pagebreak @endlatexonly" << endl;

  (*m_report) << "@subsection strip_hit Strip Hit Info" << endl;
  *(m_report) << "@latexonly \\nopagebreak @endlatexonly" << endl;
  *(m_report) << "@li There are @b " << ToString(m_nEventBadStrip) << " events with strip ID either outside the physical range from 0 to 1535 or outside the range read by the GTRCs." << endl;

  *(m_report) << "@li There are @b " << ToString(m_nEventMoreStrip) << " events with more than 64 strips per GTRC. ";

  *(m_report) << endl << endl;
  
  produceNhits2DPlot();

  //  produceDigiPlot();

  // produce plots for nhits distribution for 16 towers
  file = m_prefix;
  file += "_hitsPerTower_1";
  att.set(file.c_str(), "Number of strip hits in a tower(for tower 0 to tower 7).", "hitsPerTower_1", 1, 0, 18, 18, 909, 615);
  producePlot((TObject**) m_nHit, att, 4, 2);
  insertPlot(att);

  file = m_prefix;
  file += "_hitsPerTower_2";
  att.set(file.c_str(), "Number of strip hits in a tower(for tower 8 to tower 15.", "hitsPerTower_2", 1, 0, 18, 18, 909, 615);
  producePlot((TObject**) m_nHit+8, att, 4, 2);
  insertPlot(att);

  produceNHitPlane2DPlot();

  // produce plots for nLayer distribution

  file = m_prefix;
  file += "_layersPerTower_1";
  att.set(file.c_str(), "Number of planes that are hit in a tower(for tower 0 to tower 7).", "layersPerTower_1", 1, 0, 18, 18, 909, 615, 111);
  producePlot((TObject**) m_nLayer, att, 4, 2);
  insertPlot(att);

  file = m_prefix;
  file += "_layersPerTower_2";
  att.set(file.c_str(), "Number of planes that are hit in a tower(for tower 8 to tower 15).", "layersPerTower_1", 1, 0, 18, 18, 909, 615, 111);
  producePlot((TObject**) m_nLayer+8, att, 4, 2);
  insertPlot(att);

  *(m_report) << "@latexonly \\pagebreak @endlatexonly" << endl;
  *(m_report) << "@subsection totInfo Time Over Threshold (TOT) information" << endl;
  *(m_report) << "@latexonly \\nopagebreak @endlatexonly" << endl;
  *(m_report) << "@li Fraction of events with saturated TOT value of " << g_satTot << " counts(1 count = 200ns): @b " << ToString(m_nEventSatTot/double(m_nEvent)) << endl;
  *(m_report) << "@li Fraction of events with overlapped triggers i.e. TOT value of " << g_overlapTot << " counts(1 count = 200ns): @b " << ToString(m_nEvtOverlapTriggerTot/double(m_nEvent)) << endl;
  *(m_report) << "@li Fraction of events with invalid TOT (outside the range [0, " << g_satTot << "] and != g_overlapTot): @b " << ToString(m_nEvtInvalidTot/double(m_nEvent)) << endl;
  *(m_report) << "@li Fraction of events with TOT==0 and nStrip!=0 for each Si plane: @b " << ToString(m_nEventZeroTot/double(m_nEvent)) << endl;
  *(m_report) << "@li Fraction of events with TOT!=0 and nStrip==0 for each Si plane: @b " << ToString(m_nEventBadTot/double(m_nEvent)) << endl;

  // TOT plots
  produceTotNoise2DPlot();

  produceZeroSatTot2DPlot();

  produceAveTot2DPlot();
  //  produceAveTotPlots();

  (*m_report) << "@section calDigi CAL Digitization" << endl;

  produceCalNhits2DPlot();

  // ACD digis:
  (*m_report) << "@section acdDigi ACD Digitization" << endl;

  produceAcdDigiPlots();

}

void TestReport::generateReconReport()
{
  (*m_report) << "@section tkrRecon TKR Reconstruction" << endl;

  // print reconstructed track plots
  string file(m_prefix);
  file += "_nTkrTrack";
  PlotAttribute att(file.c_str(), "Number of reconstructed tracks for all trigger types. This data is obtained from track collections stored in the TkrRecon class.", "nTkrTrack", 1);
  producePlot(m_nTkrTrack, att);
  insertPlot(att);

  printNTrackTable();

  produceReconDirPlots();

  produceReconPosPlots();

  //  produceReconEnePlots();

  (*m_report) << "@section calRecon CAL Reconstruction" << endl;

  produceCalEneSum2DPlot();

  produceCalEneLayer2DPlot();

  (*m_report) << "@section align Alignment between TKR and CAL Reconstruction" << endl;

  produceAlignCalTkrPlot();

  (*m_report) << "@section acdTkrRecon Track extrapolation to ACD" << endl;

  produceAcdTkrReconPlots();

}

void TestReport::writeHeader()
{
  *(m_report) << "/** @mainpage SVAC Report" << endl
	      << "@htmlonly" << endl
	      << "<center>" << endl
	      << "<a href=\"../latex/refman.ps\"> PS file </a> &nbsp" << endl
	      << "<a href=\"../latex/refman.pdf\"> PDF file </a>" << endl 
	      << "</center>" << endl
	      << "@endhtmlonly" << endl
	      << "@author{automatically generated}" << endl << endl;
}

void TestReport::writeTail()
{
  *(m_report) << "*/" << endl;
}


void TestReport::producePlot(TObject* h, const PlotAttribute& att)
{
  TCanvas c1("c1", "produce eps file", att.m_xPixel, att.m_yPixel);
  gPad->SetBorderMode(0);
  gPad->SetFillColor(10);

  //set to default values
  gStyle->SetTitleH();
  gStyle->SetTitleW();
  gStyle->SetTitleFontSize();
  gStyle->SetStatW(0.2);
  gStyle->SetStatH(0.16);
  gStyle->SetStatX(1.0);
  gStyle->SetStatY(1.0);
  gStyle->SetPalette();

  if(att.m_yLog) gPad->SetLogy();
  if(att.m_zLog) {
    cout << "set logz" << endl;
    gPad->SetLogz();
  }

  Double_t minY(0.);
  Double_t maxY(0.);

  if(TGraph* gr = dynamic_cast<TGraph*>(h)) {
    gr->Draw("A*");
  }
  else if(TH2F* h2 = dynamic_cast<TH2F*>(h)) {
    if(att.m_2dPlotType == PlotAttribute::LEGO) {
      h2->Draw("LEGO");
    }
    else {
      gStyle->SetPalette(1);
      //      gStyle->SetPalette(att.m_nColor, (int*) att.m_colors);
      gPad->SetRightMargin(0.15);
      // 
      if (att.m_statBox) {
        gStyle->SetStatW(0.15);
        gStyle->SetStatH(0.12);
        gStyle->SetStatX(0.84);
        gStyle->SetStatY(0.99);
      }
      gStyle->SetOptStat(att.m_statMode);
      //
      h2->Draw("COLZ");
      minY = h2->GetYaxis()->GetXmin();
      maxY = h2->GetYaxis()->GetXmax();
    }
  }
  else{
    TH1* h1 = dynamic_cast<TH1*>(h);
    if ( h1 != 0 ) {
      minY = h1->GetMinimum();
      maxY = h1->GetMaximum();
    }
    gStyle->SetOptStat(att.m_statMode);
    h->Draw();
  }

  // For some of TKR plots, draw additional lines and texts to distinguish
  // among no converter, thin converter and thick converter.

  // For unknown reasons, the following variables must be outside the if
  // scope in order for lines and texts to be drawn on the canvas  
  TLine l1(3.5, 15.5, 3.5, 16);
  TLatex tex1(-0.5, 15.6, "no W");
  TLine l2(11.5, 15.5, 11.5, 16);
  TLatex tex2(5, 15.6, "thick W");
  TLatex tex3(20, 15.6, "thin W");

  if(h == m_nHit2D || h == m_nZeroHit2D) {
    l1.Draw();
    tex1.Draw();
    l2.Draw();
    tex2.Draw();
    tex3.Draw();
  }


  // For all of the ACD Gem ID plots, draw additional lines and texts to distinguish
  // among top & sides

  // Because of the memory management of TLine reasons, the following variables must be outside the if
  // scope in order for lines and texts to be drawn on the canvas  
    
  TLine lAcd1(15.5,minY,15.5,maxY);
  TLine lAcd2(31.5,minY,31.5,maxY);
  TLine lAcd3(47.5,minY,47.5,maxY);
  TLine lAcd4(63.5,minY,63.5,maxY);
  TLine lAcd5(88.5,minY,88.5,maxY);
  TLine lAcd6(95.5,minY,95.5,maxY);
  TLine lAcd7(103.5,minY,103.5,maxY);

  TLatex texAcd1(5, maxY, "-Y");
  TLatex texAcd2(21, maxY, "+Y");
  TLatex texAcd3(37, maxY, "-X");
  TLatex texAcd4(53, maxY, "+X");
  TLatex texAcd5(69, maxY, "TOP");
  TLatex texAcd6(99, maxY, "Rb");  

  if(h == m_AcdTileIdOnePMT ||
     h == m_AcdTileIdOneVeto ||
     h == m_AcdHitMap ||
     h == m_AcdVetoMap ||
     h == m_AcdPhaMapA ||
     h == m_AcdPhaMapB ||
     h == m_AcdInEfficMap ) {
    lAcd1.Draw(); lAcd2.Draw(); lAcd3.Draw(); lAcd4.Draw(); lAcd5.Draw(); lAcd6.Draw(); lAcd7.Draw(); 
    texAcd1.Draw(); texAcd2.Draw(); texAcd3.Draw(); texAcd4.Draw(); texAcd5.Draw(); texAcd6.Draw();
  }

  // FIXME -- should draw the tile edges on the miss maps


  string epsFile(m_dir);
  epsFile += "/";
  epsFile += att.m_file;
  epsFile += ".eps";
  c1.SaveAs(epsFile.c_str());

  // ROOT can not produce gif file in the batch mode
  // run pstopnm and ppmtogif to produce gif file

  string pwd = gSystem->WorkingDirectory();
  gSystem->cd(m_dir.c_str());

  string cmd1("pstopnm -ppm -xborder 0 -yborder 0 -portrait -nocrop -xsize ");
  cmd1 += ToString(att.m_xPixel);
  cmd1 += " -ysize ";
  cmd1 += ToString(att.m_yPixel);
  cmd1 += " ";
  epsFile = att.m_file;
  epsFile += ".eps";
  cmd1 += epsFile;
  gSystem->Exec(cmd1.c_str());

  string ppmFile(epsFile);
  ppmFile += "001.ppm";
  string gifFile(att.m_file);
  gifFile += ".gif";

  string cmd2("ppmtogif ");
  cmd2 += ppmFile;
  cmd2 += " > ";
  cmd2 += gifFile;
  gSystem->Exec(cmd2.c_str());

  gSystem->cd(pwd.c_str());
}

void TestReport::producePlot(TObject** h, const PlotAttribute& att, int nRow, 
			     int nCol)
{
  TCanvas c1("c1", "produce eps file");
  gPad->SetBorderMode(0);
  gPad->SetFillColor(10);
  c1.Divide(nCol, nRow, 0.001, 0.001);

  for(int i = 0; i != nRow*nCol; ++i) {

    //    gStyle->SetTitleH(0.12);
    //    gStyle->SetTitleW(0.2);
    //    gStyle->SetTitleFontSize(4);
    c1.cd(i+1);
    gStyle->SetStatH(0.4);
    gPad->SetBottomMargin(0.05*nRow);

    if(att.m_yLog) gPad->SetLogy();
    if(att.m_zLog) {
      cout << "set logz" << endl;
      gPad->SetLogz();
    }

    if(TGraph* gr = dynamic_cast<TGraph*>(h[i])) {
      gr->Draw("A*");
    }
    else if(TH2F* h2 = dynamic_cast<TH2F*>(h[i])) { 
      h2->Draw("LEGO");
    }
    else if(TH1F* h1 = dynamic_cast<TH1F*>(h[i])){
      gStyle->SetOptStat(att.m_statMode);
      h1->Draw();
    }
  }

  string epsFile(m_dir);
  epsFile += "/";
  epsFile += att.m_file;
  epsFile += ".eps";
  c1.SaveAs(epsFile.c_str());

  // ROOT can not produce gif file in the batch mode
  // run pstopnm and ppmtogif to produce gif file

  string pwd = gSystem->WorkingDirectory();
  gSystem->cd(m_dir.c_str());

  string cmd1("pstopnm -ppm -xborder 0 -yborder 0 -portrait -nocrop -xsize ");
  cmd1 += ToString(att.m_xPixel);
  cmd1 += " -ysize ";
  cmd1 += ToString(att.m_yPixel);
  cmd1 += " ";
  epsFile = att.m_file;
  epsFile += ".eps";
  cmd1 += epsFile;
  gSystem->Exec(cmd1.c_str());

  string ppmFile(epsFile);
  ppmFile += "001.ppm";
  string gifFile(att.m_file);
  gifFile += ".gif";

  string cmd2("ppmtogif ");
  cmd2 += ppmFile;
  cmd2 += " > ";
  cmd2 += gifFile;
  gSystem->Exec(cmd2.c_str());

  gSystem->cd(pwd.c_str());
}

void TestReport::insertPlot(const PlotAttribute& att)
{
  string gifFile(att.m_file);
  gifFile += ".gif";

  *(m_report) << "@htmlonly <div align=\"center\"> <p>"
	      << boldFaceHtml(eraseLatexStr(att.m_caption)) 
	      << "</p> <img src=\"../" 
	      << gifFile << "\" alt=\"../" << gifFile 
	      << "\"> </div> @endhtmlonly" << endl;
 
  string epsFile(att.m_file);
  epsFile += ".eps";

  string cap =  boldFaceLatex(eraseHtmlStr(att.m_caption));
  *(m_report) << "@latexonly \\begin{figure}[H]" << endl
	      << "\\begin{center}" << endl
	      << "\\includegraphics[height=" << att.m_height << "cm,width="
	      << att.m_width << "cm]{" << epsFile << "}\\caption{"
	      << cap << "}" << endl
	      << "\\end{center}" << endl
	      << "\\end{figure}" << endl << "@endlatexonly" << endl;
}

void TestReport::applyDash(string* x, int n) const 
{
  for(int i = 0; i != n; ++i) {

    string s;
    for(const char* p = x[i].c_str(); *p != 0; ++p) {
      if(*p == '_') s += "\\";
      if(*p == '%') s += "\\";
      s += *p;
    }

    x[i] = s;
  }
}      

void TestReport::printHtmlTable(const TableDef& r)
{
  *(m_report) << endl << "@htmlonly" << endl;
  *(m_report) << "<table border=\"1\" width=\"100%\">" << endl;
  *(m_report) << "<caption> " << r.m_caption << " </caption>" << endl;

  for(int i = 0; i != r.m_nRow; ++i) {
    *(m_report) << "  <tr>" << endl;
    for(int j = 0; j != r.m_nCol; ++j) {
      *(m_report) << "    <td> " << r.m_table[i*r.m_nCol+j] 
		  << " </td>" << endl;
    }
    *(m_report) << "  </tr>" << endl;
  }

  *(m_report) << "</table>" << endl;
  *(m_report) << "@endhtmlonly" << endl << endl;
}

void TestReport::printLatexTable(const TableDef& r)
{
  *(m_report) << endl << "@latexonly" << endl;
  *(m_report) << "\\begin{table}[h]" << endl;
  *(m_report) << "\\begin{center}" << endl;
  *(m_report) << "\\caption{" << r.m_caption << "}" << endl;
  *(m_report) << "\\label{" << r.m_label << "}" << endl;

  *(m_report) << "\\begin{tabular}{";
  for(int i = 0; i != r.m_nCol; ++i) {
    *(m_report) << "|c";
  }
  *(m_report) << "|} \\hline" << endl;

  for(int i = 0; i != r.m_nRow; ++i) {
    for(int j = 0; j != r.m_nCol-1; ++j) {
      *(m_report) << r.m_table[i*r.m_nCol+j] << " & ";
    }
    *(m_report) << r.m_table[(i+1)*r.m_nCol-1] << " \\\\ \\hline" << endl;
  }

  *(m_report) << "\\end{tabular}" << endl;
  *(m_report) << "\\end{center}" << endl;
  *(m_report) << "\\end{table}" << endl;
  *(m_report) << "@endlatexonly" << endl << endl;
}

void TestReport::printGltTriggerTable()
{
  int nRow = 3;
  int nCol = enums::number_of_trigger_bits+1;
  string table[nRow][nCol];

  table[0][0] = "Trigger bit";
  for(int i = 1; i != nCol; ++i) {
    table[0][i] = ToString(i-1);
  }
 
  table[1][0] = "Trigger";
  table[1][1] = "ACD Low";
  table[1][2] = "TKR";
  table[1][3] = "CAL Low";
  table[1][4] = "CAL High";
  table[1][5] = "ACD High";
  table[1][6] = "THROTTLE";
  
  table[2][0] = "Number of events";
  for(int i = 1; i != enums::number_of_trigger_bits+1; ++i) {
    table[2][i] = ToString(m_nEvtGltTrigger[i-1]);
  }

  TableDef t((string*) table, "Trigger bits used in TriggerAlg", "gltTriggerTable", nRow, nCol);

  printHtmlTable(t);
  printLatexTable(t);
}

void TestReport::printCondSummaryTable()
{
  int nRow = 3;
  int nCol = enums::GEM_offset+1;
  string table[nRow][nCol];

  table[0][0] = "Trigger bit";
  for(int i = 1; i != nCol; ++i) {
    table[0][i] = ToString(i-1);
  }

  table[1][0] = "Summary";
  table[1][1] = "ROI";
  table[1][2] = "TKR";
  table[1][3] = "CAL Low";
  table[1][4] = "CAL High";
  table[1][5] = "CNO";
  table[1][6] = "Periodic";
  table[1][7] = "Solicited";
  table[1][8] = "External";

  table[2][0] = "Number of events";
  for(int i = 1; i != enums::GEM_offset+1; ++i) {
    table[2][i] = ToString(m_nEvtGemTrigger[i-1]);
  }

  TableDef t((string*) table, "GEM Condition summary word", "condSummaryTable", nRow, nCol);

  printHtmlTable(t);
  printLatexTable(t);
}

void TestReport::printNTrackTable()
{
  TableDef d;

  string caption("Ratio of events with different number of reconstructed TKR tracks.");
  d.m_caption = caption.c_str();
  d.m_label = "nEventDigi";
  d.m_nRow = 2;
  d.m_nCol = 5;

  string table[d.m_nRow][d.m_nCol];
  d.m_table = (string*) table;
  table[0][1] = "0 tracks"; 
  table[0][2] = "1 track"; 
  table[0][3] = "2 tracks";
  table[0][4] = "More than 2 tracks";

  table[1][0] = "Ratio";
  table[1][1] = ToString(m_nTkrTrack->GetBinContent(1)/double(m_nEvent));
  table[1][2] = ToString(m_nTkrTrack->GetBinContent(2)/double(m_nEvent));
  table[1][3] = ToString(m_nTkrTrack->GetBinContent(3)/double(m_nEvent));
  int n = m_nEvent - m_nTkrTrack->GetBinContent(1) - m_nTkrTrack->GetBinContent(2) - m_nTkrTrack->GetBinContent(3);
  table[1][4] = ToString(n/double(m_nEvent));

  printHtmlTable(d);

  printLatexTable(d);
}

void TestReport::printNDigiTable()
{
  if(m_nTkrTrigger == 0) {
    *m_report << "There are no events with TKR trigger from GEM condition summary word. Please check the config report to see whether the GEM is present." << endl;
    return;
  }

  TableDef d;

  string caption("Number of events with different number of TKR digis. There are ");
  caption += ToString(m_nTkrTrigger); 
  caption += " events with 3 in a row TKR trigger in the GEM.";
  d.m_caption = caption.c_str();
  d.m_label = "nEventDigi";

  d.m_nRow = 8;
  d.m_nCol = 3;
  string table[d.m_nRow][d.m_nCol];
  d.m_table = (string*) table;
  table[0][0] = "Number of TKR digis";
  table[0][1] = "Number of TKR events"; 
  table[0][2] = "Ratio";

  for(int i = 1; i != d.m_nRow; ++i) {
    if(i == 7) {
      table[i][0] =  ">= 6";
    }
    else {
      table[i][0] = ToString(i-1);
    }
    table[i][1] = ToString(m_nEventDigi[i-1]);  
    table[i][2] = ToString(float(m_nEventDigi[i-1])/m_nTkrTrigger);
  }

  printHtmlTable(d);

  table[7][0] =  "$\\geq$ 6";
  applyDash((string*) table, d.m_nRow*d.m_nCol);
  printLatexTable(d);
}

void TestReport::printNDigiTowerTable()
{
  if(m_nTkrTrigger == 0) {
    //    *m_report << "There are no events with TKR trigger." << endl;
    return;
  }

  double tower[g_nTower], bad[g_nTower];

  for(int i = 0; i != g_nTower; ++i) {
    tower[i] = i;
    if(m_nTkrEvent[i] != 0) {
      bad[i] = float(m_nTkrBadEvent[i])/m_nTkrEvent[i];
    }
    else {
      bad[i] = 0.;
    }
  }

  int nRow = 2;
  int nCol = 17;
  string table[nRow][nCol];

  table[0][0] = "Tower";
  table[1][0] = "Ratio";

  for(int i = 1; i != nCol; ++i) {
    table[0][i] = ToString(tower[i-1]);
    table[1][i] = ToString(bad[i-1]);
  }

  TableDef t((string*) table, "Ratio of events with a TKR trigger and less than 6 digis in each tower", "nDigiTowerTable", nRow, nCol);

  printHtmlTable(t);
  printLatexTable(t);
}

void TestReport::produceNDigiPlot()
{
  double tower[g_nTower], bad[g_nTower];

  // no. of towers with TKR trigger
  int nDataTower = 0;

  for(int i = 0; i != g_nTower; ++i) {
    if(m_nTkrEvent[i] != 0) {
      bad[nDataTower] = float(m_nTkrBadEvent[i])/m_nTkrEvent[i];
      tower[nDataTower] = i;
      ++nDataTower;
    }
  }

  m_nDigi = new TGraph(nDataTower, tower, bad);

  TCanvas temp("temp", "temp");
  m_nDigi->Draw("A*");
  m_nDigi->GetXaxis()->SetTitle("Tower");
  m_nDigi->GetYaxis()->SetTitle("Ratio of events with less than 6 digis");

  string file(m_prefix);
  file += "_nDigi";
  PlotAttribute att(file.c_str(), "Ratio of events with TKR trigger and at least 6 digis", "nDigi", 0);
  producePlot(m_nDigi, att);
  insertPlot(att);
}

void TestReport::produceAveTotPlots()
{
  // *2 because there are 2 TOTs per plane
  int nTot = g_nPlane * 2;
  float id[nTot], ave[nTot];

  TGraph* graphs[g_nTower];

  for(int i = 0; i != g_nTower; ++i) {
    for(int j = 0; j != g_nPlane; ++j) {
      for(int k = 0; k != 2; ++k) {

	int iTot = j*2 + k;
	ave[iTot] = m_tot[i][j][k]->GetMean();
	id[iTot] = float(iTot)/2.;

      }
    }
    graphs[i] = new TGraph(nTot, id, ave);
    TCanvas temp("temp", "temp");
    graphs[i]->Draw("A*");
    char name[] = "Layer(tower00)";
    sprintf(name, "Layer(tower%02d)", i);
    GraphAttribute att(name, "Ave TOT value", 0.1, 0.07, 0.6, 0.4, 0.3);
    setGraphParameters(graphs[i], att);
  }

  string file(m_prefix);
  file += "_tot0";
  PlotAttribute att(file.c_str(), "Average TOT value in tower 0 to tower 7(excluding 0 and saturation). Plane 0 is at bottom of the tracker.", "tot0", 0, 0, 18, 18, 909, 615);
  producePlot((TObject**) graphs, att, 4, 2);
  insertPlot(att);

  file = m_prefix;
  file += "_tot1";
  att.set(file.c_str(), "Average TOT value in tower 8 to tower 15(excluding 0 and saturation). Plane 0 is at bottom of the tracker.", "tot1", 0, 0, 18, 12.2, 909, 615);
  att.m_2dPlotType = PlotAttribute::COLZ;
  producePlot((TObject**) graphs+8, att, 4, 2);
  insertPlot(att);
}

void TestReport::produceNhits2DPlot()
{
  for(int i = 0; i != g_nTower; ++i) {
    for(int j = 0; j != g_nPlane; ++j) {

      if(m_nEvtPlane[i][j]) {
	m_nHit2D->Fill(j, i, double(m_nHitPlane[i][j])/m_nEvtPlane[i][j]);
      }
      m_nZeroHit2D->Fill(j+0.25, i, double(m_nEvent-m_nEvtHitPlane[i][j][0])/m_nEvent);
      m_nZeroHit2D->Fill(j+0.75, i, double(m_nEvent-m_nEvtHitPlane[i][j][1])/m_nEvent);
    }
  }

  string file(m_prefix);
  file += "_nhits2d";
  PlotAttribute att(file.c_str(), "Average number of strip hits in a TKR plane. Events with zero hits are not used in calculating the average", "nhits2d");
  producePlot(m_nHit2D, att);
  insertPlot(att);

  file = m_prefix;
  file += "_nZeroHit2d";
  att.set(file.c_str(), "Fraction of events with 0 strip hits. Note that the plot contains information from both ends of the same plane. For example, the bin at 0-0.5 along the X axis corresponds to the value from the GTRC close to strip 0 in plane 0, the bin at 0.5-1. along the X axis corresponds to the value from the GTRC close to strip 1536 in plane 0", "nZeroHit2d");
  producePlot(m_nZeroHit2D, att);
  insertPlot(att);
}

void TestReport::produceCalNhits2DPlot()
{
  for(int i = 0; i != g_nTower; ++i) {
    for(int j = 0; j != g_nCalLayer; ++j) {
      if(m_nEvtCalHit[i][j]) {
	if(i==4) {
	  cout << "i = " << i << " " << m_nCalHit[i][j] << " " << m_nEvtCalHit[i][j];
	}
	m_nCalHit2D->Fill(j, i, double(m_nCalHit[i][j])/m_nEvtCalHit[i][j]);
      }
      if(m_nEvent > m_nEvtCalHit[i][j]) {
	m_nZeroCalHit2D->Fill(j, i, double(m_nEvent-m_nEvtCalHit[i][j])/m_nEvent);
      }
    }
  }

  string file(m_prefix);
  file += "_nCalHits2d";
  PlotAttribute att(file.c_str(), "Average number of crystal hits in a particular CAL layer. Note 0 hit is not used to calculate the average", "nCalHits2d");
  producePlot(m_nCalHit2D, att);
  insertPlot(att);

  file = m_prefix;
  file += "_nZeroCalHit2d";
  att.set(file.c_str(), "Fraction of events with zero hits in a particular CAL layer", "nZeroCalHit2d");
  producePlot(m_nZeroCalHit2D, att);
  insertPlot(att);
}

void TestReport::produceZeroSatTot2DPlot()
{
  /*
  string file = m_prefix;
  file += "_totZero";
  PlotAttribute att(file.c_str(), "Fraction of events with TOT equal to zero in each plane (plane 0 is at the bottom) in each tower. Note the plot contains info for both tot counters in the same plane. For example, bin at 0-0.5 along the X axis corresponds to tot value from GTRC close to strip 0 at plane 0, bin at 0.5-1. along the X axis corresponds to tot value from GTRC close to strip 1536 at plane 0", "satTot");
  att.m_nColor = 4;
  producePlot(m_totZero2D, att);
  insertPlot(att);
  */

  // scale the histogram
  int nEvts[g_nPlane*g_nEnd][g_nTower];

  for(int i = 0; i != g_nTower; ++i) {
    for(int j = 0; j != g_nPlane; ++j) {
      nEvts[j*2][i] = m_nEvtHitPlane[i][j][0];
      nEvts[j*2+1][i] = m_nEvtHitPlane[i][j][1];
    }
  }

  scale2DHist(m_totSat2D, (int*) nEvts);

  string file = m_prefix;
  file += "_totSat";
  PlotAttribute att(file.c_str(), "Fraction of events with saturated TOT value of 250 counts (1 count = 200 ns, plane 0 is at the bottom). When calculating the fraction, the denominator is the number of events with at least 1 hit in the corresponding region. The plot contains information for both TOT counters in the same plane. For example, the bin at tower 0, plane 0-0.5 corresponds to the TOT value from the GTRC close to strip 0 in plane 0 in tower 0. The bin at tower 0, plane 0.5-1. corresponds to the TOT value from the GTRC close to strip 1536 in plane 0 in tower 0", "satTot");
  producePlot(m_totSat2D, att);
  insertPlot(att);
}

void TestReport::produceTotNoise2DPlot()
{
  // scale the histogram
  int nEvts[g_nPlane*g_nEnd][g_nTower];

  for(int i = 0; i != g_nTower; ++i) {
    for(int j = 0; j != g_nPlane; ++j) {
      nEvts[j*2][i] = m_nEvtHitPlane[i][j][0];
      nEvts[j*2+1][i] = m_nEvtHitPlane[i][j][1];
    }
  }

  scale2DHist(m_totNoise2D, (int*) nEvts);

  string file = m_prefix;
  file += "_totNoise";
  PlotAttribute att(file.c_str(), "Fraction of events with TOT equal to zero but nonzero number of strip hits (plane 0 is at the bottom). When calculating the fraction, the denominator is the number of events with at least 1 hit in the corresponding region. The plot contains information for both TOT counters in the same plane (one for each end). For example, the bin at 0-0.5 along the X axis corresponds to the TOT value from the GTRC close to strip 0 in plane 0. The bin at 0.5-1. along the X axis corresponds to the TOT value from the GTRC close to strip 1535 in plane 0", "TotNoise");
  producePlot(m_totNoise2D, att);
  insertPlot(att);
}

void TestReport::produceAveTot2DPlot()
{
  for(int i = 0; i != g_nTower; ++i) {
    for(int j = 0; j != g_nPlane; ++j) {
      m_totAve2D->Fill(j+0.25, i, m_tot[i][j][0]->GetMean());
      m_totAve2D->Fill(j+0.75, i, m_tot[i][j][1]->GetMean());
    }
  }

  string file(m_prefix);
  file += "_totAve2D";
  PlotAttribute att(file.c_str(), "Average TOT value(excluding 0 and saturation value, plane 0 is at bottom). Note the plot contains info for both tot counters in the same plane. For example, bin at tower 0, plane 0-0.5 corresponds to tot value from GTRC close to strip 0 at plane 0 in tower 0. Bin at tower 0, plane 0.5-1. corresponds to tot value from GTRC close to strip 1536 at plane 0 in tower 0", "totAve2D");
  producePlot(m_totAve2D, att);
  insertPlot(att);
}

void TestReport::produceReconDirPlots()
{
  string file(m_prefix);
  file += "_reconDirXY";
  PlotAttribute att(file.c_str(), "Reconstructed event direction along the X and the Y axis. The color scheme represents the number of events in a bin. The values are obtained from the first reconstructed vertex.", "reconDirXY");
  producePlot(m_reconDirXY, att);
  insertPlot(att);

  file = m_prefix;
  file += "_reconDirZ";
  att.set(file.c_str(), "Reconstructed event direction along the Z axis.The value is obtained from the first reconstructed vertex.", "reconDirZ");
  producePlot(m_reconDirZ, att);
  insertPlot(att);
}

void TestReport::produceReconPosPlots()
{
  string file(m_prefix);
  file += "_reconPosXY";
  PlotAttribute att(file.c_str(), "Reconstructed event position along the X and the Y axis. The color scheme represents the number of events in a bin. The values are obtained from the first reconstructed vertex.", "reconPosXY");
  att.m_statMode = 110011;
  att.m_statBox = 1;
  producePlot(m_reconPosXY, att);
  insertPlot(att);

  file = m_prefix;
  file += "_reconPosZ";
  att.set(file.c_str(), "Reconstructed event position along the Z axis. The value is obtained from the first reconstructed vertex.", "reconPosZ", 1);
  att.m_statMode = 111111;
  producePlot(m_reconPosZ, att);
  insertPlot(att);
}

void TestReport::produceReconEnePlots()
{
  string file(m_prefix);
  file += "_reconEne";
  PlotAttribute att(file.c_str(), "Reconstructed event energy (MeV) assigned to the first reconstructed vertex. By default, it is calculated based on the number of hits in the tracker and the amount of energy measured in the calorimeter.", "reconEne", 1);
  producePlot(m_reconEne, att);
  insertPlot(att);
}

void TestReport::produceCalEneSum2DPlot()
{
  string file = m_prefix;
  file += "_calSumEne";
  PlotAttribute att(file.c_str(), "Sum of crystal energies in the CAL cluster (MeV). Note that there is only one CAL cluster produced by CalRecon at the moment. Energy measured in each crystal is obtained by using the getEnergy() member function of the CalXtalRecData class.", "calSumEne", 1);
  producePlot(m_calSumEne, att);
  insertPlot(att);
}

void TestReport::produceCalEneLayer2DPlot()
{
  for(int i = 0; i != g_nTower; ++i) {
    for(int j = 0; j != g_nCalLayer; ++j) {
      if(m_nCalEneLayer[i][j]) {
	m_calEneLayer2D->Fill(j, i, m_calEneLayer[i][j]/m_nCalEneLayer[i][j]);
      }
      if(m_nEvent > m_nCalEneLayer[i][j]) {
	m_zeroCalEneLayer2D->Fill(j, i, double(m_nEvent-m_nCalEneLayer[i][j])/m_nEvent);
      }
    }
  }

  string file(m_prefix);
  file += "_calEneLayer2d";
  PlotAttribute att(file.c_str(), "Average energies (MeV) measured in each CAL layer, scaled by the color Z axis. Note that zero energy is not used in calculating the average. Energy measured in each crystal is obtained by using the getEnergy() member function of the CalXtalRecData class.", "calEneLayer2d");
  producePlot(m_calEneLayer2D, att);
  insertPlot(att);

  file = m_prefix;
  file += "_zeroCalEndLayer2d";
  att.set(file.c_str(), "Fraction of events with zero energy measured for all CAL layers.", "zeroCalEndLayer2d");
  producePlot(m_zeroCalEneLayer2D, att);
  insertPlot(att);
}

void TestReport::scale2DHist(TH2F* h, int* nEvents)
{
  int nBinsX = h->GetNbinsX();
  int nBinsY = h->GetNbinsY();

  for(int i = 0; i != nBinsX; ++i) {
    for(int j = 0; j != nBinsY; ++j) {

      // note in ROOT, first bin is bin 1, bin 0 contains underflow

      int content = (int) h->GetBinContent(i+1, j+1);
      if(content) {
	h->SetBinContent(i+1, j+1, double(content)/ (*(nEvents+nBinsY*i+j)) );
      }
    }
  }
}


void TestReport::produceTriggerPerTowerPlot()
{
  string file(m_prefix);
  file += "_tkrPerTower";
  PlotAttribute att(file.c_str(), "Number of TKR triggers per tower","tkrPerTower");
  producePlot(m_tkrPerTower, att);
  insertPlot(att);

  file = m_prefix;
  file += "_calLoPerTower";
  att.set(file.c_str(), "Number of CAL LO triggers per tower","calLoPerTower");
  producePlot(m_calLoPerTower, att);
  insertPlot(att);

  file = m_prefix;
  file += "_calHiPerTower";
  att.set(file.c_str(), "Number of CAL Hi triggers per tower","calHiPerTower");
  producePlot(m_calHiPerTower, att);
  insertPlot(att);
}


void TestReport::produceGemDiscardedPlot()
{
  string file(m_prefix);
  file += "_gemDiscarded";
  PlotAttribute att(file.c_str(), "Number of GEM discarded events between two successive read out events","gemDiscarded",true);
  producePlot(m_gemDiscarded, att);
  insertPlot(att);

  file = m_prefix;
  file += "_gemDiscardedTime";
  att.set(file.c_str(), "Time between the previous read out event and the last discarded event in system clock ticks (nominally 50 ns). Only non-saturated values of the GEM time counters have been used.","gemDiscardedTime",true);
  producePlot(m_gemDiscardedTime, att);
  insertPlot(att);
}


void TestReport::produceTimeIntervalPlotSBC()
{
  string file(m_prefix);
  file += "_timeInterval";
  PlotAttribute att(file.c_str(), "Time interval between adjacent events in millseconds. Note that this interval is between the time when the events are built, NOT the GEM trigger time. The time is measured by the 16MHZ clock in the power PC.", "timeInterval", true);
  producePlot(m_timeInterval, att);
  insertPlot(att);

  file = m_prefix;
  file += "_timeIntervalCut";
  att.set(file.c_str(), "Time interval between adjacent events in millseconds with a cut of 1 ms. Note that this interval is between the time when the events are built, NOT the GEM trigger time. The time is measured by the 16MHZ clock in the power PC.", "timeIntervalCut", true);
  producePlot(m_timeIntervalCut, att);
  insertPlot(att);
}



//
void TestReport::produceTimeIntervalPlotGEM()
{
  string file(m_prefix);
  file = m_prefix;
  file += "_timeIntervalGem";
  PlotAttribute att(file.c_str(), "Time interval between adjacent events in millseconds. Note that this interval is measured in the GEM. The time is stored in a 16 bit counter, each count is equal to 50 ns, so the time will saturate at roughly 3.3 ms.", "timeIntervalGem", true);
  producePlot(m_timeIntervalGem, att);
  insertPlot(att);

  file = m_prefix;
  file += "_timeIntervalGemZoom";
  att.set(file.c_str(), "Time interval between adjacent events in millseconds with a cut of 1 millisecond. Note that this interval is measured in the GEM. The time is stored in a 16 bit counter, each count is equal to 50 ns.", "timeIntervalGemZoom", true);
  producePlot(m_timeIntervalGemZoom, att);
  insertPlot(att);
}





string TestReport::boldFaceLatex(const string& s) 
{
  string temp("{\\bf ");
  temp += s;
  string::size_type pos = temp.find('.');
  if(pos != string::npos) {
    temp.insert(pos+1, "}");
  }
  else {
    temp += "}";
  }
  return temp;
}

string TestReport::boldFaceHtml(const string& s) 
{
  string temp("<strong> ");
  temp += s;
  string::size_type pos = temp.find('.');
  if(pos != string::npos) {
    temp.insert(pos+1, "</strong>");
  }
  else {
    temp += "</strong>";
  }
  return temp;
}

void TestReport::produceNHitPlane2DPlot()
{
  TH2F h2("nHitPlane2D", "number of hit planes distribution", 36, 0.5, 36.5, 16, -0.5, 15.5);
  HistAttribute att("Number of planes that have strip hits", "Tower");
  setHistParameters(&h2, att);

  for(int i = 0; i != g_nTower; ++i) {
    // Take out events with no planes hit:
    for(int j = 1; j != g_nPlane+1; ++j) {

      // For missing towers, all events will have 0 planes that are hit.
      // For clarity of the plot, the corresponding bins won't be filled.
      if(m_nLayer[i]->GetBinContent(j+1) != m_nEvent) {
	h2.Fill(j, i, m_nLayer[i]->GetBinContent(j+1));
      }
    }
  }

  string file(m_prefix);
  file += "_nHitPlane2D";
  PlotAttribute pAtt(file.c_str(), "Number of planes in a tower that have strip hits. Events with no planes hit are not used. If a tower is missing, the information is not included in the plot (bins are not filled).", "nHitPlane2D");
  producePlot(&h2, pAtt);
  insertPlot(pAtt);
}

void TestReport::produceAlignCalTkrPlot()
{
  string file(m_prefix);
  file += "_alignCalTkr";
  PlotAttribute att(file.c_str(), "Distance between the reconstructed CAL cluster XY coordinates and the XY coordinates extrapolated from TKR according to reconstructed track direction. The plot only contains events with more than 50 MeV energy deposited in the CAL.", "alignCalTkr", true);
  att.m_statMode = 111111;
  producePlot(m_alignCalTkr, att);
  insertPlot(att);
}

// ACD digis:
void TestReport::produceAcdDigiPlots()
{

  // divide out some plots to have effics
  Float_t vetoToHitRatio = efficDivide(*m_AcdVetoMap,*m_AcdHitMap,kTRUE);
  Float_t singlePmtRatio = efficDivide(*m_AcdTileIdOnePMT,*m_AcdHitMap);
  Float_t singleVetoRatio = efficDivide(*m_AcdTileIdOneVeto,*m_AcdHitMap);

  string file(m_prefix);

  file += "_nAcdDigis";
  PlotAttribute att(file.c_str(), "Number of ACD digis.", "nAcdDigis");
  att.m_statMode = 111111;
  att.m_yLog = kTRUE;
  producePlot(m_nAcdDigis, att);
  insertPlot(att);

  file = m_prefix;
  file += "_AcdHitMap";
  att.set(file.c_str(), "ACD Gem ID for all hits", "AcdHitMap" );
  att.m_statMode = 0;
  producePlot(m_AcdHitMap, att);
  insertPlot(att);  

  file = m_prefix;
  file += "_AcdVetoMap";
  att.set(file.c_str(), "Fraction of hits below Veto threshold.  By ACD Gem ID.", "AcdVetoMap" );
  att.m_statMode = 0;
  producePlot(m_AcdVetoMap, att);
  insertPlot(att);

  file = m_prefix;
  file += "_AcdTileIdOnePMT";
  att.set(file.c_str(), "Fraction of hits where only 1 PMT in a tile fired.  By ACD Gem ID", "AcdTileIdOnePMT");
  att.m_statMode = 0;
  producePlot(m_AcdTileIdOnePMT, att);
  insertPlot(att);

  file = m_prefix;
  file += "_AcdTileIdOneVeto";
  att.set(file.c_str(), "Fraction of hits where only 1 PMT in a tile was above Veto threshold.  By ACD Gem ID", "AcdTileIdOneVeto");
  att.m_statMode = 0;
  producePlot(m_AcdTileIdOneVeto, att);
  insertPlot(att);
  
  file = m_prefix;
  file += "_AcdPhaMapA";
  att.set(file.c_str(), "ACD PHA map -- A PMTs.", "AcdPhaMapA" );
  att.m_zLog = true;
  producePlot(m_AcdPhaMapA, att);
  insertPlot(att);

  file = m_prefix;  
  file += "_AcdPhaMapB";  
  att.set(file.c_str(), "ACD PHA map -- B PMTs.", "AcdPhaMapB" );
  att.m_zLog = true;
  producePlot(m_AcdPhaMapB, att);
  insertPlot(att);
}


// ACD recon:
void TestReport::produceAcdTkrReconPlots()
{
  
  // divide out some plots to have effics
  m_AcdEfficMap->Add(m_AcdInEfficMap);

  Float_t inEfficRatio = efficDivide(*m_AcdInEfficMap,*m_AcdEfficMap);

  string file(m_prefix);

  file = m_prefix;
  file += "_AcdInEfficMap";
  
  PlotAttribute att(file.c_str(), "Fraction of tracks extapolated to tile NOT MATCHED with hits.  By ACD Gem ID.", "AcdInEfficMap");
  att.m_statMode = 0;
  producePlot(m_AcdInEfficMap, att);
  insertPlot(att);  

  file = m_prefix;
  file += "_AcdMissMapTop";
  att.set(file.c_str(), "GLOBAL X-Y postions for track extrapolations NOT MATCHED hits: top of ACD", "AcdMissMapTop" );
  producePlot(m_AcdMissMapTop, att);
  insertPlot(att);

  file = m_prefix;
  file += "_AcdMissMapMinusX";
  att.set(file.c_str(), "GLOBAL Y-Z postions for track extrapolations NOT MATCHED hits: -X side of ACD", "AcdMissMapMinusX" );
  producePlot(m_AcdMissMapMinusX, att);
  insertPlot(att);

  file = m_prefix;
  file += "_AcdMissMapMinusY";
  att.set(file.c_str(), "GLOBAL X-Z postions for track extrapolations NOT MATCHED hits: -Y side of ACD", "AcdMissMapMinusY" );
  producePlot(m_AcdMissMapMinusY, att);
  insertPlot(att);
  
  file = m_prefix;
  file += "_AcdMissMapPlusX";
  att.set(file.c_str(), "GLOBAL Y-Z postions for track extrapolations NOT MATCHED hits: +X side of ACD", "AcdMissMapPlusX" );
  producePlot(m_AcdMissMapPlusX, att);
  insertPlot(att);

  file = m_prefix;
  file += "_AcdMissMapPlusY";
  att.set(file.c_str(), "GLOBAL X-Z postions for track extrapolations NOT MATCHED hits: +Y side of ACD", "AcdMissMapPlusY" );
  producePlot(m_AcdMissMapPlusY, att);
  insertPlot(att);

}


string TestReport::eraseLatexStr(const std::string& s)
{
  string::size_type start = s.find("@latex");
  if(start == string::npos) return s;

  string::size_type end = s.find("@endlatex");
  if(end == string::npos) return s;

  string temp(s);
  temp.erase(start, end-start+9);

  start = temp.find("@html");
  if(start != string::npos) {
    temp.replace(start, 6, "");
  }
  end = temp.find("@endhtml");
  if(end != string::npos) {
    temp.replace(end, 9, "");
  }

  return temp;
}

string TestReport::eraseHtmlStr(const std::string& s)
{
  string::size_type start = s.find("@html");
  if(start == string::npos) return s;

  string::size_type end = s.find("@endhtml");
  if(end == string::npos) return s;

  string temp(s);
  temp.erase(start, end-start+8);

  start = temp.find("@latex");
  if(start != string::npos) {
    temp.replace(start, 6, "");
  }
  end = temp.find("@endlatex");
  if(end != string::npos) {
    temp.replace(end, 9, "");
  }

  return temp;
}
