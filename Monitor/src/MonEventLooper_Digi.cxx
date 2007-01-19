#include "MonEventLooper_Digi.h"

#include "DigiFiller.h"
#include "digiRootData/DigiEvent.h"

#include <cstdio>

DigiDataFiller* myDigiFiller() {
  return new DigiDataFiller("Digi","");
}

MonEventLooper_Digi::MonEventLooper_Digi(TChain* digiChain, UInt_t binSize)
  :MonEventLooper(binSize),
   m_digiChain(digiChain),
   m_digiEvent(0),
   m_digiFiller(0){

  m_digiFiller = myDigiFiller();

  Bool_t ok = attachChains();
  if ( ! ok ) {
    std::cerr << "ERR:  Failed to attach to input chains."  << std::endl;
  }


}


MonEventLooper_Digi::~MonEventLooper_Digi() 
{
  if (m_digiEvent) delete m_digiEvent;
}

void MonEventLooper_Digi::init() {
    
  stripVals().addVal(m_digiFiller->vals());

  TTree* newTree = new TTree("Time","Time binned data");
  attachTree(*newTree);

}

Bool_t MonEventLooper_Digi::attachChains() {
  if (m_digiChain != 0) {
    m_digiEvent = 0;
    m_digiChain->SetBranchAddress("DigiEvent", &m_digiEvent);
    m_digiChain->SetBranchStatus("*",0);  // disable all branches
    // activate desired brances
    m_digiFiller->attachInput(*m_digiChain);
  }
  
  return kTRUE;
}


Bool_t MonEventLooper_Digi::readEvent(Long64_t ievent, Bool_t& filtered, ULong64_t& timeStamp){

  // ok, grab the event
  if(m_digiEvent) m_digiEvent->Clear();

  filtered = kFALSE;
  if(m_digiChain) { 
    m_digiChain->GetEvent(ievent);
    timeStamp = m_digiEvent->getMetaEvent().time().current().timeSecs();
    m_digiFiller->filterEvent(*m_digiEvent,filtered);
  }

  return kTRUE;
}


void MonEventLooper_Digi::useEvent(Bool_t& used) {
  m_digiFiller->useEvent(*m_digiEvent,used);
}

