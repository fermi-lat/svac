## @file JobOptions.py
## @brief Configuration for spectral analysis package.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

#

"""@brief Configuration for spectral analysis package.

"""

# # config

# input files
specDataFile = "../Data/vdg_em_4M_ene.dat"
responseDataFile = "../Data/gamma_9_25_198M_ene.dat"

# output files
phaFile = "VdG.pha"
rmfFile = "VdG.rmf"
arfFile = "VdG.arf"

# define true energy "bins"
eTrueMin = 9.0
eTrueMax = 25.0
nBin = 160

# define reconstructed energy "channels"
eReconMin = 7.0
eReconMax = 35.0
nChan = 100

# input spectrum used to build the response set
sourceModel = "powerlaw"
offset = 8.0
slope = -1.0
norm = 198e6
sourceParam = (offset, slope, norm)

# # end config
