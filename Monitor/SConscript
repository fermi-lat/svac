# -*- python -*-
# $Header: 
# Authors: Authors: E. Charles <echarles@slac.stanford.edu> 
# Version: Monitor-02-00-00
Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

progEnv.Tool('addLibrary', library = baseEnv['rootLibs'])
progEnv.Tool('addLibrary', library = baseEnv['rootGuiLibs'])
progEnv.Tool('addLibrary', library = baseEnv['xercesLibs'])
progEnv.Tool('addLibrary', library = ['rt'])
progEnv.Tool('commonRootDataLib')
progEnv.Tool('digiRootDataLib')
progEnv.Tool('mcRootDataLib')
progEnv.Tool('reconRootDataLib')
progEnv.Tool('facilitiesLib')
progEnv.Tool('xmlBaseLib')
progEnv.Tool('configDataLib')
progEnv.Tool('calibUtilLib')
progEnv.Tool('identsLib')

runStrip_t = progEnv.Program('runStrip_t', listFiles(['src/JobConfig.cxx', 'src/MonValue_t.cxx', 
				'src/MonValueImpls_t.cxx', 'src/MonInputCollection.cxx', 'src/MonInputCollection_*.cxx', 
				'src/MonEventLooper_t.cxx', 'src/runStrip_t.cxx', 'src/MonObjFactory.cxx', 
				'src/MonConfigParser.cxx', 'src/recXmlList.cxx', 'src/merit/MonInput_*.cxx',
				'src/cal/MonInput_*.cxx', 'src/fastmon/MonInput_*.cxx', 'src/trackermon/MonInput_*.cxx', 
				'src/svac/MonInput_*.cxx', 'src/mc/MonInput_*.cxx', 'src/recon/MonInput_*.cxx', 
				'src/digi/MonInput_*.cxx', 'src/compareFiles.cxx', 'src/MonGlobalCut.cxx', 'src/Geo.cxx', 
				'src/TestReport.cxx', 'src/RFun.cxx', 'src/MonInputObject.cxx', 'src/AcdPeds.cxx', 
				'src/AcdPedProxy.cxx', 'src/AcdPedParser.cxx', 'src/CalPeds.cxx', 'src/CalPedProxy.cxx', 
				'src/CalPedParser.cxx']))
treemerge = progEnv.Program('treemerge', ['src/treemerge.cxx'])
MergeHistFiles = progEnv.Program('MergeHistFiles', ['src/MergeHistFiles.cxx'])
MakeACDNicePlots = progEnv.Program('MakeACDNicePlots', ['src/MakeACDNicePlots.cxx'])
inputObjects = progEnv.Program('inputObjects', listFiles(['src/inputObjects.cxx', 'src/MonObjFactory.cxx',
				'src/merit/MonInput_*.cxx', 'src/cal/MonInput_*.cxx', 'src/fastmon/MonInput_*.cxx',
				'src/trackermon/MonInput_*.cxx', 'src/svac/MonInput_*.cxx', 'mc/MonInput_*.cxx', 
				'src/recon/MonInput_*.cxx', 'src/digi/MonInput_*.cxx', 'src/Geo.cxx', 'src/TestReport.cxx']))

progEnv.Tool('registerTargets', package = 'Monitor',
             binaryCxts = [[runStrip_t,progEnv],[treemerge,progEnv],
	     [MergeHistFiles,progEnv],[MakeACDNicePlots,progEnv],[inputObjects,progEnv]],
	     includes = listFiles(['Monitor/*.h']))
