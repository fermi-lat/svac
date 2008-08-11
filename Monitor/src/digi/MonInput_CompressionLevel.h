// 
// Class for input of quantity CompressionLevel for monitoring 
// 
// Created by dpaneque on Mon Aug 11 18:05:27 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CompressionLevel_h
#define MonInput_CompressionLevel_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Int_t 

// end user defined part

class MonInput_CompressionLevel: public MonInputObject{
 public:
  MonInput_CompressionLevel();
  ~MonInput_CompressionLevel();
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

