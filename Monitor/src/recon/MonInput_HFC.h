// 
// Class for input of quantity HFC for monitoring 
// 
// Created by kocian on Mon May 14 20:21:34 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_HFC_h
#define MonInput_HFC_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Bool_t 

// end user defined part

class MonInput_HFC: public MonInputObject{
 public:
  MonInput_HFC();
  ~MonInput_HFC();
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

