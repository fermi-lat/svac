#ifndef TkrDeadChannel_Header
#define TkrDeadChannel_Header

#include "OracleTable.h"

struct TkrDeadChannel : public OracleTable{

  long m_tkrDeadChId; // is a oracle sequence number
  long m_tkrIndexId; 
  int m_strip;
  float m_avgCount;

  TkrDeadChannel(OCIWrapper* db=0) : OracleTable(db) { }

  virtual void prepareFill();

};

#endif
