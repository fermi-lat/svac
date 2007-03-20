// Base class to allow time stamps of different types
#ifndef Timestamp_h
#define Timestamp_h

class Timestamp{
 public:
  Timestamp(){}
  virtual ULong64_t value()=0;
};

// Now the concrete implementations:

class Timestamp_Short_t:public Timestamp{
  
 public:
  Timestamp_Short_t(Short_t* ts):m_timestamp(ts){};
  ULong64_t value(){
    return (ULong64_t)*m_timestamp;
  }
 private:
  Short_t* m_timestamp;
};

class Timestamp_UShort_t:public Timestamp{
  
 public:
  Timestamp_UShort_t(UShort_t* ts):m_timestamp(ts){};
  ULong64_t value(){
    return (ULong64_t)*m_timestamp;
  }
 private:
  UShort_t* m_timestamp;
};

class Timestamp_Int_t:public Timestamp{
  
 public:
  Timestamp_Int_t(Int_t* ts):m_timestamp(ts){};
  ULong64_t value(){
    return (ULong64_t)*m_timestamp;
  }
 private:
  Int_t* m_timestamp;
};

class Timestamp_UInt_t:public Timestamp{
  
 public:
  Timestamp_UInt_t(UInt_t* ts):m_timestamp(ts){};
  ULong64_t value(){
    return (ULong64_t)*m_timestamp;
  }
 private:
  UInt_t* m_timestamp;
};

class Timestamp_Float_t:public Timestamp{
  
 public:
  Timestamp_Float_t(Float_t* ts):m_timestamp(ts){};
  ULong64_t value(){
    return (ULong64_t)*m_timestamp;
  }
 private:
  Float_t* m_timestamp;
};

class Timestamp_Double_t:public Timestamp{
  
 public:
  Timestamp_Double_t(Double_t* ts):m_timestamp(ts){};
  ULong64_t value(){
    return (ULong64_t)*m_timestamp;
  }
 private:
  Double_t* m_timestamp;
};

class Timestamp_Long64_t:public Timestamp{
  
 public:
  Timestamp_Long64_t(Long64_t* ts):m_timestamp(ts){};
  ULong64_t value(){
    return (ULong64_t)*m_timestamp;
  }
 private:
  Long64_t* m_timestamp;
};

class Timestamp_ULong64_t:public Timestamp{
  
 public:
  Timestamp_ULong64_t(ULong64_t* ts):m_timestamp(ts){};
  ULong64_t value(){
    return *m_timestamp;
  }
 private:
  ULong64_t* m_timestamp;
};

#endif
