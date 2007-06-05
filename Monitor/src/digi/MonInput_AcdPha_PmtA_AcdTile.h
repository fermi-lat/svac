// 
// Class for input of quantity AcdPha_PmtA_AcdTile for monitoring 
// 
// Created by dpaneque on Tue Jun  5 01:11:11 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_AcdPha_PmtA_AcdTile_h
#define MonInput_AcdPha_PmtA_AcdTile_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UShort_t 

// end user defined part

class MonInput_AcdPha_PmtA_AcdTile: public MonInputObject{
 public:
  MonInput_AcdPha_PmtA_AcdTile();
  ~MonInput_AcdPha_PmtA_AcdTile();
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

