// 
// Class for input of quantity CurrentORPreviousTimeToneMissing for monitoring 
// 
// Created by dpaneque on Thu Apr 24 16:33:12 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_CurrentORPreviousTimeToneMissing.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME CurrentORPreviousTimeToneMissing
#define OUTBRANCH "CurrentORPreviousTimeToneMissing"
#define LEAF "CurrentORPreviousTimeToneMissing/O"
#define INBRANCH "m_metaEvent"
//#define ACCESSOR bb
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "1 if time tone from current or previous evt is NOT complete. Zero otherwise."
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_CurrentORPreviousTimeToneMissing::MonInput_CurrentORPreviousTimeToneMissing(){
  m_name=OUTBRANCH;
}
MonInput_CurrentORPreviousTimeToneMissing::~MonInput_CurrentORPreviousTimeToneMissing(){
}


int MonInput_CurrentORPreviousTimeToneMissing::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_CurrentORPreviousTimeToneMissing::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_CurrentORPreviousTimeToneMissing::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= 0;
  if(de->getMetaEvent().time().current().incomplete() || de->getMetaEvent().time().previous().incomplete())
    m_val =1;


}
std::string MonInput_CurrentORPreviousTimeToneMissing::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_CurrentORPreviousTimeToneMissing::getDescription(){
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

