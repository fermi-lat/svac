// 
// Class for input of quantity xoverthresh for monitoring 
// 
// Created by kocian on Thu May 31 20:39:26 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_xoverthresh.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME xoverthresh
#define OUTBRANCH "xoverthresh"
#define LEAF "xoverthresh[8]/s"
#define INBRANCH "m_cal"
#define ACCESSOR asf
#define MONSOURCE ReconEvent
#define INPUTSOURCE "ReconEvent"
#define DESCRIPTION "Number of crystals over 50 MeV threhold per layer"
#include "reconRootData/ReconEvent.h"

// End user defined part 

MonInput_xoverthresh::MonInput_xoverthresh(){
  m_name=OUTBRANCH;
}
MonInput_xoverthresh::~MonInput_xoverthresh(){
}


int MonInput_xoverthresh::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_xoverthresh::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_xoverthresh::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  for (int j=0;j<8;j++){
    m_val[j]=0;
  }
  TObjArray *xtalRecCol = de->getCalRecon()->getCalXtalRecCol();
  TIter xtalIter(xtalRecCol);
  CalXtalRecData *xtal = 0;
  Double_t threshold=50; // 50 MeV threshold
  while ((xtal = (CalXtalRecData*)xtalIter.Next())) {
    const CalXtalId& cId=xtal->getPackedId();
    Int_t layer  = cId.getLayer();
    double xenergy=xtal->getEnergy();
    if (xenergy>threshold)m_val[layer]++;
  }
}
std::string MonInput_xoverthresh::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_xoverthresh::getDescription(){
  return DESCRIPTION;
}

#undef INPUTSOURCE
#undef NAME
#undef OUTBRANCH
#undef LEAF
#undef INBRANCH 
#undef ACCESSOR
#undef MONSOURCE
#undef DESCRIPTION

