// 
// Class for input of quantity AcdHit_GafeGarc for monitoring 
// 
// Created by dpaneque on Sun Jan  6 02:11:29 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_AcdHit_GafeGarc_h
#define MonInput_AcdHit_GafeGarc_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Int_t 

// end user defined part

class MonInput_AcdHit_GafeGarc: public MonInputObject{
 public:
  MonInput_AcdHit_GafeGarc();
  ~MonInput_AcdHit_GafeGarc();
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

