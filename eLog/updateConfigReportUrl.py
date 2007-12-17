#!/afs/slac.stanford.edu/package/python/2.4.3/i386_linux24/bin/linux2.4
#!/usr/bin/env python2.4

"""Usage: update.py [dataRoot] [runId]

dataRoot is the root directory for the run tree on the FTP server
(default /glast.u01/EM2/rootData/)

default runId is -10

"""

import sys
from xml.dom.ext.reader import Sax2
from xml.dom import Node
import string
import re
import DCOracle2

#used to form ftp URL - default value
rootDataDir = '/glast.u01/EM2/rootData/'
runId = -10

# parse args
nArg = len(sys.argv)
if nArg == 3:
    rootDataDir = sys.argv[1]
    runId = sys.argv[2]
else:
    print __doc__
    sys.exit(99)    

#open connection to oracle database
db = DCOracle2.connect('GLAST_CAL/9square#')

c = db.cursor()

# determine whether run is already in the database
sqlStr = 'select * from eLogReport where RunId = ' + str(runId)

c.execute(sqlStr)

result = c.fetchone()

if(result == None):
    print 'run ' + str(runId) + ' does not exist in the database, abortted!'
    db.close()
    sys.exit()
    
# construct URL string for config report generated from online snapshots
    
configReportUrl = 'ftp://ftp-glast.slac.stanford.edu' + rootDataDir + str(runId) + '/config/ConfigTables.html'
    
# construct sql string to input data into oracle database.
# in python, \' is used to put ' inside a string.
# in oracle, '' is used to put ' inside a string.
                
sqlStr = 'update eLogReport set ConfigReportUrl =  \'' + configReportUrl + '\' where RunId = ' + str(runId);

try:
    c.execute(sqlStr)
except:
    (exc_type, exc_value) = sys.exc_info()[:2]

    print sqlStr
    print exc_type
    print exc_value

    db.rollback()
    db.close()
    sys.exit()
    
# safe to commit
db.commit()
    
#close database
db.close()
