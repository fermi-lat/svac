// 
// Class for input of quantity CompressedEventSizeInBytes for monitoring 
// 
// Created by dpaneque on Mon Aug 11 18:04:30 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_CompressedEventSizeInBytes.h"
#include <iostream>

// User defined part 

#define NAME CompressedEventSizeInBytes
#define OUTBRANCH "CompressedEventSizeInBytes"
#define LEAF "CompressedEventSizeInBytes/i"
#define INBRANCH "m_metaEvent"
#define ACCESSOR getMetaEvent().compressedSize() 
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "bb"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_CompressedEventSizeInBytes::MonInput_CompressedEventSizeInBytes(){
  m_name=OUTBRANCH;
}
MonInput_CompressedEventSizeInBytes::~MonInput_CompressedEventSizeInBytes(){
}


int MonInput_CompressedEventSizeInBytes::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_CompressedEventSizeInBytes::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_CompressedEventSizeInBytes::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;
}
std::string MonInput_CompressedEventSizeInBytes::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_CompressedEventSizeInBytes::getDescription(){
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

