// 
// Class for input of quantity calxtalmaxtower for monitoring 
// 
// Created by kocian on Fri Apr 20 23:42:44 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_calxtalmaxtower_h
#define MonInput_calxtalmaxtower_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Short_t 

// end user defined part

class MonInput_calxtalmaxtower: public MonInputObject{
 public:
  MonInput_calxtalmaxtower();
  ~MonInput_calxtalmaxtower();
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

