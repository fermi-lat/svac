#!/usr/bin/env python

import sys
import numarray

rate = numarray.array((25, 100, 250, 500, 1e3, 5e3, 10e3, 20e3))
dead = numarray.array((20e-6, 30e-6, 100e-6, 2.3e-3, 3e-3))

arg = numarray.multiply.outer(rate, dead)
fraction = 1 - numarray.exp(-arg)
pct = fraction * 100

dstr = '<- Deadtime (s)'
dlen = len(dstr)

fchr = 10
fmt = '%-' + `fchr` + '.3g'

sys.stdout.write('Percent Deadtime Loss\n\n')
for dd in dead:
    sys.stdout.write(fmt % dd)
sys.stdout.write(dstr + '\n')
sys.stdout.write('-' * (fchr * len(dead) + dlen) + '\n')
for ir in xrange(len(rate)):
    for pp in pct[ir]:
        sys.stdout.write(fmt % pp)
    sys.stdout.write('| ' + (fmt % rate[ir]) + '\n')
sys.stdout.write('-' * (fchr * len(dead)) + '| ^\n')
sys.stdout.write(' ' * (fchr * len(dead)) + '| | Rate (Hz)\n')
