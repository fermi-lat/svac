## @file configParser.py
## @brief Make LAT configuration tables 
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

#

import math

import html
import ndDict
import htmlTable as table
import tableFromXml
import temUtil

import jobOptions


#
def globalStuff(doc):
    """Deal with stuff that applies to the whole instrument"""
    
    output = []

    sectionTitle = 'LAT globals'
    output.append(html.Heading(sectionTitle, 1))

    for name in jobOptions.globoLogicals:
        tag, label = jobOptions.tables[name]
        line = globoLogical(doc, tag, label)
        output.append(line)
        #output.append(html.Element("BR"))
        output.append('<br/>')
    
    output.append(html.Element("HR"))    
    output.append(html.Element("HR"))    
    return output

#
def globoLogical(doc, tag, label):
    table = tableFromXml.xTableGen(doc, tag)
    value = table.data[0]
    onOff = ['OFF', 'ON'][value]
    output = '%s is %s.\n' % (label, onOff)
    return output


#
def tkrSplits(doc):
    """Get GTRC splits."""

    output = []

    sectionTitle = "TKR GTRC Layer Readout Split Points"
    output.append(html.Heading(sectionTitle, 1))
    tabTitle = sectionTitle + ' (Left:Dead:Right)'
    
    # read in nRead field from GTRC csr registers
    regSpec, regLabel = jobOptions.tables['TKR_NR']
    nRead = tableFromXml.xTableGen(doc, regSpec)
    # read in GTFE mode registers
    regSpec, regLabel = jobOptions.tables['TKR_MODE']
    mode = tableFromXml.xTableGen(doc, regSpec)

    nReadData, (tems, cables, readers) = nRead.data.table()
    modeData, junk = mode.data.table()

    # calculate spilt points
    sideSplits = ndDict.ndDict(dim=3, empty=jobOptions.absent)
    for temCell, iTem in enumerate(tems):
        temRead = nReadData[temCell]
        temMode = modeData[temCell]
        for iSide, (left, right) in enumerate(temUtil.tccLRMap):
            for layerCell, iLayer in enumerate(readers):
                split = temUtil.getSplit(temRead[left, layerCell],
                                         temRead[right, layerCell],
                                         temMode[left, layerCell],
                                         temMode[right, layerCell])
                sideSplits[iTem, iSide, iLayer] = split
                pass
            pass
        pass

    # map from (side, GTRC) to (view. layer)
    viewSplits = ndDict.ndDict(dim=3, empty=jobOptions.absent)
    tems, sides, readers = sideSplits.indices()
    for iTem in tems:
        for iSide in sides:
            for iReader in readers:
                view, layer = temUtil.tkrLayerMap[iSide][iReader]
                viewSplits[iTem, view, layer] = sideSplits[iTem, iSide, iReader]
                pass
            pass
        pass

    tems, views, layers = viewSplits.indices()
    layers.reverse()

    width = jobOptions.tkrSplitWidth
    nTab = int(math.ceil(float(len(tems)) / width))
    temChunks = [tems[iChunk*width:(iChunk+1)*width] for iChunk in range(nTab)]

    # construct table(s)
    for chunk in temChunks:
        tabData = []
        for iLayer in layers:
            row = [iLayer]
            for iTem in chunk:
                for iView in views:
                    row.append(viewSplits[iTem, iView, iLayer])
                    pass
                pass
            tabData.append(row)
            pass
        tabColumns = ['Layer']
        for iTem in chunk:
            for iView in views:
                tabColumns.append('Tower %s %s' % (iTem, iView))
                pass
            pass
        
        splitTab = table.oneDTable(tabData, tabTitle, tabColumns)
        output.append(splitTab)
        pass

    output.append(html.Element("HR"))    
    output.append(html.Element("HR"))    
    return output


#
def calFeReg(doc):
    """get stuff from CAL front ends
    and make tables of it
    """

    output = []

    sectionTitle = "CAL front end (GCFE) settings"
    output.append(html.Heading(sectionTitle, 1))
    
    for registerTag in jobOptions.calTags:
        nTable = oneCalReg(doc, registerTag)
        output.extend(nTable)
        output.append(html.Element("HR"))
        pass
    output.append(html.Element("HR"))    
    return output

#
def oneCalReg(doc, tag):
    """Make a table for one GCFE register"""

    output = []
    
    axisLabels = jobOptions.calAxisLabels
    regSpec, regLabel = jobOptions.tables[tag]
    
    sectionTitle = "%s (%s)" % (regLabel, regSpec)
    output.append(html.Heading(sectionTitle, 2))

    xTable = tableFromXml.xTableGen(doc, regSpec)
    regTables = []
    tems = xTable.data.items()
    tems.sort()
    for iTem, temData in tems:
        gcccs = temData.items()
        gcccs.sort()
        for iGccc, gcccData in gcccs:
            array, labels = gcccData.table()
            layerMap = temUtil.cccLayerMap[iGccc]
            labels[0] = [layerMap[x] for x in labels[0]]
            sideLabel = temUtil.cccSideMap[iGccc]
            title = "%s for Tower %d side %s" % (regLabel, iTem, sideLabel)
            sideTable = table.twoDTable(array, title, axisLabels, labels)
            regTables.append(sideTable)
            pass
        pass
    nTable = html.nWay(regTables, jobOptions.calTabWidth)
    output.append(nTable)

    return output


#
def delays(doc):
    output = []

    sectionTitle = "Synchronization timings"
    output.append(html.Heading(sectionTitle, 1))

    for name in jobOptions.cableDelays:
        dTable = oneCableDelay(doc, name)
        output.extend(dTable)
        output.append(html.Element("HR"))
        pass

    output.append(html.Element("HR"))    
    return output

#
def oneCableDelay(doc, name):
    output = []
    
    axisLabels = jobOptions.cableLabels
    regSpec, regLabel = jobOptions.tables[name]

    sectionTitle = '%s (%s)' % (regLabel, regSpec)
    output.append(html.Heading(sectionTitle, 2))
    tableTitle = regLabel + ' (ticks (ns))'

    ticks = tableFromXml.xTableGen(doc, regSpec)
    times = ticks.data.map(displayTime)
    timeData, labels = times.table()
    dTable = table.twoDTable(timeData, tableTitle, axisLabels, labels)
    output.append(dTable)

    return output

#
def ticksToTime(ticks):
    seconds = ticks * jobOptions.tick
    scaled = seconds * jobOptions.timeScale
    scaled = int(scaled + 0.5)
    time = '%s%s' % (scaled, jobOptions.timeUnits)
    return time

#
def displayTime(ticks):
    time = '%s (%s)' % (ticks, ticksToTime(ticks))
    return time
