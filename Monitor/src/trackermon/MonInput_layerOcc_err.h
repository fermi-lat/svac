// 
// Class for input of quantity layerOcc_err for monitoring 
// 
// Created by lbaldini on Fri Jan 15 11:25:13 2010 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_layerOcc_err_h
#define MonInput_layerOcc_err_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_layerOcc_err: public MonInputObject{
 public:
  MonInput_layerOcc_err();
  ~MonInput_layerOcc_err();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  // Modification by lb starting...
  VARTYPE m_val[16][36];
  // Modification by lb ended.
};

#undef VARTYPE
#endif

