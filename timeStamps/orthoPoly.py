#!/usr/bin/env python

import numarray as num

import basis

defaultType = num.Float64

class orthoPoly:

    def __init__(self, order, x):
        self.x = num.array(x, defaultType)
        xBar = num.sum(self.x) / len(self.x)
        self.x -= xBar
        self.order = order
        self.basis = basis.Basis()
        for io in num.arange(order + 1):
            self.basis.add(x**io)
            pass
        return

    def modelFunc(self, parm, x):
        return self.basis.build(parm)

    pass
