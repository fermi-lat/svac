// 
// Class for input of quantity acdpha for monitoring 
// 
// Created by kocian on Sat May 26 18:13:04 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_acdpha_h
#define MonInput_acdpha_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UShort_t 

// end user defined part

class MonInput_acdpha: public MonInputObject{
 public:
  MonInput_acdpha();
  ~MonInput_acdpha();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[12][18];
};

#undef VARTYPE
#endif

