// 
// Class for input of quantity timestamp for monitoring 
// 
// Created by kocian on Tue Feb 27 23:48:45 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_timestamp_h
#define MonInput_timestamp_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UInt_t 

// end user defined part

class MonInput_timestamp: public MonInputObject{
 public:
  MonInput_timestamp();
  ~MonInput_timestamp();
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

