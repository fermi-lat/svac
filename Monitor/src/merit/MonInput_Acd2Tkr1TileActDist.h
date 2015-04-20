// 
// Class for input of quantity Acd2Tkr1TileActDist for monitoring 
// 
// Created by maldera on Mon Apr 20 13:15:04 2015 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_Acd2Tkr1TileActDist_h
#define MonInput_Acd2Tkr1TileActDist_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_Acd2Tkr1TileActDist: public MonInputObject{
 public:
  MonInput_Acd2Tkr1TileActDist();
  ~MonInput_Acd2Tkr1TileActDist();
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

