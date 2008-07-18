// 
// Class for input of quantity MootKey for monitoring 
// 
// Created by dpaneque on Thu Jul 17 22:33:04 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_MootKey_h
#define MonInput_MootKey_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UInt_t 

// end user defined part

class MonInput_MootKey: public MonInputObject{
 public:
  MonInput_MootKey();
  ~MonInput_MootKey();
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

