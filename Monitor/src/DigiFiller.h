#ifndef DigiFiller_h
#define DigiFiller_h 

#include "MonDataFiller.h"

class TTree;
class DigiEvent;

class DigiDataFiller : public MonDataFiller { 
public:
  DigiDataFiller(const char* name, const char* prefix);
  virtual ~DigiDataFiller() {;}

  virtual void filterEvent(DigiEvent& /* event */, Bool_t& /* filtered */) { return; }

  virtual void useEvent(DigiEvent& event, Bool_t& used);
private:
  MonMean m_nAcd;
  MonCounterDiff m_elapsed;
  MonCounterDiff m_livetime;
};

#endif
