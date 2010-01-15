// 
// Class for input of quantity fracSat_err for monitoring 
// 
// Created by lbaldini on Thu Jan 14 18:31:31 2010 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_fracSat_err_h
#define MonInput_fracSat_err_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_fracSat_err: public MonInputObject{
 public:
  MonInput_fracSat_err();
  ~MonInput_fracSat_err();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  // Modification by lb starting.
  VARTYPE m_val[16][36];
  // Modification by lb ending.
};

#undef VARTYPE
#endif

