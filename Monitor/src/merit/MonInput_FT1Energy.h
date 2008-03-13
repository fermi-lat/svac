// 
// Class for input of quantity FT1Energy for monitoring 
// 
// Created by dpaneque on Thu Mar 13 01:03:40 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FT1Energy_h
#define MonInput_FT1Energy_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_FT1Energy: public MonInputObject{
 public:
  MonInput_FT1Energy();
  ~MonInput_FT1Energy();
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

