## @file configParser.py
## @brief Make LAT configuration tables 
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

#

import math

import bitField
import eLogDB
import html
import mappings
import ndDict
import ndList
import htmlTable as table
import tableFromXml
import temUtil

import jobOptions

#
def hasGlt(doc):
    """"""
    hasGlt = True
    glts = doc.getElementsByTagName('GGLT')
    if len(glts) < 1:
        hasGlt = False
    return hasGlt

#
def globalStuff(doc):
    """@brief Deal with stuff that applies to the whole instrument"""
    
    output = []

    sectionTitle = 'LAT globals'
    output.append(html.Heading(sectionTitle, 1))

    if hasGlt(doc):
        for name in jobOptions.globoLogicals:
            tag, label = jobOptions.tables[name]
            line = globoLogical(doc, tag, label)
            output.append(line)
            output.append('<br/>\n')
            pass
        pass

    output.extend(globalDBStrings())
    output.append('<br/>\n')

    return output

#
def globalDBStrings():
    """@brief Deal with LAT globals that are read from eLog DB as strings."""
    output = []

    tags = jobOptions.globalDBKeys
    args = [jobOptions.runNumber]
    args.extend(tags)

    values = eLogDB.query(*args)
    values = map(nicenDBStrings, values)

    for tag, value in zip(tags, values):
        if not value:
            break
        label = jobOptions.globalDBStringLabels[tag]
        line = "%s: %s\n" % (label, value)
        output.append(line)
        output.append('<br/>\n')
        pass

    return output

def nicenDBStrings(oldString):
    """@brief make ???-delimited strings from eLogDB look nicer."""
    strings = oldString.split('???')
    strings = [xx for xx in strings if xx]
    newString = ', '.join(strings)
    return newString

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
    """@brief Do we have a TKR?"""

    hasTkr = True

    frontEnds = doc.getElementsByTagName('GTFE')
    if len(frontEnds) < 1:
        hasTkr = False
    
    return hasTkr

#
def tkrSplits(doc):
    """@brief Get GTRC splits."""

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

    # # write split file
    # writeSplits(viewSplits)
    # # no, don't

    tems, views, layers = viewSplits.indices()
    layers.reverse()

    # split into multi tables so it fits in the width of the page
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

    return output


#
def writeSplits(splits):
    """@brief Write out split file for use in (recon,digi) reports.

    We don't use this anymore.  Never did, actually.

    """

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
    """@brief Get stuff from TKR front ends
    and make tables of it.
    """

    output = []

    sectionTitle = "TKR front end (GTFE) settings"
    output.append(html.Heading(sectionTitle, 1))
    output.append(html.Element("HR"))    

    if not hasTkr(doc):
        output.append("There is no TKR here!")
        return output

    for registerTag in jobOptions.tkrTags:
        nTable = simpleTkrReg(doc, registerTag)
        output.extend(nTable)
        output.append(html.Element("HR"))
        pass
    return output

# embarrasingly similar to oneCalReg
def oneTkrReg(doc, tag):
    """@brief Make a table for one GTFE register
    Tries to map layers as seen in recon file."""

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
    """@brief Make a table for one GTFE register, indexed by GTCC,GTRC and GFE"""

    output = []
    
    axisLabels = jobOptions.tkrSimpleAxisLabels
    regSpec, regLabel = jobOptions.tables[tag]
    
    sectionTitle = "%s (%s)" % (regLabel, regSpec)
    output.append(html.Heading(sectionTitle, 2))

    xTable = tableFromXml.xTableGen(doc, regSpec)

    if jobOptions.mappers.has_key(tag):
        xTable.data = xTable.data.map(jobOptions.mappers[tag])
        pass
    
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
def perGtrc(doc):
    """@brief Make tables for stuff that comes from GTRCs.

    """
    
    output = []

    sectionTitle = "TKR readout controller (GTRC) settings"
    output.append(html.Heading(sectionTitle, 1))
    output.append(html.Element("HR"))    

    if not hasTkr(doc):
        output.append("There is no TKR here!")
        return output

    for registerTag in jobOptions.gtrcTags:
        nTable = oneGtrcReg(doc, registerTag)
        output.extend(nTable)
        output.append(html.Element("HR"))
        pass
    return output

#
def oneGtrcReg(doc, tag):
    """@brief Make tables for one GTRC register.

    """

    output = []

    regSpec, regLabel = jobOptions.tables[tag]
    axisLabels = jobOptions.gtrcLabels

    sectionTitle = "%s (%s)" % (regLabel, regSpec)
    output.append(html.Heading(sectionTitle, 2))

    xTable = tableFromXml.xTableGen(doc, regSpec)

    regTables = []
    tems = xTable.data.items()
    tems.sort()
    for iTem, temData in tems:
        array, indices = temData.table()
        title = "%s for Tower %d" % (regLabel, iTem)
        hTable = table.twoDTable(array, title, axisLabels, indices)
        regTables.append(hTable)
        pass
    nTable = html.nWay(regTables, jobOptions.rcWidth)
    output.append(nTable)
    
    return output


################################ ACD ####################################

#
def hasAcd(doc):
    """@brief Do we have an ACD?"""

    hasAcd = True

    frontEnds = doc.getElementsByTagName("GAFE")
    if len(frontEnds) < 1:
        hasAcd = False
        pass

    return hasAcd
    
#
def oneGarc(doc, name, mappers):
    """@brief Make tables of per-GARC values."""
    output = []

    display, units = mappers

    columnLabels = jobOptions.garcLabels
    regSpec, regLabel = jobOptions.tables[name]

    sectionTitle = '%s (%s)' % (regLabel, regSpec)
    output.append(html.Heading(sectionTitle, 2))
    tableTitle = regLabel + units

    ticks = tableFromXml.xTableGen(doc, regSpec)
    if not ticks.data:
        return []
    times = ticks.data.map(display)
    timeData, labels = times.table()

    data = zip(labels[1], timeData[0])
    
    dTable = table.oneDTable(data, tableTitle, columnLabels)
    output.append(dTable)    
    
    return output

#
def manyGarcs(doc, names, mappers):
    """@brief Organize multiple table of per-GARC values."""
    output = []

    # This was gonna put several tables side-by-side, as they're tall and skinny.
    # But I'm not sure what to do with the titles & captions.

    for name in names:
        dTable = oneGarc(doc, name, mappers)
        output.extend(dTable)        
        output.append(html.Element("HR"))
        pass
    output.append(html.Element("HR"))

    return output

#
def garcMask(doc, base):
    """@brief Format GARC PHA and veto enables."""
    output = []

    data = []

    regs = jobOptions.acdMaskRegs[base]
    regLens = (16, 2)
    for reg, regLen in zip(regs, regLens):
        dTable = tableFromXml.xTableGen(doc, reg)
        masks, labels = dTable.table()
        masks = masks[0]
        for mask in masks:
            for bit in range(regLen):
                # oh crap
                pass
            pass
        pass
    
    return output
    
#
def oneGafeReg(doc, tag):
    """@brief Make a table for one GAFE register"""

    output = []
    
    axisLabels = jobOptions.gafeLabels
    regSpec, regLabel = jobOptions.tables[tag]
    
    sectionTitle = "%s (%s)" % (regLabel, regSpec)
    output.append(html.Heading(sectionTitle, 2))

    xTable = tableFromXml.xTableGen(doc, regSpec)
    data, indices = xTable.data.table()

    # only one GAEM
    data = data[0]
    indices = indices[1:]

    hTable = table.twoDTable(data, regLabel, axisLabels, indices)

    output.append(hTable)
    return output

def gafeRegs(doc):
    """@grief Display stuff that lives in GAFE registers"""
    output = []

    sectionTitle = 'GAFE Reisters'
    output.append(html.Heading(sectionTitle, 2))
    output.append(html.Element("HR"))

    for tag in jobOptions.acdGafe:
        output.extend(oneGafeReg(doc, tag))
        output.append(html.Element("HR"))
        pass
    
    return output

#
def acdStuff(doc):
    """@brief ACD stuff"""
    output = []

    sectionTitle = 'ACD'
    output.append(html.Heading(sectionTitle, 1))
    output.append(html.Element("HR"))
    output.append(html.Element("HR"))

    output.append(html.Heading('Voltage conversions are bogus!', 2))
    output.append(html.Element("HR"))
    output.extend(manyGarcs(doc, jobOptions.acdHvTags, jobOptions.voltMap))
    output.extend(manyGarcs(doc, jobOptions.acdGarcRandom, jobOptions.hexMap))
    output.extend(gafeRegs(doc))
    output.append(html.Element("HR"))
        
    return output

################################ CAL ####################################

#
def hasCal(doc):
    """@brief Do we have a CAL?"""

    hasCal = True
    
    frontEnds = doc.getElementsByTagName("GCFE")
    if len(frontEnds) < 1:
        hasCal = False
    
    return hasCal

#
def calFeReg(doc):
    """@brief Get stuff from CAL front ends
    and make tables of it
    """

    output = []

    sectionTitle = "CAL front end (GCFE) settings"
    output.append(html.Heading(sectionTitle, 1))
    output.append(html.Element("HR"))    

    if not hasCal(doc):
        output.append("There is no CAL here!")
        return output

    for registerTag in jobOptions.calTags:
        nTable = oneCalReg(doc, registerTag)
        output.extend(nTable)
        output.append(html.Element("HR"))
        pass
    return output

#
def oneCalReg(doc, tag):
    """@brief Make a table for one GCFE register"""

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

################## Synchronization delays ###########################

#
def delays(doc):
    """@brief Top-level function for all synchronization delays."""
    output = []

    sectionTitle = "Synchronization timings"
    output.append(html.Heading(sectionTitle, 1))
    output.append(html.Element("HR"))    

    # anyTems = hasTem(doc)
    anyTems = True

    # per-cable times
    if anyTems:
        for name in jobOptions.cableDelays:
            dTable = oneCableDelay(doc, name)
            output.extend(dTable)
            pass
        output.append(html.Element("HR"))
        pass

    # per-GARC times
    if hasAcd(doc):
        output.extend(manyGarcs(doc, jobOptions.garcDelays, jobOptions.timeMap))
        pass
    
    # GEM window width
    output.extend(gemTimes(doc))
    output.append(html.Element("HR"))    

    # per-TEM delays
    if anyTems:
        tTable = tackDelays(doc)
        output.extend(tTable)
        output.append(html.Element("HR"))
        pass
    
    # CAL delays
    if hasCal(doc):
        output.extend(calDelays(doc))
        output.append(html.Element("HR"))
        pass

    return output

#
def oneCableDelay(doc, name):
    """@brief Make tables of per-cable delays for one type of cable controller."""
    output = []
    
    axisLabels = jobOptions.cableLabels
    regSpec, regLabel = jobOptions.tables[name]

    sectionTitle = '%s (%s)' % (regLabel, regSpec)
    output.append(html.Heading(sectionTitle, 2))
    tableTitle = regLabel + ' (ticks (ns))'

    ticks = tableFromXml.xTableGen(doc, regSpec)
    if not ticks.data:
        return []
    times = ticks.data.map(mappings.displayTime)
    timeData, labels = times.table()
    dTable = table.twoDTable(timeData, tableTitle, axisLabels, labels)
    output.append(dTable)

    return output


#
def hasGem(doc):
    """@brief Do we have a GEM?"""
    
    hasGem = True
    
    gems = doc.getElementsByTagName("GGEM")
    if len(gems) < 1:
        hasGem = False
    
    return hasGem

#
def gemTimes(doc):
    """@brief Display synchronization delays that live in GGEM."""
    output = []

    regSpec, sectionTitle = jobOptions.tables['GEM_WIDTH']
    output.append(html.Heading(sectionTitle, 2))

    if not hasGem(doc):
        output.append("Sorry, no GEM.")
        return output

    dTab = tableFromXml.xTableGen(doc, regSpec)
    data = dTab.data[0]
    if 0 in data:
        data = data[0]
        time = mappings.ticksToTime(data)
        value = '%s ticks = %s' % (data, time)
    else:
        value = jobOptions.absent
        pass
    output.append(value)

    return output

#
def tackDelays(doc):
    """@brief Delays from trigger TACK to shaper hold."""
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
    """@brief Make a table of one type of TACK."""
    regSpec, junk = jobOptions.tables[name]
    title, columns = jobOptions.tackDelayLabels[name]
    
    regTable = tableFromXml.xTableGen(doc, regSpec)
    labels = regTable.data.indices()[0]
    data = regTable.data.map(mappings.displayTime)
    data, labels = data.table()
    hTable = table.oneDTable(zip(labels[0], data), title, columns)

    return hTable

#
def calDelays(doc):
    """@brief Show delays from GCRCs."""
    output = []

    sectionTitle = "Delays from GCRCs"
    output.append(html.Heading(sectionTitle, 2))

    for name in jobOptions.calDelays:
        hTable = oneGcrcDelay(doc, name)
        output.extend(hTable)
        pass
    
    return output

# embarassingly similar to oneGtrcReg
def oneGcrcDelay(doc, tag):
    """@brief Make tables for one GCRC dalay register.

    """

    output = []

    regSpec, regLabel = jobOptions.tables[tag]
    axisLabels = jobOptions.gcrcLabels

    sectionTitle = "%s (%s)" % (regLabel, regSpec)
    output.append(html.Heading(sectionTitle, 2))

    xTable = tableFromXml.xTableGen(doc, regSpec)

    regTables = []
    tems = xTable.data.items()
    tems.sort()
    for iTem, temData in tems:
        temData = temData.map(mappings.displayTime)
        array, indices = temData.table()
        title = "%s for Tower %d (ticks (ns))" % (regLabel, iTem)
        hTable = table.twoDTable(array, title, axisLabels, indices)
        regTables.append(hTable)
        pass
    nTable = html.nWay(regTables, jobOptions.rcWidth)
    output.append(nTable)
    
    return output

######################## per-TEM stuff ##########################

#
def hasTem(doc):
    """@brief Do we have any TEMs?"""
    return hasTkr(doc) or hasCal(doc)

#
def perTem(doc):
    """@brief Make tables for all quantities that are per-TEM."""

    output = []

    sectionTitle = "Per-TEM quantities."
    output.append(html.Heading(sectionTitle, 1))    

    for name in jobOptions.perTem:
        output.append(oneTem(doc, name))
        pass

    return output

#
def oneTem(doc, name):
    """@brief Make a table for one per-TEM register."""

    regSpec, title = jobOptions.tables[name]
    regTable = tableFromXml.xTableGen(doc, regSpec)
    data, labels = regTable.data.table()
    labels = labels[0]
    hTable = table.oneDTable(zip(labels, data), title, jobOptions.perTemColumns)
    return hTable

################### GEM config ###################################

def gemStuff(doc):
    """@brief Display GEM configuration."""

    output = []

    sectionTitle = "GEM configuration"
    output.append(html.Heading(sectionTitle, 1))    

    if not hasGem(doc):
        output.append("Sorry, no GEM.")
        return output

    output.extend(perEngine(doc))
    output.extend(conditionsTable(doc))

    return output

#
def perEngine(doc):
    """@brief Display info from Message Engines.

    """

    output = []

    sectionTitle = 'Message engine configuration'
    output.append(html.Heading(sectionTitle, 2))

    columns = [jobOptions.messageEngineRowLabels]
    columnLabels = ['Engine']
    for name in jobOptions.messageEngineColumns:
        column = []
        columns.append(column)
        tag, label = jobOptions.tables[name]
        columnLabels.append(label)
        engines = expandRegs(tag, jobOptions.messageEngineRowLabels)
        for engine in engines:
            regTable = tableFromXml.xTableGen(doc, engine)
            data, labels = regTable.data.table()
            column.append(data[0][0])
            pass
        pass

    rows = transpose(columns)

    hTable = table.oneDTable(rows, sectionTitle, columnLabels)
    output.append(hTable)
    
    return output

#
def conditionsTable(doc):
    """@brief Display Condition Summary -> Message Engine lookup table.

    """

    output = []

    sectionTitle = 'Message engine lookup table'
    output.append(html.Heading(sectionTitle, 2))

    regSpec, label = jobOptions.tables[jobOptions.conditionTag]

    subFields = map(bitField.subField, jobOptions.conditionFields)

    tabWidth = 16
    xLabels = ['X%x' % nibble for nibble in range(tabWidth)]
    yLabels = ['%xX' % nibble for nibble in range(tabWidth)]

    registers = expandRegs(regSpec, jobOptions.conditionStrings)
    entries = []
    for reg in registers:
        regTable = tableFromXml.xTableGen(doc, reg)
        data, indices = regTable.data.table()
        for field in subFields:
            entries.append(field(data[0][0]))
            pass
        pass

    data = [entries[nibble*tabWidth:(nibble+1)*tabWidth]
            for nibble in range(tabWidth)]

    caption = "(L,M)SN = (Least,Most) Significant Nibble of Condition Summary"
    hTable = table.twoDTable(data, caption, jobOptions.conditionAxes,
                             (yLabels, xLabels))
    output.append(hTable)    
    
    return output

#
def expandRegs(tag, fillers):
    """@brief Expand wildcards in register names.

    """

    wild = '*'

    engines = []
    for address in fillers:
        engines.append(tag.replace(wild, address))
        pass

    return engines

#
def transpose(array):
    """@brief Transpose a nested list.

    """
    nCol = len(array)
    nRow = len(array[0])
    transposed = []
    for iRow in range(nRow):
        row = []
        transposed.append(row)
        for iCol in range(nCol):
            row.append(array[iCol][iRow])
        pass
    
    return transposed
