## @file configParser.py
## @brief Make LAT configuration tables 
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

#

import html
import ndTable
import htmlTable as table
import tableFromXml
import temUtil

import jobOptions


#
def calFeReg(doc):
    # get stuff from CAL front ends
    # and make tables of it

    calTables = []
    for registerTag in jobOptions.calTags:
        nTable = oneCalReg(doc, registerTag)
        calTables.extend(nTable)
        calTables.append(html.Element("HR"))
        pass
    return calTables

#
def oneCalReg(doc, tag):
    axisLabels = jobOptions.calAxisLabels
    regSpec, regLabel = jobOptions.tables[tag]
    sectionTitle = "%s (%s)" % (regLabel, regSpec)
    header = html.Heading(sectionTitle, 2)
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
    return header, nTable



#
def tkrSplits(doc):
    # get TKR CSRs
    gtccs = doc.getElementsByTagName("GTCC")
    tCsrs = []
    for gtcc in gtccs:
        tCsrs.extend(gtcc.getElementsByTagName("csr"))
        pass
    tCsrs = util.contain(tCsrs, shapes, blank=-1)
    
    subField = util.SubField(7, 13)
    nRead = util.superMap(subField, tCsrs)

    # get TKR modes
    gtrcs = doc.getElementsByTagName("GTRC")
    modes = []
    for gtrc in gtrcs:
        modes.extend(gtrc.getElementsByTagName("mode"))
        pass
    modes = util.contain(modes, shapes)

    nTrc = shapes["GTRC"]

    # calc split points
    splits = []
    for jtem in range(len(tCsrs)):
        sides = []
        for left, right in temUtil.tccLRMap:
            layers = []
            for jlayer in range(nTrc):
                split = util.getSplit(nRead[jtem][left][jlayer],
                                      nRead[jtem][right][jlayer],
                                      modes[jtem][left][jlayer],
                                      modes[jtem][right][jlayer])
                layers.append(split)
                pass
            sides.append(layers)
            pass
        splits.append(sides)
        pass

    # build split point table
    tkrLayers = 2 * nTrc
    layers = range(tkrLayers)
    array = [layers]
    labels = ["Layer"]
    for jtem, tem in enumerate(splits):
        for view in ("X", "Y"):
            row = []
            for layer in layers:
                side, trc = temUtil.trcLayerMap[view][layer]
                row.append(tem[side][trc])
                pass
            array.append(row)
            labels.append("Tower %s %s" % (jtem, view))
            pass
        pass
    array = util.transpose(array)
    array.reverse()


    output.addChild("\n")
    output.addChild(html.Element("HR"))
    output.addChild("\n")

    splitLabel = "Tracker Split Points"
    output.addChild(html.Heading(splitLabel, 2))

    splitCaption = splitLabel + " (Left:Right)"
    hTable = table.oneDTable(array, splitCaption, labels)
    output.addChild(hTable)
    
    output.addChild("\n")

    return

