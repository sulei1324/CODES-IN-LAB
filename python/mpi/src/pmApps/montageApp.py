import mpi4py
from mpi4py import MPI
import cv2, numpy as np
import sys, os
import cv,string,shutil
import findLostFile as flf
import allocateNum as aN

comm = MPI.COMM_WORLD
mpiSize = comm.Get_size()
rank = comm.Get_rank()
name = MPI.Get_processor_name()

if rank == 0:
    src ="G:\\sulei\\test\\"
    readPre = "test__"
    readPost = ".png"
    dst = "G:\\sulei\\test\\montage\\"
    writePre = "test_"
    writePost = "python.tif"
    begNum = 108       #input("Please input begin num\n")
    endNum = 460   # input("Please input end num\n")
    xBeg = 40         # input("xBeg:\n")
    xEnd = 45         # input("xEnd:\n")
    yBeg = 31        # input("yBeg:\n")
    yEnd = 35        # input("yEnd:\n")
    isReverse = 0   # input("is reverse?1:0\n")
    terminateFlag = None
    
    eA = flf.getAvailSerial(begNum, endNum, src, '', '')
    if eA == None:
        print "There is no file to dispose."
        terminateFlag = 1
    else:
        uA = aN.alloNum(mpiSize, eA)  
      
        for i in range(len(uA)):
            if i == 0:
                sA = uA[i]
            else:
                comm.send(uA[i],dest=i,tag=77)
        
else:
    sA = None
    src = None
    dst = None
    readPre = None
    readPost = None
    writePre = None
    writePost = None
    xBeg = None
    xEnd = None
    yBeg = None
    yEnd = None
    isReverse = None
    terminateFlag = None
  
terminateFlag = comm.bcast(terminateFlag,root=0)
print rank,terminateFlag
if terminateFlag == 1:
    print "the end: ",rank
    exit()

if rank !=0:
    sA = comm.recv(source=0,tag=77)
    
print sA,rank    
src = comm.bcast(src,root=0)
dst = comm.bcast(dst,root=0)
readPre = comm.bcast(readPre,root=0)
readPost = comm.bcast(readPost,root=0)
writePre = comm.bcast(writePre,root=0)
writePost = comm.bcast(writePost,root=0)
xBeg = comm.bcast(xBeg,root=0)
xEnd = comm.bcast(xEnd,root=0)
yBeg = comm.bcast(yBeg,root=0)
yEnd = comm.bcast(yEnd,root=0)
isReverse = comm.bcast(isReverse,root=0)

if sA == []:
    print name+" is not working!"
    exit()        
  
numStr = "%05d"%(sA[0])
xStr = "%d"%(xBeg)
yStr = "%d"%(yBeg)
filename = src + numStr + "\\" + readPre + numStr +"_" + xStr + "_" + yStr + readPost

subimg = cv2.imread(filename,cv2.CV_LOAD_IMAGE_UNCHANGED)
xWidth = subimg.shape[0]
yWidth = subimg.shape[1]
img = np.zeros((subimg.shape[0]*(yEnd-yBeg+1),subimg.shape[1]*(xEnd-xBeg+1)),np.uint8)


for z in range(len(sA)):
    s = sA[z]
    numStr = "%05d"%(s)
    print "processing " + writePre + numStr + writePost
    for i in xrange(yBeg,yEnd+1):
        for j in xrange(xBeg,xEnd+1):
            yStr = "%d"%(i)
            xStr = "%d"%(j)
            filename = src + numStr + "/" + readPre + numStr + "_" + xStr + "_" + yStr + readPost
            subimg = cv2.imread(filename,cv2.CV_LOAD_IMAGE_UNCHANGED)
            if isReverse == 0:
                img[(i-yBeg)*xWidth:(i+1-yBeg)*xWidth,(j-xBeg)*yWidth:(j+1-xBeg)*yWidth] = subimg
            if isReverse == 1:
                subimg = subimg[:,::-1]
                img[(i-yBeg)*xWidth:(i+1-yBeg)*xWidth,(j-xBeg)*yWidth:(j+1-xBeg)*yWidth] = subimg
    cv2.imwrite(dst + writePre + numStr + writePost,img)
