// 
// Class for input of quantity PrescaledDelta for monitoring 
// 
// Created by dpaneque on Fri Sep 28 18:41:04 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_PrescaledDelta_h
#define MonInput_PrescaledDelta_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Long64_t 

// end user defined part

class MonInput_PrescaledDelta: public MonInputObject{
 public:
  MonInput_PrescaledDelta();
  ~MonInput_PrescaledDelta();
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

