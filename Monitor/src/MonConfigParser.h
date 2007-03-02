#ifndef MonConfigParser_h
#define MonConfigParser_h

#include <string>
#include <list>
#include <map>

class MonConfigParser{
 public:
  MonConfigParser(const char* filename);
  std::list<std::string>& getInputList();
  std::list<std::map<std::string,std::string> >& getOutputList();
  std::string& getEventCut();
  std::string& getTimeStamp();
 private:
  std::list<std::string> m_inlist;
  std::list<std::map<std::string,std::string> > m_outlist;
  std::string m_eventcut;
  std::string m_timestamp;
};

#endif
   
