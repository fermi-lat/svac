#include <iostream>
#include <cstdio>
#include "TROOT.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TPostScript.h"
#include "TestReport.h"
#include "ToString.h"
#include "TStyle.h"

using std::cout;
using std::endl;
using std::string;

TestReport::TestReport(const char* dir, const char* prefix, 
		       const char* version, const char* emVersion)
  : m_dir(dir), m_prefix(prefix), m_version(version), m_emVersion(emVersion),
    m_outputFile(0), m_mcFile(0), m_mcTree(0),
    m_mcBranch(0), m_mcEvent(0), m_reconFile(0), m_reconTree(0), 
    m_reconBranch(0), m_reconEvent(0), m_digiFile(0), m_digiTree(0),
    m_digiBranch(0), m_digiEvent(0), m_trigger(0), m_nEvent(0),
    m_nTkrTrigger(0), m_nEventBadStrip(0), m_nEventMoreStrip(0), 
    m_nEventSatTot(0), m_nEventZeroTot(0), m_nEventBadTot(0), m_startTime(0),
    m_endTime(0), m_nDigi(0)
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

  string r(dir);
  r += '/';
  r += prefix;
  r += "_hist.root";
  m_outputFile = new TFile(r.c_str(), "RECREATE");

  m_trigger = new TH1F("trigger", "Trigger distribution", 32, -0.5, 31.5);
  HistAttribute att("Trigger word", "Number of events");
  setHistParameters(m_trigger, att);

  m_condSummary = new TH1F("condSummary", "Condition summary distribution", 32, -0.5, 31.5);
  att.m_xTitle = "Condition summary word";
  setHistParameters(m_condSummary, att);

  for(int i = 0; i != 7; ++i) {
    m_nEventDigi[i] = 0;
  }

  m_nHit2D = new TH2F("nHit2D", "nhits distribution", 16, -0.5, 15.5, 36, -0.5, 35.5);
  att.set("Tower", "Plane");
  setHistParameters(m_nHit2D, att);

  for(int i = 0; i != g_nTower; ++i) {
    char name[] = "nHitss00";
    sprintf(name, "nHitss%02d", i);
    char xTitle[] = "No. of strip hits in tower 00";
    sprintf(xTitle, "No. of strip hits in tower %02d", i);
    m_nHit[i] = new TH1F(name, xTitle, 20, 0., 20.);
    att.set(xTitle, "No. of events", 0.1, 0.07, 0.6, 0.4);
    setHistParameters(m_nHit[i], att);
 
    char name1[] = "nLayer00";
    sprintf(name1, "nLayer%02d", i);
    char xTitle1[] = "No. of hit layers in tower 00";
    sprintf(xTitle1, "No. of hit layers in tower %02d", i);
    m_nLayer[i] = new TH1F(name1, xTitle1, 18, -0.5, 17.5);
    att.set(xTitle1, "No. of events", 0.1, 0.07, 0.6, 0.4);
    setHistParameters(m_nLayer[i], att);

    m_nTkrEvent[i] = 0;
    m_nTkrBadEvent[i] = 0;

    for(int j = 0; j != g_nPlane; ++j) {
      for(int k = 0; k != 2; ++k) {
	char name[] = "tot00000";
	sprintf(name, "tot%02d%02d%1d", i, j, k);
	m_tot[i][j][k] = new TH1F(name, name, g_satTot, 0, g_satTot);
      }
    }
  }

  m_nCalHit2D = new TH2F("nCalHit2D", "nhits distribution", 16, -0.5, 15.5, 8, -0.5, 7.5);
  att.set("Tower", "Layer");
  setHistParameters(m_nCalHit2D, att);

  m_totZero2D = new TH2F("totZero2D", "Zerot tot0 distribution", 16, -0.5, 15.5, 72, 0., 36.);
  att.set("Tower", "Plane");
  setHistParameters(m_totZero2D, att);

  m_totSat2D = new TH2F("totSat2D", "Tot distribution", 16, -0.5, 15.5, 72, 0, 36);
  att.set("Tower", "Plane");
  setHistParameters(m_totSat2D, att);

  m_totAve2D = new TH2F("totAve2D", "Tot distribution", 16, -0.5, 15.5, 72, 0, 36);
  att.set("Tower", "Plane");
  setHistParameters(m_totAve2D, att);

  m_nTkrTrack = new TH1F("nTkrTrack", "Number of reconstructed tracks", 10, -0.5, 9.5);
  att.m_xTitle = "Number of reconstructed tracks";
  att.m_canRebin = false;
  setHistParameters(m_nTkrTrack, att);

  char* temp[3];
  temp[0] = "X", temp[1] = "Y", temp[2] = "Z";
  for(int i = 0; i != 3; ++i) {
    char name[] = "reconDir0";
    sprintf(name, "reconDir%1d", i);
    char xTitle[] = "Reconstructed 0 direction";
    sprintf(xTitle, "Reconstructed %s direction", temp[i]);
    m_reconDir[i] = new TH1F(name, xTitle, 100, -1., 1.);
    att.set(xTitle, "No. of events", 0.06, 0.05, 0.7, 0.5);
    setHistParameters(m_reconDir[i], att);
  }
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
    h2->SetStats(kFALSE);
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

  for(int iEvent = 0; iEvent != m_nEvent; ++iEvent) {

    if(m_mcFile) {
      m_mcBranch->GetEntry(iEvent);
      analyzeMcTree();
    }

    if(m_digiFile) {
      m_digiBranch->GetEntry(iEvent);
      analyzeDigiTree();

      if(iEvent == 0) {
	m_startTime = m_digiEvent->getEbfTimeSec();
      }
      else if(iEvent == m_nEvent-1) {
	m_endTime = m_digiEvent->getEbfTimeSec();
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
 
  assert(tkrRecon != 0);

  m_nTkrTrack->Fill(tkrRecon->getTrackCol()->GetLast()+1);

  TObjArray* vertices = tkrRecon->getVertexCol();
  if(tkrRecon->getVertexCol()->GetLast() >= 0) {
    TkrVertex* tkrVertex = dynamic_cast<TkrVertex*>(vertices->At(0));
    if(tkrVertex) {
      const TVector3& pos = tkrVertex->getPosition();
      const TVector3& dir = tkrVertex->getDirection();
      m_reconDir[0]->Fill(dir.X());
      m_reconDir[1]->Fill(dir.Y());
      m_reconDir[2]->Fill(dir.Z());
      /*
      m_ntuple.m_pos[0] = pos.X();
      m_ntuple.m_pos[1] = pos.Y();
      m_ntuple.m_pos[2] = pos.Z();
      m_ntuple.m_dir[0] = dir.X();
      m_ntuple.m_dir[1] = dir.Y();
      m_ntuple.m_dir[2] = dir.Z();
      m_ntuple.m_fitTotalEnergy = tkrVertex->getEnergy();
      m_ntuple.m_vtxTrks = tkrVertex->getNumTracks();
      */
    }
  }

}


void TestReport::analyzeDigiTree()
{
  int trigger = m_digiEvent->getL1T().getTriggerWord();
  m_trigger->Fill(trigger);

  int cond = m_digiEvent->getGem().getConditionSummary();
  m_condSummary->Fill(cond);

  int tkrVector = m_digiEvent->getGem().getTkrVector();

  // 3 in a row TKR trigger
  bool tkrTrigger;
  if(cond & 2) {
    ++m_nTkrTrigger;
    tkrTrigger = true;

    for(int i = 0; i != g_nTower; ++i) {
      if( (tkrVector >> i) && 1 ) ++m_nTkrEvent[i];
    }
  }
  else {
    tkrTrigger = false;
  }

  int nTkrDigis = m_digiEvent->getTkrDigiCol()->GetLast()+1;

  int nHit[g_nTower], nLayer[g_nTower], nDigi[g_nTower];
  for(int i = 0; i != g_nTower; ++i) {
    nHit[i] = 0;
    nLayer[i] = 0;
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
    int plane = 2 * biLayer;
    if(view == GlastAxis::Y) ++plane;

    ++nDigi[tower];

    ++nLayer[tower];

    nHit[tower] += tkrDigi->getNumHits();

    m_nHit2D->Fill(tower, plane, double(tkrDigi->getNumHits())/m_nEvent);

    int lowCount = 0, highCount = 0;
    int nStrips = tkrDigi->getNumHits();
    for(int i = 0; i != nStrips; ++i) {
      int stripId = tkrDigi->getStrip(i);
      if(stripId < 0 || stripId >1535) badStrip = true;

      int div = getGtrcSplit(biLayer, view);
      (stripId < div) ? ++lowCount : ++highCount;
 
    }

    if(lowCount > 64 || highCount > 64) {
      moreStrip = true;
    }

    int tot0 = tkrDigi->getToT(0);
    int tot1 = tkrDigi->getToT(1);

    if((tot0> 0 || tot1> 0) && nStrips == 0) badTot = true;
    if(tot0 <= 0 && tot1 <= 0 && nStrips > 0) zeroTot = true;
    
    assert(tot0>=0 && tot0 <=g_satTot && tot1>=0 && tot1 <=g_satTot); 

    if(tot0 == 0){
      m_totZero2D->Fill(tower, plane+0.25);
    }
    if(tot1 == 0){
      m_totZero2D->Fill(tower, plane+0.75);
    }

    if(tot0 == g_satTot){
      satTot = true;
      m_totSat2D->Fill(tower, plane+0.25);
    }
    if(tot1 == g_satTot){
      satTot = true;
      m_totSat2D->Fill(tower, plane+0.75);
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
    m_nLayer[i]->Fill(nLayer[i]);
    if(nDigi[i] > maxNDigi) maxNDigi = nDigi[i];
    if( ((tkrVector >> i) && 1) && nDigi[i] < 6) ++m_nTkrBadEvent[i];
  }

  if(tkrTrigger) {
    (maxNDigi >= 6) ? ++m_nEventDigi[6] : ++m_nEventDigi[maxNDigi];
  }

  /*
  int nCalDigis = m_digiEvent->getCalDigiCol()->GetLast()+1;
  cout << "nCalDigis = " << nCalDigis << endl;
  for(int i = 0; i != nCalDigis; ++i) {

    const CalDigi* calDigi = m_digiEvent->getCalDigi(i);
    assert(calDigi != 0);

    int tower = calDigi->getPackedId().getTower();
    int layer = calDigi->getPackedId().getLayer();

    m_nCalHit2D->Fill(tower, layer, 1./double(m_nEvent));
  }
  */
}

void TestReport::generateReport()
{
  writeHeader();

  (*m_report) << "@section purpose Purpose" << endl;
  (*m_report) << "This report is used in offline data analyses to identify apparent problems in cosmic ray muon and VDG data. <b>Warning, results from other tests should be studied with care</b>" << endl;

  (*m_report) << "@section summary Summary" << endl;
  (*m_report) << "This report is produced using the @b " << m_version 
	      << " TestReport package and the @b " << m_emVersion 
	      << " EngineeringModel package." << endl << endl;

  if(m_reconFile) generateReconReport();

  if(m_digiFile) generateDigiReport();
 
  writeTail(); 
}

void TestReport::generateDigiReport()
{
  (*m_report) << "In digi file @em " << m_digiFile->GetName() << endl;
  (*m_report) << "@li There are @b " << m_nEvent << " triggers " << endl;
  (*m_report) << "@li Time of first trigger: <b>" << ctime((time_t*) (&m_startTime)) << " (GMT) </b>";
  (*m_report) << "@li Time of last trigger: <b>" << ctime((time_t*) (&m_endTime)) << " (GMT) </b>";
  (*m_report) << "@li Duration: <b>" << m_endTime - m_startTime << " seconds" << "</b>" << endl;
  (*m_report) << "@li Rate: <b>" << double(m_nEvent)/(m_endTime - m_startTime) << " hz" << "</b>" << endl;
 
  (*m_report) << "@section digi Digi" << endl;
  *(m_report) << "@latexonly \\nopagebreak @endlatexonly" << endl;
  printNDigiTable();
  *(m_report) << "@latexonly \\nopagebreak @endlatexonly" << endl;
  printNDigiTowerTable();
  *(m_report) << "@latexonly \\pagebreak @endlatexonly" << endl;

  *(m_report) << "@section badStrip Bad Strip" << endl;
  *(m_report) << "@latexonly \\nopagebreak @endlatexonly" << endl;
  *(m_report) << "@li There are @b " << ToString(m_nEventBadStrip) << " events with strip ID outside the range from 0 to 1535." << endl;

  *(m_report) << "@li There are @b " << ToString(m_nEventMoreStrip) << " events with more than 64 strips per GTRC. <b> Warning: EM2 splitting is assumed where tot0 at X1 reads from front end card 0-3 </b>" << endl << endl;
  
  *(m_report) << "@section totInfo TOT info" << endl;
  *(m_report) << "@latexonly \\nopagebreak @endlatexonly" << endl;
  *(m_report) << "@li There are @b " << ToString(m_nEventSatTot) << " events with saturated TOT values." << endl;
  *(m_report) << "@li There are @b " << ToString(m_nEventZeroTot) << " events with zero TOT in one plane but nonzero number of strip hits in that plane." << endl;
  *(m_report) << "@li There are @b " << ToString(m_nEventBadTot) << " events with nonzero TOT on one plane but no strip hits in that plane." << endl << endl;


  (*m_report) << "@section trigger Trigger" << endl;

  // print trigger plots
  string file(m_prefix);
  file += "_trigger";
  PlotAttribute att(file.c_str(), "Trigger distribution. The word is deduced by combining bit patterns from table 3", "trigger", 1);
  producePlot(m_trigger, att);
  insertPlot(att);
  *(m_report) << "@latexonly \\nopagebreak @endlatexonly" << endl;
  printGltTriggerTable();
  *(m_report) << "@latexonly \\pagebreak @endlatexonly" << endl;

  // print condition summary plots
  file = m_prefix;
  file += "_condSummary";
  att.set(file.c_str(), "Condition summary distribution. The word is deduced by combining bit patterns from table 4", "condSummary", 1);
  producePlot(m_condSummary, att);
  insertPlot(att);
  *(m_report) << "@latexonly \\nopagebreak @endlatexonly" << endl;
  printCondSummaryTable();
  *(m_report) << "@latexonly \\pagebreak @endlatexonly" << endl;

  (*m_report) << "@section strip_hit Strip Hit Info" << endl;

  produceNhits2DPlot();

  produceCalNhits2DPlot();

  // produce plots for nhits distribution for 16 towers
  file = m_prefix;
  file += "_hitsPerTower_1";
  att.set(file.c_str(), "Number of strip hits distribution for tower 0 to tower 7", "hitsPerTower_1", 1, 18, 12.2, 909, 615);
  producePlot((TObject**) m_nHit, att, 4, 2);
  insertPlot(att);

  file = m_prefix;
  file += "_hitsPerTower_2";
  att.set(file.c_str(), "Number of strip hits distribution from tower 8 to tower 15", "hitsPerTower_2", 1, 18, 12.2, 909, 615);
  producePlot((TObject**) m_nHit+8, att, 4, 2);
  insertPlot(att);

  // produce plots for nLayer distribution
  (*m_report) << "@section layer_hit Total number of layers hit per tower" << endl;

  file = m_prefix;
  file += "_layersPerTower_1";
  att.set(file.c_str(), "Number of hit layers distribution for tower 0 to tower 7", "layersPerTower_1", 1, 18, 12.2, 909, 615);
  producePlot((TObject**) m_nLayer, att, 4, 2);
  insertPlot(att);

  file = m_prefix;
  file += "_layersPerTower_2";
  att.set(file.c_str(), "Number of hit layers distribution for tower 8 to tower 15", "layersPerTower_1", 1, 18, 12.2, 909, 615);
  producePlot((TObject**) m_nLayer+8, att, 4, 2);
  insertPlot(att);

  //  produceDigiPlot();

  // TOT plots
  produceZeroSatTot2DPlot();

  produceAveTot2DPlot();
  //  produceAveTotPlots();
}

void TestReport::generateReconReport()
{
  (*m_report) << "In recon file @em " << m_reconFile->GetName() << endl;

  // print trigger plots
  string file(m_prefix);
  file += "_nTkrTrack";
  PlotAttribute att(file.c_str(), "Number of reconstructed tracks", "nTkrTrack", 1);
  producePlot(m_nTkrTrack, att);
  insertPlot(att);

  produceReconDirPlots();
}

void TestReport::writeHeader()
{
  *(m_report) << "/** @mainpage Run Test Report" << endl
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

  if(att.m_yLog) gPad->SetLogy();
 
  if(TGraph* gr = dynamic_cast<TGraph*>(h)) {
    gr->Draw("A*");
  }
  else if(TH2F* h2 = dynamic_cast<TH2F*>(h)) {
    if(att.m_2dPlotType == PlotAttribute::LEGO) {
      h2->Draw("LEGO");
    }
    else {
      h2->Draw("COLZ");
    }
  }
  else{
    h->Draw();
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

void TestReport::producePlot(TObject** h, const PlotAttribute& att, int nRow, 
			     int nCol)
{
  TCanvas c1("c1", "produce eps file");
  gPad->SetBorderMode(0);
  gPad->SetFillColor(10);
  c1.Divide(nCol, nRow, 0.001, 0.001);

  for(int i = 0; i != nRow*nCol; ++i) {

    gStyle->SetTitleH(0.12);
    gStyle->SetTitleW(0.2);
    gStyle->SetTitleFontSize(2);
    gStyle->SetStatW(0.4);
    gStyle->SetStatH(0.3);
    gPad->SetBottomMargin(0.05*nRow);

    if(att.m_yLog) gPad->SetLogy();

    c1.cd(i+1);
    if(TGraph* gr = dynamic_cast<TGraph*>(h[i])) {
      gr->Draw("A*");
    }
    else if(TH2F* h2 = dynamic_cast<TH2F*>(h[i])) {
      h2->Draw("LEGO");
    }
    else if(TH1F* h1 = dynamic_cast<TH1F*>(h[i])){
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

  *(m_report) << "@htmlonly <div align=\"center\"> <p><strong>"
	      << att.m_caption << "</strong></p> <img src=\"../" 
	      << gifFile << "\" alt=\"../" << gifFile 
	      << "\"> </div> @endhtmlonly" << endl;
 
  string epsFile(att.m_file);
  epsFile += ".eps";

  *(m_report) << "@image latex " << epsFile << " \"" << att.m_caption << "\" "
	      << "height=" << att.m_height << "cm" << ",width=" 
	      << att.m_width << "cm " << endl << endl;
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
  int nRow = 2;
  int nCol = 8;
  string table[nRow][nCol];

  table[0][0] = "Trigger bit";
  for(int i = 1; i != nCol; ++i) {
    table[0][i] = ToString(i-1);
  }
 
  table[1][0] = "Trigger";
  table[1][1] = "ACD Low";
  table[1][2] = "ACD High";
  table[1][3] = "TKR";
  table[1][4] = "CAL Low";
  table[1][5] = "CAL High";
  table[1][6] = "Throttle";
  table[1][7] = "LiveTime";

  TableDef t((string*) table, "Trigger bit used in triggerAlg calculation", "gltTriggerTable", nRow, nCol);

  printHtmlTable(t);
  printLatexTable(t);
}

void TestReport::printCondSummaryTable()
{
  int nRow = 2;
  int nCol = 8;
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

  TableDef t((string*) table, "Condition summary word in GEM", "condSummaryTable", nRow, nCol);

  printHtmlTable(t);
  printLatexTable(t);
}

void TestReport::printNDigiTable()
{
  if(m_nTkrTrigger == 0) {
    *m_report << "There are no events with TKR trigger." << endl;
    return;
  }

  TableDef d;

  string caption("Number of events with different number of TKR digis. There are ");
  caption += ToString(m_nTkrTrigger); 
  caption += " events with 3 in a row TKR trigger in GEM.";
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
    table[i][1] =  ToString(m_nEventDigi[i-1]);  
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
    *m_report << "There are no events with TKR trigger." << endl;
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

  TableDef t((string*) table, "Ratio of event with TKR trigger and less than 6 digis in each tower", "nDigiTowerTable", nRow, nCol);

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

int TestReport::getGtrcSplit(int layer, GlastAxis::axis view)
{
  // for EM2
  if(layer == 1 && view == GlastAxis::X) {
    return g_nStrip / g_nFEC * 4;
  }
  else {
    return g_nStrip / 2;
  }
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
  PlotAttribute att(file.c_str(), "Average TOT value in tower 0 to tower 7(excluding 0 and saturation). Plane 0 is at bottom of the tracker.", "tot0", 0, 18, 12.2, 909, 615);
  producePlot((TObject**) graphs, att, 4, 2);
  insertPlot(att);

  file = m_prefix;
  file += "_tot1";
  att.set(file.c_str(), "Average TOT value in tower 8 to tower 15(excluding 0 and saturation). Plane 0 is at bottom of the tracker.", "tot1", 0, 18, 12.2, 909, 615);
  att.m_2dPlotType = PlotAttribute::COLZ;
  producePlot((TObject**) graphs+8, att, 4, 2);
  insertPlot(att);
}

void TestReport::produceNhits2DPlot()
{
  string file(m_prefix);
  file += "_nhits2d";
  PlotAttribute att(file.c_str(), "Average number of strip hits in each plane of each tower", "nhits2d");
  att.m_2dPlotType = PlotAttribute::COLZ;
  producePlot(m_nHit2D, att);
  insertPlot(att);
}

void TestReport::produceCalNhits2DPlot()
{
  string file(m_prefix);
  file += "_nCalHits2d";
  PlotAttribute att(file.c_str(), "Average number of crystal hits in each CAL layer of each tower", "nCalHits2d");
  att.m_2dPlotType = PlotAttribute::COLZ;
  producePlot(m_nHit2D, att);
  insertPlot(att);
}

void TestReport::produceZeroSatTot2DPlot()
{

  string file = m_prefix;
  file += "_totZero";
  PlotAttribute att(file.c_str(), "Number of events with zero TOT in each plane (plane 0 is at bottom) in each tower. Note the plot contains info for both tot counters in the same plane. For example, bin at tower 0, plane 0-0.5 contains tot0 value at plane 0 in tower 0. Bin at tower 0, plane 0.5-1. contains tot1 value at plane 0 in tower 0", "satTot");
  producePlot(m_totZero2D, att);
  insertPlot(att);

  file = m_prefix;
  file += "_totSat";
  att.set(file.c_str(), "Number of events with saturated TOT in each plane (plane 0 is at bottom) in each tower. Note the plot contains info for both tot counters in the same plane. For example, bin at tower 0, plane 0-0.5 contains tot0 value at plane 0 in tower 0. Bin at tower 0, plane 0.5-1. contains tot1 value at plane 0 in tower 0", "satTot");
  producePlot(m_totSat2D, att);
  insertPlot(att);
}

void TestReport::produceAveTot2DPlot()
{
  for(int i = 0; i != g_nTower; ++i) {
    for(int j = 0; j != g_nPlane; ++j) {
      m_totAve2D->Fill(i, j+0.25, m_tot[i][j][0]->GetMean());
      m_totAve2D->Fill(i, j+0.75, m_tot[i][j][1]->GetMean());
    }
  }

  string file(m_prefix);
  file += "_totAve2D";
  PlotAttribute att(file.c_str(), "Average TOT value(excluding 0 and saturation value) in each plane (plane 0 is at bottom) in each tower. Note the plot contains info for both tot counters in the same plane. For example, bin at tower 0, plane 0-0.5 contains tot0 value at plane 0 in tower 0. Bin at tower 0, plane 0.5-1. contains tot1 value at plane 0 in tower 0", "totAve2D");
  producePlot(m_totAve2D, att);
  insertPlot(att);
}

void TestReport::produceReconDirPlots()
{
  string file(m_prefix);
  file += "_reconDir";
  PlotAttribute att(file.c_str(), "Reconstructed event direction", "reconDir", 0, 18, 12.2, 909, 615);
  producePlot((TObject**) m_reconDir, att, 3, 1);
  insertPlot(att);
}
