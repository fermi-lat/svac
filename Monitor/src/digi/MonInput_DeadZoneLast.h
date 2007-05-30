// 
// Class for input of quantity DeadZoneLast for monitoring 
// 
// Created by dpaneque on Fri Apr 27 01:42:06 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_DeadZoneLast_h
#define MonInput_DeadZoneLast_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE ULong64_t 

// end user defined part

class MonInput_DeadZoneLast: public MonInputObject{
 public:
  MonInput_DeadZoneLast();
  ~MonInput_DeadZoneLast();
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

