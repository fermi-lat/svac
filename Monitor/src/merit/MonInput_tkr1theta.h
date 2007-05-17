// 
// Class for input of quantity tkr1theta for monitoring 
// 
// Created by kocian on Fri Apr 20 20:46:04 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_tkr1theta_h
#define MonInput_tkr1theta_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_tkr1theta: public MonInputObject{
 public:
  MonInput_tkr1theta();
  ~MonInput_tkr1theta();
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

