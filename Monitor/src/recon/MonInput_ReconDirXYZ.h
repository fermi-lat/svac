// 
// Class for input of quantity ReconDirXYZ for monitoring 
// 
// Created by dpaneque on Fri Jun 29 03:05:08 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_ReconDirXYZ_h
#define MonInput_ReconDirXYZ_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"
#include "TVector3.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_ReconDirXYZ: public MonInputObject{
 public:
  MonInput_ReconDirXYZ();
  ~MonInput_ReconDirXYZ();
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

