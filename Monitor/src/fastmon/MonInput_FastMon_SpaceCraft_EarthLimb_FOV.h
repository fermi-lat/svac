// 
// Class for input of quantity FastMon_SpaceCraft_EarthLimb_FOV for monitoring 
// 
// Created by bregeon on Thu Jul  3 23:04:46 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FastMon_SpaceCraft_EarthLimb_FOV_h
#define MonInput_FastMon_SpaceCraft_EarthLimb_FOV_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_FastMon_SpaceCraft_EarthLimb_FOV: public MonInputObject{
 public:
  MonInput_FastMon_SpaceCraft_EarthLimb_FOV();
  ~MonInput_FastMon_SpaceCraft_EarthLimb_FOV();
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

