#ifndef CalGeo_XinChen
#define CalGeo_XinChen

class CalGeo {

 public:

  enum { nTower = 16, nCol = 8, nLayer = 12, nRange = 4, nFace = 2 };

  static int getCalId(int tower, int layer, int col) 
    {
      return tower*nCol*nLayer + layer*nCol + col;
    }
};

#endif
