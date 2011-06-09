// 
// Class for input of quantity FT1EventClass for monitoring 
// 
// Created by dpaneque on Thu Jun  4 23:44:24 2009 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FT1EventClass_h
#define MonInput_FT1EventClass_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UInt_t 

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

