#include "CalIndex.h"

void CalIndex::prepareFill()
{
  assert (m_db != 0);

  std::string sql("INSERT INTO CALIndex VALUES(:m_id, :m_calDesId, :m_calInstId)");

  m_stmtH = m_db->prepareStatement(sql.c_str());

  m_db->bindIntVariable(m_stmtH, ":m_id", &m_id);
  m_db->bindIntVariable(m_stmtH, ":m_calDesId", &m_calDesId);
  m_db->bindIntVariable(m_stmtH, ":m_calInstId", &m_calInstId);
}
