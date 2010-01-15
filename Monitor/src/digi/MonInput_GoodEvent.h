// 
// Class for input of quantity GoodEvent for monitoring 
// 
// Created by bregeon on Tue Jan 12 15:14:48 2010 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_GoodEvent_h
#define MonInput_GoodEvent_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Bool_t 

// end user defined part

class MonInput_GoodEvent: public MonInputObject{
 public:
  MonInput_GoodEvent();
  ~MonInput_GoodEvent();
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

