
import util


def getId(node):
    attr = node.getAttribute("ID")
    return int(attr, 0)

def cmpById(*args):
    ids = map(getId, args)
    return apply(cmp, ids)

def sortById(arg):
    arg.sort(cmpById)
    return

def mkGetElts(tag):
    def getElts(node):
        return node.getElementsByTagName(tag)
    return getElts

def mkGetVal(tag):
    def getVal(node):
        elements = node.getElementsByTagName(tag)
        val = util.scalar(elements)
        return val
    return getVal

def intVal(node):
    elements = node.childNodes
    val = util.scalar(elements)
    val = val.data
    val = int(val, 0)
    return val

def fillHierarchy(arg, names):
    for depth, name in enumerate(names):
        getter = mkGetElts(name)
        arg = util.superMap(getter, arg)
        util.superMap(sortById, arg, depth)
    return arg

