// 
// Class for input of quantity EvtCREventClass for monitoring 
// 
// Created by dpaneque on Wed Jun  8 17:02:20 2011 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_EvtCREventClass_h
#define MonInput_EvtCREventClass_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UInt_t 

// end user defined part

class MonInput_EvtCREventClass: public MonInputObject{
 public:
  MonInput_EvtCREventClass();
  ~MonInput_EvtCREventClass();
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

