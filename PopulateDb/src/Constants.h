#ifndef Constants_Header
#define Constants_Header

struct Constants {

  enum CalibrationSource {CosmicMuon=0, Proton=1, ChargeInj=4};

  enum Location {SlacCleanRoom=0};

  enum Hardware {EM2=0};

  enum CalibType {CalElecGain=0, CalPedestal=4, CalLightAsy=6, TkrNoisyChannel=13, TkrDeadChannel=14};

  enum ProcLevel {Test=0, Development=1, Production=2, Superseded=2};

  enum Status {Ok=0, Incompleted=1, Aborted=2};

};

#endif
