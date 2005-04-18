## @file hqPlot.py
## @brief Quick and dirty plots with hippoDraw.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

"""@brief Quick and dirty plots with hippoDraw.

"""

import hippo

app = hippo.HDApp()
canvas = app.canvas()
controller = hippo.NTupleController.instance()
tuple = hippo.NumArrayTuple()
tuple.setName('On the Fly')
tuple.setTitle('data')
controller.registerNTuple(tuple)

#
def plot(columns, names=None):

    if names is None:
        names = [str(xx) for xx in range(len(columns))]
        pass

    for column, name in zip(columns, names):
        tuple.addColumn(name, column)
        pass 

    return
