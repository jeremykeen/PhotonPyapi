#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""Simple example command line usage:

Usage: ./check_disk_space.py <percentage free space>

e.g:

$ ./check_disk_space.py 30
Running low on disk space. 20.0% remaining (Warning Threshold: 30%)
Total: 115.13GB
Used:  92.35GB
Avail: 22.77GB

The idea would be to put this in a Cron Job and have it email you when
the free disk space is lower than "n" percent.

"""

import sys

sys.path.insert(0, '../')

from diskspace import DiskSpace

ds = DiskSpace()

perc_arg = len(sys.argv) > 1 and sys.argv[1] or None
percent_limit = perc_arg or 20

if not ds.has_free_space(percent_limit):
    print "Running low on disk space. %s%% remaining "\
       "(Warning Threshold: %s%%)" % (ds.percent_free(), percent_limit)
    print "Total: %s" % ds.humanize_bytes(ds.bytes_capacity(), 1000)
    print "Used:  %s" % ds.humanize_bytes(ds.bytes_used(), 1000)
    print "Avail: %s" % ds.humanize_bytes(ds.bytes_free(), 1000)
