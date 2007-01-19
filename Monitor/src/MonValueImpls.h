#ifndef MonValueImpls_h
#define MonValueImpls_h 

// This file has the various implementations 
// 
// Current these include
//
//  MonCounter:      Just a simple counter that can be incremented or added to
//                   reset returns to 0.
//                   Stored as a 32 bit int.
//
//  MonMean:         Keeps track of values and calculates their mean and the error on the mean
//                   reset nulls values and returns running sums to zero.
//                   Stored as a 32 bit float.
//
//  MonCounterDiff:  Keeps track of the difference in a counter.  
//                   reset 
//
//
//  MonMinMax:       Keeps track of the min and max of a value.
//                   reset nulls the caches
//

//
// Base class
#include "MonValue.h"

//
// STL 
#include <map>
#include <list>

// ROOT
#include "Rtypes.h"
#include "TMath.h"

//
// 
// This implementation is for a counter that we increment
// either using the ++ or += operators.
class MonCounter : public MonValue {

public:

  // Standard c'tor, just the name
  MonCounter(const char* name) 
    :MonValue(name),
     m_current(0),m_val(0){
  }

  // D'tor, no-op
  virtual ~MonCounter(){
  }
  
  // Reset just nulls the values
  virtual void reset() {
    m_current = 0;
    m_val = 0;
  }

  // Attach this to a TTree
  virtual int attach(TTree& tree, const std::string& prefix) const;

  // Just move the counter to the output value
  virtual void latchValue() {
    m_val = m_current;
  }

  // ++ prefix increment operator
  inline ULong64_t operator++() {
    return ++m_current;
  }
  
  // ++ postfix increment operator
  inline ULong64_t operator++(int) {
    return m_current++;
  }

  // += addition operator
  inline ULong64_t operator+=(ULong64_t val) {
    m_current += val;
    return m_current;
  }

private:

  // the cached value
  mutable ULong64_t m_current;

  // the output value
  ULong64_t m_val;
};

//
// 
// This implementation takes the average of several values
// using running sums of n, v and v2
class MonMean : public MonValue {

public:
  
  // Standard c'tor, just the name
  MonMean(const char* name) 
    :MonValue(name),
     m_nVals(0),m_sum(0.),m_sum2(0.),
     m_val(0.),m_err(0.){
  }
  
  // D'tor, no-op
  virtual ~MonMean(){
  }

  // Latch the values, so calculate mean, rms, err_on_mean
  virtual void latchValue() {
    if ( m_nVals < 1 ) return;
    m_val = m_sum / ((Double_t)m_nVals);
    Double_t err2 = m_sum2;
    err2 /= ((Double_t)m_nVals);
    err2 -= m_val*m_val;    
    err2 /= ((Double_t)m_nVals);
    m_err = err2 > 0 ? TMath::Sqrt(err2) : 0.;
  }

  // reset, null everything
  virtual void reset() {
    m_err = 0.;
    m_val = 0.;
    m_nVals = 0;
    m_sum = 0.;
    m_sum2 = 0.;
  }

  // attach both mean and err_on_mean to TTree
  virtual int attach(TTree& tree, const std::string& prefix) const;

  // add a value input the mean, so add to running sums
  inline ULong64_t operator+=(Float_t val) {
    m_nVals++;
    m_sum += val;
    m_sum2 += (val*val);    
    return m_nVals;
  }

private:

  // cached values, the running sums
  mutable ULong64_t m_nVals;
  mutable Double_t m_sum;
  mutable Double_t m_sum2;

  // output values
  Float_t m_val;
  Float_t m_err;

  
};

//
// 
// This implementation takes the difference between the 
// first and last values of a counter
class MonCounterDiff  : public MonValue {

protected:
  
  static const ULong64_t s_maxVal64;

public:
  // Standard c'tor, just the name
  MonCounterDiff(const char* name) 
    :MonValue(name),
     m_lo(s_maxVal64),m_hi(0),m_val(0){
  }

  // D'tor, no-op
  virtual ~MonCounterDiff(){
  }
  
  // Reset, check to see if the cache makes sense
  // if so, just copy hi -> lo and go on
  // in not, reset both hi and lo
  virtual void reset() {
    m_lo = m_lo >= m_hi ? s_maxVal64 : m_hi;
    m_hi = m_lo >= m_hi ? 0 : m_hi;
    m_val = 0;
  }

  // Attach this to a TTree
  virtual int attach(TTree& tree, const std::string& prefix) const;

  // Take the difference hi-lo and move it to the output value
  virtual void latchValue() {
    m_val = m_lo < m_hi ? m_hi - m_lo : 0;
  }

  // Update the value, check to make sure that things make sense
  inline ULong64_t operator+=(ULong64_t val) {
    if ( m_lo == s_maxVal64 ) {
      m_lo = val;
    }
    if ( val > m_hi ) {
      m_hi = val;
    }
    return m_hi;
  }

private:
  
  // cached values, lo and hi values from current time slice
  mutable ULong64_t m_lo;
  mutable ULong64_t m_hi;

  // output value
  ULong64_t m_val;
};

//
// 
// This implementation stores the min and max
// values of a counter
class MonMinMax  : public MonValue {

protected:
  
  static const Float_t s_huge;

public:
  // Standard c'tor, just the name
  MonMinMax(const char* name) 
    :MonValue(name),
     m_min(s_huge),m_max(-s_huge){
  }

  // D'tor, no-op
  virtual ~MonMinMax(){
  }
  
  // Reset, check to see if the cache makes sense
  // if so, just copy hi -> lo and go on
  // in not, reset both hi and lo
  virtual void reset() {
    m_min = s_huge;
    m_max = -s_huge;
  }

  // Attach this to a TTree
  virtual int attach(TTree& tree, const std::string& prefix) const;

  // Take the difference hi-lo and move it to the output value
  virtual void latchValue() {
    return;
  }

  // Update the value, check to make sure that things make sense
  inline void include(Float_t val) {
    m_min = m_min < val ? m_min : val;
    m_max = m_max > val ? m_max : val;
  }

private:
  
  // lo and hi values from current time slice
  Float_t m_min;
  Float_t m_max;
};

//
// 
// This implementation just allows recursively defining 
// collections of MonValues
class MonValueCol : public MonValue {

public:
  // Standard c'tor, just the name and a prefix
  MonValueCol(const char* name, const char* prefix)
    :MonValue(name),m_prefix(prefix){
  }
  
  // D'tor, no-op, but does clean data structure
  virtual ~MonValueCol() {
  }

  // Add a val to this collection
  void addVal(MonValue& val);

  // Find a val inside this collection
  // This does not recurse
  MonValue* findByName(const std::string& theName);

  //
  inline const std::string& prefix() const { return m_prefix; };

  // Attach all sub-nodes to a TTree, 
  // Uses name as a prefix, recurses
  virtual int attach(TTree& tree, const std::string& pref) const;

  // Reset all sub-nodes, recurses
  virtual void reset();

  // Latch values for all sub-nodes, recurses
  virtual void latchValue();

private:

  // The prefix for sub-nodes
  std::string m_prefix;

  // Just a list of the sub-nodes
  std::list<MonValue*> m_vals;  

  // A map from name -> sub-node
  std::map<std::string,MonValue*> m_nameMap;

};

#endif
