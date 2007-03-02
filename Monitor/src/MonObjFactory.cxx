// This class creates the objects that get the input values out of the digi/reco trees.
// Martin Kocian, SLAC, 2/1/07
// Code written for GLAST
//
// Last updated with object timestamp by user kocian on Tue Feb 27 23:48:45 2007
#include "MonInput_timestamp.h"
#include "MonInput_nAcd.h"
#include "MonObjFactory.h"
#include <iostream>



MonObjFactory::MonObjFactory(){;}
MonInputObject* MonObjFactory::getMonInputObject(string s){
  if(s=="nACD")
    return new MonInput_nAcd;
  if (s=="timestamp")
    return new MonInput_timestamp;
  // This line is a tag for makeNewMonObject.pl. Do not move or remove.
  else{
    std::cout<<"Object "<<s<<" does not exist"<<std::endl;
    assert(0);
  }
}
