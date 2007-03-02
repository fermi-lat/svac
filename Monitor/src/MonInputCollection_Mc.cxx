// class to hold monitoring mc input objects 
// M. Kocian, SLAC, 2/2/07
// Software developed for GLAST

#include "mcRootData/McEvent.h"
#include "MonInputCollection_Mc.h"
#include "TTree.h"

MonInputCollection_Mc::MonInputCollection_Mc(TTree* tree, std::string type): MonInputCollection(tree,type){};

void MonInputCollection_Mc::readEvent(Long64_t ievent){
  if(m_event)((McEvent*)m_event)->Clear();
  m_intree->GetEvent(ievent);
  readValues();

}
void MonInputCollection_Mc::attachChain(){
  m_intree->SetBranchAddress("McEvent",&m_event);
  m_intree->SetBranchStatus("*",0);
  attachInputTree();
}
