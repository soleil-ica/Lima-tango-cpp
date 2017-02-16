#!/usr/bin/env python
#########################################################
#Arafat NOUREDDINE
#2015/04/27
#Purpose : Test displaying image attribute in 'start' mode
#########################################################
import os
import sys
import PyTango
import time
import datetime
from matplotlib import pyplot

pyplot.ion()

proxy = ''
#------------------------------------------------------------------------------
# build exception
#------------------------------------------------------------------------------
class BuildError(Exception):
  pass

#------------------------------------------------------------------------------
# run
#------------------------------------------------------------------------------
def run(proxy_name = 'arafat/lima_simu/simu.1', exposure_time = 100, latency_time = 0, wait_first_image_extra_time = 200):
    # print arguments
    print '\nProgram inputs :\n--------------'
    print 'proxy_name\t\t\t = ', proxy_name
    print 'exposure_time\t\t\t =  %s (ms)' %(exposure_time)
    print 'latency_time\t\t\t =  %s (ms)' %(latency_time)
    print 'wait_first_image_extra_time\t =  %s (ms)' %(wait_first_image_extra_time)
    exposure_time = float(exposure_time) 
    latency_time = float(latency_time)
    wait_first_image_extra_time = float(wait_first_image_extra_time)    

    #Configure the device
    print '\nConfigure the Device :\n--------------'
    timeBegin = datetime.datetime.now()
    print '\r',timeBegin.isoformat(), " - Create a DeviceProxy to Device ", proxy_name
    proxy = PyTango.DeviceProxy(proxy_name)
    timeBegin = datetime.datetime.now()
    print '\r',timeBegin.isoformat(), " - Ping proxy(\"",proxy_name,"\") ",proxy.ping()," us"

    timeBegin = datetime.datetime.now()
    print '\r',timeBegin.isoformat(), " - State = ",proxy.state();
    print '--> Stop()'
    proxy.Stop()
    timeBegin = datetime.datetime.now()
    print '\r',timeBegin.isoformat(), " - State = ",proxy.state();
    
    print 'write exposureTime = ', exposure_time    
    proxy.exposureTime = float(exposure_time)

    print 'write latencyTime = ', latency_time    
    proxy.latencyTime = float(latency_time)
        
    timeBegin = datetime.datetime.now()
    print '\r',timeBegin.isoformat(), " - State = ",proxy.state();        
    print '--> Start()'
    proxy.Start()

    #Loop while state is RUNNING (prepare in progress...)
    while proxy.state() != PyTango.DevState.RUNNING:
        pass
    timeBegin = datetime.datetime.now()
    print '\r',timeBegin.isoformat(), " - State = ",proxy.state();
    
    wait_first_image = proxy.exposureTime + proxy.latencyTime + wait_first_image_extra_time

    time.sleep(wait_first_image/1000)#to ensure that the first image is ready
        
    ar = None
    try:
        while True:
            if ar is None:
                ar = pyplot.imshow(proxy.image)
            else:
                ar.set_data(proxy.image)            
            pyplot.draw()
            
    except Exception as err:
	    print >>sys.stderr, '--------------\nERROR :\n--------------\n%s' % err
    except KeyboardInterrupt:
        print 'properly stopped'
       
#------------------------------------------------------------------------------
# Usage
#------------------------------------------------------------------------------
def usage():
  print "Usage: [python] test_limadetector_display_image.py <my/device/proxy> <exposure_time (ms)> <latency_time (ms)> <wait_first_image_extra_time (ms)>"
  #sys.exit(1)
  
#------------------------------------------------------------------------------
# Main Entry point
#------------------------------------------------------------------------------
if __name__ == "__main__":
    #if len(sys.argv) != 5:
    usage()
    run(*sys.argv[1:])
