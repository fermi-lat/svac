// 
// Class for input of quantity AcdTotalEnergy for monitoring 
// 
// Created by dpaneque on Wed Apr  9 03:13:59 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_AcdTotalEnergy_h
#define MonInput_AcdTotalEnergy_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_AcdTotalEnergy: public MonInputObject{
 public:
  MonInput_AcdTotalEnergy();
  ~MonInput_AcdTotalEnergy();
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

