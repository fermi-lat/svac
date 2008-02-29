// 
// Class for input of quantity FastMon_CalLogEndRangeHit for monitoring 
// 
// Created by bregeon on Fri Feb 29 14:20:59 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FastMon_CalLogEndRangeHit_h
#define MonInput_FastMon_CalLogEndRangeHit_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Bool_t 

// end user defined part

class MonInput_FastMon_CalLogEndRangeHit: public MonInputObject{
 public:
  MonInput_FastMon_CalLogEndRangeHit();
  ~MonInput_FastMon_CalLogEndRangeHit();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[16][8][12][2][4];
};

#undef VARTYPE
#endif

