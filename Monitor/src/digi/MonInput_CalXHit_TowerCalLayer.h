// 
// Class for input of quantity CalXHit_TowerCalLayer for monitoring 
// 
// Created by dpaneque on Thu Jun 28 23:07:31 2007 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_CalXHit_TowerCalLayer_h
#define MonInput_CalXHit_TowerCalLayer_h
#include "../MonInputObject.h"
#include "Rtypes.h"
#include "TTree.h"
#include "TObject.h"

// user defined part

#define VARTYPE UShort_t 

// end user defined part

class MonInput_CalXHit_TowerCalLayer: public MonInputObject{
 public:
  MonInput_CalXHit_TowerCalLayer();
  ~MonInput_CalXHit_TowerCalLayer();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
  // only for test purposes...
  /*
  static int evtcounter;
  static int caldigicounter;
  */

 private:
  VARTYPE m_val[16][8];
};

#undef VARTYPE
#endif

