#ifndef MonGlobalCut_h
#define MonGlobalCut_h
#define MAXMEM 20e6

//
// This File has basic interface for the monitoring values
//
//

//
// STL 
#include <string>
#include <vector>

// ROOT
#include "Rtypes.h"

class TTree;
class TSelector;
class TEventList;


//
// 
// Base class for strip chart value objects
//
class MonGlobalCut {
  
public :
  
  // Standard c'tor, needs a name, this is where the data end up
  // on the output tree
  MonGlobalCut(const char* name, const char* cut);

  // D'tor, no-op
  virtual ~MonGlobalCut(){
  }

  // Reset the cached and output values
  virtual void reset() ;

  // Just return the name of this var
  inline const std::string& name() const { return m_name; }
  
  virtual void applyCut(TTree* tree);

  virtual void makeProxy(TTree* tree);
  unsigned long long nUsed(){return m_nUsed;}
  unsigned long long nFilter(){return m_nFilter;}
  TEventList* eventList(){return m_eventlist;}
  float timeProfile();
 protected:
  

  // The name of this cut
  std::string m_name;    
  const std::string m_cut;    
  TSelector* m_sel;
  unsigned long long m_nUsed;
  unsigned long long m_nFilter;
  TEventList* m_eventlist;
  unsigned long long m_timeprof;
  unsigned int m_counter;
};

#endif
