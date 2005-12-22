
import html

def twoDTable(array, title, (yTitle, xTitle), (yLabels, xLabels)):
    haveData = False
    if len(array):
        nXVals = len(array[0])
        if nXVals:
            haveData = True
            pass
        pass
    if not haveData:
        return ''

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
