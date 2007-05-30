// 
// Class for input of quantity ElapsedLast for monitoring 
// 
// Created by dpaneque on Fri Apr 27 01:46:29 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_ElapsedLast_h
#define MonInput_ElapsedLast_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE ULong64_t 

// end user defined part

class MonInput_ElapsedLast: public MonInputObject{
 public:
  MonInput_ElapsedLast();
  ~MonInput_ElapsedLast();
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

