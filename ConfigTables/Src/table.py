
import sys

import html
import util


def textTable(array, title, (xTitle, yTitle), (xLabels, yLabels)):
    maxXLab = util.maxLen(xLabels)
    maxYLab = util.maxLen(yLabels)
    array = util.superMap(repr, array)
    maxVal = util.maxLen(array)
    maxX = max(maxXLab, maxVal)
    maxY = max(maxYLab, len(yTitle))

    xField = maxX + 1
    yField = maxY + 1
    
    nXVals = len(array[0])
    bodyWidth = nXVals * xField
    width = yField + bodyWidth + 1

    table = title.center(width) + "\n"
    table += "_" * width + "\n"
    table += " " * yField + "|" + xTitle.center(bodyWidth) + "\n"
    table += " " * yField + "|"
    for xLabel in xLabels:
        table += xLabel.rjust(xField)
    table += "\n"
    table += yTitle.center(yField) + "|" + "_" * bodyWidth + "\n"
    for iRow, row in enumerate(array):
        table += yLabels[iRow].rjust(yField) + "|"
        for iCol, value in enumerate(row):
            table += value.rjust(xField)
        table += "\n"
    table += "_" * width + "\n"
    return table


def htmlTable(array, title, (xTitle, yTitle), (xLabels, yLabels)):
    nXVals = len(array[0])

    table = html.Element("TABLE", attr={"BORDER": 1})

    table.addChild("\n")

    caption = html.Element("CAPTION")
    table.addChild(caption)
    caption.addChild(title)

    table.addChild("\n")

    header = html.Element("THEAD")
    table.addChild(header)
    row = html.Element("TR")
    header.addChild(row)

    table.addChild("\n")

    yTit = html.Element("TH", attr={"ROWSPAN": 2})
    row.addChild(yTit)
    yTit.addChild(yTitle)
    
    xTit = html.Element("TH", attr={"COLSPAN": nXVals})
    row.addChild(xTit)
    xTit.addChild(xTitle)

    row = html.Element("TR")
    header.addChild(row)
    for lab in xLabels:
        cell = html.Element("TH")
        row.addChild(cell)
        cell.addChild(lab)
        pass

    for irow in range(len(yLabels)):
        row = html.Element("TR")
        table.addChild(row)
        yTit = html.Element("TH")
        row.addChild(yTit)
        yTit.addChild(yLabels[irow])
        for data in array[irow]:
            cell = html.Element("TD")
            row.addChild(cell)
            cell.addChild(data)
            pass
        table.addChild("\n")
        pass
            
    return table


def oneDTable(array, title, labels):
    table = html.Element("TABLE", attr={"BORDER": 1})

    table.addChild("\n")

    caption = html.Element("CAPTION")
    table.addChild(caption)
    caption.addChild(title)

    table.addChild("\n")

    header = html.Element("THEAD")
    table.addChild(header)
    row = html.Element("TR")
    header.addChild(row)

    for label in labels:
        cell = html.Element("TH")
        row.addChild(cell)
        cell.addChild(label)
        pass
    row.addChild("\n")

    table.addChild("\n")

    for rowData in array:
        row = html.Element("TR")
        for data in rowData:
            cell = html.Element("TD")
            row.addChild(cell)
            cell.addChild(data)
            pass
        table.addChild(row)
        table.addChild("\n")
        pass

    return table
