## @file temUtil.py
## @brief Mappings from TEM to sensinle strings.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

"""@brief Mappings from TEM to sensible strings.

"""

cccSideMap = ("+X", "+Y", "-X", "-Y")
cccLayerMap = ((0,2,4,6),
               (1,3,5,7),
               (0,2,4,6),
               (1,3,5,7))

crcLayerMap = range(4)

registerMap = {
    # CAL stuff
    "config_0": "Configuration Register (0)",
    "config_1": "Configuration Register (1)",
    "fle_dac": "Low Energy Trigger Discriminator",
    "fhe_dac": "High Energy Trigger Discriminator",
    "log_acpt": "Log Accept Discriminator",
    "ref_dac": "DAC for DC Reference",
    "rng_uld_dac": "Range Select Discriminator",
    #
    "": "",
    }


tccLRMap = ((0,1), (3,2), (5,4), (6,7))
trcLayerMap = {"X": [(side, trc) for trc in range(9) for side in (1, 3)],
               "Y": [(side, trc) for trc in range(9) for side in (0, 2)]}
