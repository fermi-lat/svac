#ifndef CALPEDS_H
#define CALPEDS_H
class CalPeds{
 public:
  CalPeds();
  ~CalPeds(){}
  void setMean(int tower, int layer, int column, int end, int range, float value);
  void setWidth(int tower, int layer, int column, int end, int range, float value);
  const float mean(int tower, int layer, int column, int end, int range) const;
  const float width(int tower, int layer, int column, int end, int range) const;
  const float* pedpointer()const;
  void print()const;
 private:
  float m_mean[16][8][12][2][4];
  float m_width[16][8][12][2][4];
};

  
#endif
