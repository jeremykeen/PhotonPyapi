#!/usr/bin/python

"""
Disk Space
Simple class for working out the free disk space on a system

by Stuart Colville http://muffinresearch.co.uk
License: http://www.opensource.org/licenses/mit-license.php

"""

import os
import math

class DiskSpace():

    """Free Disk Space"""

    def __init__(self, path="/"):
        """Init class and retrieves disk space info"""
        self.disk = os.statvfs(path)

    def has_free_space(self, limit):
        """Bool returns true if remaining space is above limit %"""
        if float(self.percent_free()) < float(limit):
            return False
        else:
            return True

    def percent_free(self):
        """Gets the amount of space left as a percentage"""
        return (math.ceil(float(100) / float(self.bytes_capacity())
                                                * self.bytes_free()))

    def bytes_capacity(self):
        """Returns the total capacity in bytes"""
        return self.disk.f_frsize * self.disk.f_blocks

    def bytes_free(self):
        """Returns the free space in bytes"""
        return self.disk.f_frsize * self.disk.f_bavail

    def bytes_used(self):
        """Returns the used space in bytes"""
        return self.disk.f_frsize * (self.disk.f_blocks -
                                                   self.disk.f_bavail)

    @staticmethod
    def humanize_bytes(bytes, kilo=1024):

        """Humanizes bytes

        See http://en.wikipedia.org/wiki/Kilobyte for info on the
        different ways to interpret whether a kilobyte is 1,024 bytes
        or 1,000 bytes

        """

        if kilo == 1024:
            label = ["KiB", "MiB" , "GiB", "TiB"]
        else:
            # fallback
            kilo = 1000
            label = ["KB", "MB" , "GB", "TB"]

        if bytes < kilo:
            return "%d" % bytes
        elif bytes > kilo and bytes < math.pow(kilo, 2):
            return "%.2F%s" % (float(bytes/kilo), label[0])
        elif bytes > math.pow(kilo, 2) and bytes < math.pow(kilo, 3):
            return "%.2F%s" % (float(bytes/math.pow(kilo, 2)), label[1])
        elif bytes > math.pow(kilo, 3) and bytes < math.pow(kilo, 4):
            return "%.2F%s" % (float(bytes/math.pow(kilo, 3)), label[2])
        elif bytes > math.pow(kilo, 4) and bytes < math.pow(kilo, 5):
            return "%.2F%s" % (float(bytes/math.pow(kilo, 4)), label[3])