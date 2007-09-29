// 
// Class for input of quantity FT1ZenithTheta for monitoring 
// 
// Created by dpaneque on Sat Sep 29 01:08:22 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FT1ZenithTheta_h
#define MonInput_FT1ZenithTheta_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_FT1ZenithTheta: public MonInputObject{
 public:
  MonInput_FT1ZenithTheta();
  ~MonInput_FT1ZenithTheta();
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

