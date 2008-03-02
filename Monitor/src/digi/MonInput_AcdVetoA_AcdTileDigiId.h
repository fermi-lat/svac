// 
// Class for input of quantity AcdVetoA_AcdTileDigiId for monitoring 
// 
// Created by dpaneque on Sat Mar  1 22:58:58 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_AcdVetoA_AcdTileDigiId_h
#define MonInput_AcdVetoA_AcdTileDigiId_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Bool_t 

// end user defined part

class MonInput_AcdVetoA_AcdTileDigiId: public MonInputObject{
 public:
  MonInput_AcdVetoA_AcdTileDigiId();
  ~MonInput_AcdVetoA_AcdTileDigiId();
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

