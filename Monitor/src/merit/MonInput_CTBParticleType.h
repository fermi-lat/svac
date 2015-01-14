// 
// Class for input of quantity CTBParticleType for monitoring 
// 
// Created by dpaneque on Thu May 29 04:19:18 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CTBParticleType_h
#define MonInput_CTBParticleType_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_CTBParticleType: public MonInputObject{
 public:
  MonInput_CTBParticleType();
  ~MonInput_CTBParticleType();
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

