// 
// Class for input of quantity AcdTileCount for monitoring 
// 
// Created by dpaneque on Wed Mar 12 18:57:08 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_AcdTileCount_h
#define MonInput_AcdTileCount_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UInt_t 

// end user defined part

class MonInput_AcdTileCount: public MonInputObject{
 public:
  MonInput_AcdTileCount();
  ~MonInput_AcdTileCount();
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

