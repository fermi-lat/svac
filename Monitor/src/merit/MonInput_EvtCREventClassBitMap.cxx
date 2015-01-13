// 
// Class for input of quantity EvtCREventClassBitMap for monitoring 
// 
// Created by dpaneque on Wed Jun  8 19:38:30 2011 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_EvtCREventClassBitMap.h"
#include <iostream>

// User defined part 

#define NAME EvtCREventClassBitMap
#define OUTBRANCH "EvtCREventClassBitMap"
#define LEAF "EvtCREventClassBitMap[21]/I"
#define INBRANCH "EvtCREventClass"
#define ACCESSOR NotApplicable
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Vector [21] reporting the bit map of merit variable EvtCREventClass"


// End user defined part 

MonInput_EvtCREventClassBitMap::MonInput_EvtCREventClassBitMap(){
  m_name=OUTBRANCH;
}
MonInput_EvtCREventClassBitMap::~MonInput_EvtCREventClassBitMap(){
}


int MonInput_EvtCREventClassBitMap::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_EvtCREventClassBitMap::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_inputval);
}
void MonInput_EvtCREventClassBitMap::setValue(TObject* event) {
  for (Int_t i = 0; i<21;i++)
    m_val[i] = 0; 

  for (Int_t i = 0; i<21;i++){ 
    if(m_inputval & 1 << i)
      m_val[i] = 1; 
  }                   

}
std::string MonInput_EvtCREventClassBitMap::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_EvtCREventClassBitMap::getDescription(){
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

