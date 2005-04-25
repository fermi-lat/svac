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

string mergedSvacFile = "merge_svac.root";

string mergedMeritFile = "merge_merit.root";

string jobDataFile = "../src/job.dat";

string svacDir = "/nfs/farm/g/glast/u01/mc/em_v3r0404p2/fullLat/";
string meritDir = svacDir;

int main() 
{

  string fileName;

  ifstream inputFile(jobDataFile.c_str());

  TChain chainedTree1("Output");

  chainedTree1.SetAutoSave(2000000000);

  // Set max file size to 25 GB:
  Long64_t maxTreeSize = 25000000000;
  chainedTree1.SetMaxTreeSize(maxTreeSize);

  TChain chainedTree2("MeritTuple")
  chainedTree2.SetMaxTreeSize(maxTreeSize);


  while(inputFile >> fileName) {
    string svacFileName = svacDir + fileName + "_svac.root";
    string meritFileName = meritDir + fileName + "_merit.root";

    // check whether file can be properly opened
    TFile svacF(svacFileName.c_str());
    if(svacF.IsOpen()) {
      svacF.Close();
    }
    else {
      cout << "********" << svacFileName.c_str() << 
	"can not be opened *****" << " skip this file" << endl;
      continue;
    }

    cout << "Opening file " << svacFileName << endl;
    chainedTree1.Add(svacFileName.c_str());
    
    cout << "Opening file " << meritFileName << endl;
    chainedTree2.Add(meritFileName.c_str());
  }

  double nEvent = chainedTree1.GetEntries();
  cout << "Total number of event = " << nEvent << endl;

  chainedTree1.Merge(mergedSvacFile.c_str());
  chainedTree2.Merge(mergedMeritFile.c_str());

  // merged svac ntuple is too large, so it contains two cycles of the Output
  // tree, we need to delete the previous cycle

  TFile f(mergedSvacFile.c_str(), "UPDATE");

  TList* l = f.GetListOfKeys();

  int size = l->GetSize();

  assert(size <= 2);

  if(size == 2) {
    TKey* k = (TKey*) l->At(1);
    string name("Output;");
    name += ToString(k->GetCycle());
    f.Delete(name.c_str());
  }

  f.Write(0, TObject::kOverwrite);

  f.Close();

}

