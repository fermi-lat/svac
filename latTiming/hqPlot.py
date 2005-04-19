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
    """@brief Quickly plot arrays using hippoDraw.

    Actually we don't plot anything, but we do pass the arrays off to hippoDraw,
    so the user can generate plots thru the GUI.

    @arg columns A sequence of arrays (all the same length!) to plot.

    @arg [names] A sequence of column names.  If present, must be the same
    length as @a columns.  If not given, columns will be numbered.

    """

    if names is None:
        names = [str(xx) for xx in range(len(columns))]
        pass

    for column, name in zip(columns, names):
        tuple.addColumn(name, column)
        pass 

    return
