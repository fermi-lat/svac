// 
// Class for input of quantity stripOcc for monitoring 
// 
// Created by dpaneque on Fri May 16 04:57:38 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_stripOcc_h
#define MonInput_stripOcc_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_stripOcc: public MonInputObject{
 public:
  MonInput_stripOcc();
  ~MonInput_stripOcc();
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

