// 
// Class for input of quantity AcdGlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ for monitoring 
// 
// Created by dpaneque on Mon Jan  7 18:35:28 2008 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_AcdGlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ_h
#define MonInput_AcdGlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_AcdGlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ: public MonInputObject{
 public:
  MonInput_AcdGlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ();
  ~MonInput_AcdGlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[2][7][3];
  static int sillycounter;
};

#undef VARTYPE
#endif

