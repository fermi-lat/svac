## @file eLogDB.py
## @brief Query the eLog database.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

#

"""@brief Query the eLog database.
"""

import os
import sys

queryProg = 'queryElogReportTable.pl'

#
def query(run, *args):

    """@brief query one or more fields from eLog DB.

    query(run, field, ...)

    @param run The run ID.

    @param field The DB field to query.  Multiple fields for the same run may
    be queried by specifying more than 2 arguments.

    @return The (string) value of the field queried.  A tuple of strings if
    more than one field was specified.

    """

    results = []
    for field in args:
        command = '%s %s %s' % (queryProg, run, field)
        result = os.popen(command).read()
        results.append(result.strip())
        pass
    
    assert len(results) == len(args)

    if len(args) == 1:
        results = results[0]
        pass
    
    return results

