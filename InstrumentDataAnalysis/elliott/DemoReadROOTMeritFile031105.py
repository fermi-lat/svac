""" -*- mode:python -*-

Demo of reading ROOT Merit file:

author: anonymous

"""

#
# Get canvas:
#
#import hippo
app = hippo.HDApp()
canvas = app.canvas ()


#
# Hippodraw Root interface:
#
from hippo import RootController, Display
rc = RootController.instance()

#
# Merit ntuple we want to look at:
#
filename = R"E:\GLAST Data\FlightTowerA\recon-EM2-v1r0_136000332_merit_merit.root"
#
# Name of the trees:
#
ntuple_names = rc.getNTupleNames ( filename  )
print "In this file, tree names are ", ntuple_names

#
# Get the ntuple: 
#
ntuple = rc.createNTuple ( filename, ntuple_names[0] )

#
# Number of variables and events:
#
print "Number of variables = ", ntuple.columns

labels = ntuple.getLabels()
print "First ten variable names are ... ", labels[:10]

print "Number of events = ", ntuple.rows




#
# First plot: number of tracks (Merit variable 'TkrNumTracks')
#
hist = Display ( "Histogram", ntuple, ('TkrNumTracks', ) )
canvas.addDisplay ( hist )


#
# Second plot: Number of tracks with a cut (TkrNumTracks > 0):
#
from hippo import Cut

# Put the number of tracks in a histogram:
histTmp1 = Display ( "Histogram", ntuple, ('TkrNumTracks', ) )
# Define the cut variable:
hist_cut1 = Cut ( ntuple, ('TkrNumTracks',) )
# Define which histogram the cut applies to:
hist_cut1.addTarget ( histTmp1 )
# Cut values:
hist_cut1.setCutRange ( 1, 10, 'x' )
# Range of original histogram:
histTmp1.setRange ( 'x', 0, 10 )
## Plot the histogram after the cut has been applied:
canvas.addDisplay ( histTmp1 )



#
# Third plot: Number of tracks with two cuts (TkrNumTracks > 0 and
# GltWord==4). 
#                           
from hippo import Cut

histTmp2 = Display ( "Histogram", ntuple, ('TkrNumTracks', ) )
hist_cut2a = Cut ( ntuple, ('TkrNumTracks',) )
hist_cut2b = Cut ( ntuple, ('GltWord',) )
#
hist_cut2a.addTarget ( histTmp2 )
hist_cut2b.addTarget ( histTmp2 )

hist_cut2a.setCutRange ( 1, 10, 'x')
# This will only choose pure TKR triggers!
hist_cut2b.setCutRange ( 3.9, 4.1, 'x')

histTmp2.setRange ( 'x', 0, 10 )
canvas.addDisplay ( histTmp2 )



#
# Fourth plot: VtxX0 vs VtxY0 with some cuts
#
from hippo import Cut

histTmp3 = Display ( "XY Plot", ntuple, ('VtxY0','VtxX0') )

#histTmp3.setNumberOfBins ('x', 500)
#histTmp3.setNumberOfBins ('y', 500)

hist_cut3a = Cut ( ntuple, ('TkrNumTracks',) )
hist_cut3b = Cut ( ntuple, ('VtxX0',) )
hist_cut3c = Cut ( ntuple, ('VtxY0',) )

hist_cut3a.addTarget (histTmp3 )
hist_cut3b.addTarget (histTmp3 )
hist_cut3c.addTarget (histTmp3 )

hist_cut3a.setCutRange (1, 10, 'x')
hist_cut3b.setCutRange (-800, -300, 'x')
hist_cut3c.setCutRange (-800, -300, 'x')

histTmp3.setRange ( 'x', -800, -300 )
histTmp3.setRange ( 'y', -800, -300 )

canvas.addDisplay ( histTmp3 )


#
# Wait for user to terminate the script:
#
raw_input('Press Enter')



