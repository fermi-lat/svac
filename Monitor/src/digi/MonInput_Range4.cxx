// 
// Class for input of quantity Range4 for monitoring 
// 
// Created by dpaneque on Tue Aug 21 23:20:51 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_Range4.h"
#include <iostream>

// User defined part 

#define NAME Range4
#define OUTBRANCH "Range4"
#define LEAF "Range4/O"
#define INBRANCH "m_summary"
#define ACCESSOR getEventSummaryData().readout4()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Flag reporting (when 1) a 4 range readout. The value is 0 otherwise."
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_Range4::MonInput_Range4(){
  m_name=OUTBRANCH;
}
MonInput_Range4::~MonInput_Range4(){
}


int MonInput_Range4::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_Range4::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_Range4::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= Bool_t(de->ACCESSOR);
}
std::string MonInput_Range4::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_Range4::getDescription(){
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

