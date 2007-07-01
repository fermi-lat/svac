// 
// Class for input of quantity DeadZoneDelta for monitoring 
// 
// Created by dpaneque on Sun Jul  1 02:07:07 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_DeadZoneDelta_h
#define MonInput_DeadZoneDelta_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Long64_t 

// end user defined part

class MonInput_DeadZoneDelta: public MonInputObject{
 public:
  MonInput_DeadZoneDelta();
  ~MonInput_DeadZoneDelta();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  Bool_t firstevt;
  VARTYPE m_previous;
  VARTYPE m_current;
  VARTYPE m_val;
};

#undef VARTYPE
#endif

