// 
// Class for input of quantity CalXtalFaceSignal for monitoring 
// 
// Created by dpaneque on Thu Aug 23 18:28:31 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CalXtalFaceSignal_h
#define MonInput_CalXtalFaceSignal_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_CalXtalFaceSignal: public MonInputObject{
 public:
  MonInput_CalXtalFaceSignal();
  ~MonInput_CalXtalFaceSignal();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[16][8][12][2];
};

#undef VARTYPE
#endif

