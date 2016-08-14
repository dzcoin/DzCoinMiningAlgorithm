#!/usr/bin/env python

# helpful little script that spits out a comma-separated list of
# language codes for qt icons that should be included
# in binary dzcoin distributions

import glob
import os
import re
import sys

if len(sys.argv) != 3:
  sys.exit("usage: %s $qtdir/translations $dzcoindir/src/qt/locale"%sys.argv[0])

d1 = sys.argv[1]
d2 = sys.argv[2]

l1 = set([ re.search(r'qt_(.*).qm', f).group(1) for f in glob.glob(os.path.join(d1, 'qt_*.qm')) ])
l2 = set([ re.search(r'dzcoin_(.*).qm', f).group(1) for f in glob.glob(os.path.join(d2, 'dzcoin_*.qm')) ])

print ",".join(sorted(l1.intersection(l2)))



