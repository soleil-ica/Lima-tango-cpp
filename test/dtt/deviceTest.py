### Tango device test tool (python3)
####################################

import sys
import os
import getopt
from time import sleep
from distutils.util import strtobool
import logging as log
import numpy as np
from PyTango import *

#### consts
# action keys:
ACTION_COMMENT = "#"
ACTION_PRINT = "@"
ACTION_GLOBAL = "%"
ACTION_COMMAND = "CMD"
ACTION_WRITE_SCALAR = "WRITE"
ACTION_READ_SCALAR = "READ"
ACTION_WRITE_SPECTRUM = "WRITE_T"
ACTION_READ_SPECTRUM = "READ_T"
ACTION_WRITE_IMAGE = "WRITE_I"
ACTION_READ_IMAGE = "READ_I"
ACTION_EXECUTE = "EXEC"
ACTION_WAIT_SCALAR = "WAIT"
ACTION_READ_PROP = "READ_PROP"
ACTION_DEL_PROP = "DEL_PROP"
ACTION_WRITE_PROP = "WRITE_PROP"
ACTION_APPEND_PROP = "APPEND_PROP"
ACTION_REPEAT_ACTION = "REPEAT"
ACTION_REPEAT_NB_SEP = "{"
ACTION_PROXY = "SET_PROXY"

# whole list:
ActionKeys = (ACTION_COMMAND,ACTION_WRITE_SCALAR,ACTION_READ_SCALAR,ACTION_EXECUTE,ACTION_WRITE_SPECTRUM,\
              ACTION_READ_SPECTRUM,ACTION_READ_IMAGE,ACTION_WAIT_SCALAR,ACTION_READ_PROP,ACTION_DEL_PROP,\
              ACTION_WRITE_PROP,ACTION_WRITE_IMAGE,ACTION_APPEND_PROP)
# for check purpose:
WaitActionKeys = (ACTION_WAIT_SCALAR)
PropertyActionKeys = (ACTION_READ_PROP,ACTION_DEL_PROP,ACTION_WRITE_PROP,ACTION_APPEND_PROP)
MonoArgActionKeys = (ACTION_COMMAND,ACTION_WRITE_SCALAR,ACTION_READ_SCALAR,ACTION_EXECUTE,ACTION_WAIT_SCALAR)
VectArgActionKeys = (ACTION_WRITE_SPECTRUM,ACTION_READ_SPECTRUM)
MtxArgActionKeys = (ACTION_WRITE_IMAGE,ACTION_READ_IMAGE)

# check keys:
CHECK_EQUAL = "EQUAL"
CHECK_DIFFER = "DIFF"
CHECK_OK = "OK"
CHECK_KO = "KO"
CheckKeys = (CHECK_EQUAL,CHECK_DIFFER,CHECK_OK,CHECK_KO)

# type keys:
TYPE_INT = "INT"
TYPE_REAL = "REAL"
TYPE_BOOL = "BOOL"
TYPE_STR = "STR"
TYPE_STATE = "STATE"
TYPE_STR_ARRAY = "STR_A"
TypeKeys = (TYPE_INT,TYPE_REAL,TYPE_BOOL,TYPE_STR,TYPE_STATE,TYPE_STR_ARRAY)

# OS commands:
OS_CMD_SLEEP = "sleep"


#### default values for optional arguments
# timeout for WAIT action in s:
TMO = 10

# verbose mode:
VERBOSE = True

# stop on exception:
STOP_ON_FAIL = False

# stop on check KO:
STOP_ON_CHECK_KO = False


#### dictionary for global variables
# {x:(y,z,t),}  : x = variable name , y = variable type, z = associated attribute or command name, t = value
GlobalVariables = {}


# usage function
def usage():
  "Print command line usage."
  strr = "Usage: deviceTest -d <device name> -a <action file name> -o <output file name> [-v <0 or [1]>] [-t <wait timeout in s [10]>] [-s <[0] or 1>] [-c <[0] or 1>]"
  print (strr)

# config format function
def configFormat():
  "Print config file format and exit."
  strr = "Config file format: <ACTION KEY>;<ACTION NAME>;[PARAM TYPE];[<PARAM>,<PARAM>,...];[<CHECK KEY>];[CHECK VALUE];[CHECK DELTA]"
  log.error (strr)
  sys.exit(2)

# define header for output file
def defineHeader(opts):
  "Define header for output file according to tool options"
  "@return header string"
  
  verboseMode = "not set, use default [{}]".format(VERBOSE)
  waitTimeout = "not set, use default [{}]".format(TMO)
  stopOnFail = "not set, use default [{}]".format(STOP_ON_FAIL)
  stopOnCheckKo = "not set, use default [{}]".format(STOP_ON_CHECK_KO)
  
  for opt, arg in opts:
    if opt in ("-d", "--device"):
      deviceName = arg
    if opt in ("-a", "--action"):
      actionFile = arg
    if opt in ("-v", "--verbose"):
      verboseMode = (int(arg) == 1)
    if opt in ("-t", "--timeout"):
      waitTimeout = float(arg)
    if opt in ("-s", "--stop"):
      stopOnFail = (int(arg) == 1)
    if opt in ("-c", "--check"):
      stopOnCheckKo = (int(arg) == 1)

  headerStr = "---------------------------------------------------------------------\n"
  headerStr += "device name: {}\n".format(deviceName)
  headerStr += "action file: {}\n".format(actionFile)
  headerStr += "options    : verbose: {} \n".format(verboseMode)
  headerStr += "             timeout: {} \n".format(waitTimeout)
  headerStr += "             stop on fail: {} \n".format(stopOnFail)
  headerStr += "             stop on check ko: {}\n".format(stopOnCheckKo)
  headerStr += "---------------------------------------------------------------------\n"

  return headerStr

# cast parameter function
def castParam(param,ptype):
  "Define parameter type."
  "@return parameter with good type."
  value = None
  isNumpy = False

  # check if simple value or numpy array
  if 'ndarray' in str(type(param)):
    isNumpy = True

  if ptype == TYPE_INT:
    if isNumpy:
      value = param.astype(int)
    else:
      value = int(param)
  elif ptype == TYPE_REAL:
    if isNumpy:
      value = param.astype(float)
    else:
      value = float(param)
  elif ptype == TYPE_BOOL:
    if isNumpy:
      value = param.astype(int)
    else:  
      value = int(param)
  elif ptype == TYPE_STR:
    value = param
  elif ptype == TYPE_STATE:
    if isNumpy:
      value = param.astype(str)
    else:    
      value = str(param)
  else:
    strr = "Should not be here! Not implemented type: {}".format(ptype)
    log.error (strr)
    sys.exit(2)

  return value

# strict comparison function
def strictCompare(result,value,vtype):
  "Compare result and value in specified type"
  "@return result."
  check = False

  if vtype == TYPE_INT:
    valT = int(value)
    resT = int(result)
    check = (valT == resT)
  elif vtype == TYPE_REAL:
    valT = float(value)
    resT = float(result)
    check = (valT == resT)
  elif vtype == TYPE_BOOL:
    valT = strtobool(value)
    resT = int(result == True)
    check = (valT == resT)
  elif vtype == TYPE_STR:
    check = (value == result)
  elif vtype == TYPE_STATE:
    check = (value == str(result))
  else:
    strr = "Should not be here! Not implemented type for strict comparison: {}".format(vtype)
    log.error (strr)
    sys.exit(2)

  return check

# delta comparison function
def deltaCompare(result, value, vtype, delta):
  "Compare result and value in specified type, with +/- delta"
  "@return result."
  check = False

  if vtype == TYPE_INT:
    valT = int(value)
    resT = int(result)
    deltaT = int(delta)
    d1 = valT - deltaT
    d2 = valT + deltaT
    check = (d1 <= resT <= d2)

  elif vtype == TYPE_REAL:
    valT = float(value)
    resT = float(result)
    deltaT = float(delta)
    d1 = valT - deltaT
    d2 = valT + deltaT
    check = (d1 <= resT <= d2)

  else:
    strr = "No delta comparison possible with type for delta comparison: {}".format(vtype)
    log.error (strr)
    sys.exit(2)

  return check

# strict diff function
def strictDiff(result,value,vtype):
  "Compare result and value in specified type"
  "@return result."
  check = False

  if vtype == TYPE_INT:
    valT = int(value)
    resT = int(result)
    check = (valT != resT)
  elif vtype == TYPE_REAL:
    valT = float(value)
    resT = float(result)
    check = (valT != resT)
  elif vtype == TYPE_BOOL:
    valT = strtobool(value)
    resT = int(result == True)
    check = (valT != resT)
  elif vtype == TYPE_STR:
    check = (value != result)
  elif vtype == TYPE_STATE:
    check = (value != str(result))
  else:
    strr = "Should not be here! Not implemented type for strict comparison: {}".format(vtype)
    log.error (strr)
    sys.exit(2)

  return check

# check result function
def checkResult(result, vtype, check, value, delta):
  "Compare result with value, +/ delta if specified"
  "@return: check result: True or False"

  checkRes = False

  if check == CHECK_EQUAL:
    if not delta: # no delta: strict comparison
      checkRes = strictCompare(result, value, vtype)
    else: # compare with delta
      checkRes = deltaCompare(result, value, vtype, delta)

  elif check == CHECK_DIFFER:
    checkRes = strictDiff(result, value, vtype)

  elif check == CHECK_OK:
    checkRes = (result[0:2] == CHECK_OK)

  elif check == CHECK_KO:
    checkRes = (result[0:2] == CHECK_KO)

  else:
    strr = "Should not be here! Not implemented check key: {}".format(check)
    log.error (strr)
    sys.exit(2)  

  return checkRes

# memorize global variable
def memorizeGlobal(splitedLine):
  "memorize global variable. Expected format: %__<variable name>;<type>;<associated attribute or command name>"

  # check format
  if len(splitedLine) != 3:
    strr = "Bad format for definition of global variable: {}! Exiting.".format(splitedLine[0])
    log.error (strr)
    sys.exit(2)

  # check variable name:
  #  - extract name (without %)
  #  - name should begin with '__'
  lVarName = splitedLine[0][1:]
  if lVarName[0:2] != '__':
    strr = "Bad format for name of global variable: {}! Should begin with __! Exiting.".format(lVarName)
    log.error (strr)
    sys.exit(2)

  # check type
  lVarType = splitedLine[1]
  if lVarType not in TypeKeys:
    strr = "Parameter type key {} not implemented for global variable: {}! Exiting.".format(lVarType,lVarName)
    log.error (strr)
    sys.exit(2)

  # check associated action
  lVarAction = None
  lVarAction = splitedLine[2]
  if not lVarAction:
    strr = "Associated action for global variable: {} is mandatory! Exiting.".format(lVarName)
    log.error (strr)
    sys.exit(2)

  # store variable in dico (if not already defined)
  if lVarName in GlobalVariables:
    strr = "Global variable: {} already defined! Exiting.".format(lVarName)
    log.error (strr)
    sys.exit(2)

  lValue = castParam(0,lVarType)
  GlobalVariables[lVarName] = (lVarType,lVarAction,lValue)
  strr = "Global: {} - type: {} - Action: {}- Init value: {}".format(lVarName,lVarType,lVarAction,lValue)
  log.info (strr)  

# apply action on proxy function
def applyAction(pxy, actionKey, actionName, lParamType, lParams):
  "Apply action on proxy"
  "@return: raw result of action"

  # according to action key, apply action name
  try:
    #################################
    if actionKey == ACTION_COMMAND: 
      if not lParams: # command without parameter
        res = None
        res = pxy.command_inout(actionName)
        resType = str(type(res))
        if 'array' not in resType: # for array return value specific case...
          if not res:
            res = CHECK_OK

      else: # command with parameters
        if lParamType == TYPE_STR_ARRAY:
          # special case array of string argument: transform arg in list ',' separated
          lParamsL = lParams[0].split(',')
          lParams = lParamsL
          lParamType = TYPE_STR
        elif lParamType == TYPE_STR:
          pass
        else:
          lParamsL = lParams[0].split(',')
          lParams = lParamsL

        if len(lParams) == 1: # only one argument
          # check if var glob used in lParams
          if lParams[0] in GlobalVariables:
            arg = GlobalVariables[lParams[0]][2]
          else:
            arg = castParam(lParams[0],lParamType)

          res = pxy.command_inout(actionName,arg)
          resType = str(type(res))
          if 'array' not in resType: # for array return value specific case...
            if not res:
              res = CHECK_OK
        else: # multi arguments
          # convert each parameter in specified type
          lArgs = [castParam(ele,lParamType) for ele in lParams]
          res = pxy.command_inout(actionName,lArgs)
          if not res:
            res = CHECK_OK

    #######################################
    elif actionKey == ACTION_WRITE_SCALAR:
      # check if var glob used in lParams
      if lParams[0] in GlobalVariables:
        scalarValue = GlobalVariables[lParams[0]][2]
      else:
        scalarValue = castParam(lParams[0],lParamType)

      pxy.write_attribute(actionName,scalarValue)
      res = CHECK_OK

    #########################################################################
    elif actionKey == ACTION_READ_SCALAR or actionKey == ACTION_WAIT_SCALAR:
      scalar = pxy.read_attribute(actionName)
      res = scalar.value

    ##########################################
    elif actionKey == ACTION_WRITE_SPECTRUM:
      # check if var glob used in lParams
      if lParams[0] in GlobalVariables:
        spectrumValue = GlobalVariables[lParams[0]][2]
      else:
        # convert each value in specified type
        spectrumValue = [castParam(ele,lParamType) for ele in lParams]
        
      pxy.write_attribute(actionName,spectrumValue)
      res = CHECK_OK

    #########################################
    elif actionKey == ACTION_READ_SPECTRUM:
      spectrum = pxy.read_attribute(actionName)
      res = spectrum.value

    ##########################################
    elif actionKey == ACTION_WRITE_IMAGE:
      # convert each value in specified type
      imageValue = castParam(lParams,lParamType)

      pxy.write_attribute(actionName,imageValue)
      res = CHECK_OK
      
    ######################################
    elif actionKey == ACTION_READ_IMAGE:
      image = pxy.read_attribute(actionName)
      res = image.value

    #########################################
    elif actionKey == ACTION_READ_PROP:
      if actionName != '*': # single property
        prop = pxy.get_property(actionName)
        res = prop[actionName]

      else: # read all properties
        prop_list = pxy.get_property_list("*")
        res = "\n"
        for prop in prop_list:
          data = pxy.get_property(prop) # data = dictionary {'property name', 'property value'}
          for k in list(data):
            pp = data[k] # type(pp) = tango.StdStringVector
            res += "{} : {}\n".format(k, pp)
    
    #########################################
    elif actionKey == ACTION_DEL_PROP:
      prop = pxy.delete_property(actionName)
      res = CHECK_OK

    #########################################
    elif actionKey == ACTION_WRITE_PROP:
      # first get property (event if does'nt exist)
      prop = pxy.get_property(actionName)

      # then set value    
      if lParamType == TYPE_STR_ARRAY:
        # special case array of string argument: transform arg in list ',' separated
        values = lParams.split(',') # not valid if param contains any ',' !!!
      elif lParamType == TYPE_STR:
        values = [lParams]
      else:
        values = lParams.split(',')

      if len(values) == 1: # if only one param
        # direct use of param value
        prop[actionName] = lParams  
      else:
        # put param value in a list
        prop[actionName] = [e for e in values]

      # then write property
      pxy.put_property(prop)
      res = CHECK_OK

    #########################################
    elif actionKey == ACTION_APPEND_PROP:
      # first get property (event if does'nt exist)
      prop = pxy.get_property(actionName)
      propVal = prop[actionName]

      if lParamType == TYPE_STR: # STR type
        # then append new value to current one      
        propVal.extend([lParams])
        prop[actionName] = propVal

        # then write property
        pxy.put_property(prop)
        res = CHECK_OK
      else: # not implemented for other types
        strr = "Append not implemented for this type: {}".format(lParamType)
        log.error (strr)
        sys.exit(2)

    ###################################
    elif actionKey == ACTION_EXECUTE:
      if actionName == OS_CMD_SLEEP:
        delay = float(lParams[0])
        sleep(delay)
        res = CHECK_OK
      else: # not implemented
        strr = "Not implemented action: {}".format(actionName)
        log.error (strr)
        sys.exit(2)

    else:
      strr = "Should not be here! Not implemented action key: {}".format(actionKey)
      log.error (strr)
      sys.exit(2)

  except DevFailed as e:
    res = CHECK_KO + "\nCaught DevFailed: {}".format(str(e))
    if StopOnException:
      strr = "Caught Tango DevFailed! Exiting."
      log.error (strr)
      sys.exit(2)    

  return res

# parse function
def parseConfigFile(pxy, cfgDesc, resDesc, tmo_s):
  "Parse config file <cfgDesc>, execute commands on device proxy <pxy> and send results in file out <resDesc>."
  "Use tmo_s for WAIT actions timeout"

  # check counters
  CheckOK_cpt = 0
  CheckKO_cpt = 0
  
  # beginning of config file
  resDesc.write("\n------------------------ BEGINNING OF TEST --------------------------\n")

  # read config file
  content = cfgDesc.read().splitlines()
  for line in content:
    log.info (line)
    # extract parameters, with format: <ACTION KEY>;<ACTION NAME>;[PARAM TYPE];[<PARAM>,<PARAM>,...];[<CHECK KEY>];[CHECK VALUE];[CHECK DELTA]
    lData = line.split(';')
    
    #default number of loop = 1
    lLoopNb = 1

    # analyse action key:
    actionKey = lData[0]
    if actionKey == ACTION_PROXY:
      pxy = DeviceProxy(lData[1])

    elif actionKey[0] == ACTION_COMMENT: # comment
      pass

    elif actionKey[0] == ACTION_PRINT: # print
      # print in output file
      resDesc.write(actionKey[1:])
      resDesc.write("\n")

    elif actionKey[0] == ACTION_GLOBAL: # global variable definition
      # memorize global variable
      memorizeGlobal(lData)

    else: # real action
      # check if repeated action
      if actionKey.find(ACTION_REPEAT_ACTION) == 0:
        # extract number of repetitions:
        try:
          lLoopNb = int(actionKey[len(ACTION_REPEAT_ACTION):actionKey.find(ACTION_REPEAT_NB_SEP)])
          actionKey = actionKey[actionKey.find(ACTION_REPEAT_NB_SEP)+1:]
        except:
          strr = "Error in REPEAT format for {}! Exiting.".format(line)
          log.error (strr)
          configFormat()

      if actionKey not in ActionKeys:
        strr = "Action key {} not implemented! Exiting.".format(actionKey)
        log.error (strr)
        configFormat()

      # action name:
      actionName = lData[1]  
      if not actionName:
        strr = "Empty action name! Exiting."
        log.error (strr)
        configFormat()

      # parameters (optional):
      if not lData[2]: # no params because no type
        lParamType = None
        lParams = None
        isParam = False
      else:
        lParamType = lData[2]
        if lParamType not in TypeKeys:
          strr = "Parameter type key {} not implemented! Exiting.".format(lParamType)
          log.error (strr)
          configFormat()

        # <PARAM> interpretation depends on action key:
        # Property:
        if actionKey in PropertyActionKeys:
          # params = [values,] with potential ';' inside...        
          lParams = line.split('[')[1].split(']')[0]
          lData[4] = None # no check for property actions

        # Mono argument:
        elif actionKey in MonoArgActionKeys:
          # take param as is
          lParams = [lData[3]]

        # Vector argument:
        elif actionKey in VectArgActionKeys:
          # take param as a list, ',' separated
          lParams = lData[3].split(',')

        # Matrix argument:
        elif actionKey in MtxArgActionKeys:
          # take param as a val,val*val,val*val,val...
          lLines = lData[3].split('*')
          lMatrixList = [np.fromstring(ele,sep=',') for ele in lLines]
          lParams = np.array(lMatrixList)

        else:
          strr = "Action key {} not implemented! Exiting.".format(actionKey)
          log.error (strr)
          configFormat()

        isParam = True

      # check key (optional):
      if not lData[4]: # no check
        isCheck = False
        lCheck = None
        lCheckValue = None
        lCheckDelta = None
      else:
        lCheck = lData[4]
        if lCheck not in CheckKeys:
          strr = "Check key {} not implemented! Exiting.".format(lCheck)
          log.error (strr)
          configFormat()

        isCheck = True
        lCheckValue = lData[5]
        lCheckDelta = lData[6]

      # check if action is "memorized"
      isMemorized = False
      lGlobal = None
      for glob in list(GlobalVariables):
        action = GlobalVariables[glob][1]
        if action == actionName:
          isMemorized = True
          lGlobal = glob

      # action to be applied on device:
      if isParam:
        strA = "Action: {} {} param: {} - ".format(actionKey, actionName, lParams)
      else:
        strA = "Action: {} {} - ".format(actionKey, actionName)
      if isCheck:
        strC = "Check: {} value: {} delta: {} ".format(lCheck, lCheckValue, lCheckDelta)
      else:
        strC = "No check"
      log.info (strA + strC)
      resDesc.write(strA + strC)
      resDesc.write("\n")

      # repeat lLoopNb times
      for lp in range (0,lLoopNb,1):
        # WAIT actions specific
        if actionKey in WaitActionKeys:
          if not isCheck: # config error! CHECK field is mandatory for WAIT actions!
            strr = "<CHECK KEY> field mandatory for action key {}! Exiting.".format(actionKey)
            log.error (strr)
            configFormat()

          validCheck = False
          res = None
          tickNb = 0
          # waiting period defined in <PARAM> field of WAIT action
          if not lParams[0]: # config error! <PARAM> value mandatory for WAIT action (= period)
            strr = "<PARAM> field mandatory for action key {}! Exiting.".format(actionKey)
            log.error (strr)
            configFormat()

          period = float(lParams[0])
          # compute total time to wait for in tick number
          maxTickNumber = int(tmo_s / period)
          if maxTickNumber < 1: # at least one loop
            maxTickNumber = 1

          while (not validCheck and tickNb < maxTickNumber): # loop on action while check is not ok
            res = applyAction(pxy, actionKey, actionName, lParamType, lParams)
            strr = "  raw result: {}".format(res)
            #resDesc.write(strr)

            validCheck = checkResult(res, lParamType, lCheck, lCheckValue, lCheckDelta)
            strr = "\n  check result: {}".format(validCheck)
            #resDesc.write(strr)

            sleep(period) # wait specified period
            #resDesc.write("\n")
            tickNb +=1

          strr1 = "  last raw result: {}".format(res)
          resDesc.write(strr1)
          strr2 = "\n  last check result: {}".format(validCheck)
          resDesc.write(strr2)

          # update counters
          CheckOK_cpt = CheckOK_cpt + int(validCheck == True)
          CheckKO_cpt = CheckKO_cpt + int(validCheck == False)

          if (not validCheck): # tmo
            strr3 = "\n  WAIT ended on timeout!"
            resDesc.write(strr3)

        else: # other actions
          res = applyAction(pxy, actionKey, actionName, lParamType, lParams)
          strr = "  raw result: {}".format(res)
          resDesc.write(strr)

          if isCheck: # check result if required
            check = checkResult(res, lParamType, lCheck, lCheckValue, lCheckDelta)
            strr = "\n  check result: {}".format(check)
            resDesc.write(strr)

            # update counters
            CheckOK_cpt = CheckOK_cpt + int(check == True)
            CheckKO_cpt = CheckKO_cpt + int(check == False)

            if StopOnCheckKo and not check: # do we have to stop if check KO?
              strer = "Value check KO! Exiting."
              log.error (strer)
              sys.exit(2)            

          if isMemorized: # memorize result if required
            (lType,lAction,lValue) = GlobalVariables[lGlobal]
            GlobalVariables[lGlobal] = (lType,lAction,res)
            strr = "MEMO var: {} - value: {}".format(lGlobal, res)
            log.info (strr)

      # end of loop

      # next action
      resDesc.write("\n\n")

  # end of config file
  resDesc.write("------------------------ END OF TEST --------------------------\n")

  # final report: number of checks OK & KO
  resDesc.write("\n---------------------------------------------------------------------\n")
  resDesc.write("#### FINAL REPORT ####\n")
  strf = "Checks OK: {} -- checks KO: {}".format(CheckOK_cpt, CheckKO_cpt)
  resDesc.write(strf)
  resDesc.write("\n---------------------------------------------------------------------\n")
  
  
# main function
def main(argv):
  "Main program"

  # args
  deviceName = None
  actionFile = None
  outputFile = None
  verboseMode = VERBOSE
  waitTimeout = TMO

  deviceProxy = None
  fileIn = None
  fileOut = None

  # Stop on Tango exception flag
  global StopOnException
  StopOnException = STOP_ON_FAIL

  # Stop on check KO flag
  global StopOnCheckKo
  StopOnCheckKo = STOP_ON_CHECK_KO
  
  # read command line
  try:                                
    opts, args = getopt.getopt(argv, "hd:a:o:v:t:s:c:", ["help","device=","action=","out=","verbose=","timeout=","stop=","check="])
  except getopt.GetoptError:
    usage()
    sys.exit(2) 

  for opt, arg in opts:
    if opt in ("-h", "--help"):
      usage()
      sys.exit()
    if opt in ("-d", "--device"):
      deviceName = arg
    if opt in ("-a", "--action"):
      actionFile = arg
    if opt in ("-o", "--out"):
      outputFile = arg
    if opt in ("-v", "--verbose"):
      verboseMode = (int(arg) == 1)
    if opt in ("-t", "--timeout"):
      waitTimeout = float(arg)
    if opt in ("-s", "--stop"):
      StopOnException = (int(arg) == 1)      
    if opt in ("-c", "--check"):
      StopOnCheckKo = (int(arg) == 1)
      
  # check args not empty
  if not deviceName :
    strr = "Option -d is mandatory (use -h for help). Exiting."
    log.error (strr)
    sys.exit(2)

  if not actionFile :
    strr = "Option -a is mandatory (use -h for help). Exiting."
    log.error (strr)
    sys.exit(2)

  if not outputFile :
    strr = "Option -o is mandatory (use -h for help). Exiting."
    log.error (strr)
    sys.exit(2)

  # check action file exists
  if not os.path.isfile(actionFile):
    strr = "Action file {} doesn't exist! Exiting.".format(actionFile)
    log.error (strr)
    sys.exit(2)

  # open proxy on device
  try:
    deviceProxy = DeviceProxy(deviceName) 
  except:
    strr = "Cannot connect to device {}! Exiting.".format(deviceName)
    log.error (strr)
    sys.exit(2)

  # open files
  try:
    fileIn = open(actionFile,'r')
  except:
    strr = "Cannot open action file! Exiting."
    log.error (strr)
    sys.exit(2)

  try:
    fileOut = open(outputFile,'w')
  except:
    strr = "Cannot open output file! Exiting."
    log.error (strr)
    sys.exit(2)

  # set verbose mode
  if verboseMode:
    log.basicConfig(format="%(message)s", level=log.DEBUG)
  else:
    log.basicConfig(format="%(message)s")

  # check wait timeout not null (possible infinite loop)
  if waitTimeout == 0:
    strr = "Wait timeout is null (possible infinite loop)! Exiting."
    log.error (strr)
    sys.exit(2)

  strr = "Parse action file: {}, execute actions on device: {} and send results in output file: {}...".format(actionFile, deviceName, outputFile)
  log.info (strr)
  
  
  # set header in output file
  hdr = defineHeader(opts)
  fileOut.write(hdr)
  
  # parse file and execute actions on device
  parseConfigFile(deviceProxy,fileIn,fileOut,waitTimeout)
  
  # close files and exit
  fileIn.close()
  fileOut.close()
  
  strr = "End of test. Bye."
  log.info (strr)
  sys.exit()
  
  
if __name__ == '__main__':
  main(sys.argv[1:])
