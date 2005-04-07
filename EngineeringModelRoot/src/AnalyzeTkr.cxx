#include <iostream>
#include <iterator>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>
#include <strings.h>
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
  TNtuple tuple("tuple", "tuple", "maxNHits:cc:rc:badEvt:fifoErr");

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

    int nEvtPerCcRc[8][9];
    bzero(nEvtPerCcRc, 72*sizeof(int));

    int nEvtPerCc[8];
    bzero(nEvtPerCc, 8*sizeof(int));

    if(digiEvent) digiEvent->Clear();
    
    digiTree->GetEvent(iEvent);

    int id = digiEvent->getEventId();
     
    int nTkrDigis = digiEvent->getTkrDigiCol()->GetLast()+1;

    int maxNhits = 0, ccMaxHits = -9999, rcMaxHits = -9999;

    for(int i = 0; i != nTkrDigis; ++i) {
      const TkrDigi* tkrDigi = digiEvent->getTkrDigi(i);
    
      assert(tkrDigi != 0);

      int tower = tkrDigi->getTower().id();
      int layer = tkrDigi->getBilayer();
      GlastAxis::axis iView = tkrDigi->getView();
      int view = (iView == GlastAxis::X) ? 0 : 1;

      GeoToElec::gtcc_gtrc temp = GeoToElec::getInstance()->getGtccGtrc(layer, view, 0);
      int lowEndCc = temp.m_gtcc;
      int rc = temp.m_gtrc;

      temp = GeoToElec::getInstance()->getGtccGtrc(layer, view, 1);
      int highEndCc = temp.m_gtcc;

      int nStrips = tkrDigi->getNumHits();

      for(int i = 0; i != nStrips; ++i) {

	int stripId = tkrDigi->getStrip(i);

	int last0Strip = tkrDigi->getLastController0Strip();

	if(last0Strip < 0 || stripId > last0Strip) {
	  ++nEvtPerCcRc[highEndCc][rc];
	  ++nEvtPerCc[highEndCc];
	}
	else {
	  ++nEvtPerCcRc[lowEndCc][rc];
	  ++nEvtPerCc[lowEndCc];	  
	}

      }

      int maxNhits2End = std::max(nEvtPerCcRc[lowEndCc][rc], nEvtPerCcRc[highEndCc][rc]);

      if(maxNhits2End > maxNhits) {
	ccMaxHits = (nEvtPerCcRc[lowEndCc][rc]>=nEvtPerCcRc[highEndCc][rc]) ? lowEndCc : highEndCc;

	rcMaxHits = rc;

	maxNhits = maxNhits2End;
      }

    }


    int badEvt =  0;
    for(int i = 0; i != 8; ++i) {
      assert(nEvtPerCc[i] <= 128);
      if(nEvtPerCc[i] == 128) {
	badEvt = 1;
      }
    }
     
    bool temErr = digiEvent->getEventSummaryData().errorEventSummary();
    
    int fifoErr = (temErr) ? 1 : 0;

    tuple.Fill(maxNhits, ccMaxHits, rcMaxHits, badEvt, fifoErr);
  }

  f.cd();
  f.Write(0, TObject::kOverwrite);
  f.Close();
}

