## @file tableIo.py
## @brief I/O from/to ASCII ntuples.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

#

"""@brief I/O from/to ASCII ntuples.

"""

import re
import string
import sys

import Numeric as num
    
#
def readTable(file, transpose=1):
    """Read an ASCII ntuple.
    
    Reads a text file containing column of numbers.
    Any lines not starting with a number will be ignored.

    @param file A filename or a file object open for reading.

    @param [transpose=1] If this parameter is true (which is the default), the
    shape of the return value is (ncolumns, nlines), so it may be treated as
    an array of columns.  Specifying a false value for this parameter will
    cause the shape of the return value to be (nlines, ncolumns), so it can be
    treated as an array of ntuple data points.
    
    @return A 2-d array containing the data.

    @bug This is not safe.  A maliciously designed input file can execute
    arbitrary code.

    """
    
    lines = open(file).read()

    # only take lines that start with a number
    filter = re.compile('^\s*[+\-]?\.?[0-9].*$', re.MULTILINE)
    lines = filter.findall(lines)

    lines = map(string.split, lines)
    lines = map(lambda x: map(eval, x), lines)
    lines = num.array(lines)
    if transpose:
        lines = num.transpose(lines)
        pass

    return lines

#
def writeTable(data, file=sys.stdout, transpose=1):
    """Write an array to an ASCII ntuple.

    Writes an array to a text file containing columns of numbers.

    @param data A 2-dimensional array or nested sequence conatining the data
    to be written.

    @param [file=stdout] A filename, or a file object open for writing.  If it
    is a name, the file will be created, overwriting any existing file with
    that name.  Using an already open file object allows one to write text
    headers for analysis packages such as hippodraw or QDP before writing the
    data.  If this parameter is not supplied, the data will be written to
    stdout.

    @param [transpose=1] If this parameter is true (which is the default), the
    shape of @a data will be interpreted as (ncolumns, nlines), so it may be
    treated as an array of columns.  Specifying a false value for this
    parameter will cause the shape of @a data to be interpreted as (nlines,
    ncolumns), so it can be treated as an array of ntuple data points.

    @return None.
    
    """

    data = num.asarray(data)
    if transpose:
        data = num.transpose(data)
    try:
        junk = file.write
    except AttributeError:
        file = open(file, 'w')
    format = '%r ' * data.shape[-1] + '\n'
    for line in data:
        file.write(format % tuple(line))
              

