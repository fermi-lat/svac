
alignment = 'l'
collSep = '|'
cellSep = ' & '
endRow = ' \\\\'
rowSep = '\\hline'
headSep = '\\hline\n\\hline'

def tRow(values):
    values = map(str, values)
    row = cellSep.join(values) + endRow
    return row

def twoDtable(array, title, (xTitle, yTitle), (xLabels, yLabels)):
    table = "Sorry, not implemented yet."
    return table

def oneDtable(array, title, labels):
    table = []
    
    table = "Sorry, not implemented yet."
    return table
