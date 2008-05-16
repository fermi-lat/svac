// 
// Class for input of quantity DataTransferId for monitoring 
// 
// Created by dpaneque on Fri May 16 01:13:45 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_DataTransferId_h
#define MonInput_DataTransferId_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UInt_t 

// end user defined part

class MonInput_DataTransferId: public MonInputObject{
 public:
  MonInput_DataTransferId();
  ~MonInput_DataTransferId();
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

