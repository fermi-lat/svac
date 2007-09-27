// 
// Class for input of quantity Sequence for monitoring 
// 
// Created by dpaneque on Wed Sep 26 22:12:04 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_Sequence_h
#define MonInput_Sequence_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Long64_t 

// end user defined part

class MonInput_Sequence: public MonInputObject{
 public:
  MonInput_Sequence();
  ~MonInput_Sequence();
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

