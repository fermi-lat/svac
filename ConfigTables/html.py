

def formatDict(dict):
    val = []
    for key, value in dict.items():
        if value is None:
            val.append(" %s" % key)
            pass
        else:
            val.append(" %s=%s" % (key, value))
            pass
    val = "".join(val)
    return val


class Element:

    tag = ""

    def __init__(self, tag=None, attr={}):
        if tag is not None:
            self.tag = tag
        self.children = []
        self.attr = attr
        return

    def addChild(self, child):
        self.children.append(child)
        return

    def __repr__(self):
        return "<HTML Element %s at %x>" % (self.tag, id(self))

    def __str__(self):
        val = ["<%s%s>" % (self.tag, formatDict(self.attr))] + \
              map(str, self.children) + \
              ["</%s>" % (self.tag)]
        val = "".join(val)
        return val

    def toString(self):
        return self.__str__()

    pass


class Page(Element):

    tag = "HTML"

    def __init__(self, title=""):
        Element.__init__(self)
        self.title = title
        self.addChild(Title(self.title))
        return

    pass

class Title(Element):

    tag = "TITLE"

    def __init__(self, title=""):
        Element.__init__(self)
        self.addChild(title)
        return

    pass


def nWay(elements, width=2):
    import math

    elements = list(elements)

    # figure out how many rows we're gonna use
    nelem = len(elements)
    nrow = int(math.ceil(float(nelem)/width))
    
    # pad the set of items to fill an integer # of rows
    nnew = width * nrow
    nadd = nnew - nelem
    elements += [""] * nadd

    table = Element("TABLE")

    cols = range(width)
    for irow in [x * width for x in range(nrow)]:
        row = Element("TR")
        table.addChild(row)
        for icol in cols:
            cell = Element("TD")
            row.addChild(cell)
            cell.addChild(elements[irow + icol])
            pass
        table.addChild("\n")
        pass
    
    return table
