// 
// Class for input of quantity callayers for monitoring 
// 
// Created by kocian on Wed May 30 18:47:05 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_callayers_h
#define MonInput_callayers_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_callayers: public MonInputObject{
 public:
  MonInput_callayers();
  ~MonInput_callayers();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[8];
};

#undef VARTYPE
#endif

