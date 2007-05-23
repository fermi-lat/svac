// 
// Base class for an input quantity for monitoring
// 
// Martin Kocian, SLAC, 2/1/07
// Software developed for GLAST

#include "MonInputObject.h"
#include <time.h>
#include <iostream>
#include <iomanip>

void MonInputObject::setValueProf(TObject* event){
  struct timespec ts1, ts2;
  clock_gettime(CLOCK_REALTIME, &ts1);
  setValue(event);
  clock_gettime(CLOCK_REALTIME, &ts2);
  unsigned long starttime=ts1.tv_sec*1000000+ts1.tv_nsec/1000;
  unsigned long endtime=ts2.tv_sec*1000000+ts2.tv_nsec/1000;
  //sometimes the clock goes backwards.
  if (starttime<endtime) m_timeprof+=(endtime-starttime);
}

float MonInputObject::timeProfile(){
  float timeprof=(float)m_timeprof/1e6;
  std::cout<<setiosflags(std::ios::left);
  std::cout<<std::setw(60)<<std::setfill(' ')<<m_name<<": "<<timeprof<<" seconds"<<std::endl;
  return timeprof;
}
 
