#!/usr/bin/env python
#########################################################
#Arafat NOUREDDINE
#2014/11/19
#Purpose : Test LimaDetector state
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
# Colors
#------------------------------------------------------------------------------
class bcolors:
    PINK = '\033[95m'
    BLUE = '\033[94m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    RED = '\033[91m'
    ENDC = '\033[0m'
    UNDERLINE = '\033[4m'

def disable(self):
    self.PINK = ''
    self.BLUE = ''
    self.GREEN = ''
    self.YELLOW = ''
    self.FAIL = ''
    self.ENDC = ''
    self.UNDERLINE = ''

#------------------------------------------------------------------------------
def prepare(proxy):

    print '\nprepare\n--------------------------'
    #Display time when state is STANDBY (just before Prepare())
    timeBegin = datetime.datetime.now()
    print timeBegin.isoformat(), ' - ', proxy.state()

    proxy.Prepare()

    #Display time when state is RUNNING (just after prepare())
    timePrepare = datetime.datetime.now()
    print timePrepare.isoformat(), ' - ', proxy.state()

    #Loop while (prepare in progress...)
    time.sleep(1) #ensure that prepare is finish ...
    
    #Display time when state is STANDBY (just after prepare is finish)
    timeEnd = datetime.datetime.now()
    print '\n', timeEnd.isoformat(), ' - ', proxy.state()
    print '\nDuration = ', ((timeEnd-timePrepare).total_seconds()*1000),'(ms)'
    return


#------------------------------------------------------------------------------
def snap(proxy):

    print '\nsnap\n--------------------------'
    #Configure the device   
    acquired_frame = proxy.currentFrame 
    nb_frames = proxy.nbFrames
    
    while(acquired_frame != nb_frames):

        #Display time (just before Snap())
        
        timeBegin = datetime.datetime.now()
        print timeBegin.isoformat(), ' - ', proxy.state()
        current_frame  = proxy.currentFrame
    	
        proxy.Snap()

        #Display time when state is RUNNING (just after Snap())
        timeSnap = datetime.datetime.now()
        print timeSnap.isoformat(), ' - ', proxy.state()

        #Loop while current frame is not changed (acquisition in progress...)
        while (acquired_frame == current_frame):
	    acquired_frame = proxy.currentFrame
	    print '\r', '...',
	    time.sleep(0)

        #Display time when state is STANDBY (just after acquisition is finish)
        timeEnd = datetime.datetime.now()
        print '\n', timeEnd.isoformat(), ' - ', proxy.state()
        print 'Current Frame = ', acquired_frame, ' : Duration = ', ((timeEnd-timeSnap).total_seconds()*1000),'(ms)\n'
        print '--------------------------'
        
        #return proxy.image


#------------------------------------------------------------------------------
# Usage
#------------------------------------------------------------------------------
def usage():
  print "Usage: [python] test_limadetector.py <my/device/proxy> <exposureTime> <nbFrames> <fileGeneration> <nb_loops>"
  sys.exit(1)


#------------------------------------------------------------------------------
# run
#------------------------------------------------------------------------------
def run(proxy_name = 'arafat/lima_basler/basler.2', exposure_time = 100, latency_time = 0, nb_frames = 10, file_generation_str = True, nb_loops = 1):
    # print arguments
    print '\nProgram inputs :\n--------------'
    print 'proxy_name\t = ', proxy_name
    print 'exposure_time\t =  %s (ms)' %(exposure_time)
    print 'latency_time\t =  %s (ms)' %(latency_time)
    print 'nb_frames\t = ', nb_frames
    print 'file_generation\t = ', file_generation_str
    print 'nb_loops\t = ', nb_loops
    proxy = PyTango.DeviceProxy(proxy_name)
    #Configure the device
    print '\nConfigure Device attributes :\n--------------'
    nb_frames = int(nb_frames)
    proxy.Stop()
    print 'write triggerMode\t = ', "INTERNAL_MULTI"
    proxy.triggerMode="INTERNAL_MULTI"
    print 'write exposureTime\t = ', float(exposure_time)
    proxy.exposureTime = float(exposure_time)
    print 'write latencyTime\t = ', float(latency_time)
    proxy.latencyTime = float(latency_time)
    print 'write nbFrames\t\t = ', int(nb_frames)
    proxy.nbFrames = int(nb_frames)
    print 'write fileGeneration\t = ', file_generation_str
    if file_generation_str == True:
        file_generation = True
    else:
        file_generation = False
    proxy.fileGeneration = int(file_generation)
    nb_loops = int(nb_loops)
    print '\n'
    try:
        prepare(proxy)
        current_loop = 0
        while(current_loop<nb_loops):
            print '\n========================================================'
            print '\t' + bcolors.RED + 'Loop : ', current_loop, bcolors.ENDC,
            print '\n========================================================'
            
            snap(proxy)
            current_loop=current_loop+1
            state = proxy.state()
            if (state!=PyTango.DevState.STANDBY):
                raise Exception('FAIL : Acquisition is end with state (%s)' %(state))
            #print '\noutput :\n--------------'
            #print 'currentFrame = ', proxy.currentFrame

            #if proxy.currentFrame!=nb_frames:
            #   raise Exception('FAIL : Acquired frames (%s) is different from requested nb_frames (%s)'  % (proxy.currentFrame, nb_frames))
        #print '\nProgram outputs :\n--------------'
        #print '\nimage = '
        #return proxy.image
    except Exception as err:
	   sys.stderr.write('--------------\nERROR :\n--------------\n%s\n' %err)

#------------------------------------------------------------------------------
# Main Entry point
#------------------------------------------------------------------------------
if __name__ == "__main__":
#    if len(sys.argv) < 4:
#        usage()
    print run(*sys.argv[1:])


    
