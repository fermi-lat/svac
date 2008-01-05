// 
// Class for input of quantity DeltaEvtID for monitoring 
// 
// Created by dpaneque on Tue Dec 18 02:30:41 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_DeltaEvtID.h"
#include <iostream>

// User defined part 

#define NAME DeltaEvtID
#define OUTBRANCH "DeltaEvtID"
#define LEAF "DeltaEvtID/L"
#define INBRANCH "m_metaEvent"
//#define ACCESSOR xxxx
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Delta EvtID computed using de->getMetaEvent().scalers().sequence()"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_DeltaEvtID::MonInput_DeltaEvtID(){
  m_name=OUTBRANCH;
  firstevt = 1;
  m_previous = 0;
  m_current = 0;
}
MonInput_DeltaEvtID::~MonInput_DeltaEvtID(){
}


int MonInput_DeltaEvtID::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_DeltaEvtID::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_DeltaEvtID::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }

  m_val = 0;
  m_current = de->getMetaEvent().scalers().sequence();
  if(firstevt){
    m_previous = m_current;
    firstevt = 0;
  }
  else{
    m_val = m_current-m_previous;
    if(m_val <0)
      {
	std::cout << "MonInput_DeltaEvtID::setValue : WARNING" << std::endl
		  << "Problems with EvtID. " << std::endl
		  << "previousID = " << m_previous << ", currentID = " << m_current << std::endl;
      }
    m_previous = m_current;
  }
}
std::string MonInput_DeltaEvtID::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_DeltaEvtID::getDescription(){
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

