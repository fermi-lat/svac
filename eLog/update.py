#!/afs/slac.stanford.edu/g/glast/applications/install/i386_linux22/usr/bin/python
"""Usage: update.py [xmlFile] [dataRoot] [rawRoot]

xmlFile is the run report (default rcReport.out)

rawRoot is the root directory for the raw data tree on the FTP server
(default is environment variable rawUrl)

dataRoot is the root directory for the root data tree on the FTP server
(default is environment variable rootUrl)

"""

import os
import sys
from xml.dom.ext.reader import Sax2
from xml.dom import Node
import string
import re
import DCOracle2

oracleTimeFormat = 'YYYY-MM-DD HH24:MI:SS'

def execSql(c, sqlStr):
    try:
        c.execute(sqlStr)
    except:
        (exc_type, exc_value) = sys.exc_info()[:2]

        print sqlStr
        print exc_type
        print exc_value

        db.rollback()
        db.close()
        sys.exit(1) 
    
# parse time to a format for oracle
def parseTime(l):
    l = l.split('(')
    l = l[1].split(')')
    l = l[0].split(', ')
    
    # make month, date, hour, min and sec to 2 digits if they are one
    # this is required by time format for Oracle

    for i in range(1, 5):
        if len(l[i]) == 1:
            l[i] = '0' + l[i]
            
    time = l[0] + '-' + l[1] + '-' + l[2] + ' ' + l[3] + ':' + l[4] + ':' + l[5]

    return time

# check whether there is a new data value in the tables if so, add the new
# value to table. This is necessary since eLog perl cgi scripts will
# dynamically produce a drop down menu based on contents of the table
def checkNewValue(value, table, col):

# it is necessary to lock the table here since this script can be run in
# multiple batch jobs to cause a race condition
    sqlStr = 'lock table ' + table + ' in exclusive mode'
    
    execSql(c, sqlStr)
    
    id = {'eLogSite':'Seq_eLogSiteID.NextVal', 'eLogPhase':'Seq_eLogPhaseID.NextVal', 'eLogOrientation':'Seq_eLogOrientationID.NextVal', 'eLogInstrumentType':'Seq_eLogInstrumentTypeID.NextVal', 'eLogParticleType':'Seq_eLogParticleTypeID.NextVal'};
          
    sqlStr = 'select ' + col + ' from ' + table + ' where ' + col + ' = \'' + value + '\''
    execSql(c, sqlStr)
    result = c.fetchone()

    if(result == None):
        print 'new ' + col + ' value found: ' + value + ', adding it to the database'
        sqlStr = 'insert into ' + table + ' values(' + id[table] + ', \'' + value + '\')'
        execSql(c, sqlStr)

# parse SerialNos tag in rcReport to reture a list containing 3 info:
# 1. no. of towers 2. serial no. of TKRs 3. serial no. of CALs
def parseSerialNosTag(value):
    dict = eval(value)

    nTowers = 0

    tkrSerNo = ''
    calSerNo = ''

    for k, v in dict.iteritems():
        if(re.match('GTEM', k)):
            nTowers += 1
            if(v.has_key('tkr')):
                tkrSerNo = tkrSerNo + v['tkr'] + '???'
            if(v.has_key('calinstrument')):
                calSerNo = calSerNo + v['calinstrument'] + '???'

    return [nTowers, tkrSerNo, calSerNo]

# turn a string of a python list to a string of items in the list separated
# by : in order to save storage in oracle
def transformStrList(string):

    l = eval(string)

    oracleStr = ''

    length = len(l)

    for item in l[0:length-1]:
        oracleStr = oracleStr + str(item) + ':'

    oracleStr += str(l[length-1])

    return oracleStr


def insertIntRunConfigId(id):

    sqlStr = 'lock table elogintrunconfiguration in exclusive mode'
    
    execSql(c, sqlStr)
    
    l = eval(id)

    sqlStr= 'select id from elogintrunconfiguration where E2EID=\'' + l[0] + '\' and configid=' + l[1]

    execSql(c, sqlStr)
    result = c.fetchone()

    if(result == None):
        print 'new intRunConfiguration id found: ' + l[0] + ' ' + l[1] + ', adding it to the database'
        sqlStr = 'insert into elogintrunconfiguration  values(Seq_eLogIntRunConfigurationID.NextVal, \'' +  l[0] + '\', ' + l[1]+ ', \'\')'
        execSql(c, sqlStr)
        sqlStr= 'select id from elogintrunconfiguration where E2EID=\'' + l[0] + '\' and configid=' + l[1]

        execSql(c, sqlStr)
        result =  c.fetchone()

    [id] = result
    return id

# main codes start from here 
#used to form ftp URL - default value
xmlFileName = 'rcReport.out'
#rootDataDir = '/glast.u12/EM2/rootData/'
rootDataDir = os.environ['rootUrl']
#rawDataDir = '/glast.u12/EM2/rawData/'
rawDataDir = os.environ['rawUrl']

# parse args
nArg = len(sys.argv)
if nArg == 2:
    xmlFileName = sys.argv[1]
elif nArg == 3:
    xmlFileName, rootDataDir = sys.argv[1:]
elif nArg == 4:
    xmlFileName, rootDataDir, rawDataDir = sys.argv[1:]
else:
    print __doc__
    sys.exit(99)    

#define tags for xml

testReportTag = 'testReport'
timeStampTag = 'timestamp'
runIdTag = 'RunId'
testNameTag = 'TestName'
operatorTag = 'Operator'
operatorIdTag = 'OperatorId'
eventCountTag = 'EventCount'
badEventCountTag = 'BadEventCount'
pauseCountTag = 'PauseCount'
startTimeTag = 'StartTime'
elapsedTimeTag = 'ElapsedTime'
endTimeTag = 'EndTime'
schemaConfigFileTag = 'SchemaConfigFile'
additionalInputFilesTag = 'AdditionalInputFiles'
releaseTag = 'Release'
modulesFailedVerificationTag = 'ModulesFailedVerification'
versionDataTag = 'VersionData'
completionStatusTag = 'CompletionStatus'
completionStatusStrTag = 'CompletionStatusStr'
archiveFileTag = 'ArchiveFile'
errorArchiveTag = 'ErrorArchive'
commentsTag = 'comments'
logFileTag = 'LogFile'
fitsFileTag = 'FITSfile'
siteTag = 'Site'
particleTypeTag = 'ParticleType'
instrumentTypeTag = 'InstrumentType'
orientationTag = 'Orientation'
phaseTag = 'Phase'
commentsTag = 'Comments'
errorEventCountTag = 'ErrorEventCount'
# note additionFields is not a tag in rcReport.out, it is a column in the
# table to store any unfound tags
additionFieldsTag = 'additionFields'
onlineReportTag = 'ScriptReport'
csvTestIdTag = 'csvTestId'
serNoTag = 'SerialNos'
suiteNameTag = 'suiteName'
suiteRunListTag = 'suiteRunList'
suiteTimeStampTag = 'suiteTimeStamp'

tags = [timeStampTag, testNameTag, runIdTag, operatorTag, operatorIdTag, eventCountTag, badEventCountTag, pauseCountTag, startTimeTag, elapsedTimeTag, endTimeTag, schemaConfigFileTag, additionalInputFilesTag, releaseTag, modulesFailedVerificationTag, versionDataTag, completionStatusTag, completionStatusStrTag, archiveFileTag, errorArchiveTag, logFileTag, fitsFileTag, siteTag, particleTypeTag, instrumentTypeTag, orientationTag, phaseTag, commentsTag, errorEventCountTag, onlineReportTag, suiteNameTag, suiteRunListTag, suiteTimeStampTag]

# create Reader object
reader = Sax2.Reader()

xmlFile = open(xmlFileName)
#xmlFile = open('newrep.out')

errFile = open('err.log', 'w')

#open connection to oracle database
db = DCOracle2.connect('GLAST_CAL/9square#')

c = db.cursor()

# parse the document
try:
    doc = reader.fromStream(xmlFile)
except:
    msg = 'rcReport %s is missing, unreadable, or invalid.\n' % xmlFileName
    sys.stderr.write(msg)
    errFile.write(msg)
    sys.exit(0)
    
reports = doc.getElementsByTagName(testReportTag)

for report in reports:
    
    e = report.getAttribute(timeStampTag)

    if(e == None):
        errFile.write('timestamp can not be found for report \n')
        continue

    data = { }
            
    data[timeStampTag] = parseTime(e)
    
    data[additionFieldsTag] = ''
    
    intRunConfigId = 'null'

    for node in report.childNodes:

        if (node.nodeType == Node.TEXT_NODE and \
         (node.data[0] == '\n' or node.data[0].strip() == '')) \
         or node.nodeType == Node.COMMENT_NODE:
            continue;
        
        name = node.nodeName
        
        if(name == serNoTag):
            [nTowers, tkrSerNo, calSerNo] = parseSerialNosTag(node.childNodes[0].data)
        elif( name == csvTestIdTag ):
            intRunConfigId = insertIntRunConfigId(node.childNodes[0].data)
            
        if(name not in tags):
            
            # if tag is not found, append it to data['additionFields']
            # format is fieldName???value!!!
            # all addition fields are saved as string
           
            data[additionFieldsTag] = data[additionFieldsTag] + name + '???' + node.childNodes[0].data + '!!!'
            
            continue

        if ((name == startTimeTag) or (name == endTimeTag)
            or (name == suiteTimeStampTag)):
            data[name] = parseTime(node.childNodes[0].data)
        elif( name == suiteRunListTag ):
            data[name] = transformStrList(node.childNodes[0].data)
        elif (
              name == releaseTag or
              name == additionalInputFilesTag
              ):
            #replace ' with '' in order to input data into oracle
            data[name] = node.childNodes[0].data
            data[name] = string.replace(data[name], '\'', '\'\'')
        else: 
            data[name] = node.childNodes[0].data

# fill in default
    if(data.has_key(badEventCountTag) == 0):
        data[badEventCountTag] = '0'
    if(data.has_key(errorEventCountTag) == 0):
        data[errorEventCountTag] = '0'

    for tag in tags:
        if(data.has_key(tag) == 0):
#            errFile.write(tag + ' is not found! Set to empty! \n')
            data[tag] = ''

    print 'Processing run ' + data[runIdTag]
    
    # determine whether run is already in the database
    sqlStr = 'select * from eLogReport where RunId = ' + data[runIdTag]

    c.execute(sqlStr)

    result = c.fetchone()

    if(result != None):
        print 'run ' + data[runIdTag] + ' already exists in the database, ignore this run'
        continue

    sqlStr = 'lock table eLogCompletionStatus in exclusive mode'
    
    execSql(c, sqlStr)
    
    #determine whether there is a new completionStatus value
    sqlStr = 'select Id from eLogCompletionStatus where Id = ' + data[completionStatusTag]
    c.execute(sqlStr)
    result = c.fetchone()

    if(result == None):
        print 'new completion status value found: ' + data[completionStatusTag] + ' adding it to the database'
        sqlStr = 'insert into eLogCompletionStatus values(' + data[completionStatusTag] + ', \'' + data[completionStatusStrTag] + '\')'
        try:
            c.execute(sqlStr)
        except:
            (exc_type, exc_value) = sys.exc_info()[:2]

            print sqlStr
            print exc_type
            print exc_value

            db.rollback()
            continue

    # determine whether there is a new site
    checkNewValue(data[siteTag], 'eLogSite', 'Site')

    # determine whether there is a new phase
    checkNewValue(data[phaseTag], 'eLogPhase', 'Phase')

    # determine whether there is a new particle type
    checkNewValue(data[particleTypeTag], 'eLogParticleType', 'Type')

    # determine whether there is a new instrument type
    checkNewValue(data[instrumentTypeTag], 'eLogInstrumentType', 'Instrument')

    # determine whether there is a new orientation
    checkNewValue(data[orientationTag], 'eLogOrientation', 'Orientation')

    # construct URL string for online test report 
    
    onlineReportUrl = 'ftp://ftp-glast.slac.stanford.edu' + '/' + rawDataDir + '/' + data[runIdTag] + '/'
    
    if(data.has_key(onlineReportTag)):
        onlineReportUrl += data[onlineReportTag]
     
    # construct sql string to input data into oracle database.
    # in python, \' is used to put ' inside a string.
    # in oracle, '' is used to put ' inside a string.
            
    # modulesFailedVerification, Comments, versionData, additionFields
    # are stored as CLOB in oracle, they need to be binded in order to insert
    
    sqlStr = 'insert into eLogReport(TimeStamp, RunID, TestName, Operator, OperatorId, EventCount, BadEventCount, PauseCount, StartTime, ElapsedTime, EndTime, SchemaConfigFile, AdditionalInputFiles, Release, ModulesFailedVerification, VersionData, CompletionStatus, ArchiveFile, ErrorArchive, LogFile, FitsFile, Site, ParticleType, InstrumentType, Orientation, Phase, Comments, AdditionFields, ErrorEventCount, OnlineReportUrl, NoOfTowers, TKR_SER_NO, CAL_SER_NO, intRunConfigId) values( to_date(\'' + data[timeStampTag] + '\', \'' + oracleTimeFormat + '\'), ' + data[runIdTag] + ', \'' + data[testNameTag] + '\', \'' + data[operatorTag] + '\', ' + data[operatorIdTag] + ', ' + data[eventCountTag] + ', ' + data[badEventCountTag] + ', ' + data[pauseCountTag] + ', to_date(\'' + data[startTimeTag] + '\', \'' + oracleTimeFormat + '\'), ' + data[elapsedTimeTag] + ', to_date(\'' + data[endTimeTag] + '\', \'' + oracleTimeFormat + '\'), ' + '\'' + data[schemaConfigFileTag] + '\', \'' + data[additionalInputFilesTag] + '\', \'' + data[releaseTag] + '\', :1, :2, ' + data[completionStatusTag] + ', \'' + data[archiveFileTag] + '\', \'' + data[errorArchiveTag] + '\', \'' + data[logFileTag] + '\', \'' + data[fitsFileTag] + '\', \'' + data[siteTag] + '\', \'' + data[particleTypeTag] + '\', \'' + data[instrumentTypeTag] + '\', \'' + data[orientationTag] + '\', \'' + data[phaseTag] + '\', :3, :4, ' + data[errorEventCountTag] + ', \'' + onlineReportUrl + '\' ,' + str(nTowers) + ', \'' + tkrSerNo + '\', \'' + calSerNo + '\', ' + str(intRunConfigId) + ')'
       
    try:
       c.execute(sqlStr, str(data[modulesFailedVerificationTag]), str(data[versionDataTag]), str(data[commentsTag]), str(data[additionFieldsTag]))
    except:
       (exc_type, exc_value) = sys.exc_info()[:2]

       print sqlStr
       print exc_type
       print exc_value

       db.rollback()
       continue

    if(data[testNameTag] == 'suiteSummary'):
        sqlStr = 'update eLogReport set suiteName = \'' + data[suiteNameTag] + '\', suiteTimeStamp = to_date(\'' + data[suiteTimeStampTag] + '\', \'' + oracleTimeFormat + '\'), suiteRunList = \'' + data[suiteRunListTag] + '\' where runid = ' + data[runIdTag]

        try:
            c.execute(sqlStr)
        except:
            (exc_type, exc_value) = sys.exc_info()[:2]

            print sqlStr
            print exc_type
            print exc_value

            db.rollback()
            continue    

    # safe to commit
    db.commit()
    
#close database
db.close()
