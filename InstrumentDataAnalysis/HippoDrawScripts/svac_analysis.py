"""
@brief Some classes to simplify the syntax to drive a HippoDraw analysis
of ROOT ntuples from the Python prompt.

@author J. Chiang
"""
#
# $Header$
#
import os

class Cut(object):
    def __init__(self, cut):
        self.cut = cut
        # hippo.Cut objects lack proper introspection:
        if len(cut.cutRange()) == 2:
            self.vars = (cut.getLabel('x'),)
        elif len(cut.cutRange()) == 4:
            self.vars = (cut.getLabel('x'), cut.getLabel('y'))
        else:
            raise ValueError, "cut object has invalid number of ranges"
    def __getattr__(self, attrname):
        return getattr(self.cut, attrname)
    def show(self):
        import hippoplotter as plot
        plot.canvas.addDisplay(self.cut)
    def __call__(self):
        return self.cut
    def __repr__(self):
        lines = []
        for i, var in zip([0, 1], self.vars):
            lines.append(var + ": %s - %s" % self.cut.cutRange()[2*i: 2*i+2])
        return '\n'.join(lines)
    def TCut(self):
        tcuts = []
        for i, var in zip([0, 1], self.vars):
            cutRange = self.cut.cutRange()[2*i: 2*i+2]
            tcuts.append('%.2e < %s < %.2e' %
                         (cutRange[0], var, cutRange[1]))
        return ' && '.join(tcuts)

class Display(object):
    def __init__(self, rootNTuple, disp):
        self.rootNTuple = rootNTuple
        self.nt = rootNTuple.nt
        self.title = rootNTuple.filename + ": " + rootNTuple.tree
        self.disp = disp
        self.cuts = []
    def cut(self, variable, cutRange=None, lowerLimit=None, upperLimit=None,
            show=False, xlog=0, ylog=0):
        import hippoplotter as plot
        if isinstance(variable, str):
            self.rootNTuple._updateNTuple((variable,))
        else:
            self.rootNTuple._updateNTuple(variable)
        if cutRange is None:
            data = self.nt.getColumn(variable)
            cutRange = [min(data), max(data)]
        if lowerLimit is not None:
            cutRange = [lowerLimit, max(lowerLimit, cutRange[1])]
        if upperLimit is not None:
            cutRange = [min(upperLimit, cutRange[0]), upperLimit]
        try:
            my_cut = Cut(plot.hippo.Cut(self.nt, (variable,)))
            my_cut.setCutRange(cutRange[0], cutRange[1], 'x')
        except TypeError:
            my_cut = Cut(plot.hippo.Cut(self.nt, variable))
            my_cut.setCutRange(cutRange[0][0], cutRange[0][1], 'x')
            my_cut.setCutRange(cutRange[1][0], cutRange[1][1], 'y')
        my_cut.addTarget(self.disp)
        if show:
            plot.canvas.addDisplay(my_cut())
        my_cut.setLog('x', xlog)
        my_cut.setLog('y', ylog)
        my_cut.setTitle(self.title)
        self.cuts.append(my_cut)
        return my_cut
    def __call__(self):
        return self.disp
    def __getattr__(self, attrname):
        return getattr(self.disp, attrname)
    def addCuts(self, disp):
        for cut in disp.cuts:
            self.applyCut(cut)
    def applyCut(self, cut):
        cut.addTarget(self.disp)
        self.cuts.append(cut)
    def showCuts(self):
        for cut in self.cuts:
            cut.show()
    def TCut(self):
        cut_list = []
        for cut in self.cuts:
            cut_list.append(cut.TCut())
        return ' && '.join(cut_list)

class RootNTuple(object):
    _validDisplays = ['Histogram', 'Y Plot', 'Scatter Plot', 'XY Plot',
                      'Strip Chart', 'Profile', 'Color Plot', 'Contour Plot']
    def __init__(self, filename, tree='MeritTuple', useBaseName=True):
        self.nt = self._get_tree(filename, tree)
        self.displays = []
        self.filename = os.path.basename(filename)
        self.tree = tree
        self.friends = []
    def _get_tree(self, rootfile, treeName):
        import hippo
        rc = hippo.RootController.instance()
        names = rc.getNTupleNames(rootfile)
        if treeName in names:
            try:
                nt = rc.createDataArray(rootfile, treeName)
                self.using_DA = True
            except RuntimeError:
                nt = rc.createNTuple(rootfile, treeName)
                self.using_DA = False
            return nt
        else:
            message = ("Tree %s not found in root file %s.\n"
                       % (treeName, rootfile))
            message += "Valid names are\n"
            for name in names:
                message += name + "\n"
            raise LookupError, message
    def __call__(self):
        return self.nt
    def add_friend(self, friend):
        if friend.nt.rows != self.nt.rows:
            raise RuntimeError, "Incompatible friend ntuple size"
        self.friends.append(friend.nt)
    def hist(self, variable, xlog=0, ylog=0, xrange=(), yrange=()):
        import hippoplotter as plot
        self._updateNTuple((variable,))
        my_hist = plot.Histogram(self.nt, variable, xlog=xlog, ylog=ylog,
                                 xrange=xrange, yrange=yrange)
        return self._displayWrapper(my_hist)
    def xyhist(self, xvar, yvar, xlog=0, ylog=0, xrange=(), yrange=()):
        import hippoplotter as plot
        self._updateNTuple((xvar, yvar))
        my_hist = plot.XYHist(self.nt, xvar, yvar, xlog=xlog, ylog=ylog,
                              xrange=xrange, yrange=yrange)
        return self._displayWrapper(my_hist)
    def draw(self, columns, displayType=None):
        if displayType is None:
            if len(columns) == 1:
                displayType = 'Histogram'
            elif len(columns) == 2:
                displayType = 'Scatter Plot'
        if displayType not in self._validDisplays:
            message = "Valid display types are "
            for disp in self._validDisplays:
                message += '%s\n' % disp
            raise LookupError, message
        import hippoplotter as plot
        self._updateNTuple(columns)
        my_disp = plot.hippo.Display(displayType, self.nt, columns)
        plot.canvas.addDisplay(my_disp)
        return self._displayWrapper(my_disp)
    def _displayWrapper(self, disp):
        my_disp = Display(self, disp)
        my_disp.setTitle(self.filename + ": " + self.tree)
        self.displays.append(my_disp)
        return my_disp
    def _updateNTuple(self, vars):
        for var in vars:
            if var not in self.nt.getLabels():
                for friend in self.friends:
                    try:
                        if self.using_DA:
                            self.nt[var] = friend[var]
                        else:
                            self.nt.addColumn(var, friend.getColumn(var))
                        return
                    except RuntimeError, message:
                        print message
                raise LookupError, "Column %s not found" % var
    def find(self, expression):
        colnames = self.nt.getLabels()
        return [name for name in colnames if name.find(expression) != -1]
    def getColumn(self, colname):
        try:
            return self.nt.getColumn(colname)
        except:
            for friend in self.friends:
                try:
                    return friend.getColumn(colname)
                except RuntimeError, message:
                    print message
            raise LookupError, "Column %s not found" % colname
    def addSummedColumn(self, variable):
        import numarray as num
        newcol = num.zeros(self.nt.rows, type=num.Float)
        for i in xrange(len(newcol)):
            newcol[i] = sum(self.nt.valueAt(i, variable).flat)
        self.nt.addColumn(variable + '_sum', newcol)
    def __getattr__(self, attrname):
        return getattr(self.nt, attrname)
    
if __name__ == '__main__':
    import hippoplotter as plot
#    path = ('/nfs/farm/g/glast/u01/svac_workshop/Workshop-3/'
#            + 'Data/GlastRelease_v6r2p1-AdditionalCAL/Run-140001338')
    path = ''
    prefix = '140001338'
    merit = RootNTuple(os.path.join(path, prefix+'_merit.root'), 'MeritTuple')
    svac = RootNTuple(os.path.join(path, prefix+'_svac.root'), 'Output')

    # One can add a friend ntuple much as in ROOT:
    merit.add_friend(svac)

    # hist and xyhist have special methods:
    hist = merit.hist('TkrSumKalEne', xlog=1)
    hist.cut('TkrNumTracks', (0.9, 1.1))
    hist.cut('Tkr1ZDir', (-1, -0.9))
    hist.cut('CalEnergySum', (40, 400), xlog=True)

    # A friend branch is available even though this is a hist from merit:
    hist.cut('TkrNumVertices', (0.9, 1.1))

    # Print the cuts in TCut format for use with ROOT event filter:
    print hist.TCut()

    # Other hippo display types can be accessed generically with the
    # draw(...) method, 'Scatter Plot' is the default for 2D:
    scatter = merit.draw(('EvtEnergySumOpt', 'TkrSumKalEne'))
    scatter.setLog('x', 1)
    scatter.setLog('y', 1)
    
    # Cuts can be applied from other displays, collectively or one at a time:
    plot.prompt("\nAdd cuts from hist to scatter plot? <return>")
    scatter.addCuts(hist)

    # Cuts associated with any display can be shown at will:
    plot.prompt("\nShow the cuts that have been applied? <return>")
    scatter.showCuts()
