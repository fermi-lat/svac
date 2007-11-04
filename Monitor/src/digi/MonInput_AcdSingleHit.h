// 
// Class for input of quantity AcdSingleHit for monitoring 
// 
// Created by dpaneque on Wed Oct 31 22:24:42 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_AcdSingleHit_h
#define MonInput_AcdSingleHit_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Bool_t 

// end user defined part

class MonInput_AcdSingleHit: public MonInputObject{
 public:
  MonInput_AcdSingleHit();
  ~MonInput_AcdSingleHit();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[128];
};

#undef VARTYPE
#endif

