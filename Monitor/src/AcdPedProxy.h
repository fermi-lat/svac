/** @class AcdPedProxy
    @author M. Kocian

    A DB proxy class for AcdPeds to be used with runstrip_t

    $Id$
*/
#ifndef ACDPEDPROXY_H
#define ACDPEDPROXY_H
#include "facilities/Timestamp.h"
#include "AcdPeds.h"

using facilities::Timestamp;

class AcdPedProxy{
 public:
  static const AcdPeds* getAcdPeds(unsigned int timestamp);
 protected:
  static AcdPeds* m_thepeds;
  static Timestamp* m_startvalidity;
  static Timestamp* m_endvalidity;
};
    
  
#endif
