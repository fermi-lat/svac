#include "CalPeds.h"
#include <iostream>

CalPeds::CalPeds(){
  for (int tower=0;tower<16;tower++){
    for (int layer=0;layer<8;layer++){
      for (int column=0;column<12;column++){
	for (int end=0;end<2;end++){
	  for (int range=0;range<4;range++){
	    m_mean[tower][layer][column][end][range]=0;
	    m_width[tower][layer][column][end][range]=0;
	  }
	}
      }
    }
  }
}
void CalPeds::setMean(int tower, int layer, int column, int end,int range, float value){
  if (tower<0 || tower>15)return;
  if (layer<0 || layer>7)return;
  if (column<0 || column>11)return;
  if (end<0 || end>1)return;
  if (range<0 || range>3)return;
  m_mean[tower][layer][column][end][range]=value;
}
void CalPeds::setWidth(int tower, int layer, int column, int end, int range, float value){
  if (tower<0 || tower>15)return;
  if (layer<0 || layer>7)return;
  if (column<0 || column>11)return;
  if (end<0 || end>1)return;
  if (range<0 || range>3)return;
  m_width[tower][layer][column][end][range]=value;
}
const float CalPeds::mean(int tower, int layer, int column, int end, int range) const{
  if (tower<0 || tower>15)return -1;
  if (layer<0 || layer>7)return -1;
  if (column<0 || column>11)return -1;
  if (end<0 || end>1)return -1;
  if (range<0 || range>3)return -1;
  return m_mean[tower][layer][column][end][range];
}
const float CalPeds::width(int tower, int layer, int column, int end, int range) const{
  if (tower<0 || tower>15)return -1;
  if (layer<0 || layer>7)return -1;
  if (column<0 || column>11)return -1;
  if (end<0 || end>1)return -1;
  if (range<0 || range>3)return -1;
  return m_width[tower][layer][column][end][range];
}

void CalPeds::print()const {
std::cout<<"CAL Pedestals:"<<std::endl;
  for (int tower=0;tower<16;tower++){
    for (int layer=0;layer<8;layer++){
      for (int column=0;column<12;column++){
	for (int end=0;end<2;end++){
	  for (int range=0;range<4;range++){
	    std::cout<<tower<<" "<<layer<<" "<<column<<" "<<end<<" "<<range<<" "<<m_mean[tower][layer][column][end][range]<<" "<<m_width[tower][layer][column][end][range]<<std::endl;
	  }
	}
      }
    }
  }
}
const float* CalPeds::pedpointer()const{
  return (float*)m_mean;
}
