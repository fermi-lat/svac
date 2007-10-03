// 
// Class for input of quantity DeltaWindowOpen for monitoring 
// 
// Created by dpaneque on Wed Oct  3 00:33:15 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_DeltaWindowOpen_h
#define MonInput_DeltaWindowOpen_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UShort_t 

// end user defined part

class MonInput_DeltaWindowOpen: public MonInputObject{
 public:
  MonInput_DeltaWindowOpen();
  ~MonInput_DeltaWindowOpen();
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

