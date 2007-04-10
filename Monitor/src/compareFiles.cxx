#include "compareFiles.h"
#include <iostream>
#include <fstream>

int compareFiles(const char* file1, const char* file2){
  int retval=0;
  long begin,end;
  std::ifstream f1 (file1);
  begin = f1.tellg();
  f1.seekg (0, std::ios::end);
  end = f1.tellg();
  long lf1=end-begin;
  std::ifstream f2 (file2);
  begin = f2.tellg();
  f2.seekg (0, std::ios::end);
  end = f2.tellg();
  long lf2=end-begin;
  if(lf1!=lf2)retval=1;
  f1.seekg(0,std::ios::beg);
  f2.seekg(0,std::ios::beg);
  std::string s1,s2;
  while (retval==0 &&! f1.eof()&&!f2.eof() ){
    getline (f1,s1);
    getline (f2,s2);
    if (s1!=s2){
      retval=1;
    }
  }
  f1.close();
  f2.close();
  return retval;
}
