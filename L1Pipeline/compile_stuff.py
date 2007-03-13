#!/usr/bin/env python

import os

import config

import runner


for packName, package in config.packages.items():

    args = {
        'glastSetup': config.glastSetup,
        'L1Cmt': config.L1Cmt,
        'glastExt': config.glastExt,
        'cmtConfig': config.cmtConfig,
        'cmtPath': config.cmtPath,
        'rootSys': config.rootSys,
        }
    args.update(package)

    cmd = '''source %(glastSetup)s
    CMTCONFIG=%(cmtConfig)s ; export CMTCONFIG
    CMTPATH=%(cmtPath)s ; export CMTPATH
    GLAST_EXT=%(glastExt)s ; export GLAST_EXT
    LD_LIBRARY_PATH="" ; export LD_LIBRARY_PATH
    ROOTSYS=%(rootSys)s ; export ROOTSYS
    cd %(L1Cmt)s
    cmt co -r %(version)s %(checkOutName)s
    cd %(cmtDir)s
    make clean
    make''' % args
    
    runner.run(cmd)
    continue
