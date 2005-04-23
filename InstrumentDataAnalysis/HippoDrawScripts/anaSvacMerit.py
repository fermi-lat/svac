from svac_analysis import RootNTuple

filenameSvac = ( "/nfs/farm/g/glast/u01/svac_workshop/Workshop-3/Data/" +
                 "GlastRelease_v6r2p1-AdditionalCAL/Run-140001338/" +
                 "140001338_svac.root" )

svac = RootNTuple(filenameSvac, 'Output')
print "Number of variables: ", svac.columns
print "Number of events: ", svac.rows

filenameMerit = ( "/nfs/farm/g/glast/u01/svac_workshop/Workshop-3/Data/" +
                  "GlastRelease_v6r2p1-AdditionalCAL/Run-140001338/" +
                  "140001338_merit.root" )

merit = RootNTuple(filenameMerit, 'MeritTuple')

merit.add_friend(svac)

hist1 = merit.hist('TkrNumDigis')

hist2 = merit.hist('TkrNumTracks')
