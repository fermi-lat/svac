## @file tableIo.py
## @brief I/O from/to ASCII ntuples.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC
##
## This file can be run as a script to perform a simple test:
## "python tableIo.py" should create a file "test.dat" and print
## "Passed unit test." if all is well.

#

"""@brief I/O from/to ASCII ntuples.

"""

import re
import string
import sys

import Numeric as num
    
#
def readTable(infile, transpose=1):
    """Read an ASCII ntuple.
    
    Reads a text file containing column of numbers.
    Any lines not starting with a number will be ignored.

    @param infile A filename or a file object open for reading.

    @param [transpose=1] If this parameter is true (which is the default), the
    shape of the return value is (ncolumns, nlines), so it may be treated as
    an array of columns.  Specifying a false value for this parameter will
    cause the shape of the return value to be (nlines, ncolumns), so it can be
    treated as an array of ntuple data points.
    
    @return A 2-d array containing the data.

    """

    if not hasattr(infile, "read"):
        infile = file(infile)
    lines = infile.read()

    # only take lines that start with a number
    filter = re.compile(r"^\s*[+\-]?\.?[0-9].*$", re.MULTILINE)
    lines = filter.findall(lines)

    numFinder = re.compile(r"[-\+]?(?:\d+\.?\d*|\.\d+)(?:[eEdD][-\+]?\d+)?")

    numbers = []
    for line in lines:
        # pull out all numeric strings
        row = numFinder.findall(line)
        row = map(eval, row)
        numbers.append(row)
    numbers = num.array(numbers)
    if transpose:
        numbers = num.transpose(numbers)
        pass

    return numbers

#
def writeTable(data, outfile=sys.stdout, transpose=1):
    """Write an array to an ASCII ntuple.

    Writes an array to a text file containing columns of numbers.

    @param data A 2-dimensional array or nested sequence conatining the data
    to be written.

    @param [outfile=stdout] A filename, or a file object open for writing.  If
    it is a name, the file will be created, overwriting any existing file with
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
    if not hasattr(outfile, "write"):
        outfile = open(outfile, 'w')
    format = '%r ' * data.shape[-1] + '\n'
    for line in data:
        outfile.write(format % tuple(line))
              

if __name__ == "__main__":
    import os

    testFile = 'test.dat'
    nCols = 2
    nRows = 3

    dataOut = num.arange(nCols * nRows)
    dataOut.shape = (nCols, nRows)
    
    writeTable(dataOut, testFile)
    dataIn = readTable(testFile)

    test = dataIn == dataOut
    if num.alltrue(test.flat):
        print "Passed unit test."
    else:
        print "Failed unit test."
        
