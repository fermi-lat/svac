## @file WrtARF.py
## @brief Write OGIP ARF files for the GLAST LAT.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC
##
## This file can be run as a script to perform a simple test:
## "python WrtARF.py" should create a file "test.arf" and print out
## the results of running fverify and fdump on that file.

#

"""@brief Write OGIP ARF files for the GLAST LAT.

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


def createArfHdu(fptr, prod, edges):
    """@brief Append an ARF HDU to a GLAST FITS file.

    @param fptr A GLAST FITS file open for writing.

    @param prod A numeric sequence containing the product of all the
    components (effective area, filter transmission, correction factors etc)
    specific to a given PHA file (ie the spectral response of the instrument
    as a whole).  Units should be cm**2.

    @param edges A numeric sequence containing bin edges for the true energy
    bins.  Energy is measured in keV.  The bins should be contiguous,
    disjoint, and sorted.  The length of this should be one greater than the
    length of the second axis of the redistribution matrix (which lives in a
    different file).

    @return A tuple containing:
    @li CFITSIO error status, should be 0,
    @li The number of the new HDU, which will then be the current HDU.

    """

    status = 0

    pod = num.asarray(prod)
    prod = prod.astype(num.Float32)

    edges = num.asarray(edges)
    edges = edges.astype(num.Float32)
    nbin = len(edges) - 1
    elo = edges[:-1]
    ehi = edges[1:]

    st, chdu = glastFits.createTable(fptr, naxis2=0, tfields=3,
                                    ttype=["ENERG_LO", "ENERG_HI", "SPECRESP"],
                                    tform=["I", "I", "E"],
                                    tunit=["keV", "keV", "cm**2"],
                                    extname="SPECRESP")
    status |= st

    # required keywords
    status |= cfitsio.fits_update_key_str(fptr, "FILTER", "NONE",
                                         "Instrument filter in use")
    status |= cfitsio.fits_update_key_str(fptr, "HDUCLASS", "OGIP",
                                      "format conforms to OGIP/GSFC standards")
    status |= cfitsio.fits_update_key_str(fptr, "HDUCLAS1", "RESPONSE",
                                         "Extension contains response data")
    status |= cfitsio.fits_update_key_str(fptr, "HDUCLAS2", "EBOUNDS",
                                        "reconstructed energy bin boundaries")
    status |= cfitsio.fits_update_key_str(fptr, "HDUVERS", "1.1.0",
                                         "version of the file format")

    # optional keywords
    status |= cfitsio.fits_update_key_str(fptr, "ARFVERSN", "1992a",
                                         "obsolete keyword for older software")
    status |= cfitsio.fits_update_key_str(fptr, "HDUVERS1", "1.0.0",
                                         "obsolete keyword for older software")
    status |= cfitsio.fits_update_key_str(fptr, "HDUVERS2", "1.1.0",
                                         "obsolete keyword for older software")

    # Oh, yeah, the data
    status |= cfitsio.fits_write_col_dbl(fptr, 1, 1, 1, nbin, list(elo))
    status |= cfitsio.fits_write_col_dbl(fptr, 2, 1, 1, nbin, list(ehi))
    status |= cfitsio.fits_write_col_dbl(fptr, 3, 1, 1, nbin, list(prod))


    if status:
        raise IOError, "CFITSIO problem."

    return status, chdu


if __name__ == "__main__":
    import os
    
    testfile = "test.arf"

    status = 0

    nbin = 3
    prod = num.arange(nbin)
    edges = num.arange(nbin+1)
    
    st, fptr = glastFits.createFile(testfile)
    status |= st
    st, chdu = createArfHdu(fptr, prod, edges)
    status |= st
    status |= glastFits.closeFile(fptr)

    if status:
        raise IOError, "There was a CFITSIO problem."
    
    os.system("fverify %s" % testfile)
    os.system("fdump %s outfile=STDOUT rows=- columns=- page=no" % testfile)
    
