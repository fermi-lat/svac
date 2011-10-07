# -*- python -*-
# $Header$
# Authors: M.E. Monzani <monzani@slac.stanford.edu>
# Version: findGaps-02-00-00
Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
#libEnv = baseEnv.Clone()   #  doesn't build a lib


progEnv.Tool('addLibrary', library = baseEnv['rootLibs'])
progEnv.Tool('commonRootDataLib')
progEnv.Tool('digiRootDataLib')

findGaps = progEnv.Program('findGaps', listFiles(['src/*.cxx']))

progEnv.Tool('registerTargets', package = 'findGaps',
             binaryCxts = [[findGaps, progEnv]])





