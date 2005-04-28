#include "TMath.h"
#include "timestamps.h"

#define TICKRATE 20e6
#define ROLLPPS (1<<7)
#define ROLLTIMEBASE (1<<25)

Double_t evtTicks(unsigned int triggerTime, 
				  unsigned int ppsSeconds, unsigned int ppsTime, 
				  unsigned int rtcSeconds, unsigned int rtcNanoSeconds)
{  
  static bool firstEvent = true;
  static unsigned int firstSecond;
  static Int_t nRoll = 0;
  static unsigned int lastPps;
  static Double_t lastTime;
  static Double_t lastTicks;
  Double_t ticks;

  if (firstEvent) {
    firstEvent = false;
    firstSecond = rtcSeconds;
  } else {
    if (ppsSeconds < lastPps)
      nRoll++;
  }

  if (triggerTime < ppsTime)
    triggerTime += ROLLTIMEBASE;

  ticks = (nRoll * ROLLPPS + ppsSeconds) * TICKRATE
    + (triggerTime - ppsTime);

  Double_t rtcTime = (rtcSeconds - firstSecond) + rtcNanoSeconds * 1e-9;
  if (!firstEvent) {
    Double_t trialDelta = (ticks - lastTicks) / TICKRATE;
    Double_t rtcDelta = rtcTime - lastTime;
	nRoll += TMath::Nint((rtcDelta - trialDelta) / ROLLPPS);

    ticks = (nRoll * ROLLPPS + ppsSeconds) * TICKRATE
      + (triggerTime - ppsTime);
  }

  lastPps = ppsSeconds;
  lastTime = rtcTime;
  lastTicks = ticks;

  return ticks;
}

