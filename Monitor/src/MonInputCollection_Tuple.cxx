// class to hold monitoring Tuple input objects 
// M. Kocian, SLAC, 2/2/07
// Software developed for GLAST

#include "MonInputCollection_Tuple.h"
#include "TTree.h"

MonInputCollection_Tuple::MonInputCollection_Tuple(TTree* tree, std::string type): MonInputCollection(tree,type){};

void MonInputCollection_Tuple::readEvent(Long64_t ievent){
  m_intree->GetEntry(ievent);
  readValues();

}
void MonInputCollection_Tuple::attachChain(){
  m_intree->SetBranchStatus("*",0);
  attachInputTree();
}
