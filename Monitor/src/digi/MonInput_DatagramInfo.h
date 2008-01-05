// 
// Class for input of quantity DatagramInfo for monitoring 
// 
// Created by dpaneque on Mon Dec 17 21:08:27 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_DatagramInfo_h
#define MonInput_DatagramInfo_h
#include "../MonInputObject.h"
#include "enums/Lsf.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Int_t 

// end user defined part

class MonInput_DatagramInfo: public MonInputObject{
 public:
  MonInput_DatagramInfo();
  ~MonInput_DatagramInfo();
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

