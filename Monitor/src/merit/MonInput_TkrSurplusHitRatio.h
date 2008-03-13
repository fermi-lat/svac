// 
// Class for input of quantity TkrSurplusHitRatio for monitoring 
// 
// Created by dpaneque on Thu Mar 13 00:20:43 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_TkrSurplusHitRatio_h
#define MonInput_TkrSurplusHitRatio_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_TkrSurplusHitRatio: public MonInputObject{
 public:
  MonInput_TkrSurplusHitRatio();
  ~MonInput_TkrSurplusHitRatio();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val;
};

#undef VARTYPE
#endif

