## @file configParser.py
## @brief Make LAT configuration tables 
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

#


#
def calFeReg(doc):
    # get stuff from CAL front ends
    # and make tables of it
    for registerTag in joboptions.calTags:
        elements = doc.getElementsByTagName(registerTag)
        container = util.contain(elements, shapes)

        output.addChild("\n")
        output.addChild(html.Element("HR"))
        output.addChild("\n")

        registerLabel = temUtil.registerMap[registerTag]
        output.addChild(html.Heading(registerLabel, 2))
        
        for jtem, tem in enumerate(container):
            sides = []
            for iside, side in enumerate(tem):
                sideLabel = temUtil.cccSideMap[iside]
                title = "%s for Tower %d side %s" % \
                        (registerLabel, jtem, sideLabel)
                yLen = len(side)
                xLen = len(side[0])
                yLab = map(repr, temUtil.cccLayerMap[iside][:yLen])
                xLab = map(repr, range(xLen))
                hTable = table.twoDTable(side, title, ("crystal", "layer"),
                                         (xLab, yLab))
                sides.append(hTable)
                pass
            hTable = html.nWay(sides, joboptions.width)
            output.addChild(hTable)
            pass
        pass
    return






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

