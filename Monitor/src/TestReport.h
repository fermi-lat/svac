// class to write test reports similar to python online reports
// M. Kocian,SLAC, 9/20/06
//
#include <fstream>

class TestReport{
 public:
  TestReport(const char* filename);
  void newheadline(const char*);
  void additem(const char*,const char*);
  void addlink(const char*,const char*,const char*);
  void addstatus(const char*);
  void starttable( char*[],int);
  void addtableline(char*[],int);
  void endtable();
  void writereport();  
  void greentext(char* , const char*);
  void redtext(char* , const char*);
  void linktext(char*, const char*, const char*);
 private:
  std::ofstream of;
};
