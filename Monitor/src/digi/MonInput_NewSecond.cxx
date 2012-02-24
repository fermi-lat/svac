// 
// Class for input of quantity NewSecond for monitoring 
// 
// Created by dpaneque on Tue Dec 18 04:51:28 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_NewSecond.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME NewSecond
#define OUTBRANCH "NewSecond"
#define LEAF "NewSecond/O"
#define INBRANCH "m_metaEvent"
// #define ACCESSOR getMetaEvent().time().current().timeSecs()
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Variable set to 1 when current time (in units of seconds) is different to previous' evt time. The variable is 0 otherwise. The time is extracted as digi->getMetaEvent().time().current().timeSecs()."
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_NewSecond::MonInput_NewSecond(){
  m_name=OUTBRANCH;

  firstevt = 1;
  m_previoustime = 0;
  m_currenttime = 0;
}
MonInput_NewSecond::~MonInput_NewSecond(){
}


int MonInput_NewSecond::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_NewSecond::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);

  // tmp
  // tree.SetBranchStatus("m_gem",1);
  // endtmp
}
void MonInput_NewSecond::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
  
  m_val = 0; // default value
  m_currenttime = de->getMetaEvent().time().current().timeSecs();
  if(firstevt)
    {
      m_val = 1;
      m_previoustime = m_currenttime;
      firstevt = 0;
    }
  else
    {
      if(m_previoustime != m_currenttime){
	m_val = 1;
	m_previoustime = m_currenttime;
      }
    }

  // tmp
  /*
  if(m_val){
  std::cout << "MonInput_NewSecond::setValue: TMP INFO" <<std::endl
	    << "m_val = " << m_val << std::endl
	    << "m_currenttime = " << m_currenttime << std::endl
	    << "m_previoustime= " << m_previoustime << std::endl 
	    << "condsummary = " << de->getGem().getConditionSummary() << std::endl << std::endl;
  }
  */
  // end tmp



}
std::string MonInput_NewSecond::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_NewSecond::getDescription(){
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

