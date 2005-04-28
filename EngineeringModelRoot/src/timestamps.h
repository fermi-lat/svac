#ifndef TIMESTAMPS
#define TIMESTAMPS

Double_t evtTicks(unsigned int triggerTime, 
				  unsigned int ppsSeconds, unsigned int ppsTime, 
				  unsigned int rtcSeconds, unsigned int rtcNanoSeconds);

#endif
