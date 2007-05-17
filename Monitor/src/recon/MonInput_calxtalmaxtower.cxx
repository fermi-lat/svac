// 
// Class for input of quantity calxtalmaxtower for monitoring 
// 
// Created by kocian on Fri Apr 20 23:42:44 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_calxtalmaxtower.h"
#include <iostream>

// User defined part 

#define NAME calxtalmaxtower
#define OUTBRANCH "calxtalmaxtower"
#define LEAF "calxtalmaxtower/s"
#define INBRANCH "m_cal"
#define ACCESSOR bla
#define MONSOURCE ReconEvent
#define INPUTSOURCE "ReconEvent"
#define DESCRIPTION "Tower with highest crystal energy"
#include "reconRootData/ReconEvent.h"

// End user defined part 

MonInput_calxtalmaxtower::MonInput_calxtalmaxtower(){
  m_name=OUTBRANCH;
}
MonInput_calxtalmaxtower::~MonInput_calxtalmaxtower(){
}


int MonInput_calxtalmaxtower::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_calxtalmaxtower::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_calxtalmaxtower::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  TObjArray *xtalRecCol = de->getCalRecon()->getCalXtalRecCol();
  TIter xtalIter(xtalRecCol);
  CalXtalRecData *xtal = 0;
  m_val=-1;
  double energy=0;
  if (xtalRecCol){
    while ((xtal = (CalXtalRecData*)xtalIter.Next())) {
      const CalXtalId& cId=xtal->getPackedId();
      Int_t tower  = cId.getTower();
      double xenergy=xtal->getEnergy();
      if(xenergy>energy){
	energy=xenergy;
	m_val=tower;
      }
    }
  }
}
std::string MonInput_calxtalmaxtower::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_calxtalmaxtower::getDescription(){
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

