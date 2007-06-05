// 
// Class for input of quantity AcdHit_AcdTile for monitoring 
// 
// Created by dpaneque on Tue Jun  5 00:25:53 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_AcdHit_AcdTile_h
#define MonInput_AcdHit_AcdTile_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Bool_t 

// end user defined part

class MonInput_AcdHit_AcdTile: public MonInputObject{
 public:
  MonInput_AcdHit_AcdTile();
  ~MonInput_AcdHit_AcdTile();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
  UShort_t getGemId(UInt_t id);


 private:
  VARTYPE m_val[128];
};

#undef VARTYPE
#endif

