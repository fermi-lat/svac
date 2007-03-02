// class to hold monitoring recon input objects 
// M. Kocian, SLAC, 2/2/07
// Software developed for GLAST

#include "MonInputCollection_Recon.h"
#include "reconRootData/ReconEvent.h"
#include "TTree.h"

MonInputCollection_Recon::MonInputCollection_Recon(TTree* tree, std::string type): MonInputCollection(tree,type){};

void MonInputCollection_Recon::readEvent(Long64_t ievent){
  if(m_event)((ReconEvent*)m_event)->Clear();
  m_intree->GetEvent(ievent);
  readValues();

}
void MonInputCollection_Recon::attachChain(){
  m_intree->SetBranchAddress("ReconEvent",&m_event);
  m_intree->SetBranchStatus("*",0);
  attachInputTree();
}
