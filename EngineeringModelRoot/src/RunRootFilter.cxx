#include <fstream>
#include <iostream>
#include "RootFilter.h"

// If there is no argument, use FilterOption.dat as input, otherwise use first
// argument as the input

int main(int argc, char** argv)
{
  RootFilter filter;
  filter.filterDigiFile("/nfs/farm/g/glast/u03/EM2003/rootFiles/v3r3p2/vdg/ebf031007174453_digi.root", "selEvents.dat");
}
