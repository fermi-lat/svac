## @file glastFits.py
## @brief Stuff to write FITS files for GLAST.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

#

"""@brief Stuff to write FITS files for GLAST.

"""

import sys
import time

import cfitsio

## name of organization making file
ORIGIN = 'SVAC'
## software creating file
PROGRAM = sys.argv[0]
## name of person responsible for file generation
AUTHOR = "Warren Focke"
## release version of output file
VERSION = "0.0.1"
## version of the processing software
SOFTWARE = "0.0.1"


def createFile(filename):
    """@brief Create & initialize a GLAST FITS file.

    The specified @a filename will be created, with a null image primary HDU,
    and required keywords for a GLAST primary HDU.

    @param filename The name of the file to be created.

    @return A FITS file pointer to the newly-created file.

    """

    status, fptr = cfitsio.fits_create_file(filename)
    status = cfitsio.fits_create_img(fptr, cfitsio.BYTE_IMG, 0, [])
    addPrimaryKeywords(fptr)
    addStandardKeywords(fptr)

    status = cfitsio.fits_flush_file(fptr)
    
    return fptr


def addPrimaryKeywords(fptr):
    """@brief Add required keywords to a GLAST FITS primary HDU.

    This adds a number of keywords that the primary HDU of every GLAST-related
    FITS file is supposed to have.  See the <A
    HREF="http://glast.gsfc.nasa.gov/ssc/dev/fits_def/guidelines.html">GLAST
    FITS Guidelines</A> for details.

    This is kind of a hack, since almost everything is hardcoded.

    @param fptr An open FITS file pointer.  Keywords will be aded to the
    primary HDU, and the current HDU restored before returning.

    @return None
    """

    # get current HDU so we can go back there when we're done
    junk, chdu = cfitsio.fits_get_hdu_num(fptr)
    # move to primary HDU
    status, hdutype = cfitsio.fits_movabs_hdu(fptr, 1)

    status, filename = cfitsio.fits_file_name(fptr)
    status = cfitsio.fits_update_key_str(fptr, "FILENAME", filename,
                                         "name of this file")
    status = cfitsio.fits_update_key_str(fptr, "ORIGIN", ORIGIN,
                                         "name of organization making file")
    status = cfitsio.fits_update_key_str(fptr, "AUTHOR", AUTHOR,
                              "name of person responsible for file generation")
    creator = PROGRAM + '_V' + SOFTWARE
    status = cfitsio.fits_update_key_str(fptr, "CREATOR", creator,
                                         "software and version creating file")
    status = cfitsio.fits_update_key_str(fptr, "VERSION", VERSION,
                                         "release version of this file")
    status = cfitsio.fits_update_key_str(fptr, "SOFTWARE", SOFTWARE,
                                         "version of the processing software")
    
    # go back to original HDU
    status, hdutype = cfitsio.fits_movabs_hdu(fptr, chdu)
    
    return


def addStandardKeywords(fptr):
    """@brief Add required keywords to a GLAST FITS HDU.

    This adds a number of keywords that every HDU of every GLAST-related FITS
    file is supposed to have.  See the <A
    HREF="http://glast.gsfc.nasa.gov/ssc/dev/fits_def/guidelines.html">GLAST
    FITS Guidelines</A> for details.

    @param fptr An open FITS file pointer.  Keywords will be aded to the
    current HDU.

    @return None

    """

    # constant stuff
    status = cfitsio.fits_update_key_str(fptr, "TELESCOP", "GLAST",
                                        "name of telescope generating data")
    status = cfitsio.fits_update_key_str(fptr, "INSTRUME", "LAT",
                                        "name of instrument generating data")
    status = cfitsio.fits_update_key_flt(fptr, "EQUINOX", 2000.0, -9,
                                        "equinox for ra and dec")
    status = cfitsio.fits_update_key_str(fptr, "RADECSYS", "FK5",
                             "world coord. system for this file (FK5 or FK4)")
    
    # date of file creation
    datestr = time.strftime("%Y-%m-%d")
    status = cfitsio.fits_update_key_str(fptr, "DATE", datestr, 
                            "date file was made in yyyy-mm-dd")

    return


def closeFile(fptr):
    """@brief close a GLAST FITS file.

    DATASUM and CHECKSUM for each HDU will be updated before closing the file.

    @param fptr An open FITS file pointer.

    @return None

    """

    status = cfitsio.fits_flush_file(fptr)

    # update checksums
    status, nhdus = cfitsio.fits_get_num_hdus(fptr)
    for hdu in xrange(1, nhdus+1):
        status, hdutype = cfitsio.fits_movabs_hdu(fptr, hdu)
        status = cfitsio.fits_write_chksum(fptr)

    # close the file
    status = cfitsio.fits_close_file(fptr)
    
    return


if __name__ == "__main__":
    import os
    testfile = 'test.fits'
    closeFile(createFile(testfile))
    os.system('fverify %s' % testfile)
    os.system('fdump %s outfile=STDOUT rows=- columns=-' % testfile)
