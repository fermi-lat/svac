// 
// Class for input of quantity CalMIPRatio for monitoring 
// 
// Created by dpaneque on Fri Sep 12 00:39:02 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CalMIPRatio_h
#define MonInput_CalMIPRatio_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_CalMIPRatio: public MonInputObject{
 public:
  MonInput_CalMIPRatio();
  ~MonInput_CalMIPRatio();
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

