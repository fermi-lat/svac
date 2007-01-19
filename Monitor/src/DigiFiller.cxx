#include "DigiFiller.h"

#include "TTree.h"
#include "digiRootData/DigiEvent.h"

DigiDataFiller::DigiDataFiller(const char* name, const char* prefix) 
  :MonDataFiller(name,prefix),
   m_nAcd("Acd_nDigi"),
   m_elapsed("Gem_elapsed"),
   m_livetime("Gem_livetime"){
  
  // stuff for output
  vals().addVal(m_nAcd);
  vals().addVal(m_elapsed);
  vals().addVal(m_livetime);

  // stuff for input
  addBranchToRead("m_acd*");
  addBranchToRead("m_eventId"); 
  addBranchToRead("m_runId");
  addBranchToRead("m_gem");
  addBranchToRead("m_metaEvent");
}

void DigiDataFiller::useEvent(DigiEvent& event, Bool_t& used) {
  Int_t nAcdDigi = event.getAcdDigiCol()->GetEntries();
  if ( nAcdDigi > 100 ) {
    return;
  }
  used = kTRUE;
  m_nAcd += (Float_t)(nAcdDigi);
  m_elapsed += event.getMetaEvent().scalers().elapsed();
  m_livetime += event.getMetaEvent().scalers().livetime();
}
