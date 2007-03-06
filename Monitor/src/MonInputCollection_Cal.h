// class to hold monitoring Cal input objects 
// M. Kocian, SLAC, 2/2/07
// Software developed for GLAST

#ifndef MonInputCollection_Cal_h
#define MonInputCollection_Cal_h

#include "MonInputCollection.h"

class MonInputCollection_Cal: public MonInputCollection{
 public:
  MonInputCollection_Cal(TTree* tree, std::string type);
  virtual ~MonInputCollection_Cal(){};
  virtual void readEvent(Long64_t ievent);
  virtual void attachChain();
};


#endif
