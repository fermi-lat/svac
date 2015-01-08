#include <iostream>
#include <cstdio>
#include <string>
#include <stdexcept>
#include <fstream>
#include <stdlib.h>   

#include "TROOT.h"
#include "findGaps.h"
#include "TSystem.h"

using std::cout;
using std::endl;
using std::string;

findGaps::findGaps()
  : m_digiFile(0),
    m_digiTree(0),
    m_digiBranch(0),
    m_digiEvent(0)
{ 
  // initialize ROOT
  if(gROOT == 0) {
    static TROOT g_root("report", "report");
  }
  gROOT->SetBatch();  // initialize ROOT
}

findGaps::~findGaps()
{
  delete m_digiFile;
}

void findGaps::analyzeDigi(const char* digiFileName="digi.root", const char* gapsFileName="gaps.txt")
{
  unsigned int nDigi = 0, runId = 0;
  unsigned int lastEventBefore = 0, firstEventAfter = 0;
  bool gapIsOpen[EpuNumber],atLeastOneEvt[EpuNumber];
  unsigned int previousDatagram[EpuNumber],previousGemId[EpuNumber];

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
  
  // Open gaps file 
  ofstream gapsFile;
  gapsFile.open(gapsFileName);

  // Make sure we have events in the digi file:
  nDigi = (unsigned int) m_digiTree->GetEntries();
  cout << "Number of events in " << digiFileName << " : " << nDigi << endl;
  if(nDigi < 1){
    cout << "ERROR: no events in digi file " << digiFileName << endl;
    return;
  }
 
  for (unsigned int iLoop = 0; iLoop < EpuNumber; ++iLoop) {
    atLeastOneEvt[iLoop] = gapIsOpen[iLoop] = false;
    previousDatagram[iLoop] = previousGemId[iLoop] = 0;
  }

  // Loop over events:
  for(unsigned int iEvent = 0; iEvent != nDigi; ++iEvent) {

    if (iEvent % 10000 == 0) cout << "Event number " << iEvent << endl;
    // Cleanup:
    if (m_digiEvent)  m_digiEvent->Clear();
    // Analyze digi file:
    m_digiBranch->GetEntry(iEvent);
    unsigned int thisCpu = m_digiEvent->getMetaEvent().datagram().crate();
    unsigned int otherCpu = abs(int(thisCpu) - 1);
    unsigned int DatagramSeqNbr = m_digiEvent->getMetaEvent().datagram().datagrams();
    unsigned int tmpGemId = m_digiEvent->getEventId();

    // Here I do the whole check: if there is no 'current' gap, I look for a gap
    if ( !gapIsOpen[otherCpu] && DatagramSeqNbr != previousDatagram[thisCpu] &&
                (DatagramSeqNbr-previousDatagram[thisCpu])!=1 && atLeastOneEvt[thisCpu] ) {
      gapIsOpen[thisCpu] = true;
      if (previousGemId[otherCpu] > 0) {
        lastEventBefore = max(previousGemId[thisCpu],previousGemId[otherCpu]);
      } else {
        lastEventBefore = previousGemId[thisCpu];
      }	
      firstEventAfter = tmpGemId;
    }
    // If there is already a 'current' gap from the other cpu, I close it
    if (gapIsOpen[otherCpu]){
      if (abs(int(previousGemId[thisCpu]-lastEventBefore)) < abs(int(previousGemId[thisCpu]-firstEventAfter))){
        firstEventAfter = min(tmpGemId,firstEventAfter);
      } else {
        firstEventAfter = min(previousGemId[thisCpu],firstEventAfter);
      }
      cout << "Gap found between event " << lastEventBefore << " and " << firstEventAfter << endl;
      gapsFile << "r0" << runId << " " << lastEventBefore << " " << firstEventAfter << endl;
      gapIsOpen[otherCpu] = false;
    }   
    if (!atLeastOneEvt[thisCpu]) {
      runId = m_digiEvent->getMetaEvent().run().startTime();
      atLeastOneEvt[thisCpu] = true;
    }
    // Keep datagram sequence number and other infos for previous event
    previousDatagram[thisCpu] = DatagramSeqNbr;
    previousGemId[thisCpu] = tmpGemId;
    m_digiEvent->Clear();
  }

  // Closing time:  
  if(m_digiFile) m_digiFile->Close();
  gapsFile.close();
}

