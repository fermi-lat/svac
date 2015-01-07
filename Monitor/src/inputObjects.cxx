#include "MonObjFactory.h"
#include "TestReport.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <map>

int main(){
  std::string html="InputObjects.html";
  TestReport r(html.c_str());
  r.newheadline("Input Objects");
  char* inptable[]={"Name","Source","Description"};
  MonObjFactory f;
  std::map<std::string,std::map<std::string, std::string> > desc;
  desc=f.getDescriptions();
  char* line[3];
  for (int j=0;j<3;j++)line[j]=new char[512];
  r.starttable(inptable,3);
  for (std::map<std::string,std::map<std::string,std::string> >::iterator itr=desc.begin();
       itr != desc.end();itr++){
    strcpy(line[0],itr->first.c_str());
    strcpy(line[1],(itr->second["Source"]).c_str());
    strcpy(line[2],(itr->second["Description"]).c_str());
    r.addtableline(line,3);
  }
  r.endtable(); 
  r.writereport();
}
