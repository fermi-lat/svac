#ifndef RunVerify_Header
#define RunVerify_Header
#define MaxEpuNumber 5

#include <fstream>
#include <string>
#include <list>
#include <map>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "digiRootData/DigiEvent.h"
#include <xercesc/util/XercesDefs.hpp>
#include "xercesc/dom/DOMElement.hpp"

/**
 * \class RunVerify
 * \brief RunVerify verification of digi data
 * \author M.E.
 */

using std::list;
using std::string;
using std::vector;
using std::map;
using XERCES_CPP_NAMESPACE_QUALIFIER DOMElement;

class DomElement;

class EvtError{
 friend class RunVerify;
 public:
  EvtError(string errName, int errValue, int epuNumber, int datagramNbr);
  ~EvtError();

 private:
  string m_errName;
  int m_errValue;
  int m_epuNumber;
  int m_datagramNbr;
};

class EpuDatagrams {
 friend class RunVerify;
 public:
  EpuDatagrams(const char* epuName);
  ~EpuDatagrams();

 private:
  string m_epuName;
  int m_counterMissingDatagrams;
  int m_nbrEventsDatagram;
  unsigned int m_firstDatagram;
  unsigned int m_previousDatagram;
  int m_firstOpenAction;
  int m_lastCloseAction;
  int m_lastDatagramFull;
  int m_datagramGaps;
  int m_lastDatagramEvent;
  std::list<int> m_listDatagrams;
};

class RunVerify {
 public:
  RunVerify(const char* histoFileName);
  ~RunVerify();

  int analyzeDigi(const char* digiFileName, bool completeRun);
  
  // write errors to an xml file
  Bool_t writeXmlFile(const char* fileName, bool completeRun, int truncation) const;
  // write xml header
  void writeXmlHeader(DomElement& node, bool completeRun) const;
  // write xml footer
  void writeXmlFooter(DomElement& node) const;
  // write error summary to xml file
  void writeXmlErrorSummary(DomElement& node, int truncation) const;
  // write event summary to xml file
  void writeXmlEventSummary(DomElement& node, int truncation) const;

 private:
  /// root output file
  std::string m_histoFileName;
 
  TFile* m_root;
  TFile* m_digiFile;
  TTree* m_digiTree;
  TBranch* m_digiBranch;
  DigiEvent* m_digiEvent;

  int m_nEvent;
  unsigned int m_latcKey; 
  unsigned long long m_firstGemSequence;
  unsigned long long m_thisGemSequence;
  unsigned long long m_firstGemElapsed;
  unsigned long long m_thisGemElapsed;
  unsigned long long m_firstGemLivetime;
  unsigned long long m_thisGemLivetime;
  unsigned long long m_thisGemPrescaled;
  unsigned long long m_thisGemDiscarded;
  unsigned long long m_thisGemDeadzone;
  unsigned int m_thisGpsCurrent;
  unsigned int m_thisGpsPrevious;
  double m_thisTimeStamp;

  vector<EpuDatagrams> m_epuList;
  map< string, list<int> > m_errMap;
  map< int, list<EvtError*> > m_evtMap;
  // evts/datagram histogram for each EPU
  TH1F* m_datagrams[MaxEpuNumber];
};

#endif
