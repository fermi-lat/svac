
## @file WrtPHA.py
## @brief Write OGIP PHA files for the GLAST LAT.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC
##
## This file can be run as a script to perform a simple test:
## "python WrtPHA.py" should create a file "test.pha" and print out
## the results of running fverify and fdump on that file.

#


"""@brief Write OGIP PHA files for the GLAST LAT.

This module contains a buch of stuff to deal with making PHA files (see <A
HREF="http://heasarc.gsfc.nasa.gov/docs/heasarc/ofwg/docs/summary/ogip_92_007_summary.html">
The OGIP Spectral File Format </A> for details) from LAT data.

@todo This stuff should all be methods of a GlastPhaFile object, which would
subclass GlastFitsFile.

"""

import Numeric as num

import cfitsio

import glastFits


def createSpecHdu(fptr, data):
    """@brief Append a PHA SPECTRUM HDU to a GLAST FITS file.

    @param fptr A GLAST FITS file open for writing.

    @param data A numeric sequence containing a histogram of counts vs energy.
    It should contain integer values, they should not be background-subtracted.

    @return A tuple containing:
    @li CFITSIO error status, should be 0,
    @li The number of the new HDU, which will then be the current HDU.

    """

    status = 0
    
    data = num.asarray(data)
    data = data.astype(num.Int32)
    nchan = len(data)
    channel = num.arange(nchan) + 1
    
    st, chdu = glastFits.createTable(fptr, naxis2=0, tfields=2,
                          ttype=["CHANNEL", "COUNTS"], tform=["I", "J"],
                          tunit=["", "count"], extname="SPECTRUM")
    status |= st

    # required keywords
    status |= cfitsio.fits_update_key_str(fptr, "FILTER", "NONE",
                                         "Instrument filter in use")
    status |= cfitsio.fits_update_key_str(fptr, "BACKFILE", "NONE",
                                        "Background FITS file for this object")
    status |= cfitsio.fits_update_key_str(fptr, "CORRFILE", "NONE",
                                       "Correlation FITS file for this object")
    status |= cfitsio.fits_update_key_str(fptr, "RESPFILE", "NONE",
                                         "Redistribution matrix file (RMF)")
    status |= cfitsio.fits_update_key_str(fptr, "ANCRFILE", "NONE",
                                         "Ancillary response file (ARF)")
    status |= cfitsio.fits_update_key_str(fptr, "HDUCLASS", "OGIP",
                                      "format conforms to OGIP/GSFC standards")
    status |= cfitsio.fits_update_key_str(fptr, "HDUCLAS1", "SPECTRUM",
                                         "Extension contains a Spectrum")
    status |= cfitsio.fits_update_key_str(fptr, "HDUVERS", "1.2.0",
                                         "Version number of the format")
    status |= cfitsio.fits_update_key_str(fptr, "CHANTYPE", "PI",
                                  "channels are really calculated energy bins")
    status |= cfitsio.fits_update_key_flt(fptr, "EXPOSURE", 1.0, -9,
                                         "Exposure time, dummy value")
    status |= cfitsio.fits_update_key_flt(fptr, "CORRSCAL", 0.0, -9,
                                         "Correction scale factor")
    status |= cfitsio.fits_update_key_lng(fptr, "DETCHANS", nchan,
                                 "Total number of detector channels available")
    status |= cfitsio.fits_update_key_log(fptr, "POISSERR", 1, \
                                    "Poisson Distribution errors are assumed.")

    # recommended keywords
    status |= cfitsio.fits_update_key_str(fptr, "HDUCLAS2", "TOTAL",
                                         "gross PHA Spectrum (source + bkgd)")
    status |= cfitsio.fits_update_key_str(fptr, "HDUCLAS3", "COUNT",
                                         "Extension contains counts")
    status |= cfitsio.fits_update_key_str(fptr, "XFLT0001", "NONE",
                                         "XSPEC selection filter description")
    status |= cfitsio.fits_update_key_str(fptr, "HDUVERS1", "1.1.0",
                                         "obsolete keyword for older software")

    # keywords that replace constant columns
    status |= cfitsio.fits_update_key_lng(fptr, "SYS_ERR", 0,
                                          "No systematic error was specified")
    status |= cfitsio.fits_update_key_lng(fptr, "GROUPING", 0,
                                         "No grouping data has been specified")
    status |= cfitsio.fits_update_key_lng(fptr, "QUALITY", 0,
                                       "No data quality information specified")
    status |= cfitsio.fits_update_key_flt(fptr, "AREASCAL", 1.0, -9,
                                         "Nominal effective area, dummy value")
    status |= cfitsio.fits_update_key_flt(fptr, "BACKSCAL", 1.0, -9,
                                         "Background scale factor")
   
    # Oh, yeah, the data
    status |= cfitsio.fits_write_col_int(fptr, 1, 1, 1, channel)
    status |= cfitsio.fits_write_col_int(fptr, 2, 1, 1, data)

    if status:
        raise IOError, "CFITSIO problem."

    return status, chdu


if __name__ == "__main__":
    import os
    
    testpha = "test.pha"
    testrmf = "test.rmf"
    testarf = "test.arf"
    nchan = 2

    os.system("rm -f %s" % testpha)

    status = 0

    data = num.arange(nchan)
    
    st, fptr = glastFits.createFile(testpha)
    status |= st
    st, chdu = createSpecHdu(fptr, data)
    status |= st
    status |= glastFits.closeFile(fptr)

    if status:
        raise IOError, "There was a CFITSIO problem."

    # hardwire test file to use test files produced by other modules
    os.system("fparkey %s %s RESPFILE" % (testrmf, testpha))
    os.system("fparkey %s %s ANCRFILE" % (testarf, testpha))
    
    os.system("fverify %s" % testpha)
    os.system("fdump %s outfile=STDOUT rows=- columns=- page=no" % testpha)
    
