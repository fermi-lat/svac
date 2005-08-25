## @file timeLog.py
## @brief Log CPU and wall time used by process.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

#

"""@brief Log CPU and wall time used by process.
"""

import time


#
class timeLog:

    #
    def __init__(self):
        self.wall = time.time()
        self.cpu = time.clock()
        return
    
    #
    def __call__(self):
        nowWall = time.time()
        nowCpu = time.clock()
        print >> sys.stderr, "Wall: %s Cpu: %s" % \
              (nowWall - self.wall,
               nowCpu - self.cpu)
        self.wall = nowWall
        self.cpu = nowCpu
        return
    
