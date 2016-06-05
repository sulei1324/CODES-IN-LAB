import os
import re
import numpy as np
import sys
import creatMpiState as cms
import funLib as flib
from numpy.core.multiarray import dtype



rootSrc = "G:\\sulei\\workplace\\mpi\\src\\test\\rawdata\\"

# samNum = raw_input("Please input sample number: \n")
samNum = "TDI111"
samSrc = rootSrc + samNum +"\\"
print samSrc

if not os.path.exists(samSrc):
    print "The data has not been uploaded!"
    exit()
else:
    levelRange = flib.getLevlRange(samSrc)
    print levelRange
    levelMax = levelRange[1]
    levelMin = levelRange[0]
    processType= 2   #  input('What do you want? Enter 1 for AutoTar, 2 for Montage, 3 for Project, 4 for resample, 5 for crop .\n')
#     if not flib.createFile(samNum,processType):
#         print "The data has been disposed!"
#         exit()
    nodeNum = 4    #  input('How many processes do you want to use?\n')
    nodeName = "user-PC user-PC user-PC user-PC"      #  raw_input('Which node do you want to use?\n')
    mpiType = 2        # raw_input("Which mpi do you use? Enter 1 for openmpi, 2 for mpich2\n")
    
    flib.createFile(samNum, processType)
    mpiState = flib.newState(nodeName, nodeNum, processType, mpiType)   
    if processType == 1:
        commandMpi = mpiState + " " + samNum + " " + str(levelMin) + " " +str(levelMax)    
    elif processType == 2:
        proBlock = 2
        commandMpi = mpiState + " " + samNum + " " + str(levelMin) + " " +str(levelMax) + " " + str(proBlock)
    elif processType == 3:
        proBlock = 2
        xScale = 0.01
        yScale = 0.01
        zScale = 0.01
        commandMpi = mpiState + " " + samNum + " " + str(levelMin) + " " +str(levelMax) + " " + str(proBlock) + " " + str(xScale) + " " + str(yScale)
     
 
    print commandMpi
    os.system(commandMpi)



#   "/usr/mpi/gcc/openmpi-1.4.3/bin/mpirun -n 4 -host cu01 -host cu02 python ./mpiTest.py"