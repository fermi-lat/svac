def getThrDAC( dac ):
  b0 = dac & 0x40
  b1 = dac & 0x20
  b2 = dac & 0x10
  b3 = dac & 0x8
  b4 = dac & 0x4
  b5 = dac & 0x2
  return (b0>>6) + (b1>>4) + (b2>>2) + b3 + (b4<<2) + (b5<<4)

def getThrDACRange( dac ):
  return dac & 0x1
