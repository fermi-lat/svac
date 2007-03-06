// class to hold monitoring Merit input objects 
// M. Kocian, SLAC, 2/2/07
// Software developed for GLAST

#include "MonInputCollection_Merit.h"
#include "MeritEvent.h"
#include "TTree.h"

MonInputCollection_Merit::MonInputCollection_Merit(TTree* tree, std::string type): MonInputCollection(tree,type){};

void MonInputCollection_Merit::readEvent(Long64_t ievent){
  m_intree->GetEntry(ievent);
  readValues();

}
void MonInputCollection_Merit::attachChain(){
  m_event=new MeritEvent(m_intree);
  m_intree->SetBranchStatus("*",0);
  attachInputTree();
}
