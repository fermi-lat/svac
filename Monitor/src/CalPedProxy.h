/** @class CalPedProxy
    @author M. Kocian

    A DB proxy class for CalPeds to be used with runstrip_t

    $Id$
*/
#ifndef CALPEDPROXY_H
#define CALPEDPROXY_H
#include "facilities/Timestamp.h"
#include "CalPeds.h"

using facilities::Timestamp;

class CalPedProxy{
 public:
  static const CalPeds* getCalPeds(unsigned int timestamp);
 protected:
  static CalPeds* m_thepeds;
  static Timestamp* m_startvalidity;
  static Timestamp* m_endvalidity;
};
    
  
#endif
