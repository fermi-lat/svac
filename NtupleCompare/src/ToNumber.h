#ifndef ToNumber_Function
#define ToNumber_Function

#include <sstream>
#include <string>

inline double ToDouble(const std::string& s)
{
  std::istringstream stream(s);
  double temp;
  stream >> temp;
  return temp;
}

inline int ToInt(const std::string& s)
{
  std::istringstream stream(s);
  int temp;
  stream >> temp;
  return temp;
}

#endif
