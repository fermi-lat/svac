#include <string>
#include <fstream>
#include <getopt.h>
#include "findGaps.h"

int main(int argn, char** argv)
{
  std::string digiRootFile, gapsFileName, optionFileName;
  std::string digiRootFile_def, gapsFileName_def;
  int opt;
 
  while ( (opt = getopt(argn, argv, "o:d:g:")) != EOF ) {
    switch (opt) {
      case 'o':   // Option file name
        optionFileName = string(optarg);
        break;
      case 'd':   // digi file name      
        digiRootFile = string(optarg);
        break;
      case 'g':   // gaps output file name      
        gapsFileName = string(optarg);
        break;
    } 
  }

  if ( argn - optind > 0 ) {
    cout << "findGaps only takes options, not bare arguments; using default settings." << endl;
  }
  
  if (optionFileName == "") optionFileName = "../src/findGapsOption.dat";
  std::ifstream optionFile(optionFileName.c_str());
  optionFile >> digiRootFile_def >> gapsFileName_def ;

  if (digiRootFile == "") digiRootFile = digiRootFile_def;
  if (gapsFileName == "") gapsFileName = gapsFileName_def;

  findGaps g;
  g.analyzeDigi(digiRootFile.c_str(),gapsFileName.c_str());
}

