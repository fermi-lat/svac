// 
// Class for input of quantity CalTransRms for monitoring 
// 
// Created by dpaneque on Thu Mar 13 00:43:03 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CalTransRms_h
#define MonInput_CalTransRms_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_CalTransRms: public MonInputObject{
 public:
  MonInput_CalTransRms();
  ~MonInput_CalTransRms();
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

