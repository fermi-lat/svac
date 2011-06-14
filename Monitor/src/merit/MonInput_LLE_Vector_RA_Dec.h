// 
// Class for input of quantity LLE_Vector_RA_Dec for monitoring 
// 
// Created by dpaneque on Mon Jun 13 17:28:23 2011 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_LLE_Vector_RA_Dec_h
#define MonInput_LLE_Vector_RA_Dec_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE Int_t 

// end user defined part

class MonInput_LLE_Vector_RA_Dec: public MonInputObject{
 public:
  MonInput_LLE_Vector_RA_Dec();
  ~MonInput_LLE_Vector_RA_Dec();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
  Float_t getSeparation(Float_t RefRA,Float_t RefDec,Float_t RA,Float_t Dec);
 private:
  VARTYPE m_val[8][5];
  UInt_t m_ft1eventclass;
  Float_t m_RA;
  Float_t m_Dec;
  Float_t m_RALocations[8];
  Float_t m_DecLocations[5];
  Double_t m_PI;
  Float_t m_radius;
};

#undef VARTYPE
#endif

