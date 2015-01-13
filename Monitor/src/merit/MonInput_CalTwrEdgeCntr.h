// 
// Class for input of quantity CalTwrEdgeCntr for monitoring 
// 
// Created by dpaneque on Thu Mar 13 00:41:09 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CalTwrEdgeCntr_h
#define MonInput_CalTwrEdgeCntr_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_CalTwrEdgeCntr: public MonInputObject{
 public:
  MonInput_CalTwrEdgeCntr();
  ~MonInput_CalTwrEdgeCntr();
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

