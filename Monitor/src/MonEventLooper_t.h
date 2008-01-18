#ifndef MonEventLooper_h
#define MonEventLooper_h 

//
// stl
#include <iostream>

//
// ROOT IO
#include "TTree.h"
#include "TChain.h"
#include "TFile.h"

// 
// 
#include "MonValue_t.h"
#include "MonGlobalCut.h"
#include "MonInputCollection.h"
#include "Timestamp.h"

 
class MonEventLooper {

public :

  static void printTime(ostream& os, ULong64_t timestamp);
  static void printTime(ostream& os, Double_t timestamp); 

public :
  
  // Standard ctor, where user the number of second per time bin
  MonEventLooper(UInt_t binSize, MonValue* monval, MonValue* secmonval, std::vector<MonInputCollection*>, MonGlobalCut* eventcut, std::string timestampvar);
 
// Standard d'tor.  NO-OP.
 virtual ~MonEventLooper(); 


  // do the event loop
  void go(Long64_t numEvents = 0, Long64_t startEvent = 0);

  TTree* tree(){return m_tree;}


  //get the strip val col
  inline MonValue* stripVals() { return m_stripValCol; }

  // set whether intermediate tree will be saved to disk,
  // and give directory name where it will be stored.
  void writeintreetodisk(Bool_t write, std::string dir){
    m_intreeToDisk = write; 
    m_sodir = dir;
    //std::cout << "m_intreeToDisk=" << m_intreeToDisk << ";m_sodir=" << m_sodir << std::endl;
  }

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

  // Functions for timeStamp with Double precision
  
   // Set stuff up for the current bin
  void firstEvent(Double_t timeStamp);

  // latch the timestamp from one event
  void logEvent(Long64_t ievent, Double_t timeStamp);

  // called on the last event
  void lastEvent(Double_t timeStamp);

  void createtfile4intree(std::string dir, std::string filename);
  
private:

  // How many ticks per bin
  UInt_t m_binSize;

  // cached values
  // mutable ULong64_t m_timeStamp;
  mutable Double_t m_timeStamp;
  mutable UInt_t m_currentBin;
  mutable ULong64_t m_currentStart;
  mutable ULong64_t m_currentEnd;
  mutable UInt_t m_currentFlags;

  /// some run-level chached values
  Double_t m_sec_first;
  Double_t m_sec_last;
  
  // Time interval and first/last event of bin
  // those quantities are also written into the 
  // output root file
  Double_t m_timeinterval;
  Double_t m_timestamp_firstevt_inbin;
  Double_t m_timestamp_lastevt_inbin;

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

  // counter for event number currently being processed
  ULong64_t m_evtcounter;

  // bool var deciding whether to write (1) or not (0) the intermediate tree to disk.
  // Writing is necessary if info from intermediate tree, for a time bin, is close to 2 GB
  // which gets into 3 GB (limit on a on a IA32 linux for single process) with another 
  // root stuff, producing a SEG FAULT. Therefore, the default for this quantity will be 1. The user can 
  // however set it to zero (from command line) to speed up (25%) the processing speed
  // of those jobs requiring few memory (say less than 1.5 GB).
  Bool_t m_intreeToDisk;

  // TFile to store intermediate tree
  TFile* m_intreefile;
  
  /// The Output Tree. This is passed in by the sub-class using attachTree()
  TTree* m_tree;
  /// The intermediate tree. This is used to evaluate the output 
  TTree* m_intree;

  /// Tree with primary variables as a helper
  TTree* m_sectree;

  /// The collection of values we are storing
  MonValue* m_stripValCol;
  MonValue* m_secstripValCol;
  std::vector <MonInputCollection*> m_incol;
  /// global cut object
  MonGlobalCut* m_globalCut;
  std::string m_timestampvar;
  char m_timestamptype;
  Timestamp *m_currentTimestamp;

  // filename for intermediate tree
  std::string m_intreetfilename;
  // directory where intermediate tree will be stored
  std::string m_sodir;
};

#endif
