// 
// Class for input of quantity ReconDirXYZ for monitoring 
// 
// Created by dpaneque on Fri Jun 29 03:05:08 2007 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_ReconDirXYZ.h"
#include <iostream>
#include <cassert>

// User defined part 

#define NAME ReconDirXYZ
#define OUTBRANCH "ReconDirXYZ"
#define LEAF "ReconDirXYZ[3]/F"
#define INBRANCH "m_tkr"
#define ACCESSOR capullo
#define MONSOURCE ReconEvent
#define INPUTSOURCE "ReconEvent"
#define DESCRIPTION "Vector[3] containing the reconstructed vertex direction in X, Y and Z. If no reconstruction was possible, then the values of this vector are set to 2.0"
#include "reconRootData/ReconEvent.h"

// End user defined part 

MonInput_ReconDirXYZ::MonInput_ReconDirXYZ(){
  m_name=OUTBRANCH;
}
MonInput_ReconDirXYZ::~MonInput_ReconDirXYZ(){
}


int MonInput_ReconDirXYZ::setOutputBranch(TTree* tree) {
  TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
  return bErr != 0 ? 0 : 1;
}
void MonInput_ReconDirXYZ::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
}
void MonInput_ReconDirXYZ::setValue(TObject* event) {
  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<"Using object "<<OUTBRANCH<<" with wrong kind of data tree (like digi, reco, etc.)"<<std::endl;
    assert(de);
  }


  for(UInt_t i = 0; i < 3; i++)
    m_val[i] = 2.0; // silly value which is outside sensible range
                    // if not vertex available, this is what will remain.

  TkrRecon* tkrRecon = de->getTkrRecon();
  
  if(tkrRecon) {
    TVector3 dir;
    TObjArray* vertices = tkrRecon->getVertexCol();
    if(vertices->GetLast() >= 0) {
      TkrVertex* tkrVertex = dynamic_cast<TkrVertex*>(vertices->At(0));
      if(tkrVertex) {
	dir = tkrVertex->getDirection();
	m_val[0]=Float_t(dir.X());
	m_val[1]=Float_t(dir.Y());
	m_val[2]=Float_t(dir.Z());
      }
    }
  }

}
std::string MonInput_ReconDirXYZ::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_ReconDirXYZ::getDescription(){
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

