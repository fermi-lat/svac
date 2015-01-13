// 
// Class for input of quantity Tkr1LATEdge for monitoring 
// 
// Created by dpaneque on Wed Mar 12 23:31:08 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_Tkr1LATEdge.h"
#include <iostream>

// User defined part 

#define NAME Tkr1LATEdge
#define OUTBRANCH "Tkr1LATEdge"
#define LEAF "Tkr1LATEdge/F"
#define INBRANCH "Tkr1LATEdge"
#define ACCESSOR vvvv
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Minimum distance to any LAT edge of the head of the best track"


// End user defined part 

MonInput_Tkr1LATEdge::MonInput_Tkr1LATEdge(){
  m_name=OUTBRANCH;
}
MonInput_Tkr1LATEdge::~MonInput_Tkr1LATEdge(){
}


int MonInput_Tkr1LATEdge::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_Tkr1LATEdge::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,&m_val);
}
void MonInput_Tkr1LATEdge::setValue(TObject* event) {
}
std::string MonInput_Tkr1LATEdge::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_Tkr1LATEdge::getDescription(){
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

