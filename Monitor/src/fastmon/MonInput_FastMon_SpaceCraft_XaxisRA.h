// 
// Class for input of quantity FastMon_SpaceCraft_XaxisRA for monitoring 
// 
// Created by bregeon on Thu Jul  3 23:03:16 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FastMon_SpaceCraft_XaxisRA_h
#define MonInput_FastMon_SpaceCraft_XaxisRA_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_FastMon_SpaceCraft_XaxisRA: public MonInputObject{
 public:
  MonInput_FastMon_SpaceCraft_XaxisRA();
  ~MonInput_FastMon_SpaceCraft_XaxisRA();
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

