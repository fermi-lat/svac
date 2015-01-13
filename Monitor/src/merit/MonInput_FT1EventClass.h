// 
// Class for input of quantity FT1EventClass for monitoring 
// 
// Created by lbaldini on Tue Jan 13 15:31:52 2015 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FT1EventClass_h
#define MonInput_FT1EventClass_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Int_t 

// end user defined part

class MonInput_FT1EventClass: public MonInputObject{
 public:
  MonInput_FT1EventClass();
  ~MonInput_FT1EventClass();
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

