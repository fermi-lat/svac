## @file glastFits.py
## @brief Stuff to write FITS files for GLAST.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC
##
## This file can be run as a script to perform a simple test:
## "python glastFits.py" should create a file "test.fits" and print out
## the results of running fverify and fdump on that file.

#

"""@brief Stuff to write FITS files for GLAST.

@todo This stuff should all be methods on a glastFitsFile object.

@todo Maybe should enforce filename compliance to ISO 9660 Level 2 (31
character names containing uppercase letters, numbers and underscore).

"""

import sys
import time

import cfitsio

## name of organization making file
ORIGIN = 'I&T/SVAC'
## software creating file
PROGRAM = sys.argv[0]
## name of person responsible for file generation
AUTHOR = "Warren Focke"
## release version of output file
VERSION = "0.0.1"
## version of the processing software
SOFTWARE = "0.0.1"

#
def createFile(filename):
    """@brief Create & initialize a GLAST FITS file.

    The specified @a filename will be created, with a null image primary HDU,
    and required keywords for a GLAST primary HDU.

    @param filename The name of the file to be created.

    @return A tuple containing:
    @li CFITSIO error status, should be 0,
    @li A FITS file pointer to the newly-created file.

    """

    status = 0

    st, fptr = cfitsio.fits_create_file(filename)
    status |= st
    status |= cfitsio.fits_create_img(fptr, cfitsio.BYTE_IMG, 0, [])
    status |= addPrimaryKeywords(fptr)
    status |= addStandardKeywords(fptr)

    if status:
        raise IOError, "CFITSIO problem."

    return status, fptr

#
def addPrimaryKeywords(fptr):
    """@brief Add required keywords to a GLAST FITS primary HDU.

    This adds a number of keywords that the primary HDU of every GLAST-related
    FITS file is supposed to have.  See the <A
    HREF="http://glast.gsfc.nasa.gov/ssc/dev/fits_def/guidelines.html"> GLAST
    FITS Guidelines </A> for details.

    This is kind of a hack, since almost everything is hardcoded.

    @param fptr An open FITS file pointer.  Keywords will be aded to the
    primary HDU, and the current HDU restored before returning.

    @return CFITSIO error status, should be 0.
    
    """

    status = 0

    # get current HDU so we can go back there when we're done
    junk, chdu = cfitsio.fits_get_hdu_num(fptr)
    # move to primary HDU
    st, hdutype = cfitsio.fits_movabs_hdu(fptr, 1)
    status |= st

    st, filename = cfitsio.fits_file_name(fptr)
    status |= st
    status |= cfitsio.fits_update_key_str(fptr, "FILENAME", filename,
                                          "name of this file")
    status |= cfitsio.fits_update_key_str(fptr, "ORIGIN", ORIGIN,
                                          "name of organization making file")
    status |= cfitsio.fits_update_key_str(fptr, "AUTHOR", AUTHOR,
                              "name of person responsible for file generation")
    creator = PROGRAM + '_V' + SOFTWARE
    status |= cfitsio.fits_update_key_str(fptr, "CREATOR", creator,
                                          "software and version creating file")
    status |= cfitsio.fits_update_key_str(fptr, "VERSION", VERSION,
                                          "release version of this file")
    status |= cfitsio.fits_update_key_str(fptr, "SOFTWARE", SOFTWARE,
                                          "version of the processing software")
    
    # go back to original HDU
    st, hdutype = cfitsio.fits_movabs_hdu(fptr, chdu)
    status |= st
   
    if status:
        raise IOError, "CFITSIO problem."

    return status

#
def addStandardKeywords(fptr):
    """@brief Add required keywords to a GLAST FITS HDU.

    This adds a number of keywords that every HDU of every GLAST-related FITS
    file is supposed to have.  See the <A
    HREF="http://glast.gsfc.nasa.gov/ssc/dev/fits_def/guidelines.html"> GLAST
    FITS Guidelines </A> for details.

    @param fptr An open FITS file pointer.  Keywords will be aded to the
    current HDU.

    @return CFITSIO error status, should be 0.

    """

    status = 0

    # constant stuff
    status |= cfitsio.fits_update_key_str(fptr, "TELESCOP", "GLAST",
                                          "name of telescope generating data")
    status |= cfitsio.fits_update_key_str(fptr, "INSTRUME", "LAT",
                                          "name of instrument generating data")
    status |= cfitsio.fits_update_key_flt(fptr, "EQUINOX", 2000.0, -9,
                                          "equinox for ra and dec")
    status |= cfitsio.fits_update_key_str(fptr, "RADECSYS", "FK5",
                              "world coord. system for this file (FK5 or FK4)")
    
    # date of file creation
    datestr = time.strftime("%Y-%m-%d")
    status |= cfitsio.fits_update_key_str(fptr, "DATE", datestr, 
                                          "date file was made in yyyy-mm-dd")

    if status:
        raise IOError, "CFITSIO problem."

    return status

#
def createTable(fptr, naxis2=0, tfields=0, ttype=[], tform=[], tunit=[],
                extname=""):
    """@brief Append a new binary table.

    All arguments except @a fptr are optional.  If they are not supplied, the
    table will have no rows or columns; they can be added later.  The HDU will
    be created with GLAST standard keywords.

    The new HDU will be added at the end of the file, and will be the current
    HDU.

    @param fptr An open FITS file pointer.

    @param [naxis2=0] Number of table rows to preallocate.  Recommend leaving
    it at the default value of 0, the table will be extended as data are
    written.

    @param [tfields=0] Number of columns.

    @param [ttype=[]] A sequence of column names.

    @param [tfrom=[]] A sequence of column data types.  Format of these is
    defined in <A
    HREF="http://archive.stsci.edu/fits/fits_standard/node68.html"> the FITS
    standard. </A>

    @param [tunit=[]] A sequence of column units.  Standard values for these
    are defined in <A
    HREF="http://heasarc.gsfc.nasa.gov/docs/heasarc/ofwg/docs/summary/ogip_93_001_summary.html">
    Specification of Physical Units within OGIP FITS Files. </A>

    @param [extname=""] The name of the table.

    @return A tuple containing:
    @li CFITSIO error status, should be 0,
    @li The number of the new HDU, which will then be the current HDU.

    """

    status = 0

    status |= cfitsio.fits_create_tbl(fptr, cfitsio.BINARY_TBL, naxis2,
                                      tfields, ttype, tform, tunit, extname)
    status |= addStandardKeywords(fptr)    

    if status:
        raise IOError, "CFITSIO problem."

    junk, chdu = cfitsio.fits_get_hdu_num(fptr)
    return status, chdu

#
def closeFile(fptr):
    """@brief close a GLAST FITS file.

    DATASUM and CHECKSUM for each HDU will be updated before closing the file.

    @param fptr A FITS file pointer, open for writing.

    @return CFITSIO error status, should be 0.

    """

    status = 0

    status |= cfitsio.fits_flush_file(fptr)

    # update checksums
    st, nhdus = cfitsio.fits_get_num_hdus(fptr)
    status |= st
    for hdu in xrange(1, nhdus+1):
        st, hdutype = cfitsio.fits_movabs_hdu(fptr, hdu)
        status |= st
        status |= cfitsio.fits_write_chksum(fptr)

    # close the file
    status |= cfitsio.fits_close_file(fptr)
    
    if status:
        raise IOError, "CFITSIO problem."

    return status


if __name__ == "__main__":
    import os
    
    testfile = 'test.fits'

    status = 0
    
    st, fptr = createFile(testfile)
    status |= st
    st, chdu = createTable(fptr, extname="BOZO")
    status |= st
    status |= closeFile(fptr)

    if status:
        raise IOError, "There was a CFITSIO problem."
    
    os.system('fverify %s' % testfile)
    os.system('fdump %s outfile=STDOUT rows=- columns=- page=no' % testfile)
