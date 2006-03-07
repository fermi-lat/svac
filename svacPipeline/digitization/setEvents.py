#!/usr/local/bin/python

"""usage: SetEvents.py run digiFile"""

import os
import sys

import reconPM

run, digiFile = sys.argv[1:]

events = reconPM.getFileEvents(digiFile)

field = 'EVENTCOUNT'

command = '%s %s %s %d' % (os.environ['eLogUpdate'], run, field, events)
sys.stderr.write('running command [%s]\n' % command)
os.system(command)
