// 
// Class for input of quantity CalXtalAdcPed for monitoring 
// 
// Created by dpaneque on Mon Aug 11 04:39:31 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_CalXtalAdcPed.h"
#include <iostream>

// User defined part 

#define NAME CalXtalAdcPed
#define OUTBRANCH "CalXtalAdcPed"
#define LEAF "CalXtalAdcPed[16][8][12][2]/F"
#define INBRANCH "CalXtalAdcPed[16][8][12][2]"
#define ACCESSOR NotApplicable
#define MONSOURCE CalEvent
#define INPUTSOURCE "CalEvent"
#define DESCRIPTION "Vector [tower][callayer][calcolumn][xface] reporting the signal in ADC counts for the xtal log and face defined by the coordinates  tower, callayer, calcolumn, xface. If reconstruction was not possible, the value (for that tower,callayer,calcolumn,xface) is set to -1.0."


// End user defined part 

MonInput_CalXtalAdcPed::MonInput_CalXtalAdcPed(){
  m_name=OUTBRANCH;
}
MonInput_CalXtalAdcPed::~MonInput_CalXtalAdcPed(){
}


int MonInput_CalXtalAdcPed::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_CalXtalAdcPed::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchAddress(INBRANCH,m_val);

  // check that it contains something; if not, set to -1.0
  
  const UShort_t ntower(16),ncallayer(8),ncalcolumn(12), nface(2);
  for(UShort_t tower = 0; tower<ntower;tower++){
    for(UShort_t callayer=0;callayer<ncallayer;callayer++){
      for(UShort_t calcolumn=0;calcolumn<ncalcolumn;calcolumn++){
	for(UShort_t face=0;face<nface;face++){
	  if(m_val[tower][callayer][calcolumn][face] == 0.0000)
	    m_val[tower][callayer][calcolumn][face] = -1.0;
	}
      }
    }
  }
}
void MonInput_CalXtalAdcPed::setValue(TObject* event) {
}
std::string MonInput_CalXtalAdcPed::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_CalXtalAdcPed::getDescription(){
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

