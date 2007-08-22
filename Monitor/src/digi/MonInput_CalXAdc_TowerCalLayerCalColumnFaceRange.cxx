// 
// Class for input of quantity CalXAdc_TowerCalLayerCalColumnFaceRange for monitoring 
// 
// Created by dpaneque on Fri Aug 17 22:14:39 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_CalXAdc_TowerCalLayerCalColumnFaceRange.h"
#include <iostream>

// User defined part 

#define NAME CalXAdc_TowerCalLayerCalColumnFaceRange
#define OUTBRANCH "CalXAdc_TowerCalLayerCalColumnFaceRange"
#define LEAF "CalXAdc_TowerCalLayerCalColumnFaceRange[16][8][12][2][4]/S"
#define INBRANCH "m_calDigiCloneCol"
//#define ACCESSOR capullo
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Vector[tower][callayer][calcolumn][face][range] reporting the signal (in ADC counts) measured by the cal crystal defined by coordinates tower,callayer,calcolumn  at face and range."
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_CalXAdc_TowerCalLayerCalColumnFaceRange::MonInput_CalXAdc_TowerCalLayerCalColumnFaceRange(){
  m_name=OUTBRANCH;
}
MonInput_CalXAdc_TowerCalLayerCalColumnFaceRange::~MonInput_CalXAdc_TowerCalLayerCalColumnFaceRange(){
}


int MonInput_CalXAdc_TowerCalLayerCalColumnFaceRange::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_CalXAdc_TowerCalLayerCalColumnFaceRange::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  //tree.SetBranchStatus("m_gem",1);
  //tree.SetBranchStatus("m_summary",1);
}
void MonInput_CalXAdc_TowerCalLayerCalColumnFaceRange::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }

  const UShort_t ntower(16),ncallayer(8),ncalcolumn(12),nface(2),nrange(4);
  for(UShort_t tower = 0; tower<ntower;tower++){
    for(UShort_t callayer=0;callayer<ncallayer;callayer++){
      for(UShort_t calcolumn=0;calcolumn<ncalcolumn;calcolumn++){
	for(UShort_t face=0;face<nface;face++){
	  for(UShort_t range=0;range<nrange;range++){
	    m_val[tower][callayer][calcolumn][face][range] = 0;
	  }
	}
      }
    }
  }
  
  /*
  UInt_t read4 = de->getEventSummaryData().readout4();
  std::cout << "Event de->getEventSummaryData().readout4() = " << read4 << std::endl;

  UShort_t condsum = de->getGem().getConditionSummary();
  if(condsum&32)
    std::cout << "Periodic Trigger (condsum=" << condsum << ")" << std::endl;
  else
    std::cout << "NOT A Periodic Trigger (condsum=" << condsum << ")" << std::endl;
  */

  const TClonesArray* calDigiCol = de->getCalDigiCol();
  //if(condsum&32){
  //std::cout << "Periodic Trigger (condsum=" << condsum << ")" << std::endl;
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
	 //std::cout << "face= " << face << std::endl; 
	 for(UShort_t range = 0; range<nrange;range++){
	   if(!face)
	     m_val[tower][callayer][calcolumn][face][range]=p->getAdcSelectedRange(Char_t(range),CalXtalId::POS);
	   else
	     m_val[tower][callayer][calcolumn][face][range]=p->getAdcSelectedRange(Char_t(range),CalXtalId::NEG);
	   /*
	   std::cout << "Range = " << range << std::endl
		     << "Value = " <<  m_val[tower][callayer][calcolumn][face][range] << std::endl;
	   */
	 }
       }
     }
     else{
       std::cout << "MonInput_CalXAdc_TowerCalLayerCalColumnFaceRange::setValue; WARNING" 
		 << std::endl
		 << "Indices tower,layer,column out of range: tower = " << tower
		 << ", layer = " << callayer << ", column = " << calcolumn << std::endl;
     }

    
  }
        
}
std::string MonInput_CalXAdc_TowerCalLayerCalColumnFaceRange::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_CalXAdc_TowerCalLayerCalColumnFaceRange::getDescription(){
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

