#include <string>
#include <fstream>
#include <iostream>
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1.h"
#include "TList.h"
#include "TKey.h"
#include "ToString.h"
#include "TLeaf.h"
#include "TObjArray.h"
#include "TObjString.h"
#include "/nfs/slac/g/svac/common/builds/Fred/RootLibraries_EMv3r0402p17/digiRootData/v7r2/digiRootData/DigiEvent.h"


using std::string;
using std::cout;
using std::endl;

// Merge Digi root files:

string jobDataFile    = "../src/job.dat";
string digiDir        = "/nfs/farm/g/glast/u06/borgland/Workshop_mnc/EngineeringModel-v3r0402p17/LatIntegration/v1r0p1/Output/";

int main() 
{

  string fileName;
  ifstream inputFile(jobDataFile.c_str());
  
  // Combined digi file name:
  TFile *newfile = new TFile("merged_digi.root","recreate");
  TTree* newtree; 

  int iLoop = 0;

  // Loop over input files to merge:
  while (inputFile >> fileName) {

    string digiFileName = digiDir + fileName + "_digi.root";

    // Check whether file can be properly opened:
    TFile digiF(digiFileName.c_str());
    if(digiF.IsOpen()) {
      digiF.Close();
    }
    else {
      cout << "********" << digiFileName.c_str() << 
    	"can not be opened *****" << " skip this file" << endl;
      continue;
    }
    cout << "Opening file " << digiFileName << endl;
  
 
    TFile *digifile = new TFile (digiFileName.c_str());
    TTree *digiTree = (TTree *) digifile->Get("Digi");

    // Set branch address: 
    DigiEvent *evt = 0;
    digiTree->SetBranchAddress("DigiEvent",&evt);

    gDirectory->cd("awb_merged_digi.root:/");
    if (iLoop == 0) { 
      newtree = (TTree*) digiTree->CloneTree(0);
    }             
    iLoop++;

    // Total number of entries in the file:
    Int_t nentries = Int_t (digiTree->GetEntriesFast());

    // Loop over all the events in the eventlist:
    for (Int_t jentry=0; jentry<nentries;jentry++) {

      // Get the digi tree entry:
      digiTree->GetEvent(jentry);

      // Copy it over to the new (merged) tree:
      if (evt) {
	newtree->Fill();
        evt->Clear();
      }
    }
  }

  // Write out the filtered tree:
  newtree->Write();
  newfile->Write();
  newfile->Close();
}

