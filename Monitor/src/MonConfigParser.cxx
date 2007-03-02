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

#include <xercesc/dom/DOMElement.hpp>
#include "recXmlList.h"

#include <string>
#include <list>
#include <map>
#include <vector>

#include "MonConfigParser.h"

MonConfigParser::MonConfigParser(const char* filename){
  XmlParser* parser = new XmlParser( true );
  DOMDocument* doc;
  try {
    doc =parser->parse( filename );
  }
  catch (ParseException ex) {
    std::cout << "caught exception with message " << std::endl;
    std::cout << ex.getMsg() << std::endl;
    assert(false);
  }
  // top level element
  DOMElement* topElt = doc->getDocumentElement();
  recXmlList inlist;
  inlist.clearLists();
  m_inlist=inlist.readInputList("top",topElt);
   // std::cout<<inlist.getLists().size()<<std::endl;
   // std::vector<std::string>::iterator it;
   // std::vector<std::string> list=inlist.getLists();
  //  for (it=list.begin();it!=list.end();it++){
  //    std::cout<<"x"<<(*it)<<"o"<<std::endl;
   // }
  inlist.clearLists();
  m_outlist=inlist.readOutputList("top",topElt);
  m_eventcut=inlist.readItem(topElt,"eventCut");
  m_timestamp=inlist.readItem(topElt,"timestamp");
  
}

std::list<std::string>& MonConfigParser::getInputList(){
  return m_inlist;
}
std::list<std::map<std::string,std::string> >& MonConfigParser::getOutputList(){
  return m_outlist;
}

std::string& MonConfigParser::getEventCut(){
  return m_eventcut;
}
std::string& MonConfigParser::getTimeStamp(){
  return m_timestamp;
}
