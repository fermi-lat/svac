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

attributes = HashMap()
attributes.put('nMetStart', tStart)
attributes.put('nMetStop', tStop)
attributes.put('sDataSource', DATASOURCE)
attributes.put('nRun', runNumber)
attributes.put('nDownlink', DOWNLINK_ID)
attributes.put('sCreator', creator)

dsNew = NewDataset(dsName, "root", fileType, dcPath, dcGroup, site, fileName)
ds = datacatalog.registerDataset(dsNew, attributes);
