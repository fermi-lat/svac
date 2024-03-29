#include "CalibrationDescription.h"

void CalibrationDescription::prepareFill()
{
  assert (m_db != 0);

  std::string sql("INSERT INTO CalibrationDescription VALUES(:m_id, :m_location, :m_source, TO_DATE(:m_validStartTime, :timeFormat), TO_DATE(:m_validEndTime, :timeFormat), TO_DATE(:m_runStartTime, :timeFormat), TO_DATE(:m_runEndTime, :timeFormat), TO_DATE(:m_creationTime, :timeFormat), :m_software, :m_version, :m_hardware, :m_calibType, :m_procLevel, :m_status, :m_dataSize, :m_creator, :m_description)");

  m_stmtH = m_db->prepareStatement(sql.c_str());

  m_db->bindIntVariable(m_stmtH, ":m_id", &m_id);
  m_db->bindIntVariable(m_stmtH, ":m_location", &m_location);
  m_db->bindIntVariable(m_stmtH, ":m_source", &m_source);
  m_db->bindStringVariable(m_stmtH, ":m_validStartTime", 
			   m_validStartTime.c_str());
  assert(m_oracleTimeFmt != 0);
  m_db->bindStringVariable(m_stmtH, ":timeFormat", m_oracleTimeFmt);

  // note normally string::c_str() returns pointers pointing to different
  // part of the memory, so it is critical (before calling this function) 
  // to assign the string to a fixed
  // length character string so that c_str() always point to the same
  // address in memory
  m_db->bindStringVariable(m_stmtH, ":m_validEndTime", m_validEndTime.c_str());
  m_db->bindStringVariable(m_stmtH, ":m_runStartTime", m_runStartTime.c_str());
  m_db->bindStringVariable(m_stmtH, ":m_runEndTime", m_runEndTime.c_str());
  m_db->bindStringVariable(m_stmtH, ":m_creationTime", m_creationTime.c_str());
  m_db->bindStringVariable(m_stmtH, ":m_software", m_software.c_str());
  m_db->bindStringVariable(m_stmtH, ":m_version", m_version.c_str());
  m_db->bindIntVariable(m_stmtH, ":m_hardware", &m_hardware);
  m_db->bindIntVariable(m_stmtH, ":m_calibType", &m_calibType);
  m_db->bindIntVariable(m_stmtH, ":m_procLevel", &m_procLevel);
  m_db->bindIntVariable(m_stmtH, ":m_status", &m_status);
  m_db->bindIntVariable(m_stmtH, ":m_dataSize", &m_dataSize);
  m_db->bindStringVariable(m_stmtH, ":m_creator", m_creator.c_str());
  m_db->bindStringVariable(m_stmtH, ":m_description", m_description.c_str());

}

