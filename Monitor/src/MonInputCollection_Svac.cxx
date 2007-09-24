// class to hold monitoring Svac input objects 
// M. Kocian, SLAC, 2/2/07
// Software developed for GLAST

#include "MonInputCollection_Svac.h"
#include "TTree.h"

MonInputCollection_Svac::MonInputCollection_Svac(TTree* tree, std::string type): MonInputCollection(tree,type){
 };

void MonInputCollection_Svac::readEvent(Long64_t ievent){
  m_intree->GetEntry(ievent);
  readValues();

}
void MonInputCollection_Svac::attachChain(){
  m_intree->SetBranchStatus("*",0);
  attachInputTree();
}
