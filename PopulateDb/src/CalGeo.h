#ifndef CalGeo_XinChen
#define CalGeo_XinChen

class CalGeo {

 public:

  enum { nTower = 16, nCol = 12, nLayer = 8, nRange = 4, nFace = 2 };

  static int getCalId(int tower, int layer, int col) 
    {
      return tower*nCol*nLayer + layer*nCol + col;
    }
};

#endif
