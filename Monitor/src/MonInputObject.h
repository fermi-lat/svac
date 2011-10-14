// 
// Base class for an input quantity for monitoring
// 
// Martin Kocian, SLAC, 2/1/07
// Software developed for GLAST

#ifndef MonInputObject_h
#define MonInputObject_h

#include <string>
#include <ctime>

class TTree;
class TObject;

class MonInputObject{
 public:
  virtual void setValue(TObject* event) =0;
  void setValueProf(TObject* event);
  float timeProfile();
  virtual void enableInputBranch (TTree& tree)=0;
  virtual int setOutputBranch (TTree* tree)=0;
  virtual std::string getInputSource()=0;
  virtual std::string getDescription()=0;
  virtual ~MonInputObject() {}
 protected:
  MonInputObject():m_timeprof(0){}
  std::string m_name;
  unsigned long long m_timeprof;
};
#endif
