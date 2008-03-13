// 
// Class for input of quantity CalTrackAngle for monitoring 
// 
// Created by dpaneque on Thu Mar 13 00:42:08 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CalTrackAngle_h
#define MonInput_CalTrackAngle_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_CalTrackAngle: public MonInputObject{
 public:
  MonInput_CalTrackAngle();
  ~MonInput_CalTrackAngle();
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

