// Header file
#include "MonValueImpls_t.h"

// To attach to trees
#include "TTree.h"

#include <iostream>

const ULong64_t MonCounterDiff::s_maxVal64(0xFFFFFFFFFFFFFFFF);
const Float_t MonMinMax::s_huge(1e35);

// Attach a MonCounter node to a TTree (unsigned int)
int MonCounter::attach(TTree& tree, const std::string& prefix) const {
  std::string fullName = prefix + name();
  std::string leafType = fullName + "/l";
  TBranch* b = tree.Branch(fullName.c_str(),(void*)(&m_val),leafType.c_str());
  return b != 0 ? 1 : -1;
}
  // += addition operator
void MonCounter::increment(TTree* tree) {
  std::vector<std::string> result=queryTree(tree);
  for (std::vector<std::string>::iterator it=result.begin();it!=result.end();it++){
    ULong64_t val= strtoull((*it).c_str(),0,10);
    m_current += val;
  }
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
  // add a value input the mean, so add to running sums
void MonMean::increment(TTree* tree) {
  std::vector<std::string> result=queryTree(tree);
  for (std::vector<std::string>::iterator it=result.begin();it!=result.end();it++){
    float val= atof((*it).c_str());
    m_nVals++;
    m_sum += val;
    m_sum2 += (val*val);    
  }
}

// Attach a MonCounterDif node to a TTree (unsigned int)
int MonCounterDiff::attach(TTree& tree, const std::string& prefix) const {
  std::string fullName = prefix + name();
  std::string leafType = fullName + "/l";
  TBranch* b = tree.Branch(fullName.c_str(),(void*)(&m_val),leafType.c_str());
  return b != 0 ? 1 : -1;

}

  // Update the value, check to make sure that things make sense
void MonCounterDiff::increment(TTree* tree) {
  std::vector<std::string> result=queryTree(tree);
  for (std::vector<std::string>::iterator it=result.begin();it!=result.end();it++){
    ULong64_t val= strtoull((*it).c_str(),0,10);
    if ( m_lo == s_maxVal64 ) {
      m_lo = val;
    }
    if ( val > m_hi ) {
      m_hi = val;
    }
  }
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
  // Update the value, check to make sure that things make sense
void MonMinMax::increment(TTree* tree) {
  std::vector<std::string> result=queryTree(tree);
  for (std::vector<std::string>::iterator it=result.begin();it!=result.end();it++){
    ULong64_t val= strtoull((*it).c_str(),0,10);
    m_min = m_min < val ? m_min : val;
    m_max = m_max > val ? m_max : val;
  }
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

// Increment the values for all the nodes in a collection
// This does operate recursively
void MonValueCol::increment(TTree* tree) {
  for ( std::list<MonValue*>::iterator itr = m_vals.begin();
	itr != m_vals.end(); itr++ ) {
    (*itr)->increment(tree);
  }
}

MonValue* MonValFactory::makeMonValue(std::map<std::string,std::string> obj, const char* eventcut){
  std::string type=obj["type"];
  std::string name=obj["name"];
  std::string formula=obj["formula"];
  std::string cut=obj["cut"];
  std::string evc=eventcut;
  if (evc!=""){
    cut+=" && ";
    cut+=evc;
  }
  if (type=="mean"){
    return new MonMean(name.c_str(),formula.c_str(),cut.c_str());
  } else if (type=="counter"){
    return new MonCounter(name.c_str(),formula.c_str(),cut.c_str());
  } else if (type=="minmax"){
    return new MonMinMax(name.c_str(),formula.c_str(),cut.c_str());
  } else if (type=="counterdiff"){
    return new MonCounterDiff(name.c_str(),formula.c_str(),cut.c_str());
  }else{
    std::cerr<<"No such type "<<type<<std::endl;
    assert(0);
  }
}


MonValueCol* MonValFactory::makeMonValueCol(std::list<std::map<std::string,std::string> > monlist, const char* name, const char* eventcut, const char* prefix){
  MonValueCol* newcol=new MonValueCol(name,prefix);
  for ( std::list<std::map<std::string,std::string> >::iterator itr = monlist.begin(); itr != monlist.end(); itr++ ) { 
    newcol->addVal(*makeMonValue((*itr),eventcut));
  }
  return newcol;
}
    
