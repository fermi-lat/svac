#include "TkrNoisyChannel.h"

void TkrNoisyChannel::prepareFill()
{
  assert (m_db != 0);

  std::string sql("INSERT INTO TKRNoisyChannel VALUES(:m_tkrNoisyChId, :m_tkrIndexId, :m_strip, :m_avgCount)");

  m_stmtH = m_db->prepareStatement(sql.c_str());

  m_db->bindIntVariable(m_stmtH, ":m_tkrNoisyChId", &m_tkrNoisyChId);
  m_db->bindIntVariable(m_stmtH, ":m_tkrIndexId", &m_tkrIndexId);
  m_db->bindIntVariable(m_stmtH, ":m_strip", &m_strip);
  m_db->bindFloatVariable(m_stmtH, ":m_avgCount", &m_avgCount);
}
