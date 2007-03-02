// class to hold monitoring digi input objects 
// M. Kocian, SLAC, 2/2/07
// Software developed for GLAST

#ifndef MonInputCollection_Digi_h
#define MonInputCollection_Digi_h

#include "MonInputCollection.h"

class MonInputCollection_Digi: public MonInputCollection{
 public:
  MonInputCollection_Digi(TTree* tree, std::string type);
  virtual ~MonInputCollection_Digi(){};
  virtual void readEvent(Long64_t ievent);
  virtual void attachChain();
};


#endif
