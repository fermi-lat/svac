// 
// Class for input of quantity Delta_CCSDSTime_EvtTime for monitoring 
// 
// Created by dpaneque on Tue Dec 18 02:35:26 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_Delta_CCSDSTime_EvtTime.h"
#include <iostream>
#include <cassert>
#include <iomanip>

// User defined part 

#define NAME Delta_CCSDSTime_EvtTime
#define OUTBRANCH "Delta_CCSDSTime_EvtTime"
#define LEAF "Delta_CCSDSTime_EvtTime/D"
#define INBRANCH "m_ccsds"
//#define ACCESSOR xxx
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Difference digi->getCcsds().getUtc()-digi->getTimeStamp(). It should be positive."
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_Delta_CCSDSTime_EvtTime::MonInput_Delta_CCSDSTime_EvtTime(){
  m_name=OUTBRANCH;
}
MonInput_Delta_CCSDSTime_EvtTime::~MonInput_Delta_CCSDSTime_EvtTime(){
}


int MonInput_Delta_CCSDSTime_EvtTime::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_Delta_CCSDSTime_EvtTime::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);

  // tmp
  //tree.SetBranchStatus("m_metaevent",1);
  // endtmp
}
void MonInput_Delta_CCSDSTime_EvtTime::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }

  
  // Time from Mission elapsed time to Unix time:
    int deltaTimeUgly = 978307200;
    double timeStamp = de->getTimeStamp();
    // Leap second from Dec 31st, 2005
    if (timeStamp > 157766400) deltaTimeUgly--;
    // Leap second from Dec 31st, 2008
    if (timeStamp > 252460800) deltaTimeUgly--;
    

  m_val= (de->getCcsds().getUtc()-(timeStamp+deltaTimeUgly));

  // std::cout << de->getCcsds().getUtc() << "\t" << de->getTimeStamp() << "\t diff(off) =" << m_val << std::endl;
  if(m_val <0)
    {
      std::cout << "MonInput_Delta_CCSDSTime_EvtTime::setValue : WARNING" << std::endl
		<< "Delta_CCSDSTime_EvtTime is negative.  " << std::endl
		<< "m_val = " << m_val << std::endl
		<< "digi->getTimeStamp() = " << de->getTimeStamp() 
		<< ", digi->getCcsds().getUtc() = " << de->getCcsds().getUtc() << std::endl;
    }


   // temp
  /*
  std::cout << "MonInput_Delta_CCSDSTime_EvtTime::setValue : TMP INFO" << std::endl
	    << setprecision(20) 
	    << "CCSDS time = " << de->getCcsds().getUtc() << std::endl
	    << "time stamp = " << de->getTimeStamp() << std::endl
	    << "Other time stamp = " << de->getMetaEvent().time().current().timeSecs()  << std::endl
	    << "Diff = " << m_val << std::endl 
	    << "Diff2 = " <<  de->getCcsds().getUtc()-de->getMetaEvent().time().current().timeSecs() << std::endl  
	    << "Diff ref timestamps = " << de->getMetaEvent().time().current().timeSecs()- de->getTimeStamp()
	    << std::endl  
	    << std::endl << std::endl;
  */
    // end tmp

}
std::string MonInput_Delta_CCSDSTime_EvtTime::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_Delta_CCSDSTime_EvtTime::getDescription(){
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

