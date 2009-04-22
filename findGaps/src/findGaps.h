#ifndef findGaps_Header
#define findGaps_Header
#define MaxEpuNumber 2

#include <fstream>
#include <string>
#include <list>
#include <map>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "digiRootData/DigiEvent.h"

/**
 * \class findGaps
 * \brief finds gaps in the digi data
 * \author M.E.
 */

using std::list;
using std::string;
using std::vector;
using std::map;

class datagramGap {
 friend class findGaps;
 public:
  datagramGap(unsigned int lastDatagramBefore, unsigned int firstDatagramAfter);
  ~datagramGap();

 private:
  unsigned int m_lastDatagramBefore;
  unsigned int m_firstDatagramAfter;
};

class datagram {
 friend class findGaps;
 public:
  datagram(unsigned int firstGemId, unsigned int lastGemId);
  ~datagram();

 private:
  unsigned int m_firstGemId;
  unsigned int m_lastGemId;
};

class EpuDatagrams {
 friend class findGaps;
 public:
  EpuDatagrams(const char* epuName);
  ~EpuDatagrams();

 private:
  string m_epuName;
  unsigned int m_previousDatagram;
  unsigned int m_firstDatagram;
  unsigned int m_previousGemId;
  unsigned int m_firstGemIdDatagram;
  list<unsigned int> m_listDatagrams;
  map<unsigned int, datagram*> m_datagramMap;
  vector<datagramGap> m_datagramGaps;
};

class findGaps {
 public:
  findGaps();
  ~findGaps();

  void analyzeDigi(const char* digiFileName);
  // write errors to a txt file
  void writeGapsFile(const char* fileName);

 private:
  TFile* m_root;
  TFile* m_digiFile;
  TTree* m_digiTree;
  TBranch* m_digiBranch;
  DigiEvent* m_digiEvent;

  unsigned int m_nEvents;
  unsigned int m_runId;
  vector<EpuDatagrams> m_epuList;
};

#endif
