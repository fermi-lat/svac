// 
// Class for input of quantity PrescaledLast for monitoring 
// 
// Created by dpaneque on Fri Apr 27 01:45:05 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_PrescaledLast.h"
#include <iostream>

// User defined part 

#define NAME PrescaledLast
#define OUTBRANCH "PrescaledLast"
#define LEAF "PrescaledLast/l"
#define INBRANCH "m_metaEvent"
#define ACCESSOR getMetaEvent().scalers().prescaled()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Number of events prescaled away (in hardware) in this run "
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_PrescaledLast::MonInput_PrescaledLast(){
}
MonInput_PrescaledLast::~MonInput_PrescaledLast(){
}


int MonInput_PrescaledLast::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_PrescaledLast::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_PrescaledLast::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_PrescaledLast::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_PrescaledLast::getDescription(){
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

