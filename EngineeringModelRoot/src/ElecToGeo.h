#ifndef ElecToGeo_Class
#define ElecToGeo_Class

#include <map>

// this class contains mapping from electronic space(CC, RC) to physical geometry space


class ElecToGeo {
 private:
  struct gtcc_gtrc {
    gtcc_gtrc(int gtcc, int gtrc) : m_gtcc(gtcc), m_gtrc(gtrc) { }
    int m_gtcc;  
    int m_gtrc;
  };

  friend bool operator<(const gtcc_gtrc& x, const gtcc_gtrc& y);

  struct tkrLayerView {
    tkrLayerView(int layer=-9999, int view=-9999) : m_layer(layer), m_view(view) { }
    int m_layer;  // biLayer number, 0 is at the bottom
    int m_view;  // 0 means measure X, 1 means measure Y
  };

 public:
  static const ElecToGeo* getInstance();

  // return 0 means the input gtcc reads the si strips with smaller id
  // return 1 means the input gtcc reads the si strips with larger id
  int end(int gtcc) const;

  // return the si biLayer corresponding to input gtcc and gtrc, layer 0 is at the bottom
  int tkrSiLayer(int gtcc, int gtrc) const
    { return m_tkrMap.find(gtcc_gtrc(gtcc, gtrc))->second.m_layer; }

  // input an array tp (layout in ebf) which contains trigger primitive for the tracker, output a two dimension array indicating which layer sends trigger request.
  // e.g.: req[0][3][0][0]=1 means lower half of tower 0, layer X3 sends the trigger request
  // e.g.: req[0][3][1][1]=1 means upper half of tower 0, layer Y3 sends the trigger request
  // layer 0 is at the bottom
  void decodeTkrTp(unsigned tp[16][8], unsigned req[16][18][2][2], int iTower) const;

  // input an array tp (layout in ebf) which contains trigger primitive for the calorimeter, output a two dimension array in detector space.
  // e.g.: req[0][3][0] contains 16 bit diagnostic data for tower 0, layer 3, negative end 
  // e.g.: req[0][3][1] contains 16 bit diagnostic data for tower 0, layer 3, positive end 
  // layer 0 is at the top (different to the tracker)
  void decodeCalTp(unsigned tp[16][8], unsigned req[16][8][2], int iTower) const;


 private:

  ElecToGeo();
  ElecToGeo(const ElecToGeo&);

  std::map<gtcc_gtrc, tkrLayerView> m_tkrMap;

};

inline const ElecToGeo* ElecToGeo::getInstance()
{
  static ElecToGeo sig;
  return &sig;
}

inline int ElecToGeo::end(int gtcc) const 
{
  if(gtcc== 0 || gtcc==3 || gtcc==5 || gtcc==6) return 0;
  else return 1;
}

#endif
