// class to hold monitoring Tuple input objects (Merit, Svac, CAL, etc.)
// M. Kocian, SLAC, 2/2/07
// Software developed for GLAST

#ifndef MonInputCollection_Tuple_h
#define MonInputCollection_Tuple_h

#include "MonInputCollection.h"

class MonInputCollection_Tuple: public MonInputCollection{
 public:
  MonInputCollection_Tuple(TTree* tree, std::string type);
  virtual ~MonInputCollection_Tuple(){};
  virtual void readEvent(Long64_t ievent);
  virtual void attachChain();
};


#endif
