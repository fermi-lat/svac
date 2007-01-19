#ifndef MonDataFiller_h
#define MonDataFiller_h 

//
// STL 
#include <string>
#include <map>
#include <list>
#include <set>

// ROOT
#include "Rtypes.h"
#include "TMath.h"

//
#include "MonValueImpls.h"

class TTree;
class DigiEvent;
class ReconEvent;

//
// 
// Base class for strip chart value objects
//
class MonDataFiller {
  
public :
  
  // Standard c'tor, needs a name, this is where the data end up
  // on the output tree
  MonDataFiller(const char* name, const char* prefix)
    :m_name(name),m_vals(name,prefix){}

  // D'tor, no-op
  virtual ~MonDataFiller(){
  }

  // Attach to an input TTree
  virtual Bool_t attachInput(TTree& tree);

  // Specify a branch (or group of branches) to turn on
  void addBranchToRead(const std::string& bName) {
    m_readBranches.insert(bName);
  }

  // The set of all the branches to turn on
  inline const std::set<std::string>& readBranches() const { return m_readBranches; }

  // add a child node
  void addChild(MonDataFiller& child);

  // find a child node by name
  MonDataFiller* find(const std::string& name);

  // return the name
  inline const std::string& name() const { return m_name; };

  // The values to store
  inline MonValueCol& vals() { return m_vals; };

private:

  // The name of this 
  const std::string m_name;    

  // Branches to turn on
  std::set<std::string> m_readBranches;

  // Values to store
  MonValueCol m_vals;

  // sub-nodes
  std::list<MonDataFiller*> m_children;
  std::map<std::string,MonDataFiller*> m_childMap;
  
};

class ReconDataFiller : public MonDataFiller { 
public:
  ReconDataFiller(const char* name, const char* prefix)
    :MonDataFiller(name, prefix){
  }
  virtual ~ReconDataFiller() {;}

  virtual void filterEvent(ReconEvent& event, Bool_t& filtered) { return; }

  virtual void useEvent(ReconEvent& event, Bool_t& used) { return; }
};

class SvacDataFiller : public MonDataFiller { 
public:
  SvacDataFiller(const char* name, const char* prefix)
    :MonDataFiller(name,prefix){
  }
  virtual ~SvacDataFiller() {;}

  virtual void filterEvent(Long64_t iEvent, Bool_t& filtered) { return; }

  virtual void useEvent(Long64_t iEvent, Bool_t& used) { return; }
};

class MeritDataFiller : public MonDataFiller { 
public:
  MeritDataFiller(const char* name, const char* prefix)
    :MonDataFiller(name,prefix){
  }
  virtual ~MeritDataFiller() {;}

  virtual void filterEvent(Long64_t iEvent, Bool_t& filtered) { return; }

  virtual void useEvent(Long64_t iEvent, Bool_t& used) { return; }
};





#endif
