// 
// Class for input of quantity CalXHit_TowerCalLayer for monitoring 
// 
// Created by dpaneque on Thu Jun 28 23:07:31 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_CalXHit_TowerCalLayer.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME CalXHit_TowerCalLayer
#define OUTBRANCH "CalXHit_TowerCalLayer"
#define LEAF "CalXHit_TowerCalLayer[16][8]/s"
#define INBRANCH "m_calDigiCloneCol"
#define ACCESSOR CApullo
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Vector[tower][callayer]  reporting about the number of hits in the calorimeter layer defined by tower, callayer"
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_CalXHit_TowerCalLayer::MonInput_CalXHit_TowerCalLayer(){
  m_name=OUTBRANCH;
}
MonInput_CalXHit_TowerCalLayer::~MonInput_CalXHit_TowerCalLayer(){
}


int MonInput_CalXHit_TowerCalLayer::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_CalXHit_TowerCalLayer::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_CalXHit_TowerCalLayer::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }




const UShort_t ntower(16),ncallayer(8);
 for(UShort_t tower = 0; tower<ntower;tower++){
   for(UShort_t callayer=0;callayer<ncallayer;callayer++)
     m_val[tower][callayer] = 0;
 }

 /*
 std::cout << "MonInput_CalXHit_TowerCalLayer::evtcounter=" << evtcounter << std::endl;
 caldigicounter = 0;
 */

 const TClonesArray* calDigiCol = de->getCalDigiCol();

 // std::cout << "MonInput_CalXHit_TowerCalLayer::calDigiCol->GetLast()=" << calDigiCol->GetLast() << std::endl;

  for(int i = 0; i <= calDigiCol->GetLast(); ++i) {
    CalDigi* p = dynamic_cast<CalDigi*>(calDigiCol->At(i)); 
    assert(p); 
    UShort_t tower = p->getPackedId().getTower();
    UShort_t callayer = p->getPackedId().getLayer();
    
    m_val[tower][callayer]++;
    /*
    std::cout << "MonInput_CalXHit_TowerCalLayer::caldigicounter=" << caldigicounter << std::endl
	      << "Tower,Callayer: " << tower << ", " << callayer << std::endl
	      << "current mval value for this tower,layer= " <<  m_val[tower][callayer] << std::endl;
    caldigicounter++;
    */
  }

  //  evtcounter++;
      
}
std::string MonInput_CalXHit_TowerCalLayer::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_CalXHit_TowerCalLayer::getDescription(){
  return DESCRIPTION;
}

/*
int MonInput_CalXHit_TowerCalLayer::evtcounter = 0;
int  MonInput_CalXHit_TowerCalLayer::caldigicounter = 0;
*/


#undef INPUTSOURCE
#undef NAME
#undef OUTBRANCH
#undef LEAF
#undef INBRANCH 
#undef ACCESSOR
#undef MONSOURCE
#undef DESCRIPTION

