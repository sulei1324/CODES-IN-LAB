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


if rank == 0:
    src ="G:\\sulei\\workplace\\montage\\src\\"
    readPre = "test_"
    readPost = ".jpg"
    dst = "G:\\sulei\\workplace\\montage\\test\\"
    writePre = "mon_"
    writePost = ".tif"
    begNum = 1902       #input("Please input begin num\n")
    endNum = 1902    # input("Please input end num\n")
    xBeg = 40         # input("xBeg:\n")
    xEnd = 57         # input("xEnd:\n")
    yBeg = 31        # input("yBeg:\n")
    yEnd = 60        # input("yEnd:\n")
    isReverse = 1   # input("is reverse?1:0\n")
    
    
    eA = flf.getAvailSerial(begNum, endNum, src, '', '')
    if eA == None:
        print "There is no file to dispose."
        exit()
    uA = aN.alloNum(mpiSize, eA)  
        
        
    
    for i in range(len(uA)):
        if i == 0:
            sA = uA[i]
        else:
            comm.send(uA[i],dest=i,tag=77)
         
else:
    sA = comm.recv(source=0,tag=77)
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
   
 

numStr = "%05d"%(sA[0])
xStr = "%d"%(xBeg)
yStr = "%d"%(yBeg)
filename = src + numStr + "\\" + readPre + numStr +"_" + xStr + "_" + yStr + readPost
print filename
subimg = cv2.imread(filename,cv2.CV_LOAD_IMAGE_UNCHANGED)
height = subimg.shape[0]
width = subimg.shape[1]
print height,width
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
            print filename
            subimg = cv2.imread(filename,cv2.CV_LOAD_IMAGE_UNCHANGED)
            if isReverse == 0:
                img[(i-yBeg)*height:(i+1-yBeg)*height,(j-xBeg)*width:(j+1-xBeg)*width] = subimg
            if isReverse == 1:
                subimg = subimg[:,::-1]
                img[(i-yBeg)*height:(i+1-yBeg)*height,(j-xBeg)*width:(j+1-xBeg)*width] = subimg
#             cv2.imwrite(dst + writePre + "%d"%(i) + "%d"%(j) + "%d"%(isReverse)  + writePost,img) 
    cv2.imwrite(dst + writePre + numStr + writePost,img)
