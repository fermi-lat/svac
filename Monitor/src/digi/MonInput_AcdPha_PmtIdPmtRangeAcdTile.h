// 
// Class for input of quantity AcdPha_PmtIdPmtRangeAcdTile for monitoring 
// 
// Created by dpaneque on Sun Jan  6 22:42:24 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_AcdPha_PmtIdPmtRangeAcdTile_h
#define MonInput_AcdPha_PmtIdPmtRangeAcdTile_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Int_t 

// end user defined part

class MonInput_AcdPha_PmtIdPmtRangeAcdTile: public MonInputObject{
 public:
  MonInput_AcdPha_PmtIdPmtRangeAcdTile();
  ~MonInput_AcdPha_PmtIdPmtRangeAcdTile();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[2][2][128];
};

#undef VARTYPE
#endif

