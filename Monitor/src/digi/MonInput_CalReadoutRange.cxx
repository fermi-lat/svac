// 
// Class for input of quantity CalReadoutRange for monitoring 
// 
// Created by dpaneque on Sun Aug 26 17:38:54 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_CalReadoutRange.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME CalReadoutRange
#define OUTBRANCH "CalReadoutRange"
#define LEAF "CalReadoutRange[16][8][12][2]/S"
#define INBRANCH "m_calDigiCloneCol"
// #define ACCESSOR capullo
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Vector [tower][callayer][calcolumn][face] reporting the readout range used for this particular Xtal log and xface. The quantity only makes sense when auto-range is being used. Therefore, before retrieving the readout range, the code checks for 4-range readout, returning a negative number if 4-rane readout was used. "
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_CalReadoutRange::MonInput_CalReadoutRange(){
  m_name=OUTBRANCH;
}
MonInput_CalReadoutRange::~MonInput_CalReadoutRange(){
}


int MonInput_CalReadoutRange::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_CalReadoutRange::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchStatus("m_summary",1); // to get the 4 range readout check
}
void MonInput_CalReadoutRange::setValue(TObject* event) {
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
	  m_val[tower][callayer][calcolumn][face] = -1;
	}
      }
    }
  }


  Bool_t range4 = Bool_t(de->getEventSummaryData().readout4());
  if(range4)
    {/*
      std::cout << "MonInput_CalReadoutRange::setValue; WARNING, 4 range readout was used"
		<< std::endl
		<< "CalReadoutRange values set to -1 for all channels" << std::endl;
     */
    }
  else
    {
      const TClonesArray* calDigiCol = de->getCalDigiCol();
      for(int i = 0; i <= calDigiCol->GetLast(); ++i) {
	CalDigi* p = dynamic_cast<CalDigi*>(calDigiCol->At(i)); 
	assert(p); 
	UShort_t tower = p->getPackedId().getTower();
	UShort_t callayer = p->getPackedId().getLayer();
	UShort_t calcolumn = p->getPackedId().getColumn();
	
	/*
	std::cout << std::endl << "CalDigi number " << i << std::endl
		  << "Tower,layer,column: " << tower << ", " << callayer << ", " 
		  << calcolumn << std::endl;
	*/
	if(tower<16 && callayer<8 && calcolumn<12){
	  for(UShort_t face = 0; face<nface;face++){// 0 is POS, 1 is NEG
	    if(!face)
	      m_val[tower][callayer][calcolumn][face]=Short_t(p->getRange(0,CalXtalId::POS));
	    else
	      m_val[tower][callayer][calcolumn][face]=Short_t(p->getRange(0,CalXtalId::NEG));
	    /*
	    std::cout << "face = " << face << std::endl
		      << "Value = " <<  m_val[tower][callayer][calcolumn][face] << std::endl;
	    */
	  }
	}
	
      }
    }
}

std::string MonInput_CalReadoutRange::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_CalReadoutRange::getDescription(){
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

