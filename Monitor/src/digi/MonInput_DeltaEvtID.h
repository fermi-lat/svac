// 
// Class for input of quantity DeltaEvtID for monitoring 
// 
// Created by dpaneque on Tue Dec 18 02:30:41 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_DeltaEvtID_h
#define MonInput_DeltaEvtID_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Long64_t 

// end user defined part

class MonInput_DeltaEvtID: public MonInputObject{
 public:
  MonInput_DeltaEvtID();
  ~MonInput_DeltaEvtID();
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

