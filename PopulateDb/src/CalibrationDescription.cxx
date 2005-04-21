#include "CalibrationDescription.h"

void CalibrationDescription::prepareFill()
{
  assert (m_db != 0);

  std::string sql("INSERT INTO CalibrationDescription VALUES(:m_calDesId, :m_location, :m_source, TO_DATE(:m_validStartTime, :timeFormat), TO_DATE(:m_validEndTime, :timeFormat), TO_DATE(:m_creationTime, :timeFormat), :m_orbitPos, :m_temperature, :m_humidity, :m_hardware, :m_calibType, :m_procLevel, :m_status, :m_dataSize, :m_creator, :m_description)");

  m_stmtH = m_db->prepareStatement(sql.c_str());

  m_db->bindIntVariable(m_stmtH, ":m_calDesId", &m_calDesId);
  m_db->bindIntVariable(m_stmtH, ":m_location", &m_location);
  m_db->bindIntVariable(m_stmtH, ":m_source", &m_source);
  m_db->bindStringVariable(m_stmtH, ":m_validStartTime", 
			   m_validStartTime.c_str());
  assert(m_oracleTimeFmt != 0);
  m_db->bindStringVariable(m_stmtH, ":timeFormat", m_oracleTimeFmt);
  m_db->bindStringVariable(m_stmtH, ":m_validEndTime", m_validEndTime.c_str());
  m_db->bindStringVariable(m_stmtH, ":m_creationTime", m_creationTime.c_str());
  m_db->bindFloatVariable(m_stmtH, ":m_orbitPos", &m_orbitPos);
  m_db->bindFloatVariable(m_stmtH, ":m_temperature", &m_temperature);
  m_db->bindFloatVariable(m_stmtH, ":m_humidity", &m_humidity);
  m_db->bindIntVariable(m_stmtH, ":m_hardware", &m_hardware);
  m_db->bindIntVariable(m_stmtH, ":m_calibType", &m_calibType);
  m_db->bindIntVariable(m_stmtH, ":m_procLevel", &m_procLevel);
  m_db->bindIntVariable(m_stmtH, ":m_status", &m_status);
  m_db->bindIntVariable(m_stmtH, ":m_dataSize", &m_dataSize);
  m_db->bindStringVariable(m_stmtH, ":m_creator", m_creator.c_str());
  m_db->bindStringVariable(m_stmtH, ":m_description", m_description.c_str());

}

