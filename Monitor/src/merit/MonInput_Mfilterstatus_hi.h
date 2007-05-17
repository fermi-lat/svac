// 
// Class for input of quantity Mfilterstatus_hi for monitoring 
// 
// Created by kocian on Sat Apr 21 00:03:41 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_Mfilterstatus_hi_h
#define MonInput_Mfilterstatus_hi_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_Mfilterstatus_hi: public MonInputObject{
 public:
  MonInput_Mfilterstatus_hi();
  ~MonInput_Mfilterstatus_hi();
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

