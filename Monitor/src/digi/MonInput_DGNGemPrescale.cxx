// 
// Class for input of quantity DGNGemPrescale for monitoring 
// 
// Created by dpaneque on Sat May 24 21:47:37 2008 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_DGNGemPrescale.h"
#include <iostream>

// User defined part 

#define NAME DGNGemPrescale
#define OUTBRANCH "DGNGemPrescale"
#define LEAF "DGNGemPrescale/i"
#define INBRANCH "m_levelOneTrigger"
#define ACCESSOR bb
#define MONSOURCE DigiEvent
#define INPUTSOURCE "DigiEvent"
#define DESCRIPTION "Overall prescale factor from the combination of DGN and GEM prescale. Since DGN prescale is not yet available, the overall prescaled factors are hardcoded in the code below, according to prescription given in Jira GDQMQ-132."
#include "digiRootData/DigiEvent.h"

// End user defined part 

MonInput_DGNGemPrescale::MonInput_DGNGemPrescale(){
  m_name=OUTBRANCH;
}
MonInput_DGNGemPrescale::~MonInput_DGNGemPrescale(){
}


int MonInput_DGNGemPrescale::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_DGNGemPrescale::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_DGNGemPrescale::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }

  m_val = 0;
  Int_t engine = de->getL1T().getGemEngine();
  
  if(engine <=3 || engine ==5 || engine >=11)
    m_val = 1;
  if(engine ==4 || engine >=6 && engine <=9)
    m_val = 250;
  if(engine ==10)
    m_val = 5;
}

std::string MonInput_DGNGemPrescale::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_DGNGemPrescale::getDescription(){
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

