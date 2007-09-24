// 
// Class for input of quantity CalXtalFaceSignal for monitoring 
// 
// Created by dpaneque on Thu Aug 23 18:28:31 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_CalXtalFaceSignal.h"
#include <iostream>

// User defined part 

#define NAME CalXtalFaceSignal
#define OUTBRANCH "CalXtalFaceSignal"
#define LEAF "CalXtalFaceSignal[16][8][12][2]/F"
#define INBRANCH "CalXtalFaceSignal[16][8][12][2]"
// #define ACCESSOR CalXtalFaceSignal
#define MONSOURCE CalEvent
#define INPUTSOURCE "CalEvent"
#define DESCRIPTION "Vector [tower][callayer][calcolumn][xface] reporting the reconstructed energy (MeV) for the xtal log and face defined by the coordinates  tower, callayer, calcolumn, xface."

// End user defined part 

MonInput_CalXtalFaceSignal::MonInput_CalXtalFaceSignal(){
  m_name=OUTBRANCH;
}
MonInput_CalXtalFaceSignal::~MonInput_CalXtalFaceSignal(){
}

int MonInput_CalXtalFaceSignal::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_CalXtalFaceSignal::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,m_val);
}
void MonInput_CalXtalFaceSignal::setValue(TObject* event) {

}
std::string MonInput_CalXtalFaceSignal::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_CalXtalFaceSignal::getDescription(){
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

