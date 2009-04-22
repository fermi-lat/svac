#ifndef findGaps_Header
#define findGaps_Header
#define EpuNumber 2

#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "digiRootData/DigiEvent.h"

/**
 * \class findGaps
 * \brief finds gaps in the digi data
 * \author M.E.
 */

class findGaps {
 public:
  findGaps();
  ~findGaps();

  void analyzeDigi(const char* digiFileName, const char* gapFileName);

 private:
  TFile* m_digiFile;
  TTree* m_digiTree;
  TBranch* m_digiBranch;
  DigiEvent* m_digiEvent;
};

#endif
