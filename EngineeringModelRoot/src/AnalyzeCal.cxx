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

    int id = m_digiEvent->getEventId();

    if(id == 4542) {
      const TObjArray* calDigiCol = m_digiEvent->getCalDigiCol();

      if (!calDigiCol) continue;

      int nCalDigi = calDigiCol->GetLast()+1;

      cout << "nCalDigi = " << nCalDigi << endl;

    }
  }
 

}

