
import util


def twoDTable(array, title, (xTitle, yTitle), (xLabels, yLabels)):
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

