"""
Re-implementation of SVAC drawMerit.py using RootNTuple
"""
from svac_analysis import RootNTuple

merit = RootNTuple("140001338_merit.root", "MeritTuple")

print merit.keys()

hist = merit.hist('TkrNumTracks')

hist2 = merit.hist('TkrNumTracks', xrange=(0, 10))
hist2.cut('TkrNumTracks', (1, 10))

hist3 = merit.hist('TkrNumTracks', xrange=(0, 10))
hist3.cut('TkrNumTracks', (1, 10))
hist3.cut('GltWord', (3.9, 4.1))

hist4 = merit.xyhist('VtxY0', 'VtxX0',
                     xrange=(-800, -300), yrange=(-800, -300))
hist4.cut('TkrNumTracks', (1, 10))
hist4.cut('VtxX0', (-800, -300))
hist4.cut('VtxY0', (-800, -300))
