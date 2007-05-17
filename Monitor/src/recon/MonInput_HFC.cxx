// 
// Class for input of quantity HFC for monitoring 
// 
// Created by kocian on Mon May 14 20:21:34 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_HFC.h"
#include <iostream>
#include <math.h>


// User defined part 

#define NAME HFC
#define OUTBRANCH "HFC"
#define LEAF "HFC/O"
#define INBRANCH "m_cal"
#define ACCESSOR bla
#define MONSOURCE ReconEvent
#define INPUTSOURCE "ReconEvent"
#define DESCRIPTION "HFC filter bit"
#include "reconRootData/ReconEvent.h"

// End user defined part 

MonInput_HFC::MonInput_HFC(){
  m_name=OUTBRANCH;
}
MonInput_HFC::~MonInput_HFC(){
}


int MonInput_HFC::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_HFC::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_HFC::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  TObjArray *xtalRecCol = de->getCalRecon()->getCalXtalRecCol();
  TIter xtalIter(xtalRecCol);
  CalXtalRecData *xtal = 0;
  Double_t layereng[8];
  Int_t xtalsoverthresh[8];
  for (int j=0;j<8;j++){
    layereng[j]=0;
    xtalsoverthresh[j]=0;
  }
  Double_t threshold=50; // 50 MeV threshold
  while ((xtal = (CalXtalRecData*)xtalIter.Next())) {
    const CalXtalId& cId=xtal->getPackedId();
    Int_t layer  = cId.getLayer();
    double xenergy=xtal->getEnergy();
    layereng[layer]+=xenergy;
    if (xenergy>threshold)xtalsoverthresh[layer]++;
  }
  m_val=false;
  if (xtalsoverthresh[0]==0 ||xtalsoverthresh[1]==0 || xtalsoverthresh[2]==0 ){
    m_val=true;
  }else if(xtalsoverthresh[0]>2 ||xtalsoverthresh[1]>2 || xtalsoverthresh[2]>2 ){
    m_val=true;
  }else{
    Double_t energy_tolerance=layereng[0]*20./128;
    if (fabs(layereng[1]-layereng[0])>energy_tolerance || fabs(layereng[1]-layereng[0])>energy_tolerance)m_val=true;
  }
}
    
std::string MonInput_HFC::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_HFC::getDescription(){
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

