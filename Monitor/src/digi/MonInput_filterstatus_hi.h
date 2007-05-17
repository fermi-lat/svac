// 
// Class for input of quantity filterstatus_hi for monitoring 
// 
// Created by kocian on Fri Apr 20 19:52:10 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_filterstatus_hi_h
#define MonInput_filterstatus_hi_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UInt_t 

// end user defined part

class MonInput_filterstatus_hi: public MonInputObject{
 public:
  MonInput_filterstatus_hi();
  ~MonInput_filterstatus_hi();
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

