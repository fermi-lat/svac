// 
// Class for input of quantity TkrSurplusHitsInside for monitoring 
// 
// Created by dpaneque on Thu Mar 13 00:19:55 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_TkrSurplusHitsInside_h
#define MonInput_TkrSurplusHitsInside_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_TkrSurplusHitsInside: public MonInputObject{
 public:
  MonInput_TkrSurplusHitsInside();
  ~MonInput_TkrSurplusHitsInside();
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

