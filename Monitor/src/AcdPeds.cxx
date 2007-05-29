#include "AcdPeds.h"
#include <iostream>

AcdPeds::AcdPeds(){
  for (int garc=0;garc<12;garc++){
    for (int gafe=0;gafe<18;gafe++){
      m_mean[garc][gafe]=0;
      m_width[garc][gafe]=0;
    }
  }
}
void AcdPeds::setMean(int garc, int gafe,float value){
  if (garc<0 || garc>11)return;
  if (gafe<0 || gafe>17)return;
  m_mean[garc][gafe]=value;
}
void AcdPeds::setWidth(int garc, int gafe,float value){
  if (garc<0 || garc>11)return;
  if (gafe<0 || gafe>17)return;
  m_width[garc][gafe]=value;
}
const float AcdPeds::mean(int garc, int gafe) const{
  if (garc<0 || garc>11)return -1;
  if (gafe<0 || gafe>17)return -1;
  return m_mean[garc][gafe];
}
const float AcdPeds::width(int garc, int gafe) const{
  if (garc<0 || garc>11)return -1;
  if (gafe<0 || gafe>17)return -1;
  return m_width[garc][gafe];
}

void AcdPeds::print()const {
std::cout<<"ACD Pedestals:"<<std::endl;
  for (int garc=0;garc<12;garc++){
    for (int gafe=0;gafe<18;gafe++){
      std::cout<<garc<<" "<<gafe<<" "<<m_mean[garc][gafe]<<" "<<m_width[garc][gafe]<<std::endl;
    }
  }
}
const float* AcdPeds::pedpointer()const{
  return (float*)m_mean;
}
