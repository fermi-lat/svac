// 
// Class for input of quantity DiscardedLast for monitoring 
// 
// Created by dpaneque on Fri Apr 27 01:43:54 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_DiscardedLast_h
#define MonInput_DiscardedLast_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE ULong64_t 

// end user defined part

class MonInput_DiscardedLast: public MonInputObject{
 public:
  MonInput_DiscardedLast();
  ~MonInput_DiscardedLast();
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

