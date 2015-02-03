// 
// Class for input of quantity ReconVertexPosXYZ for monitoring 
// 
// Created by dpaneque on Fri Jun 29 03:06:54 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_ReconVertexPosXYZ_h
#define MonInput_ReconVertexPosXYZ_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"
#include "TVector3.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_ReconVertexPosXYZ: public MonInputObject{
 public:
  MonInput_ReconVertexPosXYZ();
  ~MonInput_ReconVertexPosXYZ();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[3];
};

#undef VARTYPE
#endif

