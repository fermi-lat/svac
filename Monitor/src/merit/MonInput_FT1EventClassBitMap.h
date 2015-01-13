// 
// Class for input of quantity FT1EventClassBitMap for monitoring 
// 
// Created by dpaneque on Wed Jun  8 19:17:51 2011 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_FT1EventClassBitMap_h
#define MonInput_FT1EventClassBitMap_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Int_t 

// end user defined part

class MonInput_FT1EventClassBitMap: public MonInputObject{
 public:
  MonInput_FT1EventClassBitMap();
  ~MonInput_FT1EventClassBitMap();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[16];
  UInt_t m_inputval;
};

#undef VARTYPE
#endif

