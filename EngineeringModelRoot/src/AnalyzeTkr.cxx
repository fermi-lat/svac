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
#include "RootAnalyzer.h"
#include "strings.h"

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

  TNtuple tuple("tuple", "tuple", "tower:layer:view:strip:count");
  long counts[RootAnalyzer::g_nTower][RootAnalyzer::g_nTkrLayer][RootAnalyzer::g_nView][RootAnalyzer::g_nStripsPerLayer];

  bzero(counts, RootAnalyzer::g_nTower*RootAnalyzer::g_nTkrLayer*RootAnalyzer::g_nView*RootAnalyzer::g_nStripsPerLayer*sizeof(long));

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

    if(m_digiEvent) m_digiEvent->Clear();

    m_digiBranch->GetEntry(iEvent);

    /*
    const TClonesArray* diagCol = m_digiEvent->getTkrDiagnosticCol();

    if(diagCol) {
      int nDiag = diagCol->GetLast()+1;
      for(int iDiag = 0; iDiag != nDiag; ++iDiag) {
	if(const TkrDiagnosticData* diag = dynamic_cast<const TkrDiagnosticData*>(diagCol->At(iDiag))) {
	  diag->Print();
	}
      }
    }
    else {
      cout << "no tkrDiagnostic info" << endl;
    }
    */

    const TObjArray* tkrDigiCol = m_digiEvent->getTkrDigiCol();
    if (!tkrDigiCol) continue;

    int nTkrDigi = tkrDigiCol->GetLast()+1;

    for(int iDigi = 0; iDigi != nTkrDigi; ++iDigi) {

      const TkrDigi* tkrDigi = dynamic_cast<const TkrDigi*>(tkrDigiCol->At(iDigi));

      assert(tkrDigi != 0);

      if(tkrDigi->getNumHits() == 1) {
	int tower = tkrDigi->getTower().id();
	int biLayer = tkrDigi->getBilayer();
	int view = tkrDigi->getView()==GlastAxis::X ? 0 : 1;
	int strip = tkrDigi->getStrip(0);
	++counts[tower][biLayer][view][strip];
      }
    }
    
  }
 
  for(int i = 0; i != RootAnalyzer::g_nTower; ++i) {
    for(int j = 0; j != RootAnalyzer::g_nTkrLayer; ++j) {
      for(int k = 0; k != RootAnalyzer::g_nView; ++k) {
	for(int l = 0; l != RootAnalyzer::g_nStripsPerLayer; ++l) {
	  tuple.Fill(i, j, k, l, counts[i][j][k][l]);
	}
      }
    }
  }
  f.cd();
  //  rawAdcHist->Write();
  tuple.Write();
}

