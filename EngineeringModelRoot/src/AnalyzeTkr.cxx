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
#include "strings.h"
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
    digiFile = argv[1];
    outputFile = "temp.ntp";
  }

  TFile f(outputFile.c_str(), "RECREATE");

  TNtuple tuple("tuple", "tuple", "id:uPpcT:lPpcT");
  unsigned id, uPpcT, lPpcT;

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

  nEvent = 100;

  for(int iEvent = 0; iEvent != nEvent; ++iEvent) { 

    if(m_digiEvent) m_digiEvent->Clear();

    m_digiTree->GetEvent(iEvent);

    const TObjArray* tkrDigiCol = m_digiEvent->getTkrDigiCol();

    if (!tkrDigiCol) continue;

    int nTkrDigis = tkrDigiCol->GetLast()+1;

    for(int i = 0; i != nTkrDigis; ++i) {

      const TkrDigi* tkrDigi = m_digiEvent->getTkrDigi(i);
      assert(tkrDigi != 0);

      int nHits = tkrDigi->getNumHits();

      for(int j = 0; j != nHits; ++j) {
	int strip = tkrDigi->getHit(j);
	printf("strip id = %i \n", strip);
      }

    }

  }
  f.cd();
  //  rawAdcHist->Write();
  tuple.Write();
}

