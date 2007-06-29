// 
// Class for input of quantity ReconNumTracks for monitoring 
// 
// Created by dpaneque on Fri Jun 29 03:03:51 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_ReconNumTracks_h
#define MonInput_ReconNumTracks_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UShort_t 

// end user defined part

class MonInput_ReconNumTracks: public MonInputObject{
 public:
  MonInput_ReconNumTracks();
  ~MonInput_ReconNumTracks();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val[10];
};

#undef VARTYPE
#endif

