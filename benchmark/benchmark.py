#!/usr/bin/python

import os
from subprocess import Popen, PIPE

pathtobin = '../../build2/bin/'

tests = { 'scalarmult' : { 'args' : [[10**x] for x in range(8)] }
          }


for (name, stuff) in tests.items():
    for kind in ['cpu', 'kamasu']:
        for argset in stuff['args']:
            cmd = pathtobin + name + '-' + kind + " " + ' '.join([str(x) for x in argset])
            print cmd
            p = Popen(cmd, shell=True, stdout=PIPE)
            os.waitpid(p.pid, 0)
            res = p.stdout.read()

            print [float(n) for n in res.split()]
            # oprint data




