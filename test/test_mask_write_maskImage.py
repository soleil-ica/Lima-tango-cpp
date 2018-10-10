#!/usr/bin/env python
#########################################################
#Arafat NOUREDDINE
#2018/06/11
#Purpose : Test Write imageMask attribute on the Mask specific device
#########################################################
import os
import sys
import PyTango
import time
import datetime


proxy = ''

#------------------------------------------------------------------------------
# Usage
#------------------------------------------------------------------------------
def usage():
  print "Usage: [python] test_mask_write_maskImage_1.py <my/device/proxy> <width> <height> <roi_x> <roi_width> <roi_y> <roi_height>"
  sys.exit(1)

#------------------------------------------------------------------------------
# run
#------------------------------------------------------------------------------
def run(proxy_name = 'arafat/lima_simulator/simulator.3-mask', width = 1024, height = 1024, roi_x=0, roi_width=1024/2, roi_y=0, roi_height=1024/2):
    # print arguments
    print '\nProgram inputs :\n--------------'
    print 'proxy_name\t = ', proxy_name
    print 'width\t\t = ', width
    print 'height\t\t = ', height
    print 'roi_x\t\t = ', roi_x
    print 'roi_width\t = ', roi_width
    print 'roi_y\t\t = ', roi_y
    print 'roi_height\t = ', roi_height

    width = int(width)
    height = int(height)
    roi_x = int(roi_x)
    roi_width = int(roi_width)
    roi_y = int(roi_y)
    roi_height = int(roi_height)
    mask_dev = PyTango.DeviceProxy(proxy_name)
    import numpy as np
    img_ones = np.ones((width, height), dtype='i')
    img_ones[roi_x:roi_width,roi_y:roi_height] = 0 
    mask_dev.maskImage=img_ones

#------------------------------------------------------------------------------
# Main Entry point
#------------------------------------------------------------------------------
if __name__ == "__main__":
#    if len(sys.argv) < 7:
#        usage()
    print run(*sys.argv[1:])