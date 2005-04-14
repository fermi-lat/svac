#include <map>
#include <algorithm>
#include <utility>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <string>
#include "ElecToGeo.h"
#include "RootAnalyzer.h"
#include "TROOT.h"
#include "ToString.h"

RootAnalyzer::RootAnalyzer(const char* raFileName, const char* histFileName)
  : m_outputFile(0), m_tree(0), m_branch(0), m_mcFile(0), m_mcTree(0),
    m_mcBranch(0), m_mcEvent(0), m_reconFile(0), m_reconTree(0), 
    m_reconBranch(0), m_reconEvent(0), m_digiFile(0), m_digiTree(0),
    m_digiBranch(0), m_digiEvent(0), m_histFile(0)
{
  // make sure unsigned can hold 32 bit data 
  assert(sizeof(unsigned) >= 4);

    // initialize ROOT if not already done
  if(gROOT == 0) {
    static TROOT gRoot("RootAnalyzer", "RootAnalyzer");
  }

  // open output ra root file
  // No need to delete m_outputFile as ROOT will do the garbage collection

  if(raFileName != "") {
    m_outputFile = new TFile(raFileName, "RECREATE"); 
    m_tree = new TTree("Output", "Root Analyzer");

    // create new branch
    m_tree->Branch("Analysis", &m_ntuple, NtupleDef::gRootNtupleDefStr);
  }

  if(histFileName != "") {
    m_histFile = new TFile(histFileName, "RECREATE");

    // create histograms for strip hits

    for(int iTower = 0; iTower != g_nTower; ++iTower) {
      for(int iLayer = 0; iLayer != g_nTkrLayer; ++iLayer) {
	for(int iView = 0; iView != g_nView; ++iView) {

	  char name1[] = "hit00000";
	  sprintf(name1, "hit%02d%02d%1d", iTower, iLayer, iView);

	  m_stripHits[iTower][iLayer][iView] = 
	    new TH1F(name1, name1, g_nStripsPerLayer, 0, g_nStripsPerLayer);

	  char name2[] = "map00000";
	  sprintf(name2, "map%02d%02d%1d", iTower, iLayer, iView);

	  m_stripMap[iTower][iLayer][iView] = 
	    new TH2F(name2, name2, g_nFEC, 0, g_nFEC, g_nStripsPerLayer/g_nFEC,
		     0, g_nStripsPerLayer/g_nFEC);

	}
      }
    }
  }

}

RootAnalyzer::~RootAnalyzer()
{
  TDirectory* saveDir = gDirectory;

  if(m_outputFile) {
    m_outputFile->cd();
    m_outputFile->Write(0, TObject::kOverwrite);
    m_outputFile->Close();
  }

  if(m_histFile) {
    m_histFile->cd();
    m_histFile->Write(0, TObject::kOverwrite);
    m_histFile->Close();
  }

  saveDir->cd();
}


void RootAnalyzer::analyzeMcTree()
{
    m_ntuple.m_runId = (int) m_mcEvent->getRunId();

    m_ntuple.m_seqNo = (int) m_mcEvent->getSequence();

    // get info about primary particle
    McParticle* particle = m_mcEvent->getMcParticle(0);
    if(particle) {
      m_ntuple.m_parId = particle->getParticleId();
      m_ntuple.m_mcEnergy = particle->getInitialFourMomentum().E();
      const TVector3& pos = particle->getInitialPosition();
      m_ntuple.m_startPos[0] = (float) pos.X();
      m_ntuple.m_startPos[1] = (float) pos.Y();
      m_ntuple.m_startPos[2] = (float) pos.Z();
      const TLorentzVector& lor = particle->getInitialFourMomentum();
      float norm = sqrt(lor(0)*lor(0) + lor(1)*lor(1) + lor(2)*lor(2));
      m_ntuple.m_startDir[0] = lor(0)/norm;
      m_ntuple.m_startDir[1] = lor(1)/norm;
      m_ntuple.m_startDir[2] = lor(2)/norm;
    }

    // get gamma conversion (pair production) point
    int nPar = m_mcEvent->getMcParticleCount();

    // first particle produced by pair production, used in filling m_pairEne
    int iPair = 0;

    double x0, y0, z0, x1, y1, z1;

    for(int iPar = 0; iPar != nPar; ++iPar) {
      McParticle* par = m_mcEvent->getMcParticle(iPar);
      if(par && par->getProcess() == "conv" && iPair == 0) {
	  const TVector3& pos = par->getInitialPosition();
	  m_ntuple.m_convPos[0] = (float) pos.X();
	  m_ntuple.m_convPos[1] = (float) pos.Y();
	  m_ntuple.m_convPos[2] = (float) pos.Z();
	  m_ntuple.m_pairEne[iPair++] = par->getInitialFourMomentum().Energy();
	  x0 = par->getInitialFourMomentum().Px();
	  y0 = par->getInitialFourMomentum().Py();
	  z0 = par->getInitialFourMomentum().Pz();
	  continue;
      }
      if(par && par->getProcess() == "conv" && iPair == 1) { 
	//second particle produced by pair production
	  m_ntuple.m_pairEne[iPair++] = par->getInitialFourMomentum().Energy();
	  x1 = par->getInitialFourMomentum().Px();
	  y1 = par->getInitialFourMomentum().Py();
	  z1 = par->getInitialFourMomentum().Pz();
      }
    }

    if(iPair == 2) { // there is a conversion
      double a = sqrt(x0*x0 + y0*y0 + z0*z0);
      double b = sqrt(x1*x1 + y1*y1 + z1*z1);
      m_ntuple.m_convAngle = acos((x0*x1 + y0*y1 + z0*z1) / (a * b) );
    }

    // fill in energy deposited in each TKR layer
    int nPosHit = m_mcEvent->getMcPositionHitCount();
    for(int iPosHit = 0; iPosHit != nPosHit; ++iPosHit) {
      McPositionHit* posHit = m_mcEvent->getMcPositionHit(iPosHit);
      if(posHit) {
	VolumeIdentifier id = posHit->getVolumeId();
	int iTower, iLayer, iView;
	if( extractTowerLayerView(id, iTower, iLayer, iView) ) {
	    m_ntuple.m_depositEne[iTower][iLayer][iView] += 
	      posHit->getDepositedEnergy();
	}
      }
    } 

    // fill in energy deposited in CAL
    int nIntHit = m_mcEvent->getIntegratingHitCount();
    m_ntuple.m_mcCalEnergy = 0.;
    for(int iIntHit = 0; iIntHit != nIntHit; ++iIntHit) {
      McIntegratingHit* intHit = m_mcEvent->getMcIntegratingHit(iIntHit);
      if(intHit) {
	VolumeIdentifier id = intHit->getVolumeId();
	// the 4th id must be 0 if the volume is a CAL crystal
	if(id[3] == 0) {
	  m_ntuple.m_mcCalEnergy += intHit->getTotalEnergy();
	}
      }
    }
}
 

void RootAnalyzer::analyzeReconTree()
{
  TkrRecon* tkrRecon = m_reconEvent->getTkrRecon();
 
  assert(tkrRecon != 0);

  TObjArray* siClusterCol = tkrRecon->getClusterCol();
  if(siClusterCol) {
    int nClusters = siClusterCol->GetLast()+1;
    // fill in no of clusters in each layer
    for(int i = 0; i != nClusters; ++i) {
      TkrCluster* cluster = dynamic_cast<TkrCluster*>(siClusterCol->At(i));
      if(cluster) {

	int iTower = cluster->getTower();
	int iPlane = cluster->getPlane();
	int iView = cluster->getView();

	// note here difinition of the plane is different to difinition of the
	// layer. Plane 0 is at top !!! So we need to do the conversions
	int iLayer = g_nTkrLayer - 1 - iPlane;
	assert(iLayer >= 0 && iLayer <= g_nTkrLayer - 1);

	++m_ntuple.m_nTkrClusters[iTower][iLayer][iView];

      }
    }
  }

  m_ntuple.m_nTkrTracks = tkrRecon->getTrackCol()->GetLast()+1;
  m_ntuple.m_nTkrVertices = tkrRecon->getVertexCol()->GetLast()+1;

  // fill in info stored in the very first vertex
  TObjArray* vertices = tkrRecon->getVertexCol();
  if(m_ntuple.m_nTkrVertices >= 1) {
    TkrVertex* tkrVertex = dynamic_cast<TkrVertex*>(vertices->At(0));
    if(tkrVertex) {
      const TVector3& pos = tkrVertex->getPosition();
      const TVector3& dir = tkrVertex->getDirection();
      m_ntuple.m_pos[0] = pos.X();
      m_ntuple.m_pos[1] = pos.Y();
      m_ntuple.m_pos[2] = pos.Z();
      m_ntuple.m_dir[0] = dir.X();
      m_ntuple.m_dir[1] = dir.Y();
      m_ntuple.m_dir[2] = dir.Z();
      m_ntuple.m_fitTotalEnergy = tkrVertex->getEnergy();
      m_ntuple.m_vtxTrks = tkrVertex->getNumTracks();
    }
  }

  // fill in info stored in the very first and second track
  TObjArray* tracks = tkrRecon->getTrackCol();
  for(int i = 0; i != 2; ++i) {
    TkrKalFitTrack* tkrTrack = 
      dynamic_cast<TkrKalFitTrack*>(tracks->At(i));
    if(tkrTrack) {
      m_ntuple.m_nFit[i] += (int) tkrTrack->getNumHits();
      m_ntuple.m_chi2[i] = tkrTrack->getChiSquare();
      m_ntuple.m_chi2Smooth[i] = tkrTrack->getChiSquareSmooth();
      m_ntuple.m_rms[i] = tkrTrack->getScatter();
      m_ntuple.m_msAngle[i] = tkrTrack->getKalThetaMS();
      m_ntuple.m_tkrEnergy[i] = tkrTrack->getKalEnergy();
    }
  }

  // calculate energy measured in calorimeter
  CalRecon* calRecon = m_reconEvent->getCalRecon();
  if(calRecon) {
    TObjArray* calClusterCol = calRecon->getCalClusterCol();
    if(calClusterCol) {
      // currently there is just one cluster in CAL
      CalCluster* calCluster = dynamic_cast<CalCluster*>(calClusterCol->At(0));
      if(calCluster) {
	m_ntuple.m_calPos[0] = calCluster->getPosition().x();
	m_ntuple.m_calPos[1] = calCluster->getPosition().y();
	m_ntuple.m_calPos[2] = calCluster->getPosition().z();
	m_ntuple.m_calEnergy = calCluster->getEnergySum();
      }
    }

    TObjArray* calXtalRecCol = calRecon->getCalXtalRecCol();

    if(calXtalRecCol) {
      int nCalRec = calXtalRecCol->GetLast() + 1;

      for(int i = 0; i != nCalRec; ++i) {
	CalXtalRecData* calData = 
	  dynamic_cast<CalXtalRecData*>(calXtalRecCol->At(i));
	if(calData) {

	  CalXtalId id = calData->getPackedId();
	  int iTower = id.getTower();
	  int iLayer = id.getLayer();
	  int iCol = id.getColumn();

	  float ene = calData->getEnergy();

	  if(ene >= 0) ++(m_ntuple.m_nCrystalHit[iTower]);

	  m_ntuple.m_xtalEne[iTower][iLayer][iCol] = ene;

	  if(ene > m_ntuple.m_maxCalEnergy) m_ntuple.m_maxCalEnergy = ene;
	}
      }
    }

  }  // calRecon
}
  
void RootAnalyzer::analyzeDigiTree()
{
  m_ntuple.m_runId = m_digiEvent->getRunId();
  m_ntuple.m_eventId = m_digiEvent->getEventId();

  m_ntuple.m_trigger = m_digiEvent->getL1T().getTriggerWord();

  m_ntuple.m_timeStamp = m_digiEvent->getTimeStamp();

  m_ntuple.m_ebfSecond = m_digiEvent->getEbfTimeSec();
  m_ntuple.m_ebfNanoSecond =  m_digiEvent->getEbfTimeNanoSec();

  m_ntuple.m_upperTime = m_digiEvent->getEbfUpperPpcTimeBase();
  m_ntuple.m_lowerTime = m_digiEvent->getEbfLowerPpcTimeBase();

  m_ntuple.m_summaryWord = m_digiEvent->getEventSummaryData().summary();

  // mc events can not have diagnostic info, also check summary word
  if( (! m_mcFile) && m_digiEvent->getEventSummaryData().diagnostic() ) {
    diagnostic();
  }


  // fill in no of Tkr digis and TOTs
  m_ntuple.m_nTkrDigis = m_digiEvent->getTkrDigiCol()->GetLast()+1;

  for(int i = 0; i != m_ntuple.m_nTkrDigis; ++i) {
    const TkrDigi* tkrDigi = m_digiEvent->getTkrDigi(i);

    assert(tkrDigi != 0);

   // fill hit patterns for each plane
    fillStripHits(tkrDigi);

    int iTower = tkrDigi->getTower().id();
    int iLayer = tkrDigi->getBilayer();
    GlastAxis::axis iView = tkrDigi->getView();
  
    int nStrips = tkrDigi->getNumHits();
    if(iView == GlastAxis::X) {
      m_ntuple.m_nStrips[iTower][iLayer][0] = nStrips;
      m_ntuple.m_tot[iTower][iLayer][0][0] = tkrDigi->getToT(0);
      m_ntuple.m_tot[iTower][iLayer][0][1] = tkrDigi->getToT(1);
    }
    else if(iView == GlastAxis::Y) {
      m_ntuple.m_nStrips[iTower][iLayer][1] = nStrips;
      m_ntuple.m_tot[iTower][iLayer][1][0] = tkrDigi->getToT(0);
      m_ntuple.m_tot[iTower][iLayer][1][1] = tkrDigi->getToT(1);
    }

      // fill in corrected tot
      if(m_mcFile == 0) {
	correctTotDataLinear(tkrDigi);
	correctTotDataQuad(tkrDigi);
      }
  }
}

void RootAnalyzer::fillOutputTree()
{
  if(m_outputFile) {
    TDirectory* saveDir = gDirectory;
    m_outputFile->cd();
    m_tree->Fill();
    saveDir->cd();
  }
}

void RootAnalyzer::analyzeTrees(const char* mcFileName="mc.root",
				const char* digiFileName="digi.root",
				const char* reconFileName="recon.root")
{
  //open 3 root files

  m_mcFile = new TFile(mcFileName, "READ");
  // check whether file exists
  if(m_mcFile->IsZombie()) m_mcFile = 0;
  if(m_mcFile) {
    m_mcTree = (TTree*) m_mcFile->Get("Mc");
    m_mcEvent = 0;  
    m_mcBranch = m_mcTree->GetBranch("McEvent");
    // what is stored in the root tree is actually a pointer rather than
    // mc event
    m_mcBranch->SetAddress(&m_mcEvent);
  }

  m_reconFile = new TFile(reconFileName, "READ");
  if(m_reconFile->IsZombie()) m_reconFile = 0;
  if(m_reconFile) {
    m_reconTree = (TTree*) m_reconFile->Get("Recon");
    m_reconEvent = 0;
    m_reconBranch = m_reconTree->GetBranch("ReconEvent");
    m_reconBranch->SetAddress(&m_reconEvent);
  }

  m_digiFile = new TFile(digiFileName, "READ");
  if(m_digiFile->IsZombie()) m_digiFile = 0;
  if(m_digiFile) {
    m_digiTree = (TTree*) m_digiFile->Get("Digi");
    m_digiEvent = 0;
    m_digiBranch = m_digiTree->GetBranch("DigiEvent");
    m_digiBranch->SetAddress(&m_digiEvent);
  }

  int nEvent, nMc, nRecon, nDigi;
  if(m_mcFile) {
    nMc = (int) m_mcTree->GetEntries();
    std::cout << "No of events in " << mcFileName << " : " << nMc << std::endl;
    nEvent = nMc;
  }
  if(m_reconFile) {
    nRecon = (int) m_reconTree->GetEntries();
    std::cout << "No of events in " << reconFileName << " : " << nRecon << std::endl;
    nEvent = nRecon;
  }
  if(m_digiFile) {
    nDigi = (int) m_digiTree->GetEntries();
    std::cout << "No of events in " << digiFileName << " : " << nDigi << std::endl;
    nEvent = nDigi;
  }

  if(m_mcFile == 0) { 
    // read in tot correction constants for Hiro's linear formula
    readTotCorrLinear(1, 0, "/nfs/farm/g/glast/u03/EM2003/rootFiles/em_v1r030302p5/tot//chargeInjection_x1.txt");
    readTotCorrLinear(1, 1, "/nfs/farm/g/glast/u03/EM2003/rootFiles/em_v1r030302p5/tot//chargeInjection_y1.txt");
    readTotCorrLinear(2, 0, "/nfs/farm/g/glast/u03/EM2003/rootFiles/em_v1r030302p5/tot//chargeInjection_x2.txt");
    readTotCorrLinear(2, 1, "/nfs/farm/g/glast/u03/EM2003/rootFiles/em_v1r030302p5/tot//chargeInjection_y2.txt");
    readTotCorrLinear(3, 0, "/nfs/farm/g/glast/u03/EM2003/rootFiles/em_v1r030302p5/tot//chargeInjection_x3.txt");
    readTotCorrLinear(3, 1, "/nfs/farm/g/glast/u03/EM2003/rootFiles/em_v1r030302p5/tot//chargeInjection_y3.txt");

    // read in tot correction constants for Hiro's quadratic formula
    readTotCorrQuad(1, 0, "/nfs/farm/g/glast/u03/EM2003/htajima/forEduardo/TkrTotGainNt_LayerX1_101003530.tnt");
    readTotCorrQuad(1, 1, "/nfs/farm/g/glast/u03/EM2003/htajima/forEduardo/TkrTotGainNt_LayerY1_101003530.tnt");
    readTotCorrQuad(2, 0, "/nfs/farm/g/glast/u03/EM2003/htajima/forEduardo/TkrTotGainNt_LayerX2_101003530.tnt");
    readTotCorrQuad(2, 1, "/nfs/farm/g/glast/u03/EM2003/htajima/forEduardo/TkrTotGainNt_LayerY2_101003530.tnt");
    readTotCorrQuad(3, 0, "/nfs/farm/g/glast/u03/EM2003/htajima/forEduardo/TkrTotGainNt_LayerX3_101003530.tnt");
    readTotCorrQuad(3, 1, "/nfs/farm/g/glast/u03/EM2003/htajima/forEduardo/TkrTotGainNt_LayerY3_101003530.tnt");
  }

  //        nEvent = 100;
     //   nEvent = nRecon;

  for(int iEvent = 0; iEvent != nEvent; ++iEvent) {

    //    m_timeFile << iEvent;

    m_ntuple.reset();  

    if(m_mcFile) {
      m_mcBranch->GetEntry(iEvent);
      analyzeMcTree();
    }

    if(m_digiFile) {
      m_digiBranch->GetEntry(iEvent);
      analyzeDigiTree();
    }

    if(m_reconFile) {
      m_reconBranch->GetEntry(iEvent);
      analyzeReconTree();
    }

    analyzeTot();

    fillOutputTree();
    if(m_mcEvent) m_mcEvent->Clear();
    if(m_digiEvent) m_digiEvent->Clear();
    if(m_reconEvent) m_reconEvent->Clear();
  }  
  
  if(m_mcFile) m_mcFile->Close();
  if(m_reconFile) m_reconFile->Close();
  if(m_digiFile) m_digiFile->Close();
}

bool RootAnalyzer::extractTowerLayerView(const VolumeIdentifier& id, 
					 int& iTower, int& iLayer, 
					 int& iView) const
{
  // id code is formatted as the following (if only one tower is simulated):
  // Tower(0)/TowerY(0)/TowerX(0)/TKR(1)/TrayNo(0-18)/Measure(0,1)/View(0,1)/
  // Ladder/Waffer

  iTower = id[0];

  // not Tracker
  if(id[3] != 1) return 0;

  int iTray = id[4];
  iView = id[5];  // Measure X: 0, Measure Y: 1
  int iBotTop = id[6];  // Bott: 0, Top: 1

  iLayer = iTray -1 + iBotTop;

  // check boundary condition
  if(iTower<0 || iTower>15 || iLayer<0 || iLayer>17 || iView<0 || 
     iView>1) return 0;

  return 1;
}

void RootAnalyzer::fillStripHits(const TkrDigi* tkrDigi)
{

  int tower = tkrDigi->getTower().id();
  int layer = tkrDigi->getBilayer(); 
  int view = tkrDigi->getView();

  int nStrips = tkrDigi->getNumHits();

  TDirectory* saveDir = gDirectory;
  m_histFile->cd();

  for(int i = 0; i != nStrips; ++i) {

    int stripId = tkrDigi->getStrip(i);
    m_stripHits[tower][layer][view]->Fill(stripId);

    int nStripPerFEC = g_nStripsPerLayer / g_nFEC;

    int fec = stripId / nStripPerFEC;
    int res = stripId - fec * nStripPerFEC;

    m_stripMap[tower][layer][view]->Fill(fec, res);

  }

  saveDir->cd();
}

void RootAnalyzer::readTotCorrLinear(int layer, int view, const char* file)
{

  m_aveTotGain[layer][view] = 0;
  m_aveTotOffset[layer][view] = 0;

  std::ifstream corrFile(file);
  for(int i = 0; i != 14; ++i) {
    std::string temp;
    std::getline(corrFile, temp);
  }

  int stripId;
  float gain, offset;

  int count = 0;
  while(corrFile >> stripId >> gain >> offset) {
    ++count;
    m_totGain[layer][view][stripId] = gain;
    m_totOffset[layer][view][stripId] = offset;
    m_aveTotGain[layer][view] += gain;
    m_aveTotOffset[layer][view] += offset;
  }

  assert( count == g_nStripsPerLayer);

  m_aveTotGain[layer][view] /= count;
  m_aveTotOffset[layer][view] /= count;

}

void RootAnalyzer::readTotCorrQuad(int layer, int view, const char* file)
{

  std::ifstream corrFile(file);
  for(int i = 0; i != 2; ++i) {
    std::string temp;
    std::getline(corrFile, temp);
  }

  int stripId, feId;
  float p0, p1, p2, chi2;

  int count = 0;
  while(corrFile >> stripId >> feId >> p0 >> p1 >> p2 >> chi2) {
    ++count;
    m_totP0[layer][view][stripId] = p0;
    m_totP1[layer][view][stripId] = p1;
    m_totP2[layer][view][stripId] = p2;
  }

  assert( count == g_nStripsPerLayer);

}

int RootAnalyzer::midStripId(int iLayer, GlastAxis::axis iView) const
{
  if(iLayer == 1 && iView == GlastAxis::X) {
    return g_nStripsPerLayer / g_nFEC * 4;
  }
  else {
    return g_nStripsPerLayer / 2;
  }
}

void RootAnalyzer::correctTotDataLinear(const TkrDigi* tkrDigi)
{
  int iTower = tkrDigi->getTower().id();
  int iLayer = tkrDigi->getBilayer();
  GlastAxis::axis view = tkrDigi->getView();

  int boundary = midStripId(iLayer, view);

  // iView = 0 means measureX, 1 means measure Y
  int iView;

  if(view == GlastAxis::X) {
    iView = 0;
  }
  else {
    iView = 1;
  }

  int nhits = tkrDigi->getNumHits();

  vector<int> hits;
  for(int i = 0; i != nhits; ++i) {
    hits.push_back(tkrDigi->getHit(i));
  }

  // convert TOT raw count to micro second
  float totTime[2];
  totTime[0] = ((tkrDigi->getToT(0)) << 2) * 0.05;
  totTime[1] = ((tkrDigi->getToT(1)) << 2) * 0.05;

  // since we don't know which strip has longest tot, we simply do an averaged
  // correction here
  float charge0 = 0, charge1 = 0;
  int count0 = 0, count1 = 0;

  for(int i = 0; i != nhits; ++i) {
    if(hits[i] < boundary) {      
      charge0 += (totTime[0] - m_totOffset[iLayer][iView][hits[i]]) / m_totGain[iLayer][iView][hits[i]];
      ++count0;
    }
    else {
      charge1 += (totTime[1] - m_totOffset[iLayer][iView][hits[i]]) / m_totGain[iLayer][iView][hits[i]];
      ++count1;
    }
  }

  if(count0 != 0) charge0 /= count0;
  if(count1 != 0) charge1 /= count1;

  m_ntuple.m_totCorrLinear[iTower][iLayer][iView][0] = charge0;
  m_ntuple.m_totCorrLinear[iTower][iLayer][iView][0] = charge1;

}

void RootAnalyzer::correctTotDataQuad(const TkrDigi* tkrDigi)
{
  int iTower = tkrDigi->getTower().id();
  int iLayer = tkrDigi->getBilayer();
  GlastAxis::axis view = tkrDigi->getView();

  int boundary = midStripId(iLayer, view);

  // iView = 0 means measureX, 1 means measure Y
  int iView;

  if(view == GlastAxis::X) {
    iView = 0;
  }
  else {
    iView = 1;
  }

  int nhits = tkrDigi->getNumHits();

  vector<int> hits;
  for(int i = 0; i != nhits; ++i) {
    hits.push_back(tkrDigi->getHit(i));
  }

  // convert TOT raw count to micro second
  float totTime[2];
  totTime[0] = ((tkrDigi->getToT(0)) << 2) * 0.05;
  totTime[1] = ((tkrDigi->getToT(1)) << 2) * 0.05;

  // since we don't know which strip has longest tot, we simply do an averaged
  // correction here
  float charge0 = 0, charge1 = 0;
  int count0 = 0, count1 = 0;

  for(int i = 0; i != nhits; ++i) {
    if(hits[i] < boundary) {   
      double temp = quadTotFormula(iLayer, iView, hits[i], totTime[0]);
      if(temp > 0) {   
	charge0 += temp;
	++count0;
      }
    }
    else {
      double temp = quadTotFormula(iLayer, iView, hits[i], totTime[0]);
      if(temp > 0) {   
	charge1 += temp;
	++count1;
      }
    }
  }

  if(count0 != 0) charge0 /= count0;
  if(count1 != 0) charge1 /= count1;

  m_ntuple.m_totCorrQuad[iTower][iLayer][iView][0] = charge0;
  m_ntuple.m_totCorrQuad[iTower][iLayer][iView][0] = charge1;

}

double RootAnalyzer::quadTotFormula(int layer, int view, int strip, double tot)
{
  if(m_totP2[layer][view][strip] == 0) {
    double charge =  (tot - m_totP0[layer][view][strip]) / m_totP1[layer][view][strip];
    if(charge < 0) ++ m_nTotNegRoot;
    return charge;
  }

  double temp = m_totP1[layer][view][strip]*m_totP1[layer][view][strip] - 4.*m_totP2[layer][view][strip]*(m_totP0[layer][view][strip]-tot);

  if(temp < 0) {
    ++ m_nTotNoRoot;
    return -9999;
  }

  double charge = (-m_totP1[layer][view][strip] + sqrt(temp)) / (2.*m_totP2[layer][view][strip]);

  if(charge < 0) ++m_nTotNegRoot;

  return charge;
}

void RootAnalyzer::analyzeTot()
{
  for(int iTower = 0; iTower != g_nTower; ++iTower) {
    for(int iLayer = (g_nTkrLayer-1); iLayer >= 0; --iLayer) {

      if(m_ntuple.m_nStrips[iTower][iLayer][0] > 0 &&
	 m_ntuple.m_nStrips[iTower][iLayer][1] > 0) {

	float totX = std::max(m_ntuple.m_tot[iTower][iLayer][0][0], 
			      m_ntuple.m_tot[iTower][iLayer][0][1]);
	float totY = std::max(m_ntuple.m_tot[iTower][iLayer][1][0], 
			      m_ntuple.m_tot[iTower][iLayer][1][1]);

	m_ntuple.m_topTot[iTower] = std::max(totX, totY);
	break;
      }
    }

  }

  if(m_ntuple.m_nTkrTracks > 0) {

    TkrRecon* tkrRecon = m_reconEvent->getTkrRecon();
    TObjArray* vertices = tkrRecon->getVertexCol();
    if(m_ntuple.m_nTkrVertices >= 1) {
      TkrVertex* tkrVertex = dynamic_cast<TkrVertex*>(vertices->At(0));
      if(tkrVertex) {

	int convLayer = g_nTkrLayer - 1 - tkrVertex->getLayer();
	int convTower = tkrVertex->getTower();

	assert(convLayer >= 0 && convLayer <g_nTkrLayer);
	float totX = std::max(m_ntuple.m_tot[convTower][convLayer][0][0], 
			      m_ntuple.m_tot[convTower][convLayer][0][1]);
	float totY = std::max(m_ntuple.m_tot[convTower][convLayer][1][0], 
			      m_ntuple.m_tot[convTower][convLayer][1][1]);

	m_ntuple.m_convTot = std::max(totX, totY);
      }
    }
  }
 
}

void RootAnalyzer::diagnostic()
{
  int iTower = 0;

  if(m_digiEvent->getTkrDiagnosticCol()) {
    int nTkrDiag = m_digiEvent->getTkrDiagnosticCol()->GetLast()+1;

    assert(nTkrDiag == 8);

    for(int i = 0; i != nTkrDiag; ++i) {

      const TkrDiagnosticData* pDiag = m_digiEvent->getTkrDiagnostic(i);

      m_ntuple.m_tpTkr[iTower][i] = pDiag->getDataWord();

    }

    ElecToGeo::getInstance()->decodeTkrTp(m_ntuple.m_tpTkr, 
					  m_ntuple.m_tkrReq, iTower);
  }

  if(m_digiEvent->getCalDiagnosticCol()) {

    int nCalDiag = m_digiEvent->getCalDiagnosticCol()->GetLast()+1;

    assert(nCalDiag == 8);

    for(int i = 0; i != nCalDiag; ++i) {

      const CalDiagnosticData* pDiag = m_digiEvent->getCalDiagnostic(i);

      m_ntuple.m_tpCal[iTower][i] = pDiag->getDataWord();
      ElecToGeo::getInstance()->decodeCalTp(m_ntuple.m_tpCal, 
					    m_ntuple.m_calReq, iTower);

    }

  }
}

