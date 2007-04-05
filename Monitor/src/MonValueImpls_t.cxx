// Header file
#include "MonValueImpls_t.h"

// To attach to trees
#include "TTree.h"

#include <iostream>

const ULong64_t MonCounterDiff::s_maxVal64(0xFFFFFFFFFFFFFFFF);
const Float_t MonMinMax::s_huge(1e35);

// Standard c'tor
MonCounter::MonCounter(const char* name, const char* formula, const char* cut) 
    :MonValue(name,formula,cut){
    m_current = new ULong64_t[m_dim];
    m_val = new ULong64_t[m_dim];
    reset();
  }

  // D'tor, no-op
MonCounter::~MonCounter(){
    delete [] m_current;
    delete [] m_val;
  }
  
  // Reset just nulls the values
void MonCounter::reset() {
    for (unsigned i=0;i<m_dim;i++){
      m_current[i] = 0;
      m_val[i] = 0;
    }
  }
void MonCounter::latchValue() {
    for (unsigned i=0;i<m_dim;i++){
      m_val[i] = m_current[i];
    }
  }

// Attach a MonCounter node to a TTree (unsigned int)
int MonCounter::attach(TTree& tree, const std::string& prefix) const {
  std::string fullName = prefix + name();
  std::string leafType = fullName + m_dimstring + "/l";
  TBranch* b = tree.Branch(fullName.c_str(),m_val,leafType.c_str());
  return b != 0 ? 1 : -1;
}
  // += addition operator
void MonCounter::singleincrement(Double_t* val) {
  for (unsigned i=0;i<m_dim;i++){
    m_current[i] += (ULong64_t)val[i];
  }
}

MonMean::MonMean(const char* name, const char* formula, const char* cut) 
    :MonValue(name,formula,cut),
     m_nVals(0),m_sum(0),m_sum2(0),
     m_val(0),m_err(0){
    m_nVals=new ULong64_t[m_dim];
    m_sum=new Double_t[m_dim];
    m_sum2=new Double_t[m_dim];
    m_val=new Float_t[m_dim];
    m_err=new Float_t[m_dim];
    reset();
  }
  
  // D'tor
MonMean::~MonMean(){
    delete [] m_nVals;
    delete [] m_sum;
    delete [] m_sum2;
    delete [] m_val;
    delete [] m_err;
  }

  // Latch the values, so calculate mean, rms, err_on_mean
void MonMean::latchValue() {
    for (unsigned i=0;i<m_dim;i++){
      if ( m_nVals[i] < 1 ) continue;
      m_val[i] = m_sum[i] / ((Double_t)m_nVals[i]);
      Double_t err2 = m_sum2[i];
      err2 /= ((Double_t)m_nVals[i]);
      err2 -= m_val[i]*m_val[i];    
      err2 /= ((Double_t)m_nVals[i]);
      m_err[i] = err2 > 0 ? TMath::Sqrt(err2) : 0.;
    }
  }

  // reset, null everything
void MonMean::reset() {
    for (unsigned i=0;i<m_dim;i++){
      m_err[i] = 0.;
      m_val[i] = 0.;
      m_nVals[i] = 0;
      m_sum[i] = 0.;
      m_sum2[i] = 0.;
    }
  }

// Attach a MonMean node to a TTree (mean and err as float)
int MonMean::attach(TTree& tree, const std::string& prefix) const {
  std::string fullNameVal = prefix + name();
  std::string leafTypeVal = fullNameVal + m_dimstring + "/F";
  TBranch* b = tree.Branch(fullNameVal.c_str(),m_val,leafTypeVal.c_str());
  if ( b == 0 ) return -1;
  std::string fullNameErr = fullNameVal + "_err";
  std::string leafTypeErr = fullNameErr + m_dimstring + "/F";
  TBranch* bErr = tree.Branch(fullNameErr.c_str(),m_err,leafTypeErr.c_str());
  return bErr != 0 ? 2 : -1;
}
  // add a value input the mean, so add to running sums
void MonMean::singleincrement(Double_t* val) {
  for (unsigned i =0;i<m_dim;i++){
    m_nVals[i]++;
    m_sum[i] += val[i];
    m_sum2[i] += (val[i]*val[i]);    
  }
}


MonCounterDiff::MonCounterDiff(const char* name, const char* formula, const char* cut) 
    :MonValue(name,formula, cut){
  m_lo=new ULong64_t[m_dim];
  m_hi=new ULong64_t[m_dim];
  m_val=new ULong64_t[m_dim];
  reset();
}

  // D'tor, no-op
MonCounterDiff::~MonCounterDiff(){
  delete [] m_lo;
  delete [] m_hi;
  delete [] m_val;
}
  
  // Reset, check to see if the cache makes sense
  // if so, just copy hi -> lo and go on
  // in not, reset both hi and lo
void MonCounterDiff::reset() {
  for (unsigned i=0;i<m_dim;i++){
    m_lo[i] = m_lo[i] >= m_hi[i] ? s_maxVal64 : m_hi[i];
    m_hi[i] = m_lo[i] >= m_hi[i] ? 0 : m_hi[i];
    m_val[i] = 0;
  }
}

  // Take the difference hi-lo and move it to the output value
void MonCounterDiff::latchValue() {
  for (unsigned i=0;i<m_dim;i++){
    m_val[i] = m_lo[i] < m_hi[i] ? m_hi[i] - m_lo[i] : 0;
  }
}

// Attach a MonCounterDif node to a TTree (unsigned int)
int MonCounterDiff::attach(TTree& tree, const std::string& prefix) const {
  std::string fullName = prefix + name();
  std::string leafType = fullName + m_dimstring+"/l";
  TBranch* b = tree.Branch(fullName.c_str(),m_val,leafType.c_str());
  return b != 0 ? 1 : -1;

}

  // Update the value, check to make sure that things make sense
void MonCounterDiff::singleincrement(Double_t* val) {
  for (unsigned i=0;i<m_dim;i++){
    if ( m_lo[i] == s_maxVal64 ) {
      m_lo[i] = (ULong64_t)val[i];
    }
    if ( val[i] > m_hi[i] ) {
      m_hi[i] = (ULong64_t)val[i];
    }
  }
}

// Attach a MonMinMax node to a TTree (unsigned int)
int MonMinMax::attach(TTree& tree, const std::string& prefix) const {
  std::string fullNameMin = prefix + name();
  fullNameMin += "_min";
  std::string leafTypeMin = fullNameMin+m_dimstring + "/F";
  std::string fullNameMax = prefix + name();
  fullNameMax += "_max";
  std::string leafTypeMax = fullNameMax +m_dimstring+ "/F";
  TBranch* b = tree.Branch(fullNameMin.c_str(),m_min,leafTypeMin.c_str());
  if ( b == 0 ) return -1;
  b = tree.Branch(fullNameMin.c_str(),m_max,leafTypeMax.c_str());
  return b != 0 ? 2 : -1;
}

MonMinMax::MonMinMax(const char* name, const char* formula, const char* cut) 
    :MonValue(name,formula,cut){
  m_min=new Float_t[m_dim];
  m_max=new Float_t[m_dim];
  reset();
}

  // D'tor
MonMinMax::~MonMinMax(){
  delete [] m_min;
  delete [] m_max;
}
  
  // Reset, check to see if the cache makes sense
  // if so, just copy hi -> lo and go on
  // in not, reset both hi and lo
void MonMinMax::reset() {
  for (unsigned i=0;i<m_dim;i++){
    m_min[i] = s_huge;
    m_max[i] = -s_huge;
  }
}
  // Update the value, check to make sure that things make sense
void MonMinMax::singleincrement(Double_t* val) {
  for (unsigned i=0;i<m_dim;i++){
    m_min[i] = m_min[i] < (Float_t)val[i] ? m_min[i] : (Float_t)val[i];
    m_max[i] = m_max[i] > (Float_t)val[i] ? m_max[i] : (Float_t)val[i];
  }
}



// Destructor for MonValueCol;

MonValueCol::~MonValueCol(){
  for ( std::list<MonValue*>::iterator itr = m_vals.begin();
	itr != m_vals.end(); itr++ ) {
    delete (*itr);
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

void MonValueCol::makeProxy(TTree* tree){
  for ( std::list<MonValue*>::iterator itr = m_vals.begin();
	itr != m_vals.end(); itr++ ) {
    (*itr)->makeProxy(tree);
  }
}


MonValue* MonValFactory::makeMonValue(std::map<std::string,std::string> obj){
  std::string type=obj["type"];
  std::string name=obj["name"];
  std::string formula=obj["formula"];
  std::string cut=obj["cut"];
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


MonValueCol* MonValFactory::makeMonValueCol(std::list<std::map<std::string,std::string> > monlist, const char* name,  const char* prefix){
  MonValueCol* newcol=new MonValueCol(name,prefix);
  for ( std::list<std::map<std::string,std::string> >::iterator itr = monlist.begin(); itr != monlist.end(); itr++ ) { 
    newcol->addVal(*makeMonValue(*itr));
  }
  return newcol;
}
