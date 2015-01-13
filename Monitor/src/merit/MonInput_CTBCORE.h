// 
// Class for input of quantity CTBCORE for monitoring 
// 
// Created by dpaneque on Sat Sep 29 01:11:28 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CTBCORE_h
#define MonInput_CTBCORE_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_CTBCORE: public MonInputObject{
 public:
  MonInput_CTBCORE();
  ~MonInput_CTBCORE();
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

