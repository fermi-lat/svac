// 
// Class for input of quantity DataTransferId for monitoring 
// 
// Created by dpaneque on Fri May 16 01:13:45 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_DataTransferId.h"
#include <iostream>

// User defined part 

#define NAME DataTransferId
#define OUTBRANCH "DataTransferId"
#define LEAF "DataTransferId/i"
#define INBRANCH "m_metaEvent"
#define ACCESSOR getMetaEvent().run().dataTransferId()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Id number assigned to the data transfer"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_DataTransferId::MonInput_DataTransferId(){
  m_name=OUTBRANCH;
}
MonInput_DataTransferId::~MonInput_DataTransferId(){
}


int MonInput_DataTransferId::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_DataTransferId::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_DataTransferId::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_DataTransferId::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_DataTransferId::getDescription(){
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

