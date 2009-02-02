#!/usr/bin/python

import sys
from pprint import pprint


infile = sys.argv[1]
outfile = sys.argv[2]
replacements = {}

ifile = file(infile).read()

ofile = file(outfile, 'w')

for pr in sys.argv[3:]:
    (k, v) = pr.split('=', 1)
    print "k=<<<%s>>> v=<<<%s>>>" % (k, v)
    ifile = ifile.replace('{{{' + k + '}}}', v)

print >>ofile, ifile







                  


