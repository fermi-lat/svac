// 
// Class for input of quantity Acd2TileActDistEnergy for monitoring 
// 
// Created by maldera on Mon Apr 20 12:13:49 2015 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_Acd2TileActDistEnergy_h
#define MonInput_Acd2TileActDistEnergy_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_Acd2TileActDistEnergy: public MonInputObject{
 public:
  MonInput_Acd2TileActDistEnergy();
  ~MonInput_Acd2TileActDistEnergy();
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

