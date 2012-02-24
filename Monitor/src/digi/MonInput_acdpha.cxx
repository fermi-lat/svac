// 
// Class for input of quantity acdpha for monitoring 
// 
// Created by kocian on Sat May 26 18:13:04 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_acdpha.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME acdpha
#define OUTBRANCH "acdpha"
#define LEAF "acdpha[12][18]/s"
#define INBRANCH "m_acdDigiCol"
#define ACCESSOR asf
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "ACD PHA value by GARC and GAFE"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_acdpha::MonInput_acdpha(){
  m_name=OUTBRANCH;
}
MonInput_acdpha::~MonInput_acdpha(){
}


int MonInput_acdpha::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_acdpha::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_acdpha::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  for (int garc=0;garc<12;garc++){
    for (int gafe=0;gafe<18;gafe++){
      m_val[garc][gafe]=0;
    }
  }
  const TObjArray* acdDigiCol = de->getAcdDigiCol();
  if (acdDigiCol){
    TIter acdIter(acdDigiCol);
    AcdDigi* acddigi=0;
    while ((acddigi = (AcdDigi*)acdIter.Next())) {
      AcdId id=acddigi->getId();
      UInt_t garc,gafe;
      for (int pmt=0;pmt<2;pmt++){
	AcdId::convertToGarcGafe(id.getId(),pmt,garc,gafe);
	if(garc>11 || gafe>17)continue;
	m_val[garc][gafe]= acddigi->getPulseHeight((AcdDigi::PmtId)pmt);
      }
    }
  }
}
std::string MonInput_acdpha::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_acdpha::getDescription(){
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

