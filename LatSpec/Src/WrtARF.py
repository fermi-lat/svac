## @file WrtARF.py
## @brief Create OGIP ARF files from GLAST LAT data.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

#


"""@brief Create OGIP ARF files from GLAST LAT data.

This module contains a buch of stuff to deal with making ARF files (see <A
HREF="http://legacy.gsfc.nasa.gov/docs/heasarc/caldb/docs/summary/cal_gen_92_002_summary.html">
The Calibration Requirements for Spectral Analysis </A> for details) from LAT
data.

@todo This stuff should all be methods of a GlastArfFile object, which would
subclass GlastFitsFile.

"""

import Numeric as num

import cfitsio

import glastFits


