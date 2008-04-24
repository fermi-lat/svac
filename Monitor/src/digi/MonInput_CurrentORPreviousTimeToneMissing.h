// 
// Class for input of quantity CurrentORPreviousTimeToneMissing for monitoring 
// 
// Created by dpaneque on Thu Apr 24 16:33:12 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CurrentORPreviousTimeToneMissing_h
#define MonInput_CurrentORPreviousTimeToneMissing_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Bool_t 

// end user defined part

class MonInput_CurrentORPreviousTimeToneMissing: public MonInputObject{
 public:
  MonInput_CurrentORPreviousTimeToneMissing();
  ~MonInput_CurrentORPreviousTimeToneMissing();
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

