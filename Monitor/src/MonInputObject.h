// 
// Interface class for an input quantity for monitoring
// 
// Martin Kocian, SLAC, 2/1/07
// Software developed for GLAST

#ifndef MonInputObject_h
#define MonInputObject_h

#include <string>

class TTree;
class TObject;

class MonInputObject{
 public:
  virtual void setValue(TObject* event) =0;
  virtual void enableInputBranch (TTree& tree)=0;
  virtual int setOutputBranch (TTree* tree)=0;
  virtual std::string getInputSource()=0;
  virtual ~MonInputObject() {}
 protected:
  MonInputObject(){}
};
#endif
