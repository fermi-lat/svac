// 
// Class for input of quantity layerEff_err for monitoring 
// 
// Created by dpaneque on Fri May 16 04:54:48 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_layerEff_err_h
#define MonInput_layerEff_err_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_layerEff_err: public MonInputObject{
 public:
  MonInput_layerEff_err();
  ~MonInput_layerEff_err();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[16][36];
};

#undef VARTYPE
#endif

