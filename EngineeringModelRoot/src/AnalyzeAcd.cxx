#include <string>
#include <algorithm>
#include <map>
#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TH1F.h"
#include "TH2F.h"
#include "mcRootData/McEvent.h"
#include "reconRootData/ReconEvent.h"
#include "digiRootData/DigiEvent.h"

using namespace std;

int main(int argc, char** argv)
{
  string digiFile, outputFile;

  if(argc == 3) {
    digiFile = argv[1];
    outputFile = argv[2];
  }
  else {
    digiFile = "/nfs/farm/g/glast/u01/mc/em_v2r0402p4/flight/surface_muons_100000_0_digi.root";
    outputFile = "temp.ntp";
  }

  TFile f(outputFile.c_str(), "RECREATE");

  TNtuple tuple("tuple", "tuple", "event:id:pmt1:pmt2");

  TFile m_digiFile(digiFile.c_str(), "READ");
  if(m_digiFile.IsZombie()) {
    cout << "digi file not found" << endl;
    exit(1);
  }

  TTree* m_digiTree = (TTree*) m_digiFile.Get("Digi");
  DigiEvent* m_digiEvent = 0;
  TBranch* m_digiBranch = m_digiTree->GetBranch("DigiEvent");
  m_digiBranch->SetAddress(&m_digiEvent);
  
  int nEvent = (int) m_digiTree->GetEntries();

  for(int iEvent = 0; iEvent != nEvent; ++iEvent) { 

    if(iEvent%1000 == 0) {
      cout <<" process " << iEvent << endl;
    }

    m_digiBranch->GetEntry(iEvent);

    const TObjArray* acdDigiCol = m_digiEvent->getAcdDigiCol();
    if (!acdDigiCol) continue;

    int nAcdDigi = acdDigiCol->GetLast()+1;

    for(int iDigi = 0; iDigi != nAcdDigi; ++iDigi) {

      const AcdDigi* acdDigi = dynamic_cast<const AcdDigi*>(acdDigiCol->At(iDigi));

      assert(acdDigi != 0);

      int id = acdDigi->getId().getId();

      tuple.Fill(iEvent, id, acdDigi->getPulseHeight(AcdDigi::A), acdDigi->getPulseHeight(AcdDigi::B));

    }
  }
 
  f.cd();
  tuple.Write();
}

