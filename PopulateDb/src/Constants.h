#ifndef Constants_Header
#define Constants_Header

struct Constants {

  enum CalibrationSource {Cosm_ray=0, Proton=1, Charge_Inj=4};

  enum Location {SlacCleanRoom=0};

  enum Hardware {EM=0};

  enum CalibType {TkrNoisyChannel=13, TkrDeadChannel=14};
};

#endif
