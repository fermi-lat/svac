#include "TkrTot.h"

void TkrTot::prepareFill()
{
  assert (m_db != 0);

  std::string sql("INSERT INTO TKRTimeOverThreshold VALUES(Seq_TkrTotID.NextVal, :m_tkrIndexId, :m_strip, :m_p0, :m_p1, :m_p2, :m_chi2)");

  m_stmtH = m_db->prepareStatement(sql.c_str());

  //  m_db->bindIntVariable(m_stmtH, ":m_id", &m_id);
  m_db->bindIntVariable(m_stmtH, ":m_tkrIndexId", &m_tkrIndexId);
  m_db->bindIntVariable(m_stmtH, ":m_strip", &m_strip);
  m_db->bindFloatVariable(m_stmtH, ":m_p0", &m_p0);
  m_db->bindFloatVariable(m_stmtH, ":m_p1", &m_p1);
  m_db->bindFloatVariable(m_stmtH, ":m_p2", &m_p2);
  m_db->bindFloatVariable(m_stmtH, ":m_chi2", &m_chi2);
}
