// 
// Class for input of quantity AcdVetoA_OR_B_AcdTile for monitoring 
// 
// Created by dpaneque on Wed Oct 31 19:29:40 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_AcdVetoA_OR_B_AcdTile_h
#define MonInput_AcdVetoA_OR_B_AcdTile_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Bool_t 

// end user defined part

class MonInput_AcdVetoA_OR_B_AcdTile: public MonInputObject{
 public:
  MonInput_AcdVetoA_OR_B_AcdTile();
  ~MonInput_AcdVetoA_OR_B_AcdTile();
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

