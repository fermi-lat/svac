// 
// Class for input of quantity EvtEventId for monitoring 
// 
// Created by dpaneque on Tue Apr 22 03:56:45 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_EvtEventId_h
#define MonInput_EvtEventId_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UInt_t 

// end user defined part

class MonInput_EvtEventId: public MonInputObject{
 public:
  MonInput_EvtEventId();
  ~MonInput_EvtEventId();
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

