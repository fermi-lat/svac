#ifndef recXmlList_h
#define recXmlList_h
#include "xmlBase/Dom.h"
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <list>
#include <string>
#include <vector>
#include <map>

using namespace xmlBase;
class recXmlList{
 public:
  recXmlList();
  void setLists(std::vector<std::string> lists);
  void clearLists();
  std::vector<std::string> getLists(){return m_lists;}
  std::list<std::string> readInputList(const char* elname, DOMElement* elem);
  std::list<std::map<std::string,std::string> > readOutputList(const char* elname, DOMElement* elem);
  std::string readItem(DOMElement* elem,const char* tag);
 private:
  std::vector<std::string> m_lists;
  const std::string removeWhitespace(const std::string) const;
  int findTopList(const char* elname, std::vector<DOMElement*> elem);
};
#endif
