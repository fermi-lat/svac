#ifndef MonEventLooper_Digi_h
#define MonEventLooper_Digi_h 

#include "MonEventLooper.h"

#include "TChain.h"

class DigiEvent;
class DigiDataFiller;

class MonEventLooper_Digi : public MonEventLooper {

public :
  
  // Standard ctor, where user provides the names of the input root files
  // and optionally the name of the output ROOT histogram file
  MonEventLooper_Digi(TChain* digiChain, UInt_t binSize);
  
  virtual ~MonEventLooper_Digi();  

protected:

  virtual Bool_t attachChains();

  // 
  // return the total number of events in the chains
  virtual Long64_t getTotalEvents() const { 
    if ( m_digiChain != 0 ) { return m_digiChain->GetEntries(); }
    return 0;
  } 

  // initialize at start of event loop
  virtual void init();


  // read in 1 event
  virtual Bool_t readEvent(Long64_t ievent, Bool_t& filtered, ULong64_t& timeStamp);
			   

  // actually get values and stuff like that
  virtual void useEvent(Bool_t& used);

private:

  /// TChain input
  TChain      *m_digiChain;

  /// pointer to a ReconEvent
  DigiEvent* m_digiEvent;

  /// The DataFiller for digis
  DigiDataFiller* m_digiFiller;
  
};

#endif
