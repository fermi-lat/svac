/* 
@file evtFilter.C
@brief Filter events from a digi or mc file.
@author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST LAT I&T/SVAC
*/

#ifndef __CINT__ 
#include <stdlib.h>
#include <iostream>
#include <TROOT.h> 
#include "TChain.h"
#include "TLeaf.h"
#include "TObjArray.h"
#include "TObjString.h"
#endif

#include "digiRootData/DigiEvent.h"

TTree *evtFilter(char *meritName, char *digiName, TCut cut, char *outName) {

  TFile *meritFile = new TFile(meritName);
  TFile *digiFile = new TFile(digiName);

  TTree *meritTree = (TTree *) meritFile->Get("MeritTuple");
  meritTree->Draw(">>keepers", cut);

  TTree *digiTree = (TTree *) digiFile->Get("Digi");
  digiTree->SetEventList(keepers);
  outTree = digiTree->CopyTree("");

  TFile outFile(outName, "RECREATE");
  outTree->Write();

  return outTree;
}

