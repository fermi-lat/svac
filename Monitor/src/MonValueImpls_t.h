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
//  TimeInterval  Keeps track of the time interval for the specific time bin.  
//
// Base class
#include "MonValue_t.h"

//
// STL 
#include <map>
#include <list>

// ROOT
#include "Rtypes.h"
#include "TMath.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TVector.h"

//  TimeInterval  Keeps track of the time interval for the specific time bin.  

class TimeInterval{

 public:
  TimeInterval(){}
  //inline void SetInterval(ULong64_t interval){ m_interval = interval;}
  //inline ULong64_t GetInterval() { return m_interval;}
  // static ULong64_t m_interval;
   static Double_t m_interval;
};



//
// 
// This implementation is for a counter that we increment
// either using the ++ or += operators.
class MonCounter : public MonValue {
  
 public:

  // Standard c'tor
  MonCounter(const char* name, const char* formula, const char* cut) ;

  // D'tor, no-op
  virtual ~MonCounter();
  
  // Reset just nulls the values
  virtual void reset() ;

  // Attach this to a TTree
  virtual int attach(TTree& tree, const std::string& prefix) const;

  void singleincrement(Double_t* val, Double_t* val2) ;

  // Just move the counter to the output value
  virtual void latchValue() ;

private:

  // the cached value
  ULong64_t *m_current;

  // the output value
  ULong64_t *m_val;
};



//
// 
// This implementation is for a quantity derived from the contents 
// of the TTree created with the primary list of Mon output quantities (see MonEventLooper_t and runStrip_t)
// Mon Objects (with Double precission) in the secondary list are expected to be of this type.

class MonSecondListDouble : public MonValue {
  
 public:

  // Standard c'tor
  MonSecondListDouble(const char* name, const char* formula, const char* cut) ;

  // D'tor, no-op
  virtual ~MonSecondListDouble();
  
  // Reset just nulls the values
  virtual void reset() ;

  // Attach this to a TTree
  virtual int attach(TTree& tree, const std::string& prefix) const;

  void singleincrement(Double_t* val, Double_t* val2) ;

  // Just move the counter to the output value
  virtual void latchValue() ;

private:

  // the output value
  Double_t *m_val;
};


//
// 
// This implementation is for a quantity derived from the contents 
// of the TTree created with the primary list of Mon output quantities (see MonEventLooper_t and runStrip_t)
// Mon Objects (with Double precission) in the secondary list are expected to be of this type.

class MonSecondListFloat : public MonValue {
  
 public:

  // Standard c'tor
  MonSecondListFloat(const char* name, const char* formula, const char* cut) ;

  // D'tor, no-op
  virtual ~MonSecondListFloat();
  
  // Reset just nulls the values
  virtual void reset() ;

  // Attach this to a TTree
  virtual int attach(TTree& tree, const std::string& prefix) const;

  void singleincrement(Double_t* val, Double_t* val2) ;

  // Just move the counter to the output value
  virtual void latchValue() ;

private:

  // the output value
  Float_t *m_val;
};






//
// 
// This implementation is for computing the rates.
// it is essentially equivalent to MonCounter, normalizing 
// at the end by the timebin (obtained from TimeInterval) and computing 
// the error in the rate. 
// Note that only hte error in counter is considered and not the error 
// in the timebin. 
class MonRate : public MonValue {

public:

  // Standard c'tor
  MonRate(const char* name, const char* formula, const char* cut) ;

  // D'tor, no-op
  virtual ~MonRate();
 
    // Reset just nulls the values
  virtual void reset() ;

  void singleincrement(Double_t* val, Double_t* val2) ;

  // Attach this to a TTree
  virtual int attach(TTree& tree, const std::string& prefix) const;

  // Just move the counter to the output value
  virtual void latchValue() ;


private:

  // the cached value
  ULong64_t *m_current;

  // the output value
  Float_t *m_val;
  Float_t *m_err;
  Double_t m_timebin;
  
};



// 1-d histogram
// If m_fillhistoalways ==0 and vector[index] == m_nofillvalue, then the histogram is not filled.
// If m_fillhistoalways ==1, then histogram is filled with each entry (regardless of the value).


class MonHist1d: public MonValue{
 public:
  /// Standard constructor
  MonHist1d(const char* name, const char* formula, const char* cut, const char* type, const char* axislabels,const char* titlelabel);
  /// Destructor
  virtual ~MonHist1d();
  
  /// Does nothing
  virtual void reset();
  
  /// Attach does nothing
  virtual int attach(TTree& tree, const std::string& prefix) const;

  /// fill histogram
  void singleincrement(Double_t* val, Double_t* val2);
  
  /// Latch does nothing
  virtual void latchValue();
  
 private:
  Bool_t m_fillhistoalways;
  Int_t m_nofillvalue;
  TH1F** m_hist;
};


// 1-d histogram, will loop over vector components filling histo n times
// If m_fillhistoalways ==0 and vector[index] == m_nofillvalue, then the histogram is not filled.
// If m_fillhistoalways ==1, then histogram is filled with each entry (regardless of the value).


class MonHist1d_VecDim: public MonValue{
 public:
  /// Standard constructor
  MonHist1d_VecDim(const char* name, const char* formula, const char* cut, const char* type, const char* axislabels,const char* titlelabel);
  /// Destructor
  virtual ~MonHist1d_VecDim();
  
  /// Does nothing
  virtual void reset();
  
  /// Attach does nothing
  virtual int attach(TTree& tree, const std::string& prefix) const;

  /// fill histogram
  void singleincrement(Double_t* val, Double_t* val2);
  
  /// Latch does nothing
  virtual void latchValue();
  
 private:
  Int_t m_vecdim;
  Bool_t m_fillhistoalways;
  Int_t m_nofillvalue;
  TH1F* m_hist;
};

//
// 2-d histogram
// If m_fillhistoalways ==0 and vector[index] == m_nofillvalue, then the histogram is not filled.
// If m_fillhistoalways ==1, then histogram is filled with each entry (regardless of the value).


class MonHist2d: public MonValue{
 public:
  /// Standard constructor
  MonHist2d(const char* name, const char* formula, const char* cut, const char* type, const char* axislabels,const char* titlelabel);
  /// Destructor
  virtual ~MonHist2d();
  
  /// Does nothing
  virtual void reset();
  
  /// Attach does nothing
  virtual int attach(TTree& tree, const std::string& prefix) const;

  /// fill histogram
  void singleincrement(Double_t* val, Double_t* val2);
  
  /// Latch does nothing
  virtual void latchValue();
  
 private:
  Bool_t m_fillhistoalways;
  Int_t m_nofillvalue;
  TH2F** m_hist;
};


//
// 2-d histogram,  will loop over vector components filling histo n times
// If m_fillhistoalways ==0 and vector[index] == m_nofillvalue, then the histogram is not filled.
// If m_fillhistoalways ==1, then histogram is filled with each entry (regardless of the value).


class MonHist2d_VecDim: public MonValue{
 public:
  /// Standard constructor
  MonHist2d_VecDim(const char* name, const char* formula, const char* cut, const char* type, const char* axislabels,const char* titlelabel);
  /// Destructor
  virtual ~MonHist2d_VecDim();
  
  /// Does nothing
  virtual void reset();
  
  /// Attach does nothing
  virtual int attach(TTree& tree, const std::string& prefix) const;

  /// fill histogram
  void singleincrement(Double_t* val, Double_t* val2);
  
  /// Latch does nothing
  virtual void latchValue();
  
 private:
  Int_t m_vecdim[2];
  Bool_t m_fillhistoalways;
  Int_t m_nofillvalue;
  TH2F* m_hist;
};


//
// 2-d histogram,  where indeces are specified in xml file. 
// the function singleincrement will loop, using these indices [0-maxindex) 
// over a vector and will fill maxindex times the histogram with 
// a one dimensional vector (h->Fill(index,vector[index]))
// If m_fillhistoalways ==0 and vector[index] == m_nofillvalue, then the histogram is not filled.
// If m_fillhistoalways ==1, then histogram is filled with each entry (regardless of the value).

class MonHist2d_Index: public MonValue{
 public:
  /// Standard constructor
  MonHist2d_Index(const char* name, const char* formula, const char* cut, const char* type, const char* axislabels,const char* titlelabel);
  /// Destructor
  virtual ~MonHist2d_Index();
  
  /// Does nothing
  virtual void reset();
  
  /// Attach does nothing
  virtual int attach(TTree& tree, const std::string& prefix) const;

  /// fill histogram
  void singleincrement(Double_t* val, Double_t* val2);
  
  /// Latch does nothing
  virtual void latchValue();
  
 private:
  UInt_t m_maxindex;
  Bool_t m_fillhistoalways;
  Int_t m_nofillvalue;
  TH2F* m_hist;
};



//
// 
// This implementation takes the average of several values
// using running sums of n, v and v2
class MonMean : public MonValue {

public:
  
  // Standard c'tor
  MonMean(const char* name, const char* formula, const char* cut) ;
  
  // D'tor
  virtual ~MonMean();

  // Latch the values, so calculate mean, rms, err_on_mean
  virtual void latchValue() ;

  // reset, null everything
  virtual void reset() ;

  // attach both mean and err_on_mean to TTree
  virtual int attach(TTree& tree, const std::string& prefix) const;
  virtual void singleincrement(Double_t* val, Double_t* val2) ;

protected:

  // cached values, the running sums
  ULong64_t *m_nVals;
  Double_t *m_sum;
  Double_t *m_sum2;

  // output values
  Float_t *m_val;
  Float_t *m_err;

  
};

class MonTruncatedMean:public MonMean{
  
 public:
  MonTruncatedMean(const char* name, const char* formula, const char* cut, const char* type) ;
  virtual ~MonTruncatedMean(){}
  void singleincrement(Double_t* val, Double_t* val2) ;
 private:
  Float_t m_lowerbound;
  Float_t m_upperbound;
  
};
class MonTruncatedMeanFrac:public MonMean{
  
 public:
  MonTruncatedMeanFrac(const char* name, const char* formula, const char* cut, const char* type) ;
  virtual ~MonTruncatedMeanFrac();
  void singleincrement(Double_t* val, Double_t* val2) ;
  void reset();
  virtual void latchValue() ;
 private:
  Float_t m_fraction;
  std::list<double> *m_list;
  
};

class MonTruncatedMeanBoundsAndFrac:public MonMean{
 public:
  MonTruncatedMeanBoundsAndFrac(const char* name, const char* formula, const char* cut, const char* type) ;
  virtual ~MonTruncatedMeanBoundsAndFrac();
  void singleincrement(Double_t* val, Double_t* val2) ;
  void reset();
  virtual void latchValue() ;
 private:
  Float_t m_lowerbound;
  Float_t m_upperbound;
  Float_t m_fraction;
  std::list<double> *m_list;
};

class MonTruncatedMeanBoundsAndFracBigData:public MonMean{
 public:
  MonTruncatedMeanBoundsAndFracBigData(const char* name, const char* formula, const char* cut, const char* type) ;
  virtual ~MonTruncatedMeanBoundsAndFracBigData();
  void singleincrement(Double_t* val, Double_t* val2) ;
  void reset();
  virtual void latchValue() ;
  // private:

  Bool_t createfile4tmptree(std::string dir, std::string filename);

  Float_t m_lowerbound;
  Float_t m_upperbound;
  std::string m_lowerbound_str;
  std::string m_upperbound_str;
  Float_t m_fraction;
  Double_t* m_datavector;
  std::string m_tmpdir;
  std::string m_tmpfilename;
  TFile* m_tmpfile;
  TTree* m_tmptree;
  //  TDirectory* m_filedir;
  //  TDirectory* m_memorydir;
  std::string m_tmptreename;
  std::vector<std::string> m_leafname;
  ULong64_t m_evtcounter;
};


class MonTruncatedMeanBoundsAndFracBigDataEqualNEvents:public MonTruncatedMeanBoundsAndFracBigData{
 public:
  MonTruncatedMeanBoundsAndFracBigDataEqualNEvents(const char* name, const char* formula, const char* cut, const char* type);
  //virtual ~MonTruncatedMeanBoundsAndFracBigDataEqualNEvents();
  void singleincrement(Double_t* val, Double_t* val2) ;
  // virtual void latchValue() ;
};

//
// 
//
// 
// This implementation takes the difference between the 
// first and last values of a counter
class MonCounterDiff  : public MonValue {

public:
  // Standard c'tor
  MonCounterDiff(const char* name, const char* formula, const char* cut) ;

  // D'tor, no-op
  virtual ~MonCounterDiff();
  
  // Reset, check to see if the cache makes sense
  // if so, just copy hi -> lo and go on
  // in not, reset both hi and lo
  virtual void reset() ;

  // Attach this to a TTree
  virtual int attach(TTree& tree, const std::string& prefix) const;
  void singleincrement(Double_t* val, Double_t* val2) ;

  // Take the difference hi-lo and move it to the output value
  virtual void latchValue() ;

  static const ULong64_t s_maxVal64;
private:
  
  // cached values, lo and hi values from current time slice
  ULong64_t *m_lo;
  ULong64_t *m_hi;

  // output value
  ULong64_t *m_val;
};


//
// 
//
// 
// This implementation takes the difference between the 
// first and last values of a counter
class MonCounterDiffRate  : public MonValue {

public:
  // Standard c'tor
  MonCounterDiffRate(const char* name, const char* formula, const char* cut, const char* type) ;

  // D'tor, no-op
  virtual ~MonCounterDiffRate();
  
  // Reset, check to see if the cache makes sense
  // if so, just copy hi -> lo and go on
  // in not, reset both hi and lo
  virtual void reset() ;

  // Attach this to a TTree
  virtual int attach(TTree& tree, const std::string& prefix) const;
  void singleincrement(Double_t* val, Double_t* val2) ;

  // Take the difference hi-lo and move it to the output value
  virtual void latchValue() ;


private:
  
  // cached values, lo and hi values from current time slice
  ULong64_t *m_lo;
  ULong64_t *m_hi;

  // Quantities that will be used only with MC data and sequence param
  // START
  ULong64_t *m_hi_previous; 
  ULong64_t *m_offset; 
  UInt_t m_jumpcounter;
  
  UInt_t m_jumpid; // value used to identify a jump in the quantity
  UShort_t m_jumpmagbit;// num bits determining the jump magnitude: jump = pow(2,m_jumpmagbit)
  std::string m_dataparamtype; // string identifying the data parameter type. 
  // Actions will be taken depending on this value
  // END


   // the output value
  Float_t *m_val;
  Float_t *m_err;
  Double_t m_timebin;


};


//
// 
//
// 
// This implementation takes the difference between the 
// first and last values of a double
class MonDoubleDiffRate  : public MonValue {

public:
  // Standard c'tor
  MonDoubleDiffRate(const char* name, const char* formula, const char* cut, const char* type) ;

  // D'tor, no-op
  virtual ~MonDoubleDiffRate();
  
  // Reset, check to see if the cache makes sense
  // if so, just copy hi -> lo and go on
  // in not, reset both hi and lo
  virtual void reset() ;

  // Attach this to a TTree
  virtual int attach(TTree& tree, const std::string& prefix) const;
  void singleincrement(Double_t* val, Double_t* val2) ;

  // Take the difference hi-lo and move it to the output value
  virtual void latchValue() ;

private:

 // cached values, lo and hi values from current time slice
  ULong64_t *m_lo;
  ULong64_t *m_hi;
  Float_t m_convertTicksToTime;
  Float_t m_convertToPercent;
  std::string m_dataparamtype; // string identifying the data parameter type.

  // the output value
  Double_t *m_val;
  //Float_t *m_err;
  Double_t m_timebin;
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
  MonMinMax(const char* name, const char* formula, const char* cut) ;

  // D'tor, no-op
  virtual ~MonMinMax();
  
  // Reset, check to see if the cache makes sense
  // if so, just copy hi -> lo and go on
  // in not, reset both hi and lo
  virtual void reset() ;

  // Attach this to a TTree
  virtual int attach(TTree& tree, const std::string& prefix) const;
  void singleincrement(Double_t* val, Double_t* val2) ;

  // reset values;
  virtual void latchValue();


private:
  
  // lo and hi values from current time slice
  Float_t *m_min;
  Float_t *m_max;
};
//
// 
// This implementation traces the changes of a value
class MonValueChange  : public MonValue {

  

public:
  // Standard c'tor, just the name
  MonValueChange(const char* name, const char* formula, const char* cut,const char* numval) ;

  // D'tor, no-op
  virtual ~MonValueChange();
  
  // Reset, check to see if the cache makes sense
  // if so, just copy hi -> lo and go on
  // in not, reset both hi and lo
  virtual void reset() ;

  // Attach this to a TTree
  virtual int attach(TTree& tree, const std::string& prefix) const;
  void singleincrement(Double_t* val, Double_t* val2) ;

  // Take the difference hi-lo and move it to the output value
  virtual void latchValue() ;


private:
  
  // lo and hi values from current time slice
  Double_t *m_firstval;
  Double_t *m_lastval;
  UInt_t *m_nvalues;
  Bool_t *m_startrun;
  Double_t **m_values;
  Double_t **m_times;
  UInt_t m_numval;
};

//
// 
// This implementation just allows recursively defining 
// collections of MonValues
class MonValueCol : public MonValue {

public:
  // Standard c'tor, just the name and a prefix
  MonValueCol(const char* name, const char* prefix)
    :MonValue(name,"",""),m_prefix(prefix){
  }
  
  // D'tor, deletes the MonValues it contains. 
  virtual ~MonValueCol();

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

  // Increment all sub-nodes
  void increment(TTree* tree);
  // Make proxies for all subnodes
  void makeProxy(TTree* tree);
  // do time profiling
  float timeProfile();
  // set shared lib directory
  void setSharedLibDir(std::string);
  // set no-compile flag 
  void setDontCompile(bool);
  // set the IsMC flag
  void setDataType(std::string);

private:

  // The prefix for sub-nodes
  std::string m_prefix;

  // Just a list of the sub-nodes
  std::list<MonValue*> m_vals;  

  // A map from name -> sub-node
  std::map<std::string,MonValue*> m_nameMap;

};

class MonValFactory{
 public:
  MonValFactory(){}
  MonValue* makeMonValue(std::map<std::string,std::string>);
  MonValueCol* makeMonValueCol(std::list<std::map<std::string,std::string> >, const char*, const char* ="");
};




#endif
