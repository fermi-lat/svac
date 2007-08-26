// 
// Class for input of quantity DeadZoneLast for monitoring 
// 
// Created by dpaneque on Fri Apr 27 01:42:06 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_DeadZoneLast.h"
#include <iostream>

// User defined part 

#define NAME DeadZoneLast
#define OUTBRANCH "DeadZoneLast"
#define LEAF "DeadZoneLast/l"
#define INBRANCH "m_metaEvent"
#define ACCESSOR getMetaEvent().scalers().deadzone()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Number of events lost because they arrived in the 2-tick deadzone in this run "
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_DeadZoneLast::MonInput_DeadZoneLast(){
}
MonInput_DeadZoneLast::~MonInput_DeadZoneLast(){
}


int MonInput_DeadZoneLast::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_DeadZoneLast::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_DeadZoneLast::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_DeadZoneLast::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_DeadZoneLast::getDescription(){
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

