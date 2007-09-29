// 
// Class for input of quantity CTBClassLevel for monitoring 
// 
// Created by dpaneque on Sat Sep 29 01:10:02 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CTBClassLevel_h
#define MonInput_CTBClassLevel_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_CTBClassLevel: public MonInputObject{
 public:
  MonInput_CTBClassLevel();
  ~MonInput_CTBClassLevel();
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

