// This class creates the objects that get the input values out of the digi/reco trees.
// Martin Kocian, SLAC, 2/1/07
// Code written for GLAST
//
// Last updated with object timestamp by user kocian on Tue Feb 27 23:48:45 2007
// Last updated with object acdLowerTileCount by user kocian on Tue Mar  6 21:10:00 2007
// Last updated with object eventid by user kocian on Tue Mar  6 22:51:00 2007
#include "merit/MonInput_eventid.h"
#include "merit/MonInput_acdLowerTileCount.h"
#include "digi/MonInput_timestamp.h"
#include "digi/MonInput_nAcd.h"
#include "MonObjFactory.h"
#include <iostream>



MonObjFactory::MonObjFactory(){;}
MonInputObject* MonObjFactory::getMonInputObject(string s){
  if(s=="nACD")
    return new MonInput_nAcd;
  if (s=="timestamp")
    return new MonInput_timestamp;
  if (s=="acdLowerTileCount")
    return new MonInput_acdLowerTileCount;
  if (s=="eventid")
    return new MonInput_eventid;
  // This line is a tag for makeNewMonObject.pl. Do not move or remove.
  else{
    std::cout<<"Object "<<s<<" does not exist"<<std::endl;
    assert(0);
  }
}
