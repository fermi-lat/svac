// 
// Class for input of quantity ReconVertexPosXYZ for monitoring 
// 
// Created by dpaneque on Fri Jun 29 03:06:54 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_ReconVertexPosXYZ.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME ReconVertexPosXYZ
#define OUTBRANCH "ReconVertexPosXYZ"
#define LEAF "ReconVertexPosXYZ[3]/F"
#define INBRANCH "m_tkr"
#define ACCESSOR capullo
#define MONSOURCE ReconEvent
#define INPUTSOURCE "ReconEvent"
#define DESCRIPTION "Vector [3] containing the reconstructed Vertex position in X,Y and Z. If no reconstruction was possible, then the values of this vector are set to 1000000.0"
#include "reconRootData/ReconEvent.h"

// End user defined part 

MonInput_ReconVertexPosXYZ::MonInput_ReconVertexPosXYZ(){
  m_name=OUTBRANCH;
}
MonInput_ReconVertexPosXYZ::~MonInput_ReconVertexPosXYZ(){
}


int MonInput_ReconVertexPosXYZ::setOutputBranch(TTree* tree) {
  TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
  return bErr != 0 ? 0 : 1;
}
void MonInput_ReconVertexPosXYZ::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_ReconVertexPosXYZ::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }
 

  for(UInt_t i = 0; i < 3; i++)
    m_val[i] = 1000000.0; // silly value which is outside sensible range
                          // if not vertex available, this is what will remain.

  TkrRecon* tkrRecon = de->getTkrRecon();
  
  if(tkrRecon) {
    TVector3 pos;
    TObjArray* vertices = tkrRecon->getVertexCol();
    if(vertices->GetLast() >= 0) {
      TkrVertex* tkrVertex = dynamic_cast<TkrVertex*>(vertices->At(0));
      if(tkrVertex) {
	pos = tkrVertex->getPosition();
	m_val[0]=Float_t(pos.X());
	m_val[1]=Float_t(pos.Y());
	m_val[2]=Float_t(pos.Z());
      }
    }
  }







}
std::string MonInput_ReconVertexPosXYZ::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_ReconVertexPosXYZ::getDescription(){
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

