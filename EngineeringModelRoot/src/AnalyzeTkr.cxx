#include <iostream>
#include <iterator>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>
#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TH1F.h"
#include "TH2F.h"
#include "strings.h"
#include "digiRootData/DigiEvent.h"
#include "GeoConstants.h"
#include "ElecToGeo.h"
#include "Geo.h"

using std::string;
using std::cout;
using std::endl;

int main(int argc, char** argv)
{
  string digiFile, outputFile;

  if(argc == 3) {
    digiFile = argv[1];
    outputFile = argv[2];
  }
  else {
    digiFile = argv[1];
    outputFile = "temp.ntp";
  }

  TFile f(outputFile.c_str(), "RECREATE");
  TH1F h1("h1", "h1", 72, -0.5, 71.5);
  TNtuple n1("n1", "n1", "nDigis:nRequests");

  //  int nEvt[72];
  //  bzero((void*) nEvt, 72*sizeof(int));

  TFile m_digiFile(digiFile.c_str(), "READ");
  if(m_digiFile.IsZombie()) {
    cout << "digi file not found: " << digiFile << endl;
    exit(1);
  }

  TTree* m_digiTree = (TTree*) m_digiFile.Get("Digi");
  DigiEvent* m_digiEvent = 0;
  TBranch* m_digiBranch = m_digiTree->GetBranch("DigiEvent");
  m_digiBranch->SetAddress(&m_digiEvent);
  
  int nEvent = (int) m_digiTree->GetEntries();

  //  nEvent = 100;

  for(int iEvent = 0; iEvent != nEvent; ++iEvent) { 

    if(m_digiEvent) m_digiEvent->Clear();

    m_digiTree->GetEvent(iEvent);

    // TKR trigger primitive
    unsigned int tpTkr[g_nTower][g_nGTCC];
    static unsigned int tpTkrSize = g_nTower*g_nGTCC*sizeof(unsigned int);
    bzero((void*) tpTkr, tpTkrSize);

  // decoded trigger primitive for the tracker
  // e.g.: m_tkrReq[0][3][0][0]=1 means tower 0, lower half of layer X3 sends the trigger request
  // e.g.: m_tkrReq[0][3][1][1]=1 means tower 0, upper half of layer Y3 sends the trigger request
  // layer 0 is at the bottom
    unsigned int tkrReq[g_nTower][g_nTkrLayer][g_nView][2];
    static unsigned int tkrReqSize = g_nTower*g_nTkrLayer*g_nView*2*sizeof(unsigned);
    bzero((void*) tkrReq, tkrReqSize);

    if(m_digiEvent->getTkrDiagnosticCol()) {
      int nTkrDiag = m_digiEvent->getTkrDiagnosticCol()->GetLast()+1;

      for(int i = 0; i != nTkrDiag; ++i) {

	const TkrDiagnosticData* pDiag = m_digiEvent->getTkrDiagnostic(i);
	tpTkr[pDiag->tower()][pDiag->gtcc()] = pDiag->getDataWord();

      }

      ElecToGeo::getInstance()->decodeTkrTp(tpTkr, tkrReq);
    }

    int nTkrDigis = m_digiEvent->getTkrDigiCol()->GetLast()+1;

    if(nTkrDigis >= 6) continue;

    int hitPos[g_nTkrLayer][g_nView];
    bzero((void*) hitPos, g_nTkrLayer*g_nView*sizeof(int));

    for(int i = 0; i != nTkrDigis; ++i) {
      const TkrDigi* tkrDigi = m_digiEvent->getTkrDigi(i);

      assert(tkrDigi != 0);

      int iTower = tkrDigi->getTower().id();
      int iLayer = tkrDigi->getBilayer();
      GlastAxis::axis view = tkrDigi->getView();
      int iView = (view == GlastAxis::X) ? 0 : 1;
      hitPos[iLayer][iView] = 1;      
    }

    int nTkrReq = 0;
    for(int biLayer = 0; biLayer != g_nTkrLayer; ++biLayer) {
      for(int view = 0; view != g_nView; ++view) {
	if( tkrReq[0][biLayer][view][0]==1 && hitPos[biLayer][view] == 0) {
	  int plane = Geo::instance()->getPlane(biLayer, view);
	  h1.Fill(plane*2);
	}
	else if(tkrReq[0][biLayer][view][1]==1 && hitPos[biLayer][view] == 0) {
	  int plane = Geo::instance()->getPlane(biLayer, view);
	  h1.Fill(plane*2+1);
	}
	if(tkrReq[0][biLayer][view][0] || tkrReq[0][biLayer][view][1]) ++nTkrReq;
      }
    }

    n1.Fill(nTkrDigis, nTkrReq);
  }

  f.cd();
  f.Write(0, TObject::kOverwrite);
  f.Close();
}

