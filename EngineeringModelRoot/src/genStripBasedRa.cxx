#include <string>
#include <algorithm>
#include <map>
#include <fstream>
#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TH1F.h"
#include "TH2F.h"
#include "mcRootData/McEvent.h"
#include "reconRootData/ReconEvent.h"
#include "digiRootData/DigiEvent.h"

bool extractLayerView(const VolumeIdentifier& id, int& iLayer, 
				    int& iView) 
{
  // id code is formatted as the following (if only one tower is simulated):
  // Tower(0)/TowerY(0)/TowerX(0)/TKR(1)/TrayNo(0-18)/Measure(0,1)/View(0,1)/
  // Ladder/Waffer

  if(id[0] != 0) return false;

  // not Tracker
  if(id[3] != 1) return 0;

  int iTray = id[4];
  iView = id[5];  // Measure X: 0, Measure Y: 1
  int iBotTop = id[6];  // Bott: 0, Top: 1

  iLayer = iTray -1 + iBotTop;

  // check boundary condition
  if(iLayer < 0 || iLayer > 17 || iView < 0 || iView > 1) return 0;

  return 1;
}

int main()
{
  TFile f("rootFile/ebf030904225708_strip.ntp", "RECREATE");
  TNtuple tuple("tuple", "tuple", "stripId:layer:view:xDir:yDir:zDir");

  TFile m_digiFile("rootFile/ebf030904225708_digi.root", "READ");
  if(m_digiFile.IsZombie()) {
    cout << "mc file not found" << endl;
    exit;
  }

  TTree* m_digiTree = (TTree*) m_digiFile.Get("Digi");
  DigiEvent* m_digiEvent = 0;
  TBranch* m_digiBranch = m_digiTree->GetBranch("DigiEvent");
  m_digiBranch->SetAddress(&m_digiEvent);
  
  int nEvent = (int) m_digiTree->GetEntries();

  TFile m_reconFile("rootFile/ebf030904225708_recon.root", "READ");
  if(m_reconFile.IsZombie()) {
    cout << "recon file not found" << endl;
    exit;
  }

  TTree* m_reconTree = (TTree*) m_reconFile.Get("Recon");
  ReconEvent* m_reconEvent = 0;
  TBranch* m_reconBranch = m_reconTree->GetBranch("ReconEvent");
  m_reconBranch->SetAddress(&m_reconEvent);

  //  nEvent = 100;

  for(int iEvent = 0; iEvent != nEvent; ++iEvent) { 

    float xDir = -9999., yDir = -9999., zDir = -9999.;

    m_reconBranch->GetEntry(iEvent);

    TkrRecon* tkrRecon = m_reconEvent->getTkrRecon();
    TObjArray* vertices = tkrRecon->getVertexCol();
    int noOfTkrVertices = tkrRecon->getVertexCol()->GetLast()+1;

    if(noOfTkrVertices >= 1) {
      TkrVertex* tkrVertex = dynamic_cast<TkrVertex*>(vertices->At(0));
      if(tkrVertex) {
	const TVector3& pos = tkrVertex->getPosition();
	const TVector3& dir = tkrVertex->getDirection();
	xDir = pos.X();
	yDir = pos.Y();
	zDir = pos.Z();
      }
    }

    m_digiBranch->GetEntry(iEvent);

    int noOfTkrDigis = m_digiEvent->getTkrDigiCol()->GetLast()+1;

    for(int i = 0; i != noOfTkrDigis; ++i) {
      const TkrDigi* tkrDigi = m_digiEvent->getTkrDigi(i);

      assert(tkrDigi != 0);

      int iLayer = tkrDigi->getBilayer();

      int view = tkrDigi->getView();

      int nHits = tkrDigi->getNumHits();

      for(int iHit = 0; iHit != nHits; ++iHit) {
	tuple.Fill(tkrDigi->getHit(iHit), iLayer, view, xDir, yDir, zDir);
      }
    }

  }

  f.cd();
  tuple.Write();
}

