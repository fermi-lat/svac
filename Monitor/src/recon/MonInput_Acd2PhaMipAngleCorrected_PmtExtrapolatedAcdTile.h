// 
// Class for input of quantity Acd2PhaMipAngleCorrected_PmtExtrapolatedAcdTile for monitoring 
// 
// Edited by hand by Luca Baldini based on the old file.
//
#ifndef MonInput_Acd2PhaMipAngleCorrected_PmtExtrapolatedAcdTile_h
#define MonInput_Acd2PhaMipAngleCorrected_PmtExtrapolatedAcdTile_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"
#include <map>

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_Acd2PhaMipAngleCorrected_PmtExtrapolatedAcdTile: public MonInputObject{
 public:
  MonInput_Acd2PhaMipAngleCorrected_PmtExtrapolatedAcdTile();
  ~MonInput_Acd2PhaMipAngleCorrected_PmtExtrapolatedAcdTile();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[2][128];
};

#undef VARTYPE
#endif
