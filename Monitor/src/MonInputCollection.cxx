// class to hold monitoring input objects 
// M. Kocian, SLAC, 2/2/07
// Software developed for GLAST

#include "MonInputCollection.h"
#include <iostream>
#include <iomanip>
#include <time.h>


MonInputCollection::MonInputCollection(TTree* tree, std::string type):m_intree(tree),m_type(type),m_timeprof(0){
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
    //(*itr)->setValue(m_event);
    (*itr)->setValueProf(m_event);
  }
}

unsigned MonInputCollection::nObjects(){
  if (m_inpcol)return m_inpcol->size();
  else return 0;
}

void MonInputCollection::readEventProf(Long64_t ievent){
  struct timespec ts1, ts2;
  clock_gettime(CLOCK_REALTIME, &ts1);
  readEvent(ievent);
  clock_gettime(CLOCK_REALTIME, &ts2);
  // std::cout<<"Moninputcollection "<<ts1.tv_nsec<<" "<<ts2.tv_nsec<<std::endl;
  unsigned long starttime=ts1.tv_sec*1000000+ts1.tv_nsec/1000;
  unsigned long endtime=ts2.tv_sec*1000000+ts2.tv_nsec/1000;
  m_timeprof+=(endtime-starttime);
}

float MonInputCollection::timeProfile(){
  float total=0;
  std::cout<<"Time profile for collection "<<m_type<<":"<<std::endl;
  std::cout<<"============================================"<<std::endl;
  for (std::vector<MonInputObject*>::const_iterator itr=m_inpcol->begin();
       itr != m_inpcol->end();itr++){
    total+=(*itr)->timeProfile();
  }
  float timeprof=(float)m_timeprof/1e6-total;
  std::cout<<setiosflags(std::ios::left);
  std::cout<<"-------------------------------------------------------"<<std::endl;
  std::cout<<"Total event reading time for collection "<<std::setw(20)<<std::setfill(' ')<<m_type<<": "<<timeprof<<" seconds"<<std::endl;
  std::cout<<"Total time for setting values for collection "<<std::setw(15)<<std::setfill(' ')<<m_type<<": "<<total<<" seconds"<<std::endl<<std::endl;
  return timeprof;
}
 

