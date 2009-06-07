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

using std::string;
using std::cout;
using std::endl;

// merge both svac and merit root files

TROOT merge("merge", "merge root files");

string mergedDigiFile = "merge_digi.root";

string jobDataFile = "../src/job.dat";

string digiDir = "/nfs/farm/g/glast/u01/svac_workshop/em_v3r0402p9/mc/TwoTowers/cr/batch/";

int main() 
{

  string fileName;

  ifstream inputFile(jobDataFile.c_str());

  TChain chainedTreeDigi("Digi");

  chainedTreeDigi.SetAutoSave(2000000000);

  while(inputFile >> fileName) {
    string digiFileName = digiDir + fileName + "_digi.root";

    // check whether file can be properly opened
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
    chainedTreeDigi.Add(digiFileName.c_str());
    
  }

  double nEvent = chainedTreeDigi.GetEntries();
  cout << "Total number of event = " << nEvent << endl;

  chainedTreeDigi.Merge(mergedDigiFile.c_str());

}

