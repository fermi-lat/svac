#ifndef ACDPEDPARSER_H
#define ACDPEDPARSER_H

#include "idents/AcdId.h"
#include "AcdPeds.h"
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
#include "xmlBase/XmlParser.h"
#include "facilities/Util.h"
using xmlBase::Dom;
using namespace xmlBase;

class AcdPedParser{
 public:
  AcdPedParser();
  ~AcdPedParser(){}
  void parse(AcdPeds* peds, const char* filename);
  DOMElement* findFirstPmt(const DOMElement* pmtElt);
  DOMElement* findNextPmt(const DOMElement* pmtElt);
 private:
  idents::AcdId m_id;
  unsigned int m_nPmt;
};

#endif
