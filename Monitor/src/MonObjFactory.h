// This class creates the objects that get the input values out of the digi/reco trees.
// Martin Kocian, SLAC, 2/1/07
// Code written for GLAST
//
#ifndef MonObjFactory_h
#define MonObjFactory_h

#include <string>
#include <vector>
#include <map>
#include "MonInputObject.h"
using std::string;

class MonObjFactory{
 public:
  MonObjFactory();
  MonInputObject* getMonInputObject(string s);
  const std::map<std::string, std::map<std::string, std::string> > getDescriptions();
};

#endif
