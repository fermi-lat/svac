// 
// Class for input of quantity xoverthresh for monitoring 
// 
// Created by kocian on Thu May 31 20:39:26 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_xoverthresh_h
#define MonInput_xoverthresh_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UShort_t 

// end user defined part

class MonInput_xoverthresh: public MonInputObject{
 public:
  MonInput_xoverthresh();
  ~MonInput_xoverthresh();
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

