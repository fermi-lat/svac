#include <iostream>
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
    digiFile = "";
    outputFile = "temp.ntp";
  }

  TFile f(outputFile.c_str(), "RECREATE");

  TNtuple tuple("tuple", "tuple", "event:layer:col:side:range:adc");

  //  int nLayers = 8, nCols = 12, nSides = 2, nRanges = 4;

  /*
  TObjArray* rawAdcHist = new TObjArray(nLayers*nCols*nSides);

  for(int iLayer = 0; iLayer != nLayers; ++iLayer) {
    for(int iCol = 0; iCol != nCols; ++iCol) {
      for(int iSide = 0; iSide != nSides; ++iSide) {
	  char rawAdcName[] = "adc0000";
	  sprintf(rawAdcName, "adc%1d%02d%1d", iLayer, iCol, iSide);
	  rawAdcHist->AddAt(new TH1F(rawAdcName, rawAdcName,300, 0, 4200),
			    iLayer*nCols*nSides + iCol*nSides + iSide);
      }
    }
  }
  */

  TFile m_digiFile(digiFile.c_str(), "READ");
  if(m_digiFile.IsZombie()) {
    cout << "digi file not found" << endl;
    exit;
  }

  TTree* m_digiTree = (TTree*) m_digiFile.Get("Digi");
  DigiEvent* m_digiEvent = 0;
  TBranch* m_digiBranch = m_digiTree->GetBranch("DigiEvent");
  m_digiBranch->SetAddress(&m_digiEvent);
  
  int nEvent = (int) m_digiTree->GetEntries();

  //  nEvent = 10;

  for(int iEvent = 0; iEvent != nEvent; ++iEvent) { 

    m_digiBranch->GetEntry(iEvent);

    const TObjArray* calDigiCol = m_digiEvent->getCalDigiCol();
    if (!calDigiCol) continue;

    int nCalDigi = calDigiCol->GetLast()+1;

    for(int iDigi = 0; iDigi != nCalDigi; ++iDigi) {

      const CalDigi* calDigi = dynamic_cast<const CalDigi*>(calDigiCol->At(iDigi));

      assert(calDigi != 0);

      const CalXtalId id = calDigi->getPackedId();
      int layer = id.getLayer();
      int col = id.getColumn();

      //      ((TH1F*) rawAdcHist->At(layer*nCols*nSides + col*nSides))->Fill(calDigi->getAdc(0, CalXtalId::NEG));

      //      ((TH1F*) rawAdcHist->At(layer*nCols*nSides + col*nSides + 1))->Fill(calDigi->getAdc(0, CalXtalId::POS));

      tuple.Fill(iEvent, layer, col, 0, 0, calDigi->getAdc(0, CalXtalId::NEG));
      tuple.Fill(iEvent, layer, col, 1, 0, calDigi->getAdc(0, CalXtalId::POS));

    }
  }
 
  f.cd();
  //  rawAdcHist->Write();
  tuple.Write();
}

