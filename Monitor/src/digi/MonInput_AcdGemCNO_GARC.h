// 
// Class for input of quantity AcdGemCNO_GARC for monitoring 
// 
// Created by dpaneque on Mon Jun  4 23:09:49 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_AcdGemCNO_GARC_h
#define MonInput_AcdGemCNO_GARC_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Bool_t 

// end user defined part

class MonInput_AcdGemCNO_GARC: public MonInputObject{
 public:
  MonInput_AcdGemCNO_GARC();
  ~MonInput_AcdGemCNO_GARC();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[12];
};

#undef VARTYPE
#endif

