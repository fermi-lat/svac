#ifndef NtupleDef_Class
#define NtupleDef_Class

#include <iostream>

struct NtupleDef {

  unsigned int m_time;

  enum {MAXLEN=100};
  char m_name[MAXLEN];

  double m_value;

  void print() const 
  {
    std::cout << "time = " << m_time << " name = " << m_name << " value = "
	      << m_value << std::endl;
  }
};

#endif
