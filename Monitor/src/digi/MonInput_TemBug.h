// 
// Class for input of quantity TemBug for monitoring 
// 
// Created by dpaneque on Fri Mar 27 19:50:54 2009 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_TemBug_h
#define MonInput_TemBug_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Bool_t 

// end user defined part

class MonInput_TemBug: public MonInputObject{
 public:
  MonInput_TemBug();
  ~MonInput_TemBug();
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

