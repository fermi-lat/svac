#include "CalPedParser.h"
#include <string>
#include <iostream>
#include <fstream>
#include "calibUtil/Metadata.h"
#include <unistd.h>
#include <cassert>
#include "xmlBase/Dom.h"
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMCharacterData.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMException.hpp>
#include <xercesc/dom/DOMTreeWalker.hpp>
#include <xercesc/util/TransService.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include "xmlBase/XmlParser.h"
#include "facilities/Util.h"
using xmlBase::Dom;
using namespace xmlBase;

CalPedParser::CalPedParser(){}
void CalPedParser::parse(CalPeds* peds,const char* filename){
  XmlParser parser(true);
  DOMDocument* doc;
  try {
    doc =parser.parse( filename );
  }
  catch (ParseException ex) {
    std::cerr << "caught exception with message " << std::endl;
    std::cerr << ex.getMsg() << std::endl;
    assert(false);
  }
  // top level element
  DOMElement* docElt = doc->getDocumentElement();
  DOMElement* rangeElt = findFirstRange(docElt);
  while (rangeElt != 0 ) {
    float avg, sig;
    try {
      avg = xmlBase::Dom::getDoubleAttribute(rangeElt, "avg");
      sig = xmlBase::Dom::getDoubleAttribute(rangeElt, "sig");
    }
    catch (xmlBase::DomException ex) {
      std::cerr << "From CalibSvc::XmlCalPedCnv::processRange" << std::endl;
      std::cerr << ex.getMsg() << std::endl;
      throw ex;
    }
    peds->setMean(m_nTower,m_nLayer,m_nXtal,m_nFace,m_nRange,avg);
    peds->setWidth(m_nTower,m_nLayer,m_nXtal,m_nFace,m_nRange,sig);
    rangeElt=findNextRange(rangeElt);
  }
  return ;
}
unsigned CalPedParser::findRangeAtt(const DOMElement* rangeElt) {
    using xmlBase::Dom;

    std::string att = Dom::getAttribute(rangeElt, "range");
    if (att.size() == 0) {    // Try diode next
      att = Dom::getAttribute(rangeElt, "diode");
      if (att.size() == 0)      return 0;      // no sort of range

      // else process value of diode attribute;
      //   a little bit of sleight of hand here
      if (att.compare(std::string("LE")) == 0) return 0;
      if (att.compare(std::string("HE")) == 0) return 2;
      return 0;
    }
    if (att.compare(std::string("LEX8")) == 0) return 0;
    if (att.compare(std::string("LEX1")) == 0) return 1;
    if (att.compare(std::string("HEX8")) == 0) return 2;
    if (att.compare(std::string("HEX1")) == 0) return 3; 
    // anything else is illegal.  Should be caught by parser, but
    // maybe should also throw exception here.
    return 0;
  }

unsigned CalPedParser::findFace(const DOMElement* faceElt) {
    using xmlBase::Dom;

    std::string att = Dom::getAttribute(faceElt, "end");
    if (att.compare(std::string("NEG")) == 0) return 1;
    if (att.compare(std::string("POS")) == 0) return 0;
    return 0;     // in case "end" is not applicable, this is the answer
  }


DOMElement* CalPedParser::findFirstRange(const DOMElement* docElt) {
  using xmlBase::Dom;

  DOMElement* elt = Dom::findFirstChildByName(docElt, "tower");
  if (elt == 0) return elt;

  //  std::string att = Dom::getAttribute(elt, "nRow");
  //  m_nRow = atoi(att.c_str());
  try {
    unsigned nRow = Dom::getIntAttribute(elt, "iRow");
    unsigned nCol = Dom::getIntAttribute(elt, "iCol");
    m_nTower=nCol+4*nRow;

    // All child elements of a tower are layer elements
    elt = Dom::getFirstChildElement(elt);
    m_nLayer = Dom::getIntAttribute(elt, "iLayer");

    // All child elements of layers are xtal elements
    elt = Dom::getFirstChildElement(elt);
    m_nXtal = Dom::getIntAttribute(elt, "iXtal");
  }
  catch (xmlBase::DomException ex) {
    std::cerr << "From CalibSvc::XmlCalBaseCnv::findFirstRange" << std::endl;
    std::cerr << ex.getMsg() << std::endl;
    throw ex;
  }

  // All child elements of xtal are face elements
  elt = Dom::getFirstChildElement(elt); 
  m_nFace = findFace(elt);
  
  elt = Dom::getFirstChildElement(elt);
  m_nRange = findRangeAtt(elt);
  return elt;
}

/// Still another one to navigate XML file and find next set of range data
DOMElement* CalPedParser::findNextRange(const DOMElement* rangeElt) {
  using xmlBase::Dom;
  using XERCES_CPP_NAMESPACE_QUALIFIER DOMNode;

  DOMElement* elt = Dom::getSiblingElement(rangeElt);
  if (elt != 0) {
    m_nRange = findRangeAtt(elt);
    return elt;
  }

  // Done with this xtal face; look for sibling
  DOMNode* node = rangeElt->getParentNode();
  elt = static_cast<DOMElement* >(node);   // current xtal face
  elt = Dom::getSiblingElement(elt);          // next xtal face

  if (elt != 0) {
    m_nFace = findFace(elt);

    elt = Dom::getFirstChildElement(elt);
    m_nRange = findRangeAtt(elt);
    return elt;
  }

  // Done with this xtal
  node = node->getParentNode();  // current xtal
  elt = static_cast<DOMElement* >(node);
  elt = Dom::getSiblingElement(elt);         // next xtal

  if (elt != 0) {
    try {
      m_nXtal = Dom::getIntAttribute(elt, "iXtal");
    }
    catch (xmlBase::DomException ex) {
      std::cerr << "From CalibSvc::XmlCalBaseCnv::findNextRange" << std::endl;
      std::cerr << ex.getMsg() << std::endl;
      throw ex;
    }

    //    std::string att = Dom::getAttribute(elt, "iXtal");
    //    m_nXtal = atoi(att.c_str());

    // All child elements of xtal are face elements
    elt = Dom::getFirstChildElement(elt);
    m_nFace = findFace(elt);

    elt = Dom::getFirstChildElement(elt);
    m_nRange = findRangeAtt(elt);
    return elt;
  }

  // Done with this layer
  node = node->getParentNode();  // current layer
  elt = static_cast<DOMElement* >(node);
  elt = Dom::getSiblingElement(elt);         // next layer

  if (elt != 0) {
    try {
      m_nLayer = Dom::getIntAttribute(elt, "iLayer");
    }
    catch (xmlBase::DomException ex) {
      std::cerr << "From CalibSvc::XmlCalBaseCnv::findNextRange" << std::endl;
      std::cerr << ex.getMsg() << std::endl;
      throw ex;
    }
    

    // All child elements of layers are xtal elements
    elt = Dom::getFirstChildElement(elt);

    try {
      m_nXtal = Dom::getIntAttribute(elt, "iXtal");
    }
    catch (xmlBase::DomException ex) {
      std::cerr << "From CalibSvc::XmlCalBaseCnv::findNextRange" << std::endl;
      std::cerr << ex.getMsg() << std::endl;
      throw ex;
    }

    // All child elements of xtal are face elements
    elt = Dom::getFirstChildElement(elt);
    m_nFace = findFace(elt);
    
    elt = Dom::getFirstChildElement(elt);
    m_nRange = findRangeAtt(elt);
    return elt;
  }

  // Done with this tower
  node = node->getParentNode();  // current tower
  elt = static_cast<DOMElement* >(node);
  elt = Dom::getSiblingElement(elt);         // next tower

  if (elt == 0) return elt;

  // otherwise we've got a new tower; go through the whole
  // rigamarole


  try {
    unsigned nRow = Dom::getIntAttribute(elt, "iRow");
    unsigned nCol = Dom::getIntAttribute(elt, "iCol");
    m_nTower=nCol+4*nRow;

    // All child elements of a tower are layer elements
    elt = Dom::getFirstChildElement(elt);
    m_nLayer = Dom::getIntAttribute(elt, "iLayer");

    // All child elements of layers are xtal elements
    elt = Dom::getFirstChildElement(elt);
    m_nXtal = Dom::getIntAttribute(elt, "iXtal");
  }
  catch (xmlBase::DomException ex) {
    std::cerr << "From CalibSvc::XmlCalBaseCnv::findFirstRange" << std::endl;
    std::cerr << ex.getMsg() << std::endl;
    throw ex;
  }


  // All child elements of xtal are face elements
  elt = Dom::getFirstChildElement(elt);
  m_nFace = findFace(elt);

  elt = Dom::getFirstChildElement(elt);
  m_nRange = findRangeAtt(elt);

  return elt;
}


