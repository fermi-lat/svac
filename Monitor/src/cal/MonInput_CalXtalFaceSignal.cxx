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
#include "../CalEvent.h"

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
}
void MonInput_CalXtalFaceSignal::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }

  const UShort_t ntower(16),ncallayer(8),ncalcolumn(12),nface(2);
  for(UShort_t tower = 0; tower<ntower;tower++){
    for(UShort_t callayer=0;callayer<ncallayer;callayer++){
      for(UShort_t calcolumn=0;calcolumn<ncalcolumn;calcolumn++){
	for(UShort_t face=0;face<nface;face++){
	    m_val[tower][callayer][calcolumn][face] = -1.0;;
	}
      }
    }
  }

  m_val= de->CalXtalFaceSignal;

  /*
  std::cout << "retrieved cal event energy" << std::endl;
  for(UShort_t tower = 0; tower<ntower;tower++){
    for(UShort_t callayer=0;callayer<ncallayer;callayer++){
      for(UShort_t calcolumn=0;calcolumn<ncalcolumn;calcolumn++){
	for(UShort_t face=0;face<nface;face++){
	  if(m_val[tower][callayer][calcolumn][face]>0){
	  std::cout << "tower,layer,column,face: " << tower << ", " 
		    << callayer<<", " << calcolumn << ", " << face << std::endl
		    << "val= " <<  m_val[tower][callayer][calcolumn][face] << std::endl;}
	}
      }
    }
  }
  */

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

