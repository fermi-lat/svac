// 
// Class for input of quantity digitimestamp for monitoring 
// 
// Created by kocian on Fri Apr 20 18:17:48 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_digitimestamp_h
#define MonInput_digitimestamp_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_digitimestamp: public MonInputObject{
 public:
  MonInput_digitimestamp();
  ~MonInput_digitimestamp();
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

