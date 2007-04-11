// 
// Class for input of quantity TkrTriggerTower for monitoring 
// 
// Created by dpaneque on Fri Apr  6 01:40:01 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_TkrTriggerTower_h
#define MonInput_TkrTriggerTower_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Bool_t 

// end user defined part

class MonInput_TkrTriggerTower: public MonInputObject{
 public:
  MonInput_TkrTriggerTower();
  ~MonInput_TkrTriggerTower();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
 private:
  VARTYPE m_val[16]; // TrkTrigger Per Each Tower
 
};

#undef VARTYPE
#endif

