// 
// Class for input of quantity AcdActiveDist3D for monitoring 
// 
// Created by dpaneque on Wed Apr  9 03:09:28 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_AcdActiveDist3D_h
#define MonInput_AcdActiveDist3D_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_AcdActiveDist3D: public MonInputObject{
 public:
  MonInput_AcdActiveDist3D();
  ~MonInput_AcdActiveDist3D();
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

