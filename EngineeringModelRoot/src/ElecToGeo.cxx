#include <memory>
#include "ElecToGeo.h"
#include "NtupleDef.h"

ElecToGeo::ElecToGeo()
{
  m_tkrMap[gtcc_gtrc(5,8)] = tkrLayerView(17, 1);
  m_tkrMap[gtcc_gtrc(4,8)] = tkrLayerView(17, 1);
  m_tkrMap[gtcc_gtrc(6,8)] = tkrLayerView(17, 0);
  m_tkrMap[gtcc_gtrc(7,8)] = tkrLayerView(17, 0);
  m_tkrMap[gtcc_gtrc(2,8)] = tkrLayerView(16, 0);
  m_tkrMap[gtcc_gtrc(3,8)] = tkrLayerView(16, 0);
  m_tkrMap[gtcc_gtrc(0,8)] = tkrLayerView(16, 1);
  m_tkrMap[gtcc_gtrc(1,8)] = tkrLayerView(16, 1);
  m_tkrMap[gtcc_gtrc(5,7)] = tkrLayerView(15, 1);
  m_tkrMap[gtcc_gtrc(4,7)] = tkrLayerView(15, 1);
  m_tkrMap[gtcc_gtrc(7,7)] = tkrLayerView(15, 0);
  m_tkrMap[gtcc_gtrc(6,7)] = tkrLayerView(15, 0);
  m_tkrMap[gtcc_gtrc(3,7)] = tkrLayerView(14, 0);
  m_tkrMap[gtcc_gtrc(2,7)] = tkrLayerView(14, 0);
  m_tkrMap[gtcc_gtrc(1,7)] = tkrLayerView(14, 1);
  m_tkrMap[gtcc_gtrc(0,7)] = tkrLayerView(14, 1);
  m_tkrMap[gtcc_gtrc(4,6)] = tkrLayerView(13, 1);
  m_tkrMap[gtcc_gtrc(5,6)] = tkrLayerView(13, 1);
  m_tkrMap[gtcc_gtrc(7,6)] = tkrLayerView(13, 0);
  m_tkrMap[gtcc_gtrc(6,6)] = tkrLayerView(13, 0);
  m_tkrMap[gtcc_gtrc(2,6)] = tkrLayerView(12, 0);
  m_tkrMap[gtcc_gtrc(3,6)] = tkrLayerView(12, 0);
  m_tkrMap[gtcc_gtrc(0,6)] = tkrLayerView(12, 1);
  m_tkrMap[gtcc_gtrc(1,6)] = tkrLayerView(12, 1);
  m_tkrMap[gtcc_gtrc(4,5)] = tkrLayerView(11, 1);
  m_tkrMap[gtcc_gtrc(5,5)] = tkrLayerView(11, 1);
  m_tkrMap[gtcc_gtrc(7,5)] = tkrLayerView(11, 0);
  m_tkrMap[gtcc_gtrc(6,5)] = tkrLayerView(11, 0);
  m_tkrMap[gtcc_gtrc(2,5)] = tkrLayerView(10, 0);
  m_tkrMap[gtcc_gtrc(3,5)] = tkrLayerView(10, 0);
  m_tkrMap[gtcc_gtrc(1,5)] = tkrLayerView(10, 1);
  m_tkrMap[gtcc_gtrc(0,5)] = tkrLayerView(10, 1);
  m_tkrMap[gtcc_gtrc(4,4)] = tkrLayerView(9, 1);
  m_tkrMap[gtcc_gtrc(5,4)] = tkrLayerView(9, 1);
  m_tkrMap[gtcc_gtrc(7,4)] = tkrLayerView(9, 0);
  m_tkrMap[gtcc_gtrc(6,4)] = tkrLayerView(9, 0);
  m_tkrMap[gtcc_gtrc(2,4)] = tkrLayerView(8, 0);
  m_tkrMap[gtcc_gtrc(3,4)] = tkrLayerView(8, 0);
  m_tkrMap[gtcc_gtrc(1,4)] = tkrLayerView(8, 1);
  m_tkrMap[gtcc_gtrc(0,4)] = tkrLayerView(8, 1);
  m_tkrMap[gtcc_gtrc(4,3)] = tkrLayerView(7, 1);
  m_tkrMap[gtcc_gtrc(5,3)] = tkrLayerView(7, 1);
  m_tkrMap[gtcc_gtrc(6,3)] = tkrLayerView(7, 0);
  m_tkrMap[gtcc_gtrc(7,3)] = tkrLayerView(7, 0);
  m_tkrMap[gtcc_gtrc(2,3)] = tkrLayerView(6, 0);
  m_tkrMap[gtcc_gtrc(3,3)] = tkrLayerView(6, 0);
  m_tkrMap[gtcc_gtrc(1,3)] = tkrLayerView(6, 1);
  m_tkrMap[gtcc_gtrc(0,3)] = tkrLayerView(6, 1);
  m_tkrMap[gtcc_gtrc(4,2)] = tkrLayerView(5, 1);
  m_tkrMap[gtcc_gtrc(5,2)] = tkrLayerView(5, 1);
  m_tkrMap[gtcc_gtrc(7,2)] = tkrLayerView(5, 0);
  m_tkrMap[gtcc_gtrc(6,2)] = tkrLayerView(5, 0);
  m_tkrMap[gtcc_gtrc(2,2)] = tkrLayerView(4, 0);
  m_tkrMap[gtcc_gtrc(3,2)] = tkrLayerView(4, 0);
  m_tkrMap[gtcc_gtrc(1,2)] = tkrLayerView(4, 1);
  m_tkrMap[gtcc_gtrc(0,2)] = tkrLayerView(4, 1);
  m_tkrMap[gtcc_gtrc(4,1)] = tkrLayerView(3, 1);
  m_tkrMap[gtcc_gtrc(5,1)] = tkrLayerView(3, 1);
  m_tkrMap[gtcc_gtrc(7,1)] = tkrLayerView(3, 0);
  m_tkrMap[gtcc_gtrc(6,1)] = tkrLayerView(3, 0);
  m_tkrMap[gtcc_gtrc(3,1)] = tkrLayerView(2, 0);
  m_tkrMap[gtcc_gtrc(2,1)] = tkrLayerView(2, 0);
  m_tkrMap[gtcc_gtrc(1,1)] = tkrLayerView(2, 1);
  m_tkrMap[gtcc_gtrc(0,1)] = tkrLayerView(2, 1);
  m_tkrMap[gtcc_gtrc(4,0)] = tkrLayerView(1, 1);
  m_tkrMap[gtcc_gtrc(5,0)] = tkrLayerView(1, 1);
  m_tkrMap[gtcc_gtrc(7,0)] = tkrLayerView(1, 0);
  m_tkrMap[gtcc_gtrc(6,0)] = tkrLayerView(1, 0);
  m_tkrMap[gtcc_gtrc(2,0)] = tkrLayerView(0, 0);
  m_tkrMap[gtcc_gtrc(3,0)] = tkrLayerView(0, 0);
  m_tkrMap[gtcc_gtrc(1,0)] = tkrLayerView(0, 1);
  m_tkrMap[gtcc_gtrc(0,0)] = tkrLayerView(0, 1);
}

void ElecToGeo::decodeTkrTp(unsigned tp[g_nTower][g_nGTCC], 
			    unsigned req[g_nTower][g_nTkrLayer][g_nView][g_nEnd]) const
{
  for(int iTower = 0; iTower != g_nTower; ++iTower) {
    for(int iGTCC = 0; iGTCC != g_nGTCC; ++iGTCC) {
      if(tp[iTower][iGTCC] == 0) continue;
      for(int iGTRC = 0; iGTRC != g_nGTRC; ++iGTRC) {
	tkrLayerView x = m_tkrMap.find(gtcc_gtrc(iGTCC, iGTRC))->second;
	req[iTower][x.m_layer][x.m_view][end(iGTCC)] = ( (tp[iTower][iGTCC] >> iGTRC) & 1 ) ;
      }
    }
  }
}

void ElecToGeo::decodeCalTp(unsigned tp[g_nTower][g_nCalLayer], 
			    unsigned req[g_nTower][g_nCalLayer][g_nFace],      
			    unsigned accept[g_nTower][g_nCalLayer][g_nFace]) const
{
  for(int iTower = 0; iTower != g_nTower; ++iTower) {
    for(int iLayer = 0; iLayer != g_nCalLayer; ++iLayer) {
      if(tp[iTower][iLayer] == 0) continue;
      unsigned int diag = (tp[iTower][iLayer] >> 16);
      req[iTower][iLayer][0] = (diag >> 12) & 3;
      accept[iTower][iLayer][0] = (diag & 0x0fff);
      diag = (tp[iTower][iLayer] & 0xffff);
      req[iTower][iLayer][1] = (diag >> 12) & 3;
      accept[iTower][iLayer][1] = (diag & 0x0fff);
    }
  }
}

bool operator<(const ElecToGeo::gtcc_gtrc& x, const ElecToGeo::gtcc_gtrc& y)
{
  if(x.m_gtcc > y.m_gtcc) return 1;
  else if(x.m_gtcc < y.m_gtcc) return 0;
  else {
    if(x.m_gtrc > y.m_gtrc) return 1;
    else if(x.m_gtrc < y.m_gtrc) return 0;
    else return 0;
  }
}
