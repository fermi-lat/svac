// 
// Class for input of quantity AcdVeto_GafeGarc for monitoring 
// 
// Created by dpaneque on Sun Jan  6 02:11:06 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_AcdVeto_GafeGarc_h
#define MonInput_AcdVeto_GafeGarc_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Int_t 

// end user defined part

class MonInput_AcdVeto_GafeGarc: public MonInputObject{
 public:
  MonInput_AcdVeto_GafeGarc();
  ~MonInput_AcdVeto_GafeGarc();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[18][12];
};

#undef VARTYPE
#endif

