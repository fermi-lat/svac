

flightGeom = '$(XMLGEODBSROOT)/xml/flight/flightSegVols.xml'
assemblyGeom = '$(XMLGEODBSROOT)/xml/latAssembly/latAssemblySegVols.xml'
lat10Geom = '$(XMLGEODBSROOT)/xml/latAssembly/lat10TowerSegVols.xml'
lat12Geom = '$(XMLGEODBSROOT)/xml/latAssembly/lat12TowerSegVols.xml'
lat14Geom = '$(XMLGEODBSROOT)/xml/latAssembly/lat14TowerSegVols.xml'
# the index here is the number of towers
geometries = (assemblyGeom, #  0
              assemblyGeom, #  1
              assemblyGeom, #  2
              '',         #  3
              assemblyGeom, #  4
              '',         #  5
              assemblyGeom, #  6
              '',         #  7
              assemblyGeom, #  8
              '',         #  9
              lat10Geom,  # 10
              '',         # 11
              lat12Geom,  # 12
              '',         # 13
              lat14Geom,  # 14
              '',         # 15
              assemblyGeom, # 16
              )

