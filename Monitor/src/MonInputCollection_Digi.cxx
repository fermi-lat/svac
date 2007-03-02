// class to hold monitoring digi input objects 
// M. Kocian, SLAC, 2/2/07
// Software developed for GLAST

#include "MonInputCollection_Digi.h"
#include "digiRootData/DigiEvent.h"
#include "TTree.h"

MonInputCollection_Digi::MonInputCollection_Digi(TTree* tree, std::string type): MonInputCollection(tree,type){};

void MonInputCollection_Digi::readEvent(Long64_t ievent){
  if(m_event)((DigiEvent*)m_event)->Clear();
  m_intree->GetEvent(ievent);
  readValues();

}
void MonInputCollection_Digi::attachChain(){
  m_intree->SetBranchAddress("DigiEvent",&m_event);
  m_intree->SetBranchStatus("*",0);
  attachInputTree();
}
