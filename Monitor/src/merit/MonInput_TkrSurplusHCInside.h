// 
// Class for input of quantity TkrSurplusHCInside for monitoring 
// 
// Created by dpaneque on Wed Mar 12 23:36:20 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_TkrSurplusHCInside_h
#define MonInput_TkrSurplusHCInside_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_TkrSurplusHCInside: public MonInputObject{
 public:
  MonInput_TkrSurplusHCInside();
  ~MonInput_TkrSurplusHCInside();
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

