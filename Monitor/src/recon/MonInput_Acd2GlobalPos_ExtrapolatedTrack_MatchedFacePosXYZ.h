// 
// Class for input of quantity Acd2GlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ for monitoring 
// 
// Edited by hand by Luca Baldini based on the old file.
//
#ifndef MonInput_Acd2GlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ_h
#define MonInput_Acd2GlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_Acd2GlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ: public MonInputObject{
 public:
  MonInput_Acd2GlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ();
  ~MonInput_Acd2GlobalPos_ExtrapolatedTrack_MatchedFacePosXYZ();
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
