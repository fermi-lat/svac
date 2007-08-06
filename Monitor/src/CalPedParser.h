#ifndef CALPEDPARSER_H
#define CALPEDPARSER_H

#include "CalPeds.h"
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

class CalPedParser{
 public:
  CalPedParser();
  ~CalPedParser(){}
  void parse(CalPeds* peds, const char* filename);
  DOMElement* findFirstRange(const DOMElement* docElt);
  DOMElement* findNextRange(const DOMElement* rangeElt);
  unsigned findFace(const DOMElement* faceElt);
  unsigned findRangeAtt(const DOMElement* rangeElt);
 private:
  unsigned m_nTower;
  unsigned m_nLayer;
  unsigned m_nXtal;
  unsigned m_nFace;
  unsigned m_nRange;

};

#endif
