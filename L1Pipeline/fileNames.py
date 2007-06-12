"""@brief Conventions for naming files.

@author W. Focke <focke@slac.stanford.edu>
"""

import glob
import os
import time

import config
# import glastTime
import procDirs


def join(*args):
    joined = '_'.join(args)
    return joined


def setup(dlId, runId=None, chunkId=None, crumbId=None, createDirs=True):
    """@brief Setup data directory names.

    @arg dlId The dowlink ID.

    @arg [runId] The run ID.

    @arg [chunkId] The chunk ID.

    @arg [crumbId] The crumb ID.

    @return A dictionary containing the names of various data files.
    
    """
    runHead = runId

    dirs = procDirs.setup(dlId, runId, chunkId, crumbId, createDirs)
    files = {}
    files['run'] = {}

    files['dirs'] = dirs

    #files['downlink'] = {}
    #files['downlink']['runList'] = os.path.join(dirs['downlink'], 'runList')

    if chunkId is not None:
        files['chunk'] = _setupChunk(dirs, chunkId, runHead)
        if crumbId is not None:
            chunkHead = files['chunk']['head']
            files['crumb'] = _setupCrumb(dirs, crumbId, chunkHead)
            pass
        pass

    # # This doesn't work, it gets generated differently for different
    # # processes in the same stream.  So makeFT1 can't find the merit file.
    # timestamp = '%09d' % int(glastTime.met())
    # dlHead = join(runHead, timestamp, dlId)
    
    dlHead = join(runHead, dlId) 
    files['run']['head'] = dlHead
    files['run']['digi'] = os.path.join(dirs['run'], \
                                        join(dlHead, 'digi.root'))
    files['run']['fastMon'] = os.path.join(dirs['run'], \
                                           join(dlHead, 'fastHist.root'))
    files['run']['digiMon'] = os.path.join(dirs['run'], \
                                           join(dlHead, 'digiHist.root'))
    files['run']['recon'] = os.path.join(dirs['run'], \
                                         join(dlHead, 'recon.root'))
    files['run']['merit'] = os.path.join(dirs['run'], \
                                         join(dlHead, 'merit.root'))
    files['run']['ft1'] = os.path.join(dirs['run'], \
                                         join(dlHead, 'ft1.fits'))
    files['run']['cal'] = os.path.join(dirs['run'], \
                                       join(dlHead, 'cal.root'))
    files['run']['reconMon'] = os.path.join(dirs['run'],
                                            join(dlHead, 'reconHist.root'))
    files['run']['svac'] = os.path.join(dirs['run'], join(dlHead, 'svac.root'))
    
    
    return files


def _setupChunk(dirs, chunkId, runHead):
    files = {}
    chunkHead = join(runHead, chunkId)
    files['head'] = chunkHead
    files['digi'] = os.path.join(dirs['chunk'], \
                                 join(chunkHead, 'digi.root'))
    files['fastMon'] = os.path.join(dirs['fastMon'], \
                                    join(chunkHead, 'hist.root'))
    files['digiMon'] = os.path.join(dirs['digiMon'], \
                                    join(chunkHead, 'hist.root'))
    files['recon'] = os.path.join(dirs['chunk'], \
                                  join(chunkHead, 'recon.root'))
    files['merit'] = os.path.join(dirs['chunk'], \
                                  join(chunkHead, 'merit.root'))
    files['cal'] = os.path.join(dirs['chunk'], \
                                join(chunkHead, 'cal.root'))
    files['reconMon'] = os.path.join(dirs['reconMon'], \
                                     join(chunkHead, 'hist.root'))
    files['svac'] = os.path.join(dirs['chunk'], \
                                 join(chunkHead, 'svac.root'))
    files['svacHist'] = os.path.join(dirs['chunk'], \
                                     join(chunkHead, 'svacHist.root'))

    return files


def _setupCrumb(dirs, crumbId, chunkHead):
    files = {}
    crumbHead = join(chunkHead, crumbId)
    files['head'] = crumbHead
    files['recon'] = os.path.join(dirs['crumb'], \
                                  join(crumbHead, 'recon.root'))
    files['merit'] = os.path.join(dirs['crumb'], \
                                  join(crumbHead, 'merit.root'))
    files['cal'] = os.path.join(dirs['crumb'], \
                                join(crumbHead, 'cal.root'))
    return files


def findPieces(fileType, dlId, runId, chunkId=None):
    """@brief find chunks or crumbs to merge.

    @arg fileType The type of file we're merging ('digi', 'reconMon', etc.)

    @arg dlId

    @arg runId

    @arg [chunkId]

    @return A sequence of file names
    """

    if chunkId is None:
        chunkId = '*'
        crumbId = None
        level = 'chunk'
    else:
        crumbId = '*'
        level = 'crumb'
        pass

    files = setup(dlId, runId, chunkId, crumbId, \
                  createDirs=False)
    pattern = files[level][fileType]
    inFiles = glob.glob(pattern)

    inFiles.sort(key=os.path.basename)
   
    return inFiles
