// 
// Class for input of quantity AcdPha_PmtB_AcdTile for monitoring 
// 
// Created by dpaneque on Tue Jun  5 01:12:23 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_AcdPha_PmtB_AcdTile_h
#define MonInput_AcdPha_PmtB_AcdTile_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UShort_t 

// end user defined part

class MonInput_AcdPha_PmtB_AcdTile: public MonInputObject{
 public:
  MonInput_AcdPha_PmtB_AcdTile();
  ~MonInput_AcdPha_PmtB_AcdTile();
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

