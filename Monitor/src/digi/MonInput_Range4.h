// 
// Class for input of quantity Range4 for monitoring 
// 
// Created by dpaneque on Tue Aug 21 23:20:51 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_Range4_h
#define MonInput_Range4_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Bool_t 

// end user defined part

class MonInput_Range4: public MonInputObject{
 public:
  MonInput_Range4();
  ~MonInput_Range4();
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

