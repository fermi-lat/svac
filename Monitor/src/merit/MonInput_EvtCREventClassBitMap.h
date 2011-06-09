// 
// Class for input of quantity EvtCREventClassBitMap for monitoring 
// 
// Created by dpaneque on Wed Jun  8 19:38:30 2011 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_EvtCREventClassBitMap_h
#define MonInput_EvtCREventClassBitMap_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Int_t 

// end user defined part

class MonInput_EvtCREventClassBitMap: public MonInputObject{
 public:
  MonInput_EvtCREventClassBitMap();
  ~MonInput_EvtCREventClassBitMap();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[21];
  UInt_t m_inputval;
};

#undef VARTYPE
#endif

