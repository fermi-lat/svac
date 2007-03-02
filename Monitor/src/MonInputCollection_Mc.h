// class to hold monitoring mc input objects 
// M. Kocian, SLAC, 2/2/07
// Software developed for GLAST

#ifndef MonInputCollection_Mc_h
#define MonInputCollection_Mc_h

#include "MonInputCollection.h"

class MonInputCollection_Mc: public MonInputCollection{
 public:
  MonInputCollection_Mc(TTree* tree, std::string type);
  virtual ~MonInputCollection_Mc(){};
  virtual void readEvent(Long64_t ievent);
  virtual void attachChain();
};


#endif
