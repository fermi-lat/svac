#ifndef TkrGeo_Header
#define TkrGeo_Header

class TkrGeo {

 public:

  enum { nTower = 16, nTray = 19, nPos = 2, nStripsPerLayer = 1535 };

  enum {bot = 0, top = 1};

  static int getTkrId(int tower, int tray, bool top) 
    {
      int pos = (top) ? 1 : 0;
      return tower*nTray*nPos + tray*nPos + pos;
    }
};

#endif
