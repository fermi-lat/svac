#ifndef GeoToElec_Class
#define GeoToElec_Class

#include <stdexcept>
#include <iostream>
#include <map>
#include "GeoConstants.h"

// this class contains mapping from physical geometry space to electronic space(CC, RC) 

class InvalidTkrLayerViewEnd : public std::exception {
 public:
  virtual const char* what() 
    { return "invalid tkr layer, view, end!"; }
};

class GeoToElec {
 public:
  struct gtcc_gtrc {
    gtcc_gtrc(int gtcc=-9999, int gtrc=-9999) : m_gtcc(gtcc), m_gtrc(gtrc) { }
    int m_gtcc;  
    int m_gtrc;
  };

  struct tkrLayerViewEnd {
    tkrLayerViewEnd(int layer=-9999, int view=-9999, int end=-9999) : m_layer(layer), m_view(view), m_end(end) { }
    int m_layer;  // biLayer number, 0 is at the bottom
    int m_view;  // 0 means measure X, 1 means measure Y
    int m_end;  // 0 means low end, 1 means high end
  };

 public:
  static const GeoToElec* getInstance();

  // return the gtcc and gtrc  corresponding to input layer and view, layer 0 is at the bottom
  gtcc_gtrc getGtccGtrc(int layer, int view, int end) const;

 private:

  GeoToElec();
  GeoToElec(const GeoToElec&);

  std::map<tkrLayerViewEnd, gtcc_gtrc> m_tkrMap;

};

inline const GeoToElec* GeoToElec::getInstance()
{
  static GeoToElec sig;
  return &sig;
}


#endif
