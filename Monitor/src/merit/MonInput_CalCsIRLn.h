// 
// Class for input of quantity CalCsIRLn for monitoring 
// 
// Created by dpaneque on Thu Mar 13 00:39:11 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CalCsIRLn_h
#define MonInput_CalCsIRLn_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_CalCsIRLn: public MonInputObject{
 public:
  MonInput_CalCsIRLn();
  ~MonInput_CalCsIRLn();
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

