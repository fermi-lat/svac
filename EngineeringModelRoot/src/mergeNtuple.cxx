#include <string>
#include <fstream>
#include <iostream>
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "NtupleDef.h"
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

  NtupleDef* ntuple = new NtupleDef;

  TChain chainedTree1("Output");
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
    //    chainedTree1.SetBranchAddress("Analysis", ntuple);
    chainedTree1.Add(svacFileName.c_str());
    
    std::cout << "Opening file " << meritFileName << std::endl;
    chainedTree2.Add(meritFileName.c_str());
  }

  chainedTree1.Merge(mergedSvacFile.c_str());
  chainedTree2.Merge(mergedMeritFile.c_str());

  delete ntuple;

}

