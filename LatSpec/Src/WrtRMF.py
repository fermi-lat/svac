## @file WrtRMF.py
## @brief Create OGIP RMF files from GLAST LAT data.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC
##
## This file can be run as a script to perform a simple test:
## "python WrtRMF.py" should create a file "test.rmf" and print out
## the results of running fverify and fdump on that file.

#


"""@brief Create OGIP RMF files from GLAST LAT data.

This module contains a buch of stuff to deal with making RMF files (see <A
HREF="http://legacy.gsfc.nasa.gov/docs/heasarc/caldb/docs/summary/cal_gen_92_002_summary.html">
The Calibration Requirements for Spectral Analysis </A> for details) from LAT
data.

@todo This stuff should all be methods of a GlastRmfFile object, which would
subclass GlastFitsFile.

"""

import Numeric as num

import cfitsio

import glastFits


def createRmfHdu(fptr, matrix, ebounds):
    """@brief Append a RMF HDU to a GLAST FITS file.

    @param fptr A GLAST FITS file open for writing.

    @param data A numeric 2-d array or nested sequence containing a
    redistribution matrix.  The first axis should correspond to true energy
    bins, the model will be integrated into these.  The second axis should
    correspond to recontructed energy bins, they should be the same bins used
    for the reconstructed spectrum that will be analysed with this matrix.

    @param ebounds A numeric sequence containing bin edges for the true energy
    bins.  Energy is measured in keV.  The bins should be contiguous,
    disjoint, and sorted.  The length of this should be one greater than the
    length of the first axis of the matrix.

    @return A tuple containing:
    @li CFITSIO error status, should be 0,
    @li The number of the new HDU, which will then be the current HDU.

    """

    status = 0
    
    matrix = num.asarray(matrix)
    nbin, nchan = matrix.shape

    matform = "%dE" % nchan
    
    st, chdu = glastFits.createTable(fptr, naxis2=0, tfields=3,
                                     ttype=["ENERG_LO", "ENERG_HI", "MATRIX"],
                                     tform=["1I", "1I", matform],
                                     tunit=["keV", "keV", ""],
                                     extname="MATRIX")
    status |= st

    # required keywords
    # recommended keywords
    # keywords that replace constant columns
    # Oh, yeah, the data


    if status:
        raise IOError, "CFITSIO problem."

    return status, chdu


if __name__ == "__main__":
    import os
    
    testfile = "test.rmf"

    status = 0

    nbin = 7
    nchan = 5
    matrix = num.arange(nbin*nchan)
    matrix.shape = nbin, nchan
    ebounds = num.arange(nbin+1)
    
    st, fptr = glastFits.createFile(testfile)
    status |= st
    st, chdu = createRmfHdu(fptr, matrix, ebounds)
    status |= st
    status |= glastFits.closeFile(fptr)

    if status:
        raise IOError, "There was a CFITSIO problem."
    
    os.system("fverify %s" % testfile)
    os.system("fdump %s outfile=STDOUT rows=- columns=- page=no" % testfile)
    
