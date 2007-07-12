#ifndef MonValue_h
#define MonValue_h 
#define MAXMEM 20e6

//
// This File has basic interface for the monitoring values
//
//

//
// STL 
#include <string>
#include <time.h>
#include <vector>

// ROOT
#include "Rtypes.h"

class TTree;
class TSelector;


//
// 
// Base class for strip chart value objects
//
class MonValue {
  
public :
  
  // Standard c'tor, needs a name, this is where the data end up
  // on the output tree
  MonValue(const char* name, const char* formula, const char* cut);

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
  
  virtual void increment(TTree* tree);

  virtual void makeProxy(TTree* tree);
  float timeProfile();
  void setSharedLibDir(std::string);
  void setDontCompile(bool);

 protected:
  /// val2 is only used for 2d histograms 
  virtual void singleincrement(Double_t* val,Double_t* val2=0){};
  // a helper function to parse parameter strings of the type [234, 23, 44]
  static std::vector<std::string> parse(const std::string str, const std::string beg, const std::string sep, const std::string end);
  
  const std::string indexString(int index);

  // The name of this var
  std::string m_name;    
  const std::string m_cut;    
  const std::string m_formula;    
  TSelector* m_sel;
  int m_histdim;
  unsigned long long m_timeprof;
  bool m_dontcompile;
  std::string m_dimstring;    
  unsigned m_dim;
  std::string m_sodir;
  static std::vector<double> *m_result;
  static std::vector<double> *m_result2;
  static unsigned int m_counter;
};

#endif
