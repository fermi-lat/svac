// 
// Class for input of quantity OBFStatus for monitoring 
// 
// Created by dpaneque on Wed Sep 26 01:24:44 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_OBFStatus_h
#define MonInput_OBFStatus_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Bool_t 

// end user defined part

class MonInput_OBFStatus: public MonInputObject{
 public:
  MonInput_OBFStatus();
  ~MonInput_OBFStatus();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
  // tmp for debug
  /*
  static int gfcounter;
  static int mipfcounter;
  static int mipgfcounter;
  */
  // end of tmp for debug
 private:
  VARTYPE m_val[4];
};

#undef VARTYPE
#endif

