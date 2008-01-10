// 
// Class for input of quantity AcdGlobalPos_NotMatchedTrack_FacePosXYZ for monitoring 
// 
// Created by dpaneque on Mon Jan  7 17:34:37 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_AcdGlobalPos_NotMatchedTrack_FacePosXYZ_h
#define MonInput_AcdGlobalPos_NotMatchedTrack_FacePosXYZ_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"
#include "TVector3.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_AcdGlobalPos_NotMatchedTrack_FacePosXYZ: public MonInputObject{
 public:
  MonInput_AcdGlobalPos_NotMatchedTrack_FacePosXYZ();
  ~MonInput_AcdGlobalPos_NotMatchedTrack_FacePosXYZ();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[7][3];
};

#undef VARTYPE
#endif

