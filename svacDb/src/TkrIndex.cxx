#include "TkrIndex.h"

void TkrIndex::prepareFill()
{
  assert (m_db != 0);

  std::string sql("INSERT INTO TKRIndex VALUES(:m_id, :m_calDesId, :m_tkrInstId)");

  m_stmtH = m_db->prepareStatement(sql.c_str());

  m_db->bindIntVariable(m_stmtH, ":m_id", &m_id);
  m_db->bindIntVariable(m_stmtH, ":m_calDesId", &m_calDesId);
  m_db->bindIntVariable(m_stmtH, ":m_tkrInstId", &m_tkrInstId);
}
