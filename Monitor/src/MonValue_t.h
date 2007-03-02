#ifndef MonValue_h
#define MonValue_h 

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

//
// 
// Base class for strip chart value objects
//
class MonValue {
  
public :
  
  // Standard c'tor, needs a name, this is where the data end up
  // on the output tree
  MonValue(const char* name, const char* formula, const char* cut)
    :m_name(name), m_cut(cut), m_formula(formula){}

  // D'tor, no-op
  virtual ~MonValue(){
  }

  // Do any calculations need to go from cached values to output value
  // For example averaging, summing, etc.
  virtual void latchValue() = 0;

  // Reset the cached and output values
  virtual void reset() = 0;

  // Attach this value to a TTree
  virtual int attach(TTree& tree, const std::string& prefix) const = 0;

  // Just return the name of this var
  inline const std::string& name() const { return m_name; }
  
  virtual void increment(TTree* tree)=0;

 protected:
  
  const std::vector<std::string> queryTree(TTree* tree);
  
 private:
  

  // The name of this var
  const std::string m_name;    
  const std::string m_cut;    
  const std::string m_formula;    
};

#endif
