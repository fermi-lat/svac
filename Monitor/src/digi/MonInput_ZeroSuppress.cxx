// 
// Class for input of quantity ZeroSuppress for monitoring 
// 
// Created by dpaneque on Thu Jan 24 19:13:42 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_ZeroSuppress.h"
#include <iostream>

// User defined part 

#define NAME ZeroSuppress
#define OUTBRANCH "ZeroSuppress"
#define LEAF "ZeroSuppress/O"
#define INBRANCH "m_summary"
#define ACCESSOR getEventSummaryData().zeroSuppress()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Flag reporting a ZeroSuppressed readout (when 1). If event is NOT zero suppressed, then the value is 0."
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_ZeroSuppress::MonInput_ZeroSuppress(){
  m_name=OUTBRANCH;
}
MonInput_ZeroSuppress::~MonInput_ZeroSuppress(){
}


int MonInput_ZeroSuppress::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_ZeroSuppress::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_ZeroSuppress::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= Bool_t(de->ACCESSOR);
}
std::string MonInput_ZeroSuppress::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_ZeroSuppress::getDescription(){
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

