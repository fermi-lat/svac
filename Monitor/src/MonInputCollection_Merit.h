// class to hold monitoring Merit input objects 
// M. Kocian, SLAC, 2/2/07
// Software developed for GLAST

#ifndef MonInputCollection_Merit_h
#define MonInputCollection_Merit_h

#include "MonInputCollection.h"

class MonInputCollection_Merit: public MonInputCollection{
 public:
  MonInputCollection_Merit(TTree* tree, std::string type);
  virtual ~MonInputCollection_Merit(){};
  virtual void readEvent(Long64_t ievent);
  virtual void attachChain();
};


#endif
