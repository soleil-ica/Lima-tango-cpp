#!/usr/bin/env python
#########################################################
#Arafat NOUREDDINE
#2014/12/03
#Purpose : Test writing exposure attribute while video acquisition is already RUNNING
#########################################################
import os
import sys
import PyTango
import time
import datetime

proxy = ''
#------------------------------------------------------------------------------
# build exception
#------------------------------------------------------------------------------
class BuildError(Exception):
  pass

#------------------------------------------------------------------------------
# run
#------------------------------------------------------------------------------
def run(proxy_name = 'arafat/lima_basler/basler.2', exposure_time = 100, write_period = 1, nb_loops = 1, exp_increment_value = 1):
    # print arguments
    print '\nProgram inputs :\n--------------'
    print 'proxy_name\t = ', proxy_name
    print 'exposure_time\t =  %s (ms)' %(exposure_time)
    print 'write_period\t =  %s (ms)' %(write_period)
    print 'nb_loops\t = ', nb_loops
    print 'exp_increment_value\t = ', exp_increment_value
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
    print '--> Start()'
    proxy.Start()
    timeBegin = datetime.datetime.now()
    print '\r',timeBegin.isoformat(), " - State = ",proxy.state();
    nb_loops=int(nb_loops)
    try:
        current_loop = 1
	while(current_loop <= nb_loops):
            print '\n============================'
            print 'Loop : ', current_loop,
            print '\n============================'
            timeBegin = datetime.datetime.now().isoformat()
            print '\r', timeBegin, "---> Writing exposure time = ", float(exposure_time)+float(int(current_loop)*float(exp_increment_value))
            proxy.exposureTime = float(exposure_time)+float(int(current_loop)*float(exp_increment_value))
            time.sleep(float(write_period)/1000.0)
			while (proxy.currentFrame == 0)
				time.sleep(float(1)/1000.0)
			print proxy.image	
            current_loop+=1
			            
            print '\noutput :\n--------------'
    except Exception as err:
	   sys.stderr.write('--------------\nERROR :\n--------------\n%s\n' %err)

#------------------------------------------------------------------------------
# Usage
#------------------------------------------------------------------------------
def usage():
  print "Usage: [python] test_limadetector_write_exposure_in_video.py <my/device/proxy> <exposureTime in ms> <writingPeriod in ms> <nb_loops> <exp_increment_value>"
  sys.exit(1)
  
#------------------------------------------------------------------------------
# Main Entry point
#------------------------------------------------------------------------------
if __name__ == "__main__":
#    if len(sys.argv) != 6:
#        usage()
    print run(*sys.argv[1:])
