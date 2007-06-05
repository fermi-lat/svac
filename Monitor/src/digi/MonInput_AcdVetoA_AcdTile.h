// 
// Class for input of quantity AcdVetoA_AcdTile for monitoring 
// 
// Created by dpaneque on Tue Jun  5 00:43:35 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_AcdVetoA_AcdTile_h
#define MonInput_AcdVetoA_AcdTile_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Bool_t 

// end user defined part

class MonInput_AcdVetoA_AcdTile: public MonInputObject{
 public:
  MonInput_AcdVetoA_AcdTile();
  ~MonInput_AcdVetoA_AcdTile();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
  UShort_t getGemId(UInt_t id);
 private:
  VARTYPE m_val[128];
};

#undef VARTYPE
#endif

