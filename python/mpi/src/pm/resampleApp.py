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
	src = '/lustre/share/Public/mostlsu/mpi/test/'  
	dst = '/lustre/share/Public/mostlsu/mpi/test/'
	readPre = ""
	readPost = ".tif"
	writePre = "test_"
	writePost = "_res.tif"
	reX = 0.5
	reY = 0.3
	begNum = 1  # input("input begNum\n")
	endNum = 9  # input("input endNum\n")
	terminateFlag = None
	eA = flf.getAvailSerial(begNum, endNum, src, readPre, readPost)
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
	reX = None
	reY = None
	terminateFlag = None

terminateFlag = comm.bcast(terminateFlag,root=0)
if terminateFlag == 1:
	print "the end: ",rank
	exit()

if rank !=0:
	sA = comm.recv(source=0,tag=77)

src = comm.bcast(src,root=0)
dst = comm.bcast(dst,root=0)
readPre=comm.bcast(readPre,root=0)
readPost=comm.bcast(readPost,root=0)
writePre=comm.bcast(writePre,root=0)
writePost=comm.bcast(writePost,root=0)
reX=comm.bcast(reX,root=0)
reY=comm.bcast(reY,root=0)

if sA == []:
	print name+" is not working!"
	exit()	


width = 0
height = 0
numStr = "%05d"%(sA[0])
filename = src + readPre + numStr + readPost
subimg = cv2.imread(filename,cv2.CV_LOAD_IMAGE_UNCHANGED)
width = subimg.shape[0]
height = subimg.shape[1]
newX = int(width * reX)
newY = int(height * reY)

for z in range(len(sA)):
	s = sA[z]
	numStr = "%05d"%(s)
	filename = src + readPre + numStr + readPost
	print " processing : " + readPre + numStr + readPost
	origImg = cv2.imread(filename,cv2.CV_LOAD_IMAGE_UNCHANGED)
	newImage = cv2.resize(origImg, (newY,newX))
	saveName = dst + writePre + numStr + writePost
	cv2.imwrite(saveName,newImage)

