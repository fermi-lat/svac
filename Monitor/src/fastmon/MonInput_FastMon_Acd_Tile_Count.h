// 
// Class for input of quantity FastMon_Acd_Tile_Count for monitoring 
// 
// Created by bregeon on Thu Feb 28 14:08:11 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FastMon_Acd_Tile_Count_h
#define MonInput_FastMon_Acd_Tile_Count_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Int_t 

// end user defined part

class MonInput_FastMon_Acd_Tile_Count: public MonInputObject{
 public:
  MonInput_FastMon_Acd_Tile_Count();
  ~MonInput_FastMon_Acd_Tile_Count();
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

