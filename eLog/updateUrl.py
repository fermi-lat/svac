#!/afs/slac.stanford.edu/g/glast/applications/install/i386_linux22/usr/bin/python
"""Usage: updateReportUrl.py runId reportType [dataRoot]

reportType must be one of (config, recon, digi).

dataRoot is the root directory for the run tree on the FTP server
(default glast.u01/EM2/rootData).

"""

import sys
import DCOracle2

#used to form ftp URL - default value
rootDataDir = 'glast.u01/EM2/rootData'

location = {"config": "config/v0r0/ConfigTables.html",
            "digi": "digi_report/v0r0/html/index.html",
            "recon": "calibv0/recon_report/v0r0/html/index.html"}

urlKey = {"config": "ConfigReportUrl",
          "digi": "DigiReportUrl",
          "recon": "ReconReportUrl",}

failCode = 1

# parse args
nArg = len(sys.argv)
if nArg == 3:
    runId, reportType = sys.argv[1:]
elif nArg == 4:
    runId, reportType, rootDataDir = sys.argv[1:]    
else:
    print __doc__
    sys.exit(failCode)    

if reportType not in location:
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
    
# construct URL string for config report generated from online snapshots
reportUrl = "ftp://ftp-glast.slac.stanford.edu/%s/%s/%s" % \
            (rootDataDir, runId, location[reportType])
    
# construct sql string to input data into oracle database.
# in oracle, '' is used to put ' inside a string.
sqlStr = "update eLogReport set %s = '%s' where RunId = %s" % \
         (urlKey[reportType], reportUrl, runId)

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
