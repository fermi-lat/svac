## @file WrtRMF.py
## @brief Write OGIP RMF files for the GLAST LAT.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC
##
## This file can be run as a script to perform a simple test:
## "python WrtRMF.py" should create a file "test.rmf" and print out
## the results of running fverify and fdump on that file.

#


"""@brief Write OGIP RMF files for the GLAST LAT.

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


def createMatrixHdu(fptr, matrix, edges):
    """@brief Append an RMF HDU to a GLAST FITS file.

    @param fptr A GLAST FITS file open for writing.

    @param data A numeric 2-d array or nested sequence containing a
    redistribution matrix.  The first axis should correspond to true energy
    bins, the model will be integrated into these.  The second axis should
    correspond to recontructed energy bins, they should be the same bins used
    for the reconstructed spectrum that will be analysed with this matrix.

    @param edges A numeric sequence containing bin edges for the true energy
    bins.  Energy is measured in keV.  The bins should be contiguous,
    disjoint, and sorted.  The length of this should be one greater than the
    length of the first axis of the matrix.

    @return A tuple containing:
    @li CFITSIO error status, should be 0,
    @li The number of the new HDU, which will then be the current HDU.

    """

    status = 0
    
    matrix = num.asarray(matrix)
    matrix = matrix.astype(num.Float32)
    nbin, nchan = matrix.shape
    matform = "%dE" % nchan
    nelt = nbin * nchan

    edges = num.asarray(edges)
    edges = edges.astype(num.Float32)
    if len(edges) != nbin+1:
        raise ValueError, "edges don't match matrix"
    elo = edges[:-1]
    ehi = edges[1:]

    n_grp = num.ones(nbin)
    f_chan = num.ones(nbin)
    n_chan = num.ones(nbin) * nchan
    
    st, chdu = glastFits.createTable(fptr, naxis2=0, tfields=6,
         ttype=["ENERG_LO", "ENERG_HI", "N_GRP", "F_CHAN", "N_CHAN", "MATRIX"],
         tform=["E", "E", "I", "1I", "1I", matform],
         tunit=["keV", "keV", "", "", "", ""], extname="MATRIX")
    status |= st

    # required keywords
    status |= cfitsio.fits_update_key_str(fptr, "FILTER", "NONE",
                                         "Instrument filter in use")
    status |= cfitsio.fits_update_key_str(fptr, "CHANTYPE", "PI",
                                  "channels are really calculated energy bins")
    status |= cfitsio.fits_update_key_lng(fptr, "DETCHANS", nchan,
                                 "Total number of detector channels available")
    status |= cfitsio.fits_update_key_str(fptr, "HDUCLASS", "OGIP",
                                      "format conforms to OGIP/GSFC standards")
    status |= cfitsio.fits_update_key_str(fptr, "HDUCLAS1", "RESPONSE",
                                         "Extension contains response data")
    status |= cfitsio.fits_update_key_str(fptr, "HDUCLAS2", "RSP_MATRIX",
                                        "extension contains a response matrix")
    status |= cfitsio.fits_update_key_str(fptr, "HDUVERS", "1.3.0",
                                         "Version number of the format")
    # have to change this if columns are reordered
    status |= cfitsio.fits_update_key_lng(fptr, "TLMIN4", 1,
                                         "the first channel in the response")


    # optional keywords
    status |= cfitsio.fits_update_key_lng(fptr, "NUMGRP", nbin,
                                          "the number of channel subsets")
    status |= cfitsio.fits_update_key_lng(fptr, "NUMELT", nelt,
                                          "the number of response elements")
    status |= cfitsio.fits_update_key_str(fptr, "RMFVERSN", "1992a",
                                         "obsolete keyword for older software")
    status |= cfitsio.fits_update_key_str(fptr, "HDUVERS1", "1.1.0",
                                         "obsolete keyword for older software")
    status |= cfitsio.fits_update_key_str(fptr, "HDUVERS2", "1.2.0",
                                         "obsolete keyword for older software")
    status |= cfitsio.fits_update_key_flt(fptr, "LO_THRES", 0.0, -9,
                                "lower threshold used to construct the matrix")
    status |= cfitsio.fits_update_key_str(fptr, "HDUCLAS3", "REDIST",
                              "elements represent redistribution process only")

# XSPEC didn't like this, added the real columns.
#     # keywords that replace constant columns
#     status |= cfitsio.fits_update_key_lng(fptr, "N_GRP", 1,
#                                    "number of channel subsets for every bin")
#     status |= cfitsio.fits_update_key_lng(fptr, "F_CHAN", 1,
#                                     "first channel for every channel subset")
#     status |= cfitsio.fits_update_key_lng(fptr, "N_CHAN", nchan,
#                                 "number of channels in every channel subset")
    
    # Oh, yeah, the data
    status |= cfitsio.fits_write_col_dbl(fptr, 1, 1, 1, nbin, list(elo))
    status |= cfitsio.fits_write_col_dbl(fptr, 2, 1, 1, nbin, list(ehi))
    status |= cfitsio.fits_write_col_int(fptr, 3, 1, 1, n_grp)
    status |= cfitsio.fits_write_col_int(fptr, 4, 1, 1, f_chan)
    status |= cfitsio.fits_write_col_int(fptr, 5, 1, 1, n_chan)
    status |= cfitsio.fits_write_col_dbl(fptr, 6, 1, 1, nelt,
                                         list(matrix.flat))

    if status:
        raise IOError, "CFITSIO problem."

    return status, chdu


def createEboundsHdu(fptr, ebounds):
    """@brief Append an EBOUNDS HDU to a GLAST FITS file.

    @param fptr A GLAST FITS file open for writing.

    @param ebounds A numeric sequence containing bin edges for the
    reconstructed energy bins.  Energy is measured in keV.  The length of this
    should be one greater than the length of the second axis of the
    redistribution matrix (which lives in a different extension of this file).

    @return A tuple containing:
    @li CFITSIO error status, should be 0,
    @li The number of the new HDU, which will then be the current HDU.

    """

    status = 0

    ebounds = num.asarray(ebounds)
    ebounds = ebounds.astype(num.Float32)
    nchan = len(ebounds) - 1
    emin = ebounds[:-1]
    emax = ebounds[1:]

    channel = num.arange(nchan) + 1

    st, chdu = glastFits.createTable(fptr, naxis2=0, tfields=3,
                                     ttype=["CHANNEL", "E_MIN", "E_MAX"],
                                     tform=["I", "E", "E"],
                                     tunit=["", "keV", "keV"],
                                     extname="EBOUNDS")
    status |= st
    

    # required keywords
    status |= cfitsio.fits_update_key_str(fptr, "FILTER", "NONE",
                                         "Instrument filter in use")
    status |= cfitsio.fits_update_key_str(fptr, "CHANTYPE", "PI",
                                  "channels are really calculated energy bins")
    status |= cfitsio.fits_update_key_lng(fptr, "DETCHANS", nchan,
                                 "Total number of detector channels available")
    status |= cfitsio.fits_update_key_str(fptr, "HDUCLASS", "OGIP",
                                      "format conforms to OGIP/GSFC standards")
    status |= cfitsio.fits_update_key_str(fptr, "HDUCLAS1", "RESPONSE",
                                         "Extension contains response data")
    status |= cfitsio.fits_update_key_str(fptr, "HDUCLAS2", "EBOUNDS",
                                        "reconstructed energy bin boundaries")
    status |= cfitsio.fits_update_key_str(fptr, "HDUVERS", "1.2.0",
                                         "version of the file format")
    
    # optional keywords
    status |= cfitsio.fits_update_key_str(fptr, "RMFVERSN", "1992a",
                                         "obsolete keyword for older software")
    status |= cfitsio.fits_update_key_str(fptr, "HDUVERS1", "1.0.0",
                                         "obsolete keyword for older software")
    status |= cfitsio.fits_update_key_str(fptr, "HDUVERS2", "1.1.0",
                                         "obsolete keyword for older software")

   # Oh, yeah, the data
    status |= cfitsio.fits_write_col_int(fptr, 1, 1, 1, channel)
    status |= cfitsio.fits_write_col_dbl(fptr, 2, 1, 1, nchan, list(emin))
    status |= cfitsio.fits_write_col_dbl(fptr, 3, 1, 1, nchan, list(emax))

    if status:
        raise IOError, "CFITSIO problem."

    return status, chdu


if __name__ == "__main__":
    import os
    
    testrmf = "test.rmf"
    nbin = 3
    nchan = 2

    os.system("rm -f %s" % testrmf)

    status = 0

    matrix = num.arange(nbin*nchan)
    matrix.shape = nbin, nchan
    edges = num.arange(nbin+1) + 1
    ebounds = num.arange(nchan+1) + 1
    
    st, fptr = glastFits.createFile(testrmf)
    status |= st
    st, chdu = createMatrixHdu(fptr, matrix, edges)
    status |= st
    st, chdu = createEboundsHdu(fptr, ebounds)
    status |= st
    status |= glastFits.closeFile(fptr)

    if status:
        raise IOError, "There was a CFITSIO problem."
    
    os.system("fverify %s" % testrmf)
    os.system("fdump %s outfile=STDOUT rows=- columns=- page=no" % testrmf)
    
