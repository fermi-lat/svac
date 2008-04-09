// 
// Class for input of quantity AcdRibbonEnergy for monitoring 
// 
// Created by dpaneque on Wed Apr  9 03:13:11 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_AcdRibbonEnergy_h
#define MonInput_AcdRibbonEnergy_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_AcdRibbonEnergy: public MonInputObject{
 public:
  MonInput_AcdRibbonEnergy();
  ~MonInput_AcdRibbonEnergy();
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

