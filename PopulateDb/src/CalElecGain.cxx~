#include "CalLightAsy.h"

void CalLightAsy::prepareFill()
{
  assert (m_db != 0);

  std::string sql("INSERT INTO CALLightAsymmetry VALUES(:m_id, :m_calIndexId, :m_face, :m_range, :m_slope)");

  m_stmtH = m_db->prepareStatement(sql.c_str());

  m_db->bindIntVariable(m_stmtH, ":m_id", &m_id);
  m_db->bindIntVariable(m_stmtH, ":m_calIndexId", &m_calIndexId);
  m_db->bindIntVariable(m_stmtH, ":m_face", &m_face);
  m_db->bindIntVariable(m_stmtH, ":m_range", &m_range);
  m_db->bindFloatVariable(m_stmtH, ":m_slope", &m_slope);
}
