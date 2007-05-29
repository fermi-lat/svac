#include "AcdPedParser.h"
#include <string>
#include <iostream>
#include <fstream>
#include "calibUtil/Metadata.h"
#include <unistd.h>
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
#include "idents/AcdId.h"
#include "commonRootData/idents/AcdId.h"
#include "xmlBase/XmlParser.h"
#include "facilities/Util.h"
using xmlBase::Dom;
using namespace xmlBase;

AcdPedParser::AcdPedParser(){}
void AcdPedParser::parse(AcdPeds* peds,const char* filename){
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
  DOMElement* pmtElt = findFirstPmt(docElt);
  while (pmtElt != 0 ) {
    DOMElement* pedElt = xmlBase::Dom::getFirstChildElement(pmtElt);
    UInt_t garc,gafe;
    AcdId::convertToGarcGafe(m_id.id(),m_nPmt,garc,gafe);
    peds->setMean(garc,gafe,(float)xmlBase::Dom::getDoubleAttribute(pedElt, "mean"));
    peds->setWidth(garc,gafe,(float)xmlBase::Dom::getDoubleAttribute(pedElt, "width"));
    pmtElt = findNextPmt(pmtElt);
  }
  return ;
}

  DOMElement* AcdPedParser::findFirstPmt(const DOMElement* docElt) {
  using xmlBase::Dom;

  // note that so-called <tile> may be ribbon or NA
  DOMElement* tileElt = Dom::findFirstChildByName(docElt, "tile");
  // If no <tile> elements, this file is useless
  if (tileElt == 0) return tileElt;
  DOMElement* pmtElt = Dom::getFirstChildElement(tileElt);
  if (pmtElt == 0) return pmtElt;

  try {
    std::string idString = Dom::getAttribute(tileElt, "tileId");
    m_id = idents::AcdId(idString);
    m_nPmt = Dom::getIntAttribute(pmtElt, "iPmt");
  }
  catch (xmlBase::DomException ex1) {
    std::cerr << "From CalibSvc::XmlAcdBaseCnv::findFirstPmt" << std::endl;
    std::cerr << ex1.getMsg() << std::endl;
    throw ex1;
  }
  catch (facilities::WrongType ex2) {
    std::cerr << "From CalibSvc::XmlAcdBaseCnv::findFirstPmt" << std::endl;
    std::cerr << ex2.what() << std::endl;
    throw ex2;
  }

  return pmtElt;
}

DOMElement* AcdPedParser::findNextPmt(const DOMElement* pmtElt) {
  using xmlBase::Dom;


  DOMElement* elt = Dom::getSiblingElement(pmtElt);

  if (elt != 0) {
    m_nPmt = Dom::getIntAttribute(elt, "iPmt");
    return elt;
  }

  // Done with this pmt; look for sibling
  DOMNode* node = pmtElt->getParentNode();
  DOMElement* tileElt = static_cast<DOMElement* >(node);   // current tile
  tileElt = Dom::getSiblingElement(tileElt);          // next tile

  if (tileElt != 0) {
    try {
      std::string idString = Dom::getAttribute(tileElt, "tileId");
      m_id = idents::AcdId(idString);

      elt = Dom::getFirstChildElement(tileElt);
      m_nPmt = Dom::getIntAttribute(elt, "iPmt");
    }
    catch (xmlBase::DomException ex1) {
      std::cerr << "From CalibSvc::XmlAcdBaseCnv::findNextPmt" << std::endl;
      std::cerr << ex1.getMsg() << std::endl;
      throw ex1;
    }
    catch (facilities::WrongType ex2) {
      std::cerr << "From CalibSvc::XmlAcdBaseCnv::findNextPmt" << std::endl;
      std::cerr << ex2.what() << std::endl;
      throw ex2;
    }
  }
  return elt;
}

