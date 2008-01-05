// 
// Class for input of quantity Delta_CCSDSTime_EvtTime for monitoring 
// 
// Created by dpaneque on Tue Dec 18 02:35:26 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_Delta_CCSDSTime_EvtTime_h
#define MonInput_Delta_CCSDSTime_EvtTime_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_Delta_CCSDSTime_EvtTime: public MonInputObject{
 public:
  MonInput_Delta_CCSDSTime_EvtTime();
  ~MonInput_Delta_CCSDSTime_EvtTime();
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

