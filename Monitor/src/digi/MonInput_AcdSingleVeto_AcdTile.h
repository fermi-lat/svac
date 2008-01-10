// 
// Class for input of quantity AcdSingleVeto for monitoring 
// 
// Created by dpaneque on Wed Oct 31 22:39:07 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_AcdSingleVeto_AcdTile_h
#define MonInput_AcdSingleVeto_AcdTile_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Bool_t 

// end user defined part

class MonInput_AcdSingleVeto_AcdTile: public MonInputObject{
 public:
  MonInput_AcdSingleVeto_AcdTile();
  ~MonInput_AcdSingleVeto_AcdTile();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[128];
};

#undef VARTYPE
#endif

