#include "TkrDeadChannel.h"

void TkrDeadChannel::prepareFill()
{
  assert (m_db != 0);

  std::string sql("INSERT INTO TKRDeadChannel VALUES(:m_tkrDeadChId, :m_tkrIndexId, :m_strip, :m_avgCount)");

  m_stmtH = m_db->prepareStatement(sql.c_str());

  m_db->bindIntVariable(m_stmtH, ":m_tkrDeadChId", &m_tkrDeadChId);
  m_db->bindIntVariable(m_stmtH, ":m_tkrIndexId", &m_tkrIndexId);
  m_db->bindIntVariable(m_stmtH, ":m_strip", &m_strip);
  m_db->bindFloatVariable(m_stmtH, ":m_avgCount", &m_avgCount);
}
