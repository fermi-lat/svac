// 
// Class for input of quantity Acd2PhaMips_PmtA_AcdTile for monitoring 
// 
// Edited by hand by Luca B from the old Acd file.
//
#ifndef MonInput_Acd2PhaMips_PmtA_AcdTile_h
#define MonInput_Acd2PhaMips_PmtA_AcdTile_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Float_t 

// end user defined part

class MonInput_Acd2PhaMips_PmtA_AcdTile: public MonInputObject{
 public:
  MonInput_Acd2PhaMips_PmtA_AcdTile();
  ~MonInput_Acd2PhaMips_PmtA_AcdTile();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[128];
};

#undef VARTYPE
#endif
