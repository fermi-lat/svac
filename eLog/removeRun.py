#!/afs/slac.stanford.edu/g/glast/applications/install/i386_linux22/usr/bin/python
"""Usage: removeRun.py runId

Removes a run from the eLog database.

"""

import sys
import DCOracle2

failCode = 1

# parse args
nArg = len(sys.argv)
if nArg == 2:
    runId = sys.argv[1]
else:
    print __doc__
    sys.exit(failCode)    

#open connection to oracle database
db = DCOracle2.connect('GLAST_CAL/9square#')
c = db.cursor()

# determine whether run is already in the database
sqlStr = 'select * from eLogReport where RunId = %s' % runId
c.execute(sqlStr)
result = c.fetchone()
if(result == None):
    print 'run %s does not exist in the database, abortted!' % runId
    db.close()
    sys.exit(failCode)
    
# construct sql string to remove run from oracle database.
# in oracle, '' is used to put ' inside a string.
sqlStr = "DELETE FROM eLogReport WHERE RunId = %s" % runId

try:
    c.execute(sqlStr)
except:
    (exc_type, exc_value) = sys.exc_info()[:2]

    print sqlStr
    print exc_type
    print exc_value

    db.rollback()
    db.close()
    sys.exit(failCode)
    
# safe to commit
db.commit()
    
#close database
db.close()
