// 
// Class for input of quantity DeltaEventTime for monitoring 
// 
// Created by dpaneque on Wed Oct  3 00:27:24 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_DeltaEventTime.h"
#include <iostream>

// User defined part 

#define NAME DeltaEventTime
#define OUTBRANCH "DeltaEventTime"
#define LEAF "DeltaEventTime/s"
#define INBRANCH "m_gem"
#define ACCESSOR getGem().getDeltaEventTime()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "GEM Delta event time counter in ticks of 50 ns. Saturates at 3.3 ms"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_DeltaEventTime::MonInput_DeltaEventTime(){
  m_name=OUTBRANCH;
}
MonInput_DeltaEventTime::~MonInput_DeltaEventTime(){
}


int MonInput_DeltaEventTime::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_DeltaEventTime::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_DeltaEventTime::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_DeltaEventTime::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_DeltaEventTime::getDescription(){
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

