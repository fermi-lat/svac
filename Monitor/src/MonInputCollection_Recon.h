// class to hold monitoring recon input objects 
// M. Kocian, SLAC, 2/2/07
// Software developed for GLAST

#ifndef MonInputCollection_Recon_h
#define MonInputCollection_Recon_h

#include "MonInputCollection.h"

class MonInputCollection_Recon: public MonInputCollection{
 public:
  MonInputCollection_Recon(TTree* tree, std::string type);
  virtual ~MonInputCollection_Recon(){};
  virtual void readEvent(Long64_t ievent);
  virtual void attachChain();
};


#endif
