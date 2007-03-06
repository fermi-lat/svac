// class to hold monitoring Svac input objects 
// M. Kocian, SLAC, 2/2/07
// Software developed for GLAST

#ifndef MonInputCollection_Svac_h
#define MonInputCollection_Svac_h

#include "MonInputCollection.h"

class MonInputCollection_Svac: public MonInputCollection{
 public:
  MonInputCollection_Svac(TTree* tree, std::string type);
  virtual ~MonInputCollection_Svac(){};
  virtual void readEvent(Long64_t ievent);
  virtual void attachChain();
};


#endif
