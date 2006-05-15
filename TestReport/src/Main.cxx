#include <string>
#include <fstream>
#include "TestReport.h"

int main(int argc, char** argv)
{
  std::string optionFileName;
  if(argc == 1) {
    optionFileName = "../src/ReportOption.dat";
  }
  else {
    optionFileName = argv[1];
  }
  std::ifstream optionFile(optionFileName.c_str());

  std::string digiRootFile, reconRootFile, reportDir, prefix;

  optionFile >> digiRootFile >> reconRootFile >> reportDir >> prefix;

  TestReport r(reportDir.c_str(), prefix.c_str());
  r.analyzeTrees(0, digiRootFile.c_str(), reconRootFile.c_str());
  r.generateReport();
}

