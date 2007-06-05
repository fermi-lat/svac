// 
// Class for input of quantity condarrcallo for monitoring 
// 
// Created by kocian on Thu May 31 22:59:44 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_condarrcallo_h
#define MonInput_condarrcallo_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UShort_t 

// end user defined part

class MonInput_condarrcallo: public MonInputObject{
 public:
  MonInput_condarrcallo();
  ~MonInput_condarrcallo();
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

