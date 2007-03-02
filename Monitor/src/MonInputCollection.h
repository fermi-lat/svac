// class to hold monitoring input objects 
// M. Kocian, SLAC, 2/2/07
// Software developed for GLAST

#ifndef MonInputCollection_h
#define MonInputCollection_h

#include <vector>
#include <string>
#include "MonInputObject.h"
#include "Rtypes.h"

class TObject;


class MonInputCollection{
 public:
  MonInputCollection(TTree* tree, std::string type);
  virtual ~MonInputCollection();
  void attachInputTree();
  unsigned nObjects();
  void addInputObject(MonInputObject* obj);
  void populateTableTree(TTree* tree);
  virtual void readEvent(Long64_t ievent)=0;
  virtual void attachChain()=0;
 protected:
  void readValues();
  
  std::vector<MonInputObject*>* m_inpcol;
  bool m_isattached;
  TTree* m_intree;
  std::string m_type;
  TObject* m_event;
};
#endif
