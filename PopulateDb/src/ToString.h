#ifndef ToString_Header
#define ToString_Header

#include <sstream>
#include <string>

template<class X> std::string ToString(X data)
{
  std::stringstream stream;
  stream << data;
  return stream.str();
}

#endif
