
## @file WrtPHA.py
## @brief Create OGIP PHA files from GLAST LAT data.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

#

"""@brief Create OGIP PHA files from GLAST LAT data.

This module contains a buch of stuff to deal with making PHA files (see <A
HREF="http://heasarc.gsfc.nasa.gov/docs/heasarc/ofwg/docs/summary/ogip_92_007_summary.html">
The OGIP Spectral File Format </A> for details) from LAT data.

"""

import Numeric as num

import cfitsio

import tableIo
import glastFits

def createSpecHdu(fptr, data):
    """@brief Append a PHA SPECTRUM HDU to a GLAST FITS file.

    @param fptr A GLAST FITS file open for writing.

    @param data A numeric sequence containing a histogram of counts vs energy.
    It should contain integer values, they should not be background-subtracted.

    @return CFITSIO error status, should be 0.

    """

    status = 0
    
    data = num.asarray(data)
    nchan = len(data)
    channel = num.arange(nchan) + 1
    
    glastFits.createTable(fptr, naxis2=0, tfields=2,
                          ttype=["CHANNEL", "COUNTS"], tform=["I", "J"],
                          tunit=["", "count"], extname="SPECTRUM")

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
    status |= cfitsio.fits_update_key_str(fptr, "HDUVERS", "1.1.0",
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
                                         "Version number of the format")

    # keywords that replace constant columns
    status = cfitsio.fits_update_key_lng(fptr, "SYS_ERR", 0,
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

    return status


if __name__ == "__main__":
    import os
    
    testfile = "test.pha"
    data = num.arange(8)
    fptr = glastFits.createFile(testfile)
    createSpecHdu(fptr, data)
    glastFits.closeFile(fptr)

    os.system("fverify %s" % testfile)
    os.system("fdump %s outfile=STDOUT rows=- columns=- page=no" % testfile)
    
