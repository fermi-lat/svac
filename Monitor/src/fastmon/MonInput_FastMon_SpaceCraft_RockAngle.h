// 
// Class for input of quantity FastMon_SpaceCraft_RockAngle for monitoring 
// 
// Created by bregeon on Thu Jul  3 23:02:47 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FastMon_SpaceCraft_RockAngle_h
#define MonInput_FastMon_SpaceCraft_RockAngle_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_FastMon_SpaceCraft_RockAngle: public MonInputObject{
 public:
  MonInput_FastMon_SpaceCraft_RockAngle();
  ~MonInput_FastMon_SpaceCraft_RockAngle();
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

