#include <iostream>
#include <fstream>
#include <string>
#include "RootAnalyzer.h"

// If there is no argument, use AnalyzerOption.dat as input, otherwise use 
// first argument as the input

int main(int argc, char** argv)
{
  std::string optionFileName;
  if(argc == 1) {
    optionFileName = "../src/AnalyzerOption.dat";
  }
  else {
    optionFileName = argv[1];
  }
  std::ifstream optionFile(optionFileName.c_str());
  std::string mcRootFile, reconRootFile, digiRootFile, raFile, histFile;
  optionFile >> mcRootFile >> digiRootFile >> reconRootFile >> raFile
	     >> histFile;

  RootAnalyzer analyzer(raFile.c_str(), histFile.c_str());

  std::cout << "Process " << mcRootFile << std::endl;
  std::cout << "Process " << digiRootFile << std::endl;
  std::cout << "Process " << reconRootFile << std::endl;
  std::cout << "Output " << raFile << std::endl;
  std::cout << "Output " << histFile << std::endl;

  analyzer.analyzeTrees(mcRootFile.c_str(), digiRootFile.c_str(), 
			reconRootFile.c_str());

}

