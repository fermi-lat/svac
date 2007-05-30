// 
// Class for input of quantity LivetimeLast for monitoring 
// 
// Created by dpaneque on Fri Apr 27 01:39:12 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_LivetimeLast_h
#define MonInput_LivetimeLast_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE ULong64_t 

// end user defined part

class MonInput_LivetimeLast: public MonInputObject{
 public:
  MonInput_LivetimeLast();
  ~MonInput_LivetimeLast();
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

