// class to hold monitoring Cal input objects 
// M. Kocian, SLAC, 2/2/07
// Software developed for GLAST

#include "MonInputCollection_Cal.h"
#include "TTree.h"

MonInputCollection_Cal::MonInputCollection_Cal(TTree* tree, std::string type): MonInputCollection(tree,type){};

void MonInputCollection_Cal::readEvent(Long64_t ievent){
  m_intree->GetEntry(ievent);
  readValues();

}
void MonInputCollection_Cal::attachChain(){
  m_intree->SetBranchStatus("*",0);
  attachInputTree();
}
