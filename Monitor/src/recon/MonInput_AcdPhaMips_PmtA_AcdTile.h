// 
// Class for input of quantity AcdPhaMips_PmtA_AcdTile for monitoring 
// 
// Created by dpaneque on Wed Sep 26 03:52:14 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_AcdPhaMips_PmtA_AcdTile_h
#define MonInput_AcdPhaMips_PmtA_AcdTile_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_AcdPhaMips_PmtA_AcdTile: public MonInputObject{
 public:
  MonInput_AcdPhaMips_PmtA_AcdTile();
  ~MonInput_AcdPhaMips_PmtA_AcdTile();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[128];
};

#undef VARTYPE
#endif

