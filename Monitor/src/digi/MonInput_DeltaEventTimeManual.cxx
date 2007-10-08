// 
// Class for input of quantity DeltaEventTimeManual for monitoring 
// 
// Created by dpaneque on Mon Oct  8 19:35:18 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_DeltaEventTimeManual.h"
#include <iostream>

// User defined part 

#define NAME DeltaEventTimeManual
#define OUTBRANCH "DeltaEventTimeManual"
#define LEAF "DeltaEventTimeManual/D"
#define INBRANCH "m_timeStamp"
// #define ACCESSOR getTimeStamp()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Delta evt time computed using digi->getTimeStamp()"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_DeltaEventTimeManual::MonInput_DeltaEventTimeManual(){
  m_name=OUTBRANCH;
   firstevt = 1;
  m_previous = 0;
  m_current = 0;
}
MonInput_DeltaEventTimeManual::~MonInput_DeltaEventTimeManual(){
}


int MonInput_DeltaEventTimeManual::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_DeltaEventTimeManual::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_DeltaEventTimeManual::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val = 0.0;
  m_current = de->getTimeStamp();
  if(firstevt){
    m_previous = m_current;
    firstevt = 0;
  }
  else{
    m_val = m_current-m_previous;
    m_previous = m_current;
  }

}
std::string MonInput_DeltaEventTimeManual::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_DeltaEventTimeManual::getDescription(){
  return DESCRIPTION;
}

#undef INPUTSOURCE
#undef NAME
#undef OUTBRANCH
#undef LEAF
#undef INBRANCH 
//#undef ACCESSOR
#undef MONSOURCE
#undef DESCRIPTION

