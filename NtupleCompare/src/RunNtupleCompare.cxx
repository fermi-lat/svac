#include <string>
#include "NtupleCompare.h"

int main(int argc, char** argv)
{
  std::string optionFileName;
  if(argc == 1) {
    optionFileName = "../src/ReportOption.dat";
  }
  else {
    optionFileName = argv[1];
  }

  NtupleCompare nC;
  nC.parseOptionFile(optionFileName.c_str());
  nC.compareVariables();
  nC.generateReport();
}
