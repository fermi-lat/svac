// 
// Class for input of quantity CalHiTriggerTower for monitoring 
// 
// Created by kocian on Fri Apr 20 20:14:22 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CalHiTriggerTower_h
#define MonInput_CalHiTriggerTower_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Bool_t 

// end user defined part

class MonInput_CalHiTriggerTower: public MonInputObject{
 public:
  MonInput_CalHiTriggerTower();
  ~MonInput_CalHiTriggerTower();
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

