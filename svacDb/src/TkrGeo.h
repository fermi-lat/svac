#ifndef TkrGeo_Header
#define TkrGeo_Header

class TkrGeo {

 public:

  enum { nTower = 16, nTray = 19, nPos = 2, nStripsPerLayer = 1535 };

  static int getTkrId(int tower, int tray, int pos) 
    {
      return tower*nTray*nPos + tray*nPos + pos;
    }
};

#endif
