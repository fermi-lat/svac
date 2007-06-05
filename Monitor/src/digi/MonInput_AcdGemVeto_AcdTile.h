// 
// Class for input of quantity AcdGemVeto_AcdTile for monitoring 
// 
// Created by dpaneque on Mon Jun  4 22:34:02 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_AcdGemVeto_AcdTile_h
#define MonInput_AcdGemVeto_AcdTile_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Bool_t 

// end user defined part

class MonInput_AcdGemVeto_AcdTile: public MonInputObject{
 public:
  MonInput_AcdGemVeto_AcdTile();
  ~MonInput_AcdGemVeto_AcdTile();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[128];// 1 for the existance of a ACD GEM Veto [AcdTile]
};

#undef VARTYPE
#endif

