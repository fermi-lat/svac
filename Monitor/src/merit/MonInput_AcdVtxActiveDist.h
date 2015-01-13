// 
// Class for input of quantity AcdVtxActiveDist for monitoring 
// 
// Created by dpaneque on Wed Mar 12 21:15:29 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_AcdVtxActiveDist_h
#define MonInput_AcdVtxActiveDist_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_AcdVtxActiveDist: public MonInputObject{
 public:
  MonInput_AcdVtxActiveDist();
  ~MonInput_AcdVtxActiveDist();
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

