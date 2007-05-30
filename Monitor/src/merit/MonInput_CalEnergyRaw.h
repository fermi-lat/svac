// 
// Class for input of quantity CalEnergyRaw for monitoring 
// 
// Created by dpaneque on Wed Apr 18 18:28:31 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CalEnergyRaw_h
#define MonInput_CalEnergyRaw_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_CalEnergyRaw: public MonInputObject{
 public:
  MonInput_CalEnergyRaw();
  ~MonInput_CalEnergyRaw();
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

