// 
// Class for input of quantity FT1Theta for monitoring 
// 
// Created by dpaneque on Thu Mar 13 01:04:31 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FT1Theta_h
#define MonInput_FT1Theta_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_FT1Theta: public MonInputObject{
 public:
  MonInput_FT1Theta();
  ~MonInput_FT1Theta();
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

