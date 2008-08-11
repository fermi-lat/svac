// 
// Class for input of quantity CompressionLevel for monitoring 
// 
// Created by dpaneque on Mon Aug 11 18:05:27 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_CompressionLevel.h"
#include <iostream>

// User defined part 

#define NAME CompressionLevel
#define OUTBRANCH "CompressionLevel"
#define LEAF "CompressionLevel/I"
#define INBRANCH "m_metaEvent"
#define ACCESSOR getMetaEvent().compressionLevel() 
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "bbb"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_CompressionLevel::MonInput_CompressionLevel(){
  m_name=OUTBRANCH;
}
MonInput_CompressionLevel::~MonInput_CompressionLevel(){
}


int MonInput_CompressionLevel::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_CompressionLevel::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_CompressionLevel::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_CompressionLevel::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_CompressionLevel::getDescription(){
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

