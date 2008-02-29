// 
// Class for input of quantity FastMon_geomagnetic_cutoff for monitoring 
// 
// Created by bregeon on Thu Feb 28 11:38:31 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FastMon_geomagnetic_cutoff_h
#define MonInput_FastMon_geomagnetic_cutoff_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Double_t 

// end user defined part

class MonInput_FastMon_geomagnetic_cutoff: public MonInputObject{
 public:
  MonInput_FastMon_geomagnetic_cutoff();
  ~MonInput_FastMon_geomagnetic_cutoff();
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

