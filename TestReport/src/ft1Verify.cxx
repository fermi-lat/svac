#include <iostream>
#include <cstdio>
#include <string>
#include <stdexcept>
#include <iterator>
#include <list>
#include <algorithm>

#include "ft1Verify.h"
#include "AcdXmlUtil.h"
#include "DomElement.h"
#include "TSystem.h"

#include "tip/Header.h"
#include "tip/IFileSvc.h"
#include "tip/Table.h"
#include "xmlBase/Dom.h"
#include "xmlBase/XmlParser.h"
#include "xercesc/dom/DOMElement.hpp"
#include "xercesc/dom/DOMDocument.hpp" 
#include "xercesc/dom/DOMImplementation.hpp"


using std::cout;
using std::endl;
using std::string;
using std::list;
using std::vector;

ft1Verify::ft1Verify()
  : m_nRows(0)
{ 
}

ft1Verify::~ft1Verify()
{
  m_errMap.clear();
  m_rowMap.clear();
}

RowError::RowError(string errName, double eventid, double time)
  : m_errName(errName),
    m_eventid(eventid),
    m_time(time)
{
}

RowError::~RowError() {
}

void ft1Verify::analyzeFt1(const char* ft1FileName="ft1.fit")
{
  int rowCtr = 0;
  double eventid, time, evtprev=0, timeprev=0;
  std::string errorName;

  //open fits file using the readTable method
  const tip::Table* ft1file = tip::IFileSvc::instance().readTable(ft1FileName, "EVENTS");
  tip::Table::ConstIterator it = ft1file->begin();
  tip::Table::ConstRecord& row = *it;

  for ( ; it != ft1file->end(); ++it) {
    rowCtr++;
    eventid = row["event_id"].get();
    time = row["time"].get();
    if (eventid < evtprev) {
      cout << "ERROR! Event Sequence going backwards at row " << rowCtr << endl;
      errorName = "FT1_EVENTS_BACKWARDS"; // ['Event ID is going backwards for this row']
      RowError* row_e = new RowError(errorName,eventid,time);
      m_rowMap[rowCtr].push_back(row_e);
      m_errMap[errorName].push_back(rowCtr);
    }
    if (time < timeprev) {
      cout << "ERROR! Time is going backwards at row " << rowCtr << endl;
      errorName = "FT1_TIME_BACKWARDS"; // ['Time is going backwards for this row']
      RowError* row_e = new RowError(errorName,eventid,time);
      m_rowMap[rowCtr].push_back(row_e);
      m_errMap[errorName].push_back(rowCtr);
    }
    evtprev = eventid;
    timeprev = time;
  }
  m_nRows = rowCtr;
  // Closing time 
  delete ft1file;
}

Bool_t ft1Verify::writeXmlFile(const char* fileName, int truncated) const {

  DomElement elem = AcdXmlUtil::makeDocument("errorContribution");
  writeXmlHeader(elem);
  writeXmlErrorSummary(elem, truncated);
  writeXmlEventSummary(elem, truncated);
  writeXmlFooter(elem);
  return AcdXmlUtil::writeIt(elem,fileName);

}

void ft1Verify::writeXmlHeader(DomElement& /* node */) const {
  // do nothing, for now
}

void ft1Verify::writeXmlFooter(DomElement& /* node */) const {
  // do nothing, for now
  return;
}

void ft1Verify::writeXmlErrorSummary(DomElement& node, int truncation) const {
  DomElement errSummary = AcdXmlUtil::makeChildNode(node,"errorSummary");
  // loop on the errors to make the error summary list
  for (map< string, list<int> >::const_iterator it = m_errMap.begin(); it != m_errMap.end(); it++){
    DomElement errType = AcdXmlUtil::makeChildNode(errSummary,"errorType");
    AcdXmlUtil::addAttribute(errType,"code",(*it).first.c_str());
    AcdXmlUtil::addAttribute(errType,"quantity",(int)(*it).second.size());
    if ((int)(*it).second.size()>truncation) AcdXmlUtil::addAttribute(errType,"truncated","True");
    else AcdXmlUtil::addAttribute(errType,"truncated","False");
  }
}

void ft1Verify::writeXmlEventSummary(DomElement& node, int truncation) const {
  DomElement eventSummary = AcdXmlUtil::makeChildNode(node,"eventSummary");
  AcdXmlUtil::addAttribute(eventSummary,"num_processed_events",m_nRows);
  AcdXmlUtil::addAttribute(eventSummary,"num_error_events",(int)m_rowMap.size());
  map< string, int > m_errCounter;
  for (map< string, list<int> >::const_iterator it = m_errMap.begin(); it != m_errMap.end(); it++){
    m_errCounter[(*it).first.c_str()] = 0;
    if ((int)(*it).second.size()>truncation) AcdXmlUtil::addAttribute(eventSummary,"truncated","True");
    else AcdXmlUtil::addAttribute(eventSummary,"truncated","False");
  }
  for (map< int, list<RowError*> >::const_iterator it = m_rowMap.begin(); it != m_rowMap.end(); it++){  
    // check if there is at least one error that didn't reach truncation limit for this event
    bool write_row = false;
    for (list<RowError*>::const_iterator ie = (*it).second.begin(); ie != (*it).second.end(); ie ++){
      if (m_errCounter[(*ie)->m_errName.c_str()] <= truncation) write_row = true;
     }
    if (write_row) {
      DomElement eventError = AcdXmlUtil::makeChildNode(eventSummary,"errorEvent");
      if ( (*it).first > -1 ) AcdXmlUtil::addAttribute(eventError,"rowNumber",(int)(*it).first);
      else AcdXmlUtil::addAttribute(eventError,"rowNumber","noRow");
      for (list<RowError*>::const_iterator ie = (*it).second.begin(); ie != (*it).second.end(); ie ++){
        DomElement errDetail = AcdXmlUtil::makeChildNode(eventError,"error");
        AcdXmlUtil::addAttribute(errDetail,"code",(*ie)->m_errName.c_str());
        AcdXmlUtil::addAttribute(errDetail,"event_id",(*ie)->m_eventid);
        AcdXmlUtil::addAttribute(errDetail,"time",(int)(*ie)->m_time);
        m_errCounter[(*ie)->m_errName.c_str()]++;
      }
    }
  }
}

