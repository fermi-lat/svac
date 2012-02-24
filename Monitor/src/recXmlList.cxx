
#include "recXmlList.h"
#include <vector>
#include <list>
#include <cassert>
#include "xmlBase/Dom.h"
using namespace xmlBase;

recXmlList::recXmlList(){}

void recXmlList::setLists(std::vector<std::string> lists){
  m_lists=lists;
}
void recXmlList::clearLists(){
  m_lists.clear();
}
int recXmlList::findTopList(const char* elname, std::vector<DOMElement*> elem){
  for (unsigned i=0;i<elem.size();i++){
    std::string at(Dom::getAttribute(elem[i],"name"));
    if (strstr(at.c_str(),elname)){
      return i;
    }
  }
  return -1;
}

std::list<std::string> recXmlList::readInputList(const char* elname, DOMElement* elem){
  std::list<std::string> rs;
  std::vector<DOMElement*> defOutList;
  std::string tagname("inputList");
  Dom::getChildrenByTagName( elem, tagname.c_str(), defOutList );
  int ind=findTopList(elname,defOutList);
  if (ind==-1){
    std::cerr<<"*** recXmlList.cxx: List "<<elname<<" not found"<<std::endl;
    return rs;
  }
  m_lists.push_back(std::string(elname));
  std::vector<DOMElement*> inobjects;
  Dom::getChildrenByTagName( defOutList[ind], "object", inobjects );
  for (unsigned i=0;i<inobjects.size();i++){
    std::string ous=removeWhitespace(Dom::getTextContent(inobjects[i]));
    rs.push_back(ous);
  }
  std::vector<DOMElement*> inlists; 
  Dom::getChildrenByTagName( defOutList[ind], "list", inlists );
  rs.sort();
  for (unsigned i=0;i<inlists.size();i++){
    std::string textcontent=removeWhitespace(Dom::getTextContent(inlists[i]));
    if (std::find(m_lists.begin(),m_lists.end(),textcontent)==m_lists.end()){
      recXmlList* newlist = new recXmlList;
      newlist->setLists(getLists());
      std::list<std::string> nl=newlist->readInputList(textcontent.c_str(),elem);
      setLists(newlist->getLists());
      delete newlist;
      nl.sort();
      rs.merge(nl);
    }else{
      std::cerr<<"*** recXmlList.cxx Warning: List "<<textcontent<<" added multiple times."<<std::endl;
    }
  }
  std::list<std::string>::iterator it;
  std::string oldval;
  for (it=rs.begin();it!=rs.end();it++){
    if (it==rs.begin()){
      oldval=(*it);
      continue;
    }else{
      if ((*it)==oldval){
	std::cerr<<"*** recXmlList.cxx: Warning: Input object "<<oldval<<" added multiple times."<<std::endl;
      }
      oldval=(*it);
    }
  }
  rs.unique();
  return rs;
}

std::list<std::map<std::string,std::string> > recXmlList::readOutputList(const char* elname, DOMElement* elem){
  std::list<std::map<std::string,std::string> > rs;
  std::vector<DOMElement*> defOutList;
  std::string tagname("outputList");
  Dom::getChildrenByTagName( elem, tagname.c_str(), defOutList );
  int ind=findTopList(elname,defOutList);
  if (ind==-1){
    std::cerr<<"*** recXmlList.cxx Warning: List "<<elname<<" not found"<<std::endl;
    return rs;
  }
  m_lists.push_back(std::string(elname));

  std::vector<DOMElement*> outobjects;
  Dom::getChildrenByTagName( defOutList[ind], "object", outobjects );
  for (unsigned i=0;i<outobjects.size();i++){
    xercesc::DOMNodeList* childobjects;
    childobjects=outobjects[i]->getChildNodes();
    std::map<std::string,std::string>  mp;
    for (unsigned j=0;j<childobjects->getLength();j++){
      DOMElement* currentElement = dynamic_cast< DOMElement* >( childobjects->item(j) );
      if (currentElement){
	std::string nm=removeWhitespace(Dom::getTagName(currentElement));
	//	std::cout<<"node "<<nm<<std::endl;
	std::string ous=Dom::getTextContent(currentElement);
	if (nm.find("desc")==(unsigned)-1)ous=removeWhitespace(ous);
		//std::cout<<"name "<<ous<<std::endl;
	mp[nm]=ous;
      }
    }
    rs.push_back(mp);
  }

  std::vector<DOMElement*> outlists; 
  Dom::getChildrenByTagName( defOutList[ind], "list", outlists );
  rs.sort();
  for (unsigned i=0;i<outlists.size();i++){
    std::string textcontent=removeWhitespace(Dom::getTextContent(outlists[i]));
    if (std::find(m_lists.begin(),m_lists.end(),textcontent)==m_lists.end()){
      recXmlList* newlist = new recXmlList;
      newlist->setLists(getLists());
      std::list<std::map<std::string,std::string> > nl=newlist->readOutputList(textcontent.c_str(),elem);
      setLists(newlist->getLists());
      delete newlist;
      nl.sort();
      rs.merge(nl);
    }else{
      std::cerr<<"*** recXmlList.cxx Warning: List "<<textcontent<<" added multiple times."<<std::endl;
    }
  }
  rs.unique();
  std::list<std::map<std::string,std::string> >::iterator it;
  std::list<std::string> namelist;
  for (it=rs.begin();it!=rs.end();it++){
    namelist.push_back((*it)["name"]);
  }
  namelist.sort();
  std::list<std::string>::iterator itr;
  std::string oldval;
  for (itr=namelist.begin();itr!=namelist.end();itr++){
    if (itr==namelist.begin()){
      oldval=(*itr);
      continue;
    }else{
      if ((*itr)==oldval){
	std::cerr<<"*** recXmlList.cxx: Error: Input object with name "<<oldval<<" defined multiple times."<<std::endl;
	assert(0);
      }
      oldval=(*itr);
    }
  }
  return rs;
}
 
std::string recXmlList::readItem(DOMElement* elem, const char* tag){
  std::vector<DOMElement*> defOutList;
  std::string tagname(tag);
  std::string rs;
  Dom::getChildrenByTagName( elem, tagname.c_str(), defOutList ); 
  if(defOutList.size()>1){
    std::cerr<<"More than one "<<tagname<<" defined in xml file. Exiting..."<<std::endl;
    assert(0);
  }
  if (defOutList.size()==0)rs="";
  else{
    rs=removeWhitespace(Dom::getTextContent(defOutList[0]));
  }
  return rs;
}

const std::string recXmlList::removeWhitespace(const std::string inst) const{
  std::string st(inst);
  std::string::iterator end=std::remove(st.begin(), st.end(), ' ');
  st.erase(end,st.end());
  return st;
}
