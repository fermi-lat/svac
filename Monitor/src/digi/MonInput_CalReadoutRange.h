// 
// Class for input of quantity CalReadoutRange for monitoring 
// 
// Created by dpaneque on Sun Aug 26 17:38:54 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CalReadoutRange_h
#define MonInput_CalReadoutRange_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Short_t 

// end user defined part

class MonInput_CalReadoutRange: public MonInputObject{
 public:
  MonInput_CalReadoutRange();
  ~MonInput_CalReadoutRange();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[16][8][12][2];
};

#undef VARTYPE
#endif

