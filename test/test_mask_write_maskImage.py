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

mask_dev=PyTango.DeviceProxy("arafat/lima_simulator/simulator.3-mask")
import numpy as np
img_ones = np.ones((1024, 1024), dtype='i')
img_ones[500:520,500:520] = 0 
mask_dev.maskImage=img_ones
