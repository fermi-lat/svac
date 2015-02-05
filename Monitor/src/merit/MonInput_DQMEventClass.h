// 
// Class for input of quantity DQMEventClass for monitoring 
// 
// Created by bregeon on Thu Feb  5 15:25:16 2015 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_DQMEventClass_h
#define MonInput_DQMEventClass_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UInt_t 

// end user defined part

class MonInput_DQMEventClass: public MonInputObject{
 public:
  MonInput_DQMEventClass();
  ~MonInput_DQMEventClass();
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

