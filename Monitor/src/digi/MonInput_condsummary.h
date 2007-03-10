// 
// Class for input of quantity condsummary for monitoring 
// 
// Created by kocian on Fri Mar  9 22:53:38 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_condsummary_h
#define MonInput_condsummary_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UShort_t 

// end user defined part

class MonInput_condsummary: public MonInputObject{
 public:
  MonInput_condsummary();
  ~MonInput_condsummary();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
 private:
  VARTYPE m_val;
};

#undef VARTYPE
#endif

