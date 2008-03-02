// 
// Class for input of quantity AcdVetoB_AcdTileDigiId for monitoring 
// 
// Created by dpaneque on Sat Mar  1 23:00:10 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_AcdVetoB_AcdTileDigiId_h
#define MonInput_AcdVetoB_AcdTileDigiId_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Bool_t 

// end user defined part

class MonInput_AcdVetoB_AcdTileDigiId: public MonInputObject{
 public:
  MonInput_AcdVetoB_AcdTileDigiId();
  ~MonInput_AcdVetoB_AcdTileDigiId();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[604];
};

#undef VARTYPE
#endif

