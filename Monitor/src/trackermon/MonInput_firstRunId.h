// 
// Class for input of quantity firstRunId for monitoring 
// 
// Created by dpaneque on Thu May 15 00:06:09 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_firstRunId_h
#define MonInput_firstRunId_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UInt_t 

// end user defined part

class MonInput_firstRunId: public MonInputObject{
 public:
  MonInput_firstRunId();
  ~MonInput_firstRunId();
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

