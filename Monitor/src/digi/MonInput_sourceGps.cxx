// 
// Class for input of quantity sourceGps for monitoring 
// 
// Created by dpaneque on Thu Apr 24 23:26:12 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_sourceGps.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME sourceGps
#define OUTBRANCH "sourceGps"
#define LEAF "sourceGps/O"
#define INBRANCH "m_metaEvent"
//#define ACCESSOR bb
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "DigiEvent->getMetaEvent().time().current().sourceGPS(). It returns true if GPS is in lock, false otherwise."
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_sourceGps::MonInput_sourceGps(){
  m_name=OUTBRANCH;
}
MonInput_sourceGps::~MonInput_sourceGps(){
}


int MonInput_sourceGps::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_sourceGps::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_sourceGps::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }

  m_val= Bool_t(de->getMetaEvent().time().current().sourceGps());

}
std::string MonInput_sourceGps::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_sourceGps::getDescription(){
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

