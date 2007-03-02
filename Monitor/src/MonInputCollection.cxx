// class to hold monitoring input objects 
// M. Kocian, SLAC, 2/2/07
// Software developed for GLAST

#include "MonInputCollection.h"
#include <iostream>


MonInputCollection::MonInputCollection(TTree* tree, std::string type):m_intree(tree),m_type(type){
  m_inpcol=new std::vector<MonInputObject*>;
  m_isattached=false;
  m_event=0;
}

MonInputCollection::~MonInputCollection(){
  for (std::vector<MonInputObject*>::const_iterator itr=m_inpcol->begin();
       itr != m_inpcol->end();itr++){
    delete (*itr);
  }  
  delete m_inpcol;
}

void MonInputCollection::addInputObject(MonInputObject* obj){
  if (obj->getInputSource()==m_type) m_inpcol->push_back(obj);
  else{
    std::cerr<<"Trying to attach an object of type "<<obj->getInputSource()<<" to a collection of type "<<m_type<<std::cerr;
    assert(0);
  }
}

void MonInputCollection::attachInputTree(){
  for (std::vector<MonInputObject*>::const_iterator itr=m_inpcol->begin();
       itr != m_inpcol->end();itr++){
    (*itr)->enableInputBranch(*m_intree);
  }
  m_isattached=true;
}

void MonInputCollection::populateTableTree(TTree* tree){  
  for (std::vector<MonInputObject*>::const_iterator itr=m_inpcol->begin();
       itr != m_inpcol->end();itr++){
    (*itr)->setOutputBranch(tree);
  }
}

void MonInputCollection::readValues(){
  if (!m_isattached){
    std::cerr<<"No tree attached to input objects, call attachInputTree first"<<std::endl;
    assert(m_isattached==true);
  }
  for (std::vector<MonInputObject*>::const_iterator itr=m_inpcol->begin();
       itr != m_inpcol->end();itr++){
    (*itr)->setValue(m_event);
  }
}

unsigned MonInputCollection::nObjects(){
  if (m_inpcol)return m_inpcol->size();
  else return 0;
}
