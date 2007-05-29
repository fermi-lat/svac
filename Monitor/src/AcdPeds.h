#ifndef ACDPEDS_H
#define ACDPEDS_H
class AcdPeds{
 public:
  AcdPeds();
  ~AcdPeds(){}
  void setMean(int garc, int gafe,float value);
  void setWidth(int garc, int gafe,float value);
  const float mean(int garc, int gafe) const;
  const float width(int garc, int gafe) const;
  const float* pedpointer()const;
  void print()const;
 private:
  float m_mean[12][18];
  float m_width[12][18];
};

  
#endif
