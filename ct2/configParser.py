## @file configParser.py
## @brief Make LAT configuration tables 
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

#

import math

import html
import ndDict
import ndList
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
    if 0 in table.data:
        value = table.data[0]
        onOff = ['OFF', 'ON'][value]
    else:
        onOff = 'Unknown'
        pass
    output = '%s is %s.\n' % (label, onOff)
    return output


#
def hasTkr(doc):
    """Do we have a TKR?"""

    hasTkr = True

    frontEnds = doc.getElementsByTagName('GTFE')
    if len(frontEnds) < 1:
        hasTkr = False
    
    return hasTkr

#
def tkrSplits(doc):
    """Get GTRC splits."""

    output = []

    sectionTitle = "TKR GTRC Layer Readout Split Points"
    output.append(html.Heading(sectionTitle, 1))
    tabTitle = sectionTitle + ' (Left:Dead:Right)'
    
    if not hasTkr(doc):
        output.append("There is no TKR here!")
        return output

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

    # map from (side, GTRC) to (view, layer)
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

    # write split file
    writeSplits(viewSplits)

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
def writeSplits(splits):
    """Write out split file for use in (recon,digi) reports."""

    import sys

    splitFile = jobOptions.splitFile

    try:
        splitFP = open(splitFile, 'w')
    except:
        sys.stderr.write("can't open splitFile %s for writing!\n" % splitFile)
        sys.exit(1)
        pass

    splitFP.write("Tower Layer View Left Right\n")

    tems, views, layers = splits.indices()

    # lines labeled #yuk below are to try to avoid empty cells
    for item in tems:
        views, layers = splits[item].indices() #yuk
        for xy in views:
            (layers,) = splits[item, xy].indices() #yuk
            for ilayer in layers:
                iview = temUtil.invTkrSideMap[xy]
                split = splits[item, xy, ilayer]
                if split == jobOptions.absent:
                    split = '0:0:0'
                left, dead, right = map(int, split.split(':'))
                #print item, ilayer, iview, left, right
                splitFP.write('%2d %2d %s %2d %2d\n' % \
                              (item, ilayer, iview, left, right))
                pass
            pass
        pass

    splitFP.close()
    return

# embarrasingly similar to calFeReg
def tkrFeReg(doc):
    """get stuff from TKR front ends
    and make tables of it
    """

    output = []

    sectionTitle = "TKR front end (GTFE) settings"
    output.append(html.Heading(sectionTitle, 1))

    if not hasTkr(doc):
        output.append("There is no TKR here!")
        return output

    for registerTag in jobOptions.tkrTags:
        nTable = simpleTkrReg(doc, registerTag)
        output.extend(nTable)
        output.append(html.Element("HR"))
        pass
    output.append(html.Element("HR"))    
    return output

# embarrasingly similar to oneCalReg
def oneTkrReg(doc, tag):
    """Make a table for one GTFE register"""

    output = []
    
    axisLabels = jobOptions.tkrAxisLabels
    regSpec, regLabel = jobOptions.tables[tag]
    
    sectionTitle = "%s (%s)" % (regLabel, regSpec)
    output.append(html.Heading(sectionTitle, 2))

    xTable = tableFromXml.xTableGen(doc, regSpec)
    regTables = []
    tems = xTable.data.items()
    tems.sort()
    for iTem, temData in tems:
        gtccs = temData.items()
        gtccs.sort()
        for iGtcc, gtccData in gtccs:
            array, labels = gtccData.table()
            #layerMap = temUtil.tccLayerMap[iGtcc]
            layerMap = temUtil.planeMap[iGtcc]
            labels[0] = [layerMap[x] for x in labels[0]]
            #sideLabel = temUtil.tccSideMap[iGtcc]
            sideLabel = '%s %s' % \
                        (temUtil.views[iGtcc], temUtil.edgeMap[iGtcc])
            title = "%s for Tower %d side %s" % (regLabel, iTem, sideLabel)
            sideTable = table.twoDTable(array, title, axisLabels, labels)
            regTables.append(sideTable)
            pass
        pass
    nTable = html.nWay(regTables, jobOptions.tkrTabWidth)
    output.append(nTable)

    return output

def simpleTkrReg(doc, tag):
    """Make a table for one GTFE register, indexed by GTCC,GTRC and GFE"""

    output = []
    
    axisLabels = jobOptions.tkrSimpleAxisLabels
    regSpec, regLabel = jobOptions.tables[tag]
    
    sectionTitle = "%s (%s)" % (regLabel, regSpec)
    output.append(html.Heading(sectionTitle, 2))

    xTable = tableFromXml.xTableGen(doc, regSpec)
    regTables = []
    tems = xTable.data.items()
    tems.sort()
    for iTem, temData in tems:
        tccs = temData.items()
        tccs.sort()
        flatterArray = []
        
        junk, indices = temData.table()
        tfeLabels = indices[-1]
        readerLabels = []
        labels = (readerLabels, tfeLabels)

        for iTcc, (tccId, tccData) in enumerate(tccs):
            array, indices = tccData.table()
            for iTrc, trcId in enumerate(indices[0]):
                readerLabels.append('%s,%s (%s, %s)' %
                                    (tccId, trcId, temUtil.layerMap[tccId][trcId], temUtil.wEdgeMap[tccId]))
                flatterArray.append(array[iTrc])
                pass
            pass
        title = "%s for Tower %d" % (regLabel, iTem)
        sideTable = table.twoDTable(flatterArray, title, axisLabels, labels)
        regTables.append(sideTable)
        pass
    nTable = html.nWay(regTables, jobOptions.tkrTabWidth)
    output.append(nTable)

    return output



#
def hasCal(doc):
    """Do we have a CAL?"""

    hasCal = True
    
    frontEnds = doc.getElementsByTagName("GCFE")
    if len(frontEnds) < 1:
        hasCal = False
    
    return hasCal

#
def calFeReg(doc):
    """get stuff from CAL front ends
    and make tables of it
    """

    output = []

    sectionTitle = "CAL front end (GCFE) settings"
    output.append(html.Heading(sectionTitle, 1))

    if not hasCal(doc):
        output.append("There is no CAL here!")
        return output

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

    # per-cable times
    for name in jobOptions.cableDelays:
        dTable = oneCableDelay(doc, name)
        output.extend(dTable)
        output.append(html.Element("HR"))
        pass

    # GEM window width
    output.extend(gemStuff(doc))
    output.append(html.Element("HR"))    

    # per-TEM delays
    tTable = tackDelays(doc)
    output.extend(tTable)
    output.append(html.Element("HR"))    

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
def gemStuff(doc):
    output = []

    regSpec, sectionTitle = jobOptions.tables['GEM_WIDTH']
    output.append(html.Heading(sectionTitle, 2))

    dTab = tableFromXml.xTableGen(doc, regSpec)
    data = dTab.data[0]
    if data == jobOptions.absent:
        value = "Sorry, no GEM."
    else:
        if 0 in data:
            data = data[0]
            time = ticksToTime(data)
            value = '%s ticks = %s' % (data, time)
        else:
            value = jobOptions.absent
        pass
    output.append(value)

    return output

#
def tackDelays(doc):
    output = []

    sectionTitle = "Delays from trigger TACK to shaper hold"
    output.append(html.Heading(sectionTitle, 2))

    aTable = []

    for name in jobOptions.tackDelays:
        hTable = oneTack(doc, name)
        aTable.append(hTable)
        pass

    aTable = html.nWay(aTable, 3)
    output.append(aTable)
    
    return output

#
def oneTack(doc, name):
    regSpec, junk = jobOptions.tables[name]
    title, columns = jobOptions.tackDelayLabels[name]
    
    regTable = tableFromXml.xTableGen(doc, regSpec)
    labels = regTable.data.indices()[0]
    data = regTable.data.map(displayTime)
    data, labels = data.table()
    hTable = table.oneDTable(zip(labels[0], data), title, columns)

    return hTable


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
