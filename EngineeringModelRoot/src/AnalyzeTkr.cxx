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
#include "GeoToElec.h"
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
  TH1F h1("h1", "CC occupancy", 8, -0.5, 7.5);
  TH1F h2("h2", "RC occupancy", 9, -0.5, 8.5);
  TH2F h3("h3", "CC and RC occupancy", 8, -0.5, 7.5, 9, -0.5, 8.5);

  TFile m_digiFile(digiFile.c_str(), "READ");
  if(m_digiFile.IsZombie()) {
    cout << "digi file not found: " << digiFile << endl;
    exit(1);
  }

  TTree* digiTree = (TTree*) m_digiFile.Get("Digi");
  DigiEvent* digiEvent = 0;
  TBranch* m_digiBranch = digiTree->GetBranch("DigiEvent");
  m_digiBranch->SetAddress(&digiEvent);
  
  int nEvent = (int) digiTree->GetEntries();

  //  nEvent = 100;

  for(int iEvent = 0; iEvent != nEvent; ++iEvent) { 

    if(digiEvent) digiEvent->Clear();

    digiTree->GetEvent(iEvent);

    int id = digiEvent->getEventId();


    int nTkrDigis = digiEvent->getTkrDigiCol()->GetLast()+1;

    for(int i = 0; i != nTkrDigis; ++i) {
      const TkrDigi* tkrDigi = digiEvent->getTkrDigi(i);
    
      assert(tkrDigi != 0);

      int tower = tkrDigi->getTower().id();
      int layer = tkrDigi->getBilayer();
      GlastAxis::axis iView = tkrDigi->getView();
      int view = (iView == GlastAxis::X) ? 0 : 1;

      int nStrips = tkrDigi->getNumHits();

      for(int i = 0; i != nStrips; ++i) {

	int stripId = tkrDigi->getStrip(i);

	int last0Strip = tkrDigi->getLastController0Strip();

	int end;

	if(last0Strip < 0) {
	  end = 1;
	}
	else if(stripId <= last0Strip) {
	  end = 0;
	}
	else {
	  end = 1;
	}

	GeoToElec::gtcc_gtrc temp = GeoToElec::getInstance()->getGtccGtrc(layer, view, end);

	h1.Fill(temp.m_gtcc);
	h2.Fill(temp.m_gtrc);
	h3.Fill(temp.m_gtcc, temp.m_gtrc);
      }
    }
  }

  f.cd();
  f.Write(0, TObject::kOverwrite);
  f.Close();
}

