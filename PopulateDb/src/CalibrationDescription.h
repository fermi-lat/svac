#ifndef CalibrationDescription_Header
#define CalibrationDescription_Header

#include <string>
#include "OracleTable.h"

struct CalibrationDescription : public OracleTable {
  long m_id; 
  int m_location;
  int m_source;
  std::string m_validStartTime;
  std::string m_validEndTime; 
  std::string m_creationTime;
  float m_orbitPos;
  float m_temperature;
  float m_humidity;
  int m_hardware;
  int m_calibType;
  int m_procLevel;
  int m_status;
  long m_dataSize;
  std::string m_creator;
  std::string m_description;

  CalibrationDescription(OCIWrapper* db=0) : OracleTable(db) { }

  virtual void prepareFill();

};

#endif
