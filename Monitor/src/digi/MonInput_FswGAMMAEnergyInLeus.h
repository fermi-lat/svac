// 
// Class for input of quantity FswGAMMAEnergyInLeus for monitoring 
// 
// Created by dpaneque on Mon Aug 11 16:37:56 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FswGAMMAEnergyInLeus_h
#define MonInput_FswGAMMAEnergyInLeus_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_FswGAMMAEnergyInLeus: public MonInputObject{
 public:
  MonInput_FswGAMMAEnergyInLeus();
  ~MonInput_FswGAMMAEnergyInLeus();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[2];
};

#undef VARTYPE
#endif

