// 
// Class for input of quantity FT1EventClassBitMap for monitoring 
// 
// Created by dpaneque on Wed Jun  8 19:17:51 2011 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_FT1EventClassBitMap.h"
#include <iostream>

// User defined part 

#define NAME FT1EventClassBitMap
#define OUTBRANCH "FT1EventClassBitMap"
#define LEAF "FT1EventClassBitMap[16]/I"
#define INBRANCH "FT1EventClass"
#define ACCESSOR NotApplicable
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Vector [16] reporting the bit map of merit variable FT1EventClass"


// End user defined part 

MonInput_FT1EventClassBitMap::MonInput_FT1EventClassBitMap(){
  m_name=OUTBRANCH;
}
MonInput_FT1EventClassBitMap::~MonInput_FT1EventClassBitMap(){
}


int MonInput_FT1EventClassBitMap::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_FT1EventClassBitMap::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_inputval);
}
void MonInput_FT1EventClassBitMap::setValue(TObject* event) {

  for (Int_t i = 0; i<16;i++)
    m_val[i] = 0;
  
  for (Int_t i = 0; i<16;i++){
    if(m_inputval & 1 << i)
      m_val[i] = 1;
  }

}
std::string MonInput_FT1EventClassBitMap::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_FT1EventClassBitMap::getDescription(){
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

