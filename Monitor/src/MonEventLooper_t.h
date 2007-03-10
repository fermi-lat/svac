#ifndef MonEventLooper_h
#define MonEventLooper_h 

//
// stl
#include <iostream>

//
// ROOT IO
#include "TTree.h"
#include "TChain.h"


// 
// 
#include "MonValue_t.h"
#include "MonInputCollection.h"

class MonEventLooper {

public :

  static void printTime(ostream& os, ULong64_t timestamp);

public :
  
  // Standard ctor, where user the number of second per time bin
  MonEventLooper(UInt_t binSize, MonValue* monval, std::vector<MonInputCollection*>, std::string eventcut, std::string timestampvar);
 
// Standard d'tor.  NO-OP.
 virtual ~MonEventLooper(); 


  // do the event loop
  void go(Long64_t numEvents = 0, Long64_t startEvent = 0);

  TTree* tree(){return m_tree;}


  //get the strip val col
  inline MonValue* stripVals() { return m_stripValCol; }

protected:

  // initialize at start of event loop
  virtual void init(); 

  // read in 1 event
  virtual Bool_t readEvent(Long64_t ievent) ;

  // filter event through a global cut
  virtual void filterEvent();


  // go to the next bin, called when the timeStamp is outside the current bin
  void switchBins();
    
  // set the tree
  void attachTree();

  // Set stuff up for the current bin
  void firstEvent(ULong64_t timeStamp);

  // latch the timestamp from one event
  void logEvent(Long64_t ievent, ULong64_t timeStamp);

  // called on the last event
  void lastEvent(ULong64_t timeStamp);
  
private:

  // How many ticks per bin
  UInt_t m_binSize;

  // cached values
  mutable ULong64_t m_timeStamp;
  mutable UInt_t m_currentBin;
  mutable ULong64_t m_currentStart;
  mutable ULong64_t m_currentEnd;
  mutable UInt_t m_currentFlags;

  /// some run-level chached values
  ULong_t m_sec_first;
  ULong_t m_sec_last;

  /// starting event number in chain order
  Long64_t m_startEvent;

  /// Last event to use
  Long64_t m_last;

  /// number of events we ran over
  Long64_t m_nTrigger;
  
  /// number of events that passed the filter
  Long64_t m_nFilter;
  
  /// number of events we used
  Long64_t m_nUsed;
  
  /// The Output Tree. This is passed in by the sub-class using attachTree()
  TTree* m_tree;
  /// The intermediate tree. This is used to evaluate the output 
  TTree* m_intree;

  /// The collection of values we are storing
  MonValue* m_stripValCol;
  std::vector <MonInputCollection*> m_incol;
  std::string m_eventcut;
  std::string m_timestampvar;
  UInt_t *m_currentTimeStamp;

};

#endif
