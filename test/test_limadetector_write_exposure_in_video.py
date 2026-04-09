#!/usr/bin/env python3
#########################################################
# Arafat NOUREDDINE
# 2014/12/03
# Purpose : Test writing exposure attribute while video acquisition is already RUNNING
#########################################################

import os
import sys
import PyTango
import time
import datetime

# ------------------------------------------------------------------------------
# build exception
# ------------------------------------------------------------------------------
class BuildError(Exception):
    pass

# ------------------------------------------------------------------------------
# run
# ------------------------------------------------------------------------------
def run(proxy_name='arafat/lima_basler/basler.2',
        exposure_time=100,
        exp_increment=1,
        exposure_max=1000,
        wait=1,
        nb_loops=1):

    print("\nProgram inputs :\n--------------")
    print("proxy_name\t =", proxy_name)
    print("exposure_time\t = {} (ms)".format(exposure_time))
    print("exp_increment\t =", exp_increment)
    print("exposure_max\t =", exposure_max)    
    print("wait\t = {} (ms)".format(wait))
    print("nb_loops\t =", nb_loops)


    # Conversion en float/int une seule fois
    exposure_time = float(exposure_time)
    wait = float(wait)
    nb_loops = int(nb_loops)
    exp_increment = float(exp_increment)
    exposure_max = float(exposure_max)

    # Configure the device
    print("\nConfigure the Device :\n--------------")

    time_begin = datetime.datetime.now()
    print("\r{} - Create a DeviceProxy to Device {}".format(time_begin.isoformat(), proxy_name))

    proxy = PyTango.DeviceProxy(proxy_name)

    time_begin = datetime.datetime.now()
    print("\r{} - Ping proxy(\"{}\") {} us".format(time_begin.isoformat(), proxy_name, proxy.ping()))

    time_begin = datetime.datetime.now()
    print("\r{} - State = {}".format(time_begin.isoformat(), proxy.state()))

    print("--> Stop()")
    proxy.Stop()

    time_begin = datetime.datetime.now()
    print("\r{} - State = {}".format(time_begin.isoformat(), proxy.state()))

    print("--> Start()")
    proxy.Start()

    time_begin = datetime.datetime.now()
    print("\r{} - State = {}".format(time_begin.isoformat(), proxy.state()))

    try:
        current_loop = 1
        current_exposure = exposure_time

        while current_loop <= nb_loops:
            print("\n============================")
            print("Loop :", current_loop)
            print("============================")

            time_begin = datetime.datetime.now().isoformat()

            print("\r{} ---> Writing exposure time = {}".format(time_begin, current_exposure))
            proxy.exposureTime = current_exposure

            time.sleep(wait / 1000.0)

            # Wait until a frame is available
            while proxy.currentFrame == 0:
                time.sleep(1 / 1000.0)

            print(proxy.image)

            # Calcul de la prochaine valeur
            current_exposure += exp_increment
            if current_exposure >= exposure_max:
                current_exposure = exposure_time

            current_loop += 1

        print("\noutput :\n--------------")

    except Exception as err:
        sys.stderr.write('--------------\nERROR :\n--------------\n{}\n'.format(err))


# ------------------------------------------------------------------------------
# Usage
# ------------------------------------------------------------------------------
def usage():
    print("Usage: test_limadetector_write_exposure_in_video.py "
          "<my/device/proxy> "
          "<exp_time in ms> <exp_increment> <exp_max in ms> <wait in ms> "
          "<nb_loops>")
    sys.exit(1)


# ------------------------------------------------------------------------------
# Main Entry point
# ------------------------------------------------------------------------------
if __name__ == "__main__":
    if len(sys.argv) != 7:
         usage()    
    print(run(*sys.argv[1:]))