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

  //  nEvent = 1000;

  id = 0;
  unsigned prevUPpcT = 0;
  for(int iEvent = 0; iEvent != nEvent; ++iEvent) { 

    if(m_digiEvent) m_digiEvent->Clear();

    m_digiBranch->GetEntry(iEvent);
    uPpcT = m_digiEvent->getEbfUpperPpcTimeBase();
    lPpcT = m_digiEvent->getEbfLowerPpcTimeBase();

    assert(uPpcT >= prevUPpcT);

    //    cout << "id = " << id << " uPpcT = " << uPpcT << " lPpcT = " << lPpcT 
    //	 << endl;

    prevUPpcT = uPpcT;

    tuple.Fill(id, uPpcT, lPpcT);
    ++id;
  }
  f.cd();
  //  rawAdcHist->Write();
  tuple.Write();
}

