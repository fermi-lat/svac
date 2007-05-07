// 
// Class for input of quantity CalLoTriggerTower for monitoring 
// 
// Created by kocian on Fri Apr 20 20:12:05 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CalLoTriggerTower_h
#define MonInput_CalLoTriggerTower_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Bool_t 

// end user defined part

class MonInput_CalLoTriggerTower: public MonInputObject{
 public:
  MonInput_CalLoTriggerTower();
  ~MonInput_CalLoTriggerTower();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[16];
};

#undef VARTYPE
#endif

