// 
// Class for input of quantity TkrTwrEdge for monitoring 
// 
// Created by dpaneque on Wed Mar 12 23:29:00 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_TkrTwrEdge.h"
#include <iostream>

// User defined part 

#define NAME TkrTwrEdge
#define OUTBRANCH "TkrTwrEdge"
#define LEAF "TkrTwrEdge/F"
#define INBRANCH "TkrTwrEdge"
#define ACCESSOR vv
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "The average distance of the best track from the 'edge' of each tray, weighted by radiation lengths traversed. (The edge is a plane halfway between the towers."


// End user defined part 

MonInput_TkrTwrEdge::MonInput_TkrTwrEdge(){
  m_name=OUTBRANCH;
}
MonInput_TkrTwrEdge::~MonInput_TkrTwrEdge(){
}


int MonInput_TkrTwrEdge::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_TkrTwrEdge::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_TkrTwrEdge::setValue(TObject* event) {
}
std::string MonInput_TkrTwrEdge::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_TkrTwrEdge::getDescription(){
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

