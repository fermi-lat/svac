

flightGeom = '$(XMLGEODBSROOT)/xml/flight/flightSegVols.xml'
lat10Geom = '$(XMLGEODBSROOT)/xml/latAssembly/lat10TowerSegVols.xml'
lat12Geom = '$(XMLGEODBSROOT)/xml/latAssembly/lat12TowerSegVols.xml'
lat14Geom = '$(XMLGEODBSROOT)/xml/latAssembly/lat14TowerSegVols.xml'
# the index here is the number of towers
geometries = (flightGeom, #  0
              flightGeom, #  1
              flightGeom, #  2
              '',         #  3
              flightGeom, #  4
              '',         #  5
              flightGeom, #  6
              '',         #  7
              flightGeom, #  8
              '',         #  9
              lat10Geom,  # 10
              '',         # 11
              lat12Geom,  # 12
              '',         # 13
              lat14Geom,  # 14
              '',         # 15
              flightGeom, # 16
              )

