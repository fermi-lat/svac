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

// merge both svac and merit root files

TROOT merge("merge", "merge root files");

std::string mergedSvacFile = "merge_svac.root";

std::string mergedMeritFile = "merge_merit.root";

std::string jobDataFile = "../src/job.dat";

std::string svacDir = "/nfs/farm/g/glast/u01/mc/em_v1r0401p9/oneTower/";
std::string meritDir = svacDir;

int main() 
{

  std::string fileName;

  ifstream inputFile(jobDataFile.c_str());

  TChain chainedTree1("Output");

  chainedTree1.SetAutoSave(2000000000);

  TChain chainedTree2("MeritTuple");

  while(inputFile >> fileName) {
    std::string svacFileName = svacDir + fileName + "_svac.root";
    std::string meritFileName = meritDir + fileName + "_merit.root";

    // check whether file can be properly opened
    TFile svacF(svacFileName.c_str());
    if(svacF.IsOpen()) {
      svacF.Close();
    }
    else {
      std::cout << "********" << svacFileName.c_str() << 
	"can not be opened *****" << " skip this file" << std::endl;
      continue;
    }

    std::cout << "Opening file " << svacFileName << std::endl;
    chainedTree1.Add(svacFileName.c_str());
    
    std::cout << "Opening file " << meritFileName << std::endl;
    chainedTree2.Add(meritFileName.c_str());
  }

  double nEvent = chainedTree1.GetEntries();
  std::cout << "Total number of event = " << nEvent << std::endl;

  chainedTree1.Merge(mergedSvacFile.c_str());
  chainedTree2.Merge(mergedMeritFile.c_str());

  // merged svac ntuple is too large, so it contains two cycles of the Output
  // tree, we need to delete the previous cycle

  TFile f(mergedSvacFile.c_str(), "UPDATE");

  TList* l = f.GetListOfKeys();

  int size = l->GetSize();

  assert(size <= 2);

  if(size == 2) f.Delete("Output;1");

  f.Write(0, TObject::kOverwrite);

  f.Close();

}

