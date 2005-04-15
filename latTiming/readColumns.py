## @file readColumns.py
## @brief Read columns from ROOT nTuples.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

"""@brief Read columns from ROOT nTuples.

"""

import hippo
import numarray

#
def readColumns(fileName, columns, whichTuple=0):
    """@brief Read columns from ROOT nTuples.

    @arg fileName The ROOT file to read.

    @arg columns A column name or sequence of column names to read.

    @arg [whichTuple] Name or number of tuple in file to read.
    Default is the first.

    @ret A sequence of arrays, one for each name in @a columns, or a single
    array if a single column name was given.

    """

    import types

    if isinstance(columns, types.StringTypes):
        oneColumn = True
        columns = [columns]
    else:
        oneColumn = False
        pass

    # get list of tuple names
    rc = hippo.RootController.instance()
    tupleNames = rc.getNTupleNames(fileName)
    nTuples = len(tupleNames)

    # figure out which one we want
    if whichTuple in tupleNames:
        ourTupleName = whichTuple
    elif -nTuples <= whichTuple < nTuples:
        ourTupleName = tupleNames[whichTuple]
    else:
        raise LookupError, "Requested tuple %s was not found." % whichTuple

    # grab it
    ourTuple = rc.createNTuple(fileName, ourTupleName)

    # pull out the data
    columnData = [numarray.array(ourTuple.getColumn(name)) for name in columns]

    if oneColumn:
        columnData = columnData[0]

    return columnData
