"""@brief Register output data with the data server.
@author W. Focke <focke@slac.stanford.edu>
"""
# This script is automagically pasted into the XML at install time

from java.util import HashMap
from org.glast.datacat.client.sql import NewDataset

def getVar(fileType, name):
    mangledName = '_'.join([nameManglingPrefix, fileType, name])
    value = parentPI.getVariable(mangledName)
    return value

parentPI = pipeline.getProcessInstance(parentProcess)

runNumber = int(RUNID[1:])

dsName = RUNID
fileFormat = getVar(fileType, 'format')
dcPath = getVar(fileType, 'path')
dcGroup = getVar(fileType, 'group')
site = getVar(fileType, 'site')
fileName = getVar(fileType, 'fileName')
creator = getVar(fileType, 'creator')

fcPi = pipeline.getProcessInstance(timeProcess)
lessBrokenTStart = fcPi.getVariable('tStart')
lessBrokenTStop = fcPi.getVariable('tStop')

attributes = HashMap()
attributes.put('sCreator', creator)
attributes.put('sDataSource', DATASOURCE)
attributes.put('nDownlink', DOWNLINK_ID)
attributes.put('sIntent', mootAlias)
attributes.put('nMetStart', lessBrokenTStart)
attributes.put('nMetStop', lessBrokenTStop)
attributes.put('nMootKey', mootKey)
attributes.put('nRun', runNumber)

print attributes

dsNew = NewDataset(dsName, fileFormat, fileType, dcPath, dcGroup, site, fileName)
ds = datacatalog.registerDataset(dsNew, attributes);
