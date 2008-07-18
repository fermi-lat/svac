// 
// Class for input of quantity FswGamState for monitoring 
// 
// Created by dpaneque on Thu Jul 17 22:24:13 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FswGamState_h
#define MonInput_FswGamState_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Int_t 

// end user defined part

class MonInput_FswGamState: public MonInputObject{
 public:
  MonInput_FswGamState();
  ~MonInput_FswGamState();
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

