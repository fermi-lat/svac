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
  TH1F h2("h2", "h2", 72, -0.5, 71.5);
  TH1F h3("h3", "h3", 72, -0.5, 71.5);
  TH1F h4("h4", "h4", 72, -0.5, 71.5);
  TH1F h5("h5", "h5", 72, -0.5, 71.5);

  int nEvt[72];
  bzero((void*) nEvt, 72*sizeof(int));

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

    for(int i = 0; i != nTkrDigis; ++i) {
      const TkrDigi* tkrDigi = m_digiEvent->getTkrDigi(i);

      assert(tkrDigi != 0);

      int iTower = tkrDigi->getTower().id();
      int iLayer = tkrDigi->getBilayer();
      GlastAxis::axis view = tkrDigi->getView();
      int iView = (view == GlastAxis::X) ? 0 : 1;

      vector<UInt_t> hitCol = tkrDigi->getHitCol();

      std::sort(hitCol.begin(), hitCol.end());

      int nStrips = hitCol.size();
      assert(nStrips > 0);

      int last0Strip = tkrDigi->getLastController0Strip();

      bool has0Strip = false;
      bool has1Strip = false;

      if(last0Strip <0) {
	has1Strip = true;
      }
      else if(last0Strip < hitCol[hitCol.size()-1]) {
	has0Strip = true;
	has1Strip = true;
      }
      else if(last0Strip == hitCol[hitCol.size()-1]) {
	has0Strip = true;
      }
      else {
	assert("should not come here!");
      }

      if(has0Strip) ++nEvt[iLayer*4+iView*2];
      if(has1Strip) ++nEvt[iLayer*4+iView*2+1];

      if(has0Strip && tkrReq[iTower][iLayer][iView][0] == 0) {
	//	cout << "event " << iEvent << " has strips read out from low end of si plane at tower " << iTower << " biLayer " << iLayer << " view " << iView << " but has no trigger request!" << endl;
	//	std::copy(hitCol.begin(), hitCol.end(), std::ostream_iterator<int>(cout, " "));
	//	cout << endl;
	h1.Fill(iLayer*4+iView*2);
	if(nTkrDigis == 6) {
	  h2.Fill(iLayer*4+iView*2);
	}
	else if(nTkrDigis < 6) {
	  h3.Fill(iLayer*4+iView*2);
	}
      }
      else if(has0Strip && tkrReq[iTower][iLayer][iView][0] == 1) {
	h4.Fill(iLayer*4+iView*2);
      }

      if(has1Strip && tkrReq[iTower][iLayer][iView][1] == 0) {
	//	cout << "event " << iEvent << " has strips read out from high end of si plane at tower " << iTower << " biLayer " << iLayer << " view " << iView << " but has no trigger request!" << endl;
	//	std::copy(hitCol.begin(), hitCol.end(), std::ostream_iterator<int>(cout, " "));
	//	cout << endl;
	h1.Fill(iLayer*4+iView*2+1);
	if(nTkrDigis == 6) {
	  h2.Fill(iLayer*4+iView*2+1);
	}
	else if(nTkrDigis < 6) {
	  h3.Fill(iLayer*4+iView*2+1);
	}
      }
      else if(has1Strip && tkrReq[iTower][iLayer][iView][1] == 1) {
	h4.Fill(iLayer*4+iView*2+1);
      }
      

    }

  }

  for(int i = 0; i != 72; ++i) {
    h5.Fill(i, h1.GetBinContent(i+1)/double(nEvt[i]));
  }

  f.cd();
  f.Write(0, TObject::kOverwrite);
  f.Close();
}

