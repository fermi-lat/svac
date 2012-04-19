## @file chunkSize.py
## @brief Determine chunk sizes for parallel recon.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

#

"""@brief Determine chunk sizes for parallel recon.
"""

import os

# minimum scaled observed recon rate (events / SLAC LSF second)
minRate = {
    'Cosmics': 2.84,
    'Photons': 1.15,
    'Am241': 4.67,
    }

try:
    defaultTargetSeconds = int(os.environ['chunkTime'])
except KeyError:
    defaultTargetSeconds = 100
    pass

defaultMinChunk = 1 # never do less than this
defaultMaxChunk = 550000 # never do more than this

#
def chunkSize(particleType, targetSeconds=None, minChunk=None, maxChunk=None):
    """Determine chunk size for parallel recon.

    Attempts to get a chunk that will take a specified amount of time
    (in scaled SLAC units).

    @arg particleType ParticleType for this run

    @arg [targetSeconds] Amount of CPU time (in SLAC units, this is 2-5 times real
    time) to shoot for.  Deafult is defaultTargetSeconds, a global symbol in this
    module (which, in turn, is set from the environment variable 'chunkTime' if it exists).

    @arg [minChunk] Minimum chunk size.  Deafult is defaultMinChunk, a global symbol in this
    module.

    @arg [maxChunk] Maximum chunk size.  Deafult is defaultMaxChunk, a global symbol in this
    module.

    @ret Suggested number of events per chunk

    """

    if targetSeconds is None:
        targetSeconds = defaultTargetSeconds
        pass
    if minChunk is None:
        minChunk = defaultMinChunk
        pass
    if maxChunk is None:
        maxChunk = defaultMaxChunk
        pass

    chunk = targetSeconds * minRate[particleType]

    chunk = int(chunk)
    chunk = max(chunk, minChunk)
    chunk = min(chunk, maxChunk)

    return chunk
