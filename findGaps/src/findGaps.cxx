#include <iostream>
#include <cstdio>
#include <string>
#include <stdexcept>
#include <iterator>
#include <list>
#include <algorithm>
#include <fstream>

#include "TROOT.h"
#include "findGaps.h"
#include "TSystem.h"

using std::cout;
using std::endl;
using std::string;
using std::list;
using std::vector;

findGaps::findGaps()
  : m_digiFile(0),
    m_digiTree(0),
    m_digiBranch(0),
    m_digiEvent(0),
    m_nEvents(0),
    m_runId(0)
{ 
  // initialize ROOT
  if(gROOT == 0) {
    static TROOT g_root("report", "report");
  }
  gROOT->SetBatch();  // initialize ROOT
  m_epuList.clear();

  for (unsigned int i=0; i< MaxEpuNumber; i++){
    char e_name[5];
    if(i==enums::Lsf::Epu0) sprintf(e_name,"Epu0");
    if(i==enums::Lsf::Epu1) sprintf(e_name,"Epu1");
    //if(i==enums::Lsf::Epu2) sprintf(e_name,"Epu2");
    EpuDatagrams* epu_d = new EpuDatagrams(e_name);
    m_epuList.push_back(*epu_d);
    string ptr("datagrams");
    ptr += m_epuList.at(i).m_epuName;
  }
}

findGaps::~findGaps()
{
  delete m_digiFile;
  m_epuList.clear();
}

datagram::datagram(unsigned int firstGemId, unsigned int lastGemId)
  : m_firstGemId(firstGemId),
    m_lastGemId(lastGemId)
{
}

datagramGap::datagramGap(unsigned int lastDatagramBefore, unsigned int firstDatagramAfter)
  : m_lastDatagramBefore(lastDatagramBefore),
    m_firstDatagramAfter(firstDatagramAfter)
{
}

datagramGap::~datagramGap() {
}

EpuDatagrams::EpuDatagrams(const char* epuName)
  : m_epuName(epuName),
    m_previousDatagram(0),
    m_firstDatagram(0),
    m_previousGemId(0),
    m_firstGemIdDatagram(0)
{
}

EpuDatagrams::~EpuDatagrams() {
  m_listDatagrams.clear();
  m_datagramMap.clear();
  m_datagramGaps.clear();
}

void findGaps::analyzeDigi(const char* digiFileName="digi.root")
{
  unsigned int nDigi = 0;
  unsigned int atLeastOneEvt[MaxEpuNumber];
  unsigned int idDatagram[MaxEpuNumber];
  std::string errorName;

  //open digi file
  if(digiFileName) m_digiFile = new TFile(digiFileName, "READ");
  if(m_digiFile && m_digiFile->IsZombie()) m_digiFile = 0;
  if(m_digiFile) {
    m_digiTree = (TTree*) m_digiFile->Get("Digi");
    m_digiEvent = 0;
    m_digiBranch = m_digiTree->GetBranch("DigiEvent");
    m_digiBranch->SetAddress(&m_digiEvent);
    m_digiTree->SetBranchStatus("*",0);
    m_digiTree->SetBranchStatus("m_eventId",1);
    m_digiTree->SetBranchStatus("m_metaEvent",1);
  } else {
    cout << "ERROR: no digi file " << digiFileName << "opened!" << endl;
    return;
  }
  
  // Make sure we have events in the digi file:
  nDigi = (unsigned int) m_digiTree->GetEntries();
  cout << "Number of events in " << digiFileName << " : " << nDigi << endl;
  m_nEvents = nDigi;
  if(nDigi < 1){
    cout << "ERROR: no events in digi file " << digiFileName << endl;
    return;
  }
 
  for (unsigned int iLoop = 0; iLoop < MaxEpuNumber; ++iLoop) {
    idDatagram[iLoop]    = 0;
    atLeastOneEvt[iLoop] = 0;
  }

  // Loop over events:
  //for(unsigned int iEvent = 0; iEvent != m_nEvents; ++iEvent) {
  for(unsigned int iEvent = 10000; iEvent != 90000; ++iEvent) {

    if (iEvent % 10000 == 0) {
      cout << "Event number " << iEvent << endl;
    }
    // Cleanup:
    if (m_digiEvent)  m_digiEvent->Clear();
    // Analyze digi file:
    m_digiBranch->GetEntry(iEvent);
    unsigned int cpuNbr = m_digiEvent->getMetaEvent().datagram().crate();
    unsigned int DatagramSeqNbr = m_digiEvent->getMetaEvent().datagram().datagrams();
    unsigned int tmpGemId = m_digiEvent->getEventId();

    // Here I make a list of the datagrams and feel the datagram Structures
    // First event in first datagram?
    if (atLeastOneEvt[cpuNbr] == 0) {
      m_epuList[cpuNbr].m_firstGemIdDatagram = tmpGemId;
      m_epuList[cpuNbr].m_firstDatagram = DatagramSeqNbr;
      m_runId =  m_digiEvent->getMetaEvent().run().startTime();
      atLeastOneEvt[cpuNbr] = 1;
    }
    if (atLeastOneEvt[cpuNbr] == 1) {
       // push back to DataGram list, if not already there! 
       if (DatagramSeqNbr != m_epuList[cpuNbr].m_previousDatagram && DatagramSeqNbr !=  m_epuList[cpuNbr].m_firstDatagram) {
         m_epuList[cpuNbr].m_listDatagrams.push_back(m_epuList[cpuNbr].m_previousDatagram);
         datagram* dgr = new datagram(m_epuList[cpuNbr].m_firstGemIdDatagram,m_epuList[cpuNbr].m_previousGemId);
         m_epuList[cpuNbr].m_datagramMap[m_epuList[cpuNbr].m_previousDatagram] = dgr;
	 m_epuList[cpuNbr].m_firstGemIdDatagram = tmpGemId;
       }
    }
    // At the last event, we add the last datagram for each epu to the list 
    if (iEvent == m_nEvents-1){
      for (unsigned int iLoop = 0; iLoop < MaxEpuNumber; iLoop ++) {
        if (atLeastOneEvt[iLoop] == 1) {
          m_epuList[cpuNbr].m_listDatagrams.push_back(m_epuList[cpuNbr].m_previousDatagram);
          datagram* dgr = new datagram(m_epuList[cpuNbr].m_firstGemIdDatagram,m_epuList[cpuNbr].m_previousGemId);
          m_epuList[cpuNbr].m_datagramMap[m_epuList[cpuNbr].m_previousDatagram] = dgr;
        }
      }
    }
    // Keep datagram sequence number and other infos for previous event
    m_epuList[cpuNbr].m_previousDatagram = DatagramSeqNbr;
    m_epuList[cpuNbr].m_previousGemId = tmpGemId;
    m_digiEvent->Clear();
  }

  // Loop over crates to find gaps
  for (unsigned int iLoop = 0; iLoop < MaxEpuNumber; iLoop ++) {
    if (atLeastOneEvt[iLoop] == 1) {
      // Get rid of duplicates:
      m_epuList[iLoop].m_listDatagrams.sort();
      m_epuList[iLoop].m_listDatagrams.unique();
      std::list<unsigned int>::iterator p;
      unsigned int previousDatagram = 0;
      for (p = m_epuList[iLoop].m_listDatagrams.begin(); p != m_epuList[iLoop].m_listDatagrams.end(); p++) {       
        //cout << "Datagram id: " << *p << ", Epu: " << iLoop << endl;
        if (p != m_epuList[iLoop].m_listDatagrams.begin()) {
          unsigned int diff = *p - previousDatagram;
          if (diff > 1) {
	    datagramGap* dGap = new datagramGap(previousDatagram,*p);
	    m_epuList[iLoop].m_datagramGaps.push_back(*dGap);
     	    cout << "Datagram Gap from " << previousDatagram << " to " << (*p) << " for " << m_epuList[iLoop].m_epuName << endl;
	  }
	}
        previousDatagram = *p;	
      }
    }
  }

  // Closing time:  
  if(m_digiFile) m_digiFile->Close();
}

void findGaps::writeGapsFile(const char* fileName) {
  if (m_epuList[0].m_datagramGaps.size() != m_epuList[0].m_datagramGaps.size()){
    cout << "FATAL! number of gaps is different for the 2 EPU streams!!!" << endl; 
    exit(1);
  }
  ofstream ofile;
  ofile.open(fileName);
  // Loop over the gaps to merge them
  if (m_epuList[0].m_datagramGaps.size() > 0) {
    unsigned int gapStartEvt0, gapEndEvt0, gapStartEvt1, gapEndEvt1;
    for (unsigned int iGap = 0; iGap != m_epuList[0].m_datagramGaps.size(); iGap++) {
      gapStartEvt0 = m_epuList[0].m_datagramMap[m_epuList[0].m_datagramGaps[iGap].m_lastDatagramBefore]->m_lastGemId;
      gapStartEvt1 = m_epuList[1].m_datagramMap[m_epuList[1].m_datagramGaps[iGap].m_lastDatagramBefore]->m_lastGemId;
      gapEndEvt0 = m_epuList[0].m_datagramMap[m_epuList[0].m_datagramGaps[iGap].m_firstDatagramAfter]->m_firstGemId;
      gapEndEvt1 = m_epuList[1].m_datagramMap[m_epuList[1].m_datagramGaps[iGap].m_firstDatagramAfter]->m_firstGemId;
      ofile << "r0" << m_runId << " " << max(gapStartEvt0,gapStartEvt1) << " " << min(gapEndEvt0,gapEndEvt1) << endl;
    }
  }
  ofile.close();
}

