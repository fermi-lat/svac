#include <memory>
#include "GeoToElec.h"
#include "NtupleDef.h"

using std::map;

GeoToElec::GeoToElec()
{
  // real mapping info
  m_tkrMap[tkrLayerViewEnd(17, 1, 0)] = gtcc_gtrc(5, 8);
  m_tkrMap[tkrLayerViewEnd(17, 1, 1)] = gtcc_gtrc(4, 8);
  m_tkrMap[tkrLayerViewEnd(17, 0, 0)] = gtcc_gtrc(6, 8);
  m_tkrMap[tkrLayerViewEnd(17, 0, 1)] = gtcc_gtrc(7, 8);
  m_tkrMap[tkrLayerViewEnd(16, 0, 0)] = gtcc_gtrc(3, 8);
  m_tkrMap[tkrLayerViewEnd(16, 0, 1)] = gtcc_gtrc(2, 8);
  m_tkrMap[tkrLayerViewEnd(16, 1, 0)] = gtcc_gtrc(0, 8);
  m_tkrMap[tkrLayerViewEnd(16, 1, 1)] = gtcc_gtrc(1, 8);
  m_tkrMap[tkrLayerViewEnd(15, 1, 0)] = gtcc_gtrc(5, 7);
  m_tkrMap[tkrLayerViewEnd(15, 1, 1)] = gtcc_gtrc(4, 7);
  m_tkrMap[tkrLayerViewEnd(15, 0, 0)] = gtcc_gtrc(6, 7);
  m_tkrMap[tkrLayerViewEnd(15, 0, 1)] = gtcc_gtrc(7, 7);
  m_tkrMap[tkrLayerViewEnd(14, 0, 0)] = gtcc_gtrc(3, 7);
  m_tkrMap[tkrLayerViewEnd(14, 0, 1)] = gtcc_gtrc(2, 7);
  m_tkrMap[tkrLayerViewEnd(14, 1, 0)] = gtcc_gtrc(0, 7);
  m_tkrMap[tkrLayerViewEnd(14, 1, 1)] = gtcc_gtrc(1, 7);
  m_tkrMap[tkrLayerViewEnd(13, 1, 0)] = gtcc_gtrc(5, 6);
  m_tkrMap[tkrLayerViewEnd(13, 1, 1)] = gtcc_gtrc(4, 6);
  m_tkrMap[tkrLayerViewEnd(13, 0, 0)] = gtcc_gtrc(6, 6);
  m_tkrMap[tkrLayerViewEnd(13, 0, 1)] = gtcc_gtrc(7, 6);
  m_tkrMap[tkrLayerViewEnd(12, 0, 0)] = gtcc_gtrc(3, 6);
  m_tkrMap[tkrLayerViewEnd(12, 0, 1)] = gtcc_gtrc(2, 6);
  m_tkrMap[tkrLayerViewEnd(12, 1, 0)] = gtcc_gtrc(0, 6);
  m_tkrMap[tkrLayerViewEnd(12, 1, 1)] = gtcc_gtrc(1, 6);
  m_tkrMap[tkrLayerViewEnd(11, 1, 0)] = gtcc_gtrc(5, 5);
  m_tkrMap[tkrLayerViewEnd(11, 1, 1)] = gtcc_gtrc(4, 5);
  m_tkrMap[tkrLayerViewEnd(11, 0, 0)] = gtcc_gtrc(6, 5);
  m_tkrMap[tkrLayerViewEnd(11, 0, 1)] = gtcc_gtrc(7, 5);
  m_tkrMap[tkrLayerViewEnd(10, 0, 0)] = gtcc_gtrc(3, 5);
  m_tkrMap[tkrLayerViewEnd(10, 0, 1)] = gtcc_gtrc(2, 5);
  m_tkrMap[tkrLayerViewEnd(10, 1, 0)] = gtcc_gtrc(0, 5);
  m_tkrMap[tkrLayerViewEnd(10, 1, 1)] = gtcc_gtrc(1, 5);
  m_tkrMap[tkrLayerViewEnd(9, 1, 0)] = gtcc_gtrc(5, 4);
  m_tkrMap[tkrLayerViewEnd(9, 1, 1)] = gtcc_gtrc(4, 4);
  m_tkrMap[tkrLayerViewEnd(9, 0, 0)] = gtcc_gtrc(6, 4);
  m_tkrMap[tkrLayerViewEnd(9, 0, 1)] = gtcc_gtrc(7, 4);
  m_tkrMap[tkrLayerViewEnd(8, 0, 0)] = gtcc_gtrc(3, 4);
  m_tkrMap[tkrLayerViewEnd(8, 0, 1)] = gtcc_gtrc(2, 4);
  m_tkrMap[tkrLayerViewEnd(8, 1, 0)] = gtcc_gtrc(0, 4);
  m_tkrMap[tkrLayerViewEnd(8, 1, 1)] = gtcc_gtrc(1, 4);
  m_tkrMap[tkrLayerViewEnd(7, 1, 0)] = gtcc_gtrc(5, 3);
  m_tkrMap[tkrLayerViewEnd(7, 1, 1)] = gtcc_gtrc(4, 3);
  m_tkrMap[tkrLayerViewEnd(7, 0, 0)] = gtcc_gtrc(6, 3);
  m_tkrMap[tkrLayerViewEnd(7, 0, 1)] = gtcc_gtrc(7, 3);
  m_tkrMap[tkrLayerViewEnd(6, 0, 0)] = gtcc_gtrc(3, 3);
  m_tkrMap[tkrLayerViewEnd(6, 0, 1)] = gtcc_gtrc(2, 3);
  m_tkrMap[tkrLayerViewEnd(6, 1, 0)] = gtcc_gtrc(0, 3);
  m_tkrMap[tkrLayerViewEnd(6, 1, 1)] = gtcc_gtrc(1, 3);
  m_tkrMap[tkrLayerViewEnd(5, 1, 0)] = gtcc_gtrc(5, 2);
  m_tkrMap[tkrLayerViewEnd(5, 1, 1)] = gtcc_gtrc(4, 2);
  m_tkrMap[tkrLayerViewEnd(5, 0, 0)] = gtcc_gtrc(6, 2);
  m_tkrMap[tkrLayerViewEnd(5, 0, 1)] = gtcc_gtrc(7, 2);
  m_tkrMap[tkrLayerViewEnd(4, 0, 0)] = gtcc_gtrc(3, 2);
  m_tkrMap[tkrLayerViewEnd(4, 0, 1)] = gtcc_gtrc(2, 2);
  m_tkrMap[tkrLayerViewEnd(4, 1, 0)] = gtcc_gtrc(0, 2);
  m_tkrMap[tkrLayerViewEnd(4, 1, 1)] = gtcc_gtrc(1, 2);
  m_tkrMap[tkrLayerViewEnd(3, 1, 0)] = gtcc_gtrc(5, 1);
  m_tkrMap[tkrLayerViewEnd(3, 1, 1)] = gtcc_gtrc(4, 1);
  m_tkrMap[tkrLayerViewEnd(3, 0, 0)] = gtcc_gtrc(6, 1);
  m_tkrMap[tkrLayerViewEnd(3, 0, 1)] = gtcc_gtrc(7, 1);
  m_tkrMap[tkrLayerViewEnd(2, 0, 0)] = gtcc_gtrc(3, 1);
  m_tkrMap[tkrLayerViewEnd(2, 0, 1)] = gtcc_gtrc(2, 1);
  m_tkrMap[tkrLayerViewEnd(2, 1, 0)] = gtcc_gtrc(0, 1);
  m_tkrMap[tkrLayerViewEnd(2, 1, 1)] = gtcc_gtrc(1, 1);
  m_tkrMap[tkrLayerViewEnd(1, 1, 0)] = gtcc_gtrc(5, 0);
  m_tkrMap[tkrLayerViewEnd(1, 1, 1)] = gtcc_gtrc(4, 0);
  m_tkrMap[tkrLayerViewEnd(1, 0, 0)] = gtcc_gtrc(6, 0);
  m_tkrMap[tkrLayerViewEnd(1, 0, 1)] = gtcc_gtrc(7, 0);
  m_tkrMap[tkrLayerViewEnd(0, 0, 0)] = gtcc_gtrc(3, 0);
  m_tkrMap[tkrLayerViewEnd(0, 0, 1)] = gtcc_gtrc(2, 0);
  m_tkrMap[tkrLayerViewEnd(0, 1, 0)] = gtcc_gtrc(0, 0);
  m_tkrMap[tkrLayerViewEnd(0, 1, 1)] = gtcc_gtrc(1, 0);
}


bool operator<(const GeoToElec::tkrLayerViewEnd& x, const GeoToElec::tkrLayerViewEnd& y)
{
  if(x.m_layer > y.m_layer) return 1;
  else if(x.m_layer < y.m_layer) return 0;
  else {
    if(x.m_view > y.m_view) return 1;
    else if(x.m_view < y.m_view) return 0;
    else {
      if(x.m_end > y.m_end) return 1;
      else if(x.m_end < y.m_end) return 0;
    }
  }
  return 0;
}

GeoToElec::gtcc_gtrc GeoToElec::getGtccGtrc(int layer, int view, int end) const
{  
  map<tkrLayerViewEnd, gtcc_gtrc>::const_iterator p = m_tkrMap.find(tkrLayerViewEnd(layer, view, end));

  if(p == m_tkrMap.end()) throw InvalidTkrLayerViewEnd();
  return p->second; 
}
