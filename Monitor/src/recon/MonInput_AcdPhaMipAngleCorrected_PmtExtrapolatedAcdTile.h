// 
// Class for input of quantity AcdPhaMipAngleCorrected_PmtExtrapolatedAcdTile for monitoring 
// 
// Created by dpaneque on Sun Jan  6 19:10:52 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_AcdPhaMipAngleCorrected_PmtExtrapolatedAcdTile_h
#define MonInput_AcdPhaMipAngleCorrected_PmtExtrapolatedAcdTile_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"
#include "map.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_AcdPhaMipAngleCorrected_PmtExtrapolatedAcdTile: public MonInputObject{
 public:
  MonInput_AcdPhaMipAngleCorrected_PmtExtrapolatedAcdTile();
  ~MonInput_AcdPhaMipAngleCorrected_PmtExtrapolatedAcdTile();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[2][128];
};

#undef VARTYPE
#endif

