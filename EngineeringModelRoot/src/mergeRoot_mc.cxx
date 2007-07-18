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
#include "/nfs/farm/g/glast/u09/builds/rh9_gcc32opt/EngineeringModel/EngineeringModel-v6r070329p27/mcRootData/v2r19p3/mcRootData/McEvent.h"


using std::string;
using std::cout;
using std::endl;

// Merge mc root files:
string jobDataFile    = "../src/job.dat";
string mcDir        = "/nfs/farm/g/glast/u06/borgland/Workshop_mnc/EngineeringModel-v3r0402p17/LatIntegration/v1r0p1/Output/";

int main() 
{

  string fileName;
  ifstream inputFile(jobDataFile.c_str());
  
  // Combined mc file name:
  TFile *newfile = new TFile("merged_mc.root","recreate");
  TTree* newtree; 

  // Set max file size to 25 GB:
  Long64_t maxTreeSize = 25000000000;
  newtree->SetMaxTreeSize(maxTreeSize);

  int iLoop = 0;

  // Loop over input files to merge:
  while (inputFile >> fileName) {

    string mcFileName = mcDir + fileName + "_mc.root";

    // Check whether file can be properly opened:
    TFile mcF(mcFileName.c_str());
    if(mcF.IsOpen()) {
      mcF.Close();
    }
    else {
      cout << "********" << mcFileName.c_str() << 
    	"can not be opened *****" << " skip this file" << endl;
      continue;
    }
    cout << "Opening file " << mcFileName << endl;
  
 
    TFile *mcfile = new TFile (mcFileName.c_str());
    TTree *mcTree = (TTree *) mcfile->Get("Mc");

    // Set branch address: 
    McEvent *evt = 0;
    mcTree->SetBranchAddress("McEvent",&evt);

    gDirectory->cd("merged_mc.root:/");
    if (iLoop == 0) { 
      newtree = (TTree*) mcTree->CloneTree(0);
    }             
    iLoop++;

    // Total number of entries in the file:
    Int_t nentries = Int_t (mcTree->GetEntriesFast());

    // Loop over all the events in the eventlist:
    for (Int_t jentry=0; jentry<nentries;jentry++) {

      // Get the mc tree entry:
      mcTree->GetEvent(jentry);

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

