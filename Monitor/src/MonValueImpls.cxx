// Header file
#include "MonValueImpls.h"

// To attach to trees
#include "TTree.h"
#include <cassert>

const ULong64_t MonCounterDiff::s_maxVal64(0xFFFFFFFFFFFFFFFF);
const Float_t MonMinMax::s_huge(1e35);

// Attach a MonCounter node to a TTree (unsigned int)
int MonCounter::attach(TTree& tree, const std::string& prefix) const {
  std::string fullName = prefix + name();
  std::string leafType = fullName + "/l";
  TBranch* b = tree.Branch(fullName.c_str(),(void*)(&m_val),leafType.c_str());
  return b != 0 ? 1 : -1;
}

// Attach a MonMean node to a TTree (mean and err as float)
int MonMean::attach(TTree& tree, const std::string& prefix) const {
  std::string fullNameVal = prefix + name();
  std::string leafTypeVal = fullNameVal + "/F";
  TBranch* b = tree.Branch(fullNameVal.c_str(),(void*)(&m_val),leafTypeVal.c_str());
  if ( b == 0 ) return -1;
  std::string fullNameErr = fullNameVal + "_err";
  std::string leafTypeErr = fullNameErr + "/F";
  TBranch* bErr = tree.Branch(fullNameErr.c_str(),(void*)(&m_err),leafTypeErr.c_str());
  return bErr != 0 ? 2 : -1;
}

// Attach a MonCounterDif node to a TTree (unsigned int)
int MonCounterDiff::attach(TTree& tree, const std::string& prefix) const {
  std::string fullName = prefix + name();
  std::string leafType = fullName + "/l";
  TBranch* b = tree.Branch(fullName.c_str(),(void*)(&m_val),leafType.c_str());
  return b != 0 ? 1 : -1;
}


// Attach a MonMinMax node to a TTree (unsigned int)
int MonMinMax::attach(TTree& tree, const std::string& prefix) const {
  std::string fullNameMin = prefix + name();
  fullNameMin += "_min";
  std::string leafTypeMin = fullNameMin + "/l";
  std::string fullNameMax = prefix + name();
  fullNameMax += "_min";
  std::string leafTypeMax = fullNameMax + "/l";
  TBranch* b = tree.Branch(fullNameMin.c_str(),(void*)(&m_min),leafTypeMin.c_str());
  if ( b == 0 ) return -1;
  b = tree.Branch(fullNameMin.c_str(),(void*)(&m_max),leafTypeMin.c_str());
  return b != 0 ? 2 : -1;
}

// Add a node to a MonValueCol
// Note that this does not operater recursively
void MonValueCol::addVal(MonValue& val){
  std::map<std::string,MonValue*>::const_iterator itrFind = m_nameMap.find(val.name());
  if ( itrFind != m_nameMap.end() ) {
    //    std::cerr << "Already have a variable " << val.name() 
    //	      << " in this collection" << std::endl;
    return;
  }
  m_nameMap[val.name()] = &val;
  m_vals.push_back(&val);
}

// find a node inside a collection
// Note that this does not recursively search
MonValue* MonValueCol::findByName(const std::string& theName){
  std::map<std::string,MonValue*>::iterator itrFind = m_nameMap.find(theName);
  return itrFind != m_nameMap.end() ? itrFind->second : 0;
}

// Attach a collection of nodes to a tree
// This does operate recursively
int MonValueCol::attach(TTree& tree, const std::string& pref) const {
  int retVal(0);
  std::string fullPrefix = pref;
  fullPrefix += prefix();
  for ( std::list<MonValue*>::const_iterator itr = m_vals.begin();
	itr != m_vals.end(); itr++ ) {
    int testVal = (*itr)->attach(tree,fullPrefix);
    if ( testVal < 0 ) return testVal;
    retVal += testVal;
  }
  return retVal;
}

// Reset all the nodes in a collection
// This does operate recursively
void MonValueCol::reset(){
  for ( std::list<MonValue*>::iterator itr = m_vals.begin();
	itr != m_vals.end(); itr++ ) {
    (*itr)->reset();
  }
}

// Latch the values for all the nodes in a collection
// This does operate recursively
void MonValueCol::latchValue() {
  for ( std::list<MonValue*>::iterator itr = m_vals.begin();
	itr != m_vals.end(); itr++ ) {
    (*itr)->latchValue();
  }
}
