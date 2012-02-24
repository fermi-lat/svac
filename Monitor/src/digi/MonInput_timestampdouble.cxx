// 
// Class for input of quantity timestampdouble for monitoring 
// 
// Created by dpaneque on Fri Jul 20 01:17:49 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_timestampdouble.h"
#include <iostream>
#include <cassert>
#include <iomanip>

// User defined part 

#define NAME timestampdouble
#define OUTBRANCH "timestampdouble"
#define LEAF "timestampdouble/D"
#define INBRANCH "m_timeStamp"
#define ACCESSOR getTimeStamp( )
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Time in seconds, since mission start, currently 1/1/2001 UTC, with Double precission."
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_timestampdouble::MonInput_timestampdouble(){
  m_name=OUTBRANCH;
}
MonInput_timestampdouble::~MonInput_timestampdouble(){
}


int MonInput_timestampdouble::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_timestampdouble::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_timestampdouble::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;

}
std::string MonInput_timestampdouble::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_timestampdouble::getDescription(){
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

