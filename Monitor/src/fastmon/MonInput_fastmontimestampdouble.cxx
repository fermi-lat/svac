// 
// Class for input of quantity fastmontimestampdouble for monitoring 
// 
// Created by dpaneque on Tue Feb 26 05:19:54 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_fastmontimestampdouble.h"
#include <iostream>

// User defined part 

#define NAME fastmontimestampdouble
#define OUTBRANCH "fastmontimestampdouble"
#define LEAF "fastmontimestampdouble/D"
#define INBRANCH "event_timestamp"
#define ACCESSOR NotNeeded
#define MONSOURCE FastMonEvent
#define INPUTSOURCE "FastMonEvent"
#define DESCRIPTION "Event time stamp (from FastMon)"


// End user defined part 

MonInput_fastmontimestampdouble::MonInput_fastmontimestampdouble(){
  m_name=OUTBRANCH;
}
MonInput_fastmontimestampdouble::~MonInput_fastmontimestampdouble(){
}


int MonInput_fastmontimestampdouble::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_fastmontimestampdouble::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_fastmontimestampdouble::setValue(TObject* event) {
}
std::string MonInput_fastmontimestampdouble::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_fastmontimestampdouble::getDescription(){
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

