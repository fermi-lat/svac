#include "ExtractDb.h"

using std::cout;
using std::endl;

int main(int argc, char** argv)
{
  std::string optionFileName;
  if(argc == 1) {
    optionFileName = "../src/Option.dat";
  }
  else {
    optionFileName = argv[1];
  }

  ExtractDb e;
  e.parseOptionFile(optionFileName.c_str());
  e.makeRootTree();
  e.fillRootTree();
}
