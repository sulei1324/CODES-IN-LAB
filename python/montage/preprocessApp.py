import os
import creatMpiState as cms

processType= 2   #  input('What do you want? Enter 1 for AutoTar, 2 for Montage, 3 for Project, 4 for resample .\n')
nodeNum = 1      #  input('How many processes do you want to use?\n')
nodeName = "user-PC"      #  raw_input('Which node do you want to use?\n')
mpiType = 2        # raw_input("Which mpi do you use? Enter 1 for openmpi, 2 for mpich2\n")

mpiState = cms.newState(nodeName, nodeNum, processType, mpiType)
print mpiState

os.system(mpiState)




#   "/usr/mpi/gcc/openmpi-1.4.3/bin/mpirun -n 4 -host cu01 -host cu02 python ./mpiTest.py"