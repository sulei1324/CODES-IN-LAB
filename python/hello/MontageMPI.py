from mpi4py import MPI
import cv2, numpy as np
import sys, os, string
comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()
#print size
#print rank
name = MPI.Get_processor_name()

import cv,cv2,os,string,shutil
import numpy as np
readPre="/lustre/share/Public/mostgroup/TDI010_Preprocess/TDI010_src/"
readMid1="test_"
readMid2=".jpg"
readPost=".jpg"
writePre="/lustre/share/Public/mostgroup/TDI010_Preprocess/python/"
writePost=".tif"
cacheDirName="zhouhangTest/"
tmpDir="/dev/shm/"+cacheDirName
if not os.path.exists(tmpDir):
	os.mkdir(tmpDir)
if rank == 0:
	begNum=input("Please input begin num\n")
	endNum=input("Please input end num\n")
	xBeg=input("xBeg:\n")
	xEnd=input("xEnd:\n")
	yBeg=input("yBeg:\n")
	yEnd=input("yEnd:\n")
	isReverse=input("is reverse?1:0\n")
	print "check files"
	for i in xrange(begNum, endNum+1):
        	numStr = "%05d"%(i)
        	filename = readPre+numStr+"/"
        	if os.path.exists(filename):
              	 	#print filename+" exists"
        	else:
                	print filename+" not exists"
                	exit(0)

	index=np.zeros((size,2),np.int32)
	slice = int(max(np.ceil((endNum - begNum + 1)/np.float64(size)),1))
	#print slice
	for i in xrange(begNum, endNum + 1, slice):
		tmpBeg = i
		tmpEnd = min(endNum, i + slice-1)
		index[(i-begNum) / slice,:]=[tmpBeg,tmpEnd]
	#print index	
	curBeg = index[0][0]
	curEnd = index[0][1]
	for i in xrange(1,size):
		comm.send(index[i],dest=i,tag=11)

else:
	begNum=None
	endNum=None
	xBeg=None
	xEnd=Node
	yBeg=None
	yEnd=None
	isReverse=Nonei
	curIndex = comm.recv(source=0,tag=11)
	curBeg = curIndex[0]
	curEnd = curIndex[1]
begNum=comm.bcast(begNum,root=0)
endNum=comm.bcast(endNum,root=0)
xBeg=comm.bcast(xBeg,root=0)
xEnd=comm.bcast(xEnd,root=0)
yBeg=comm.bcast(yBeg,root=0)
yEnd=comm.bcast(yEnd,root=0)
isReverse=comm.bcase(isReverse,root=0)

numStr="%05d"%(z)
xStr="%d"%(xBeg)
yStr="%d"%(yBeg)
filename=readPre+numStr+"/"+"test_"+numStr+"_"+xStr+"_"+yStr+readPost
cacheName=tmpDir+"test_"+numStr+"_"+xStr+"_"+yStr+readPost
shutil.copyfile(filename,cacheName)
subimg=cv2.imread(cacheName,cv2.CV_LOAD_IMAGE_UNCHANGED)
xWidth=subimg.shape[0]
yWidth=subimg.shape[1]
img=np.zeros((subimg.shape[0]*(yEnd-yBeg+1),subimg.shape[1]*(xEnd-xBeg+1)),np.uint8)
os.remove(cacheName)
#print img.shape
for z in xrange(curBeg, curEnd+1):
	numStr="%05d"%(z)
	print "processing "+"test_"+numStr+"python.tif"
	for i in xrange(yBeg,yEnd+1):
		for j in xrange(xBeg,xEnd+1):
			yStr="%d"%(i)
			xStr="%d"%(j)
			filename=readPre+numStr+"/"+"test_"+numStr+"_"+xStr+"_"+yStr+readPost
			cacheName=tmpDir+"test_"+numStr+"_"+xStr+"_"+yStr+readPost
			shutil.copyfile(filename,cacheName)
			subimg=cv2.imread(cacheName,cv2.CV_LOAD_IMAGE_UNCHANGED)
			os.remove(cacheName)
			if isReverse==0:
				img[(i-yBeg)*xWidth:(i+1-yBeg)*xWidth,(j-xBeg)*yWidth:(j+1-xBeg)*yWidth]=subimg
			if isReverse==1:
				subimg=subimg[:,::-1]
				img[(i-yBeg)*xWidth:(i+1-yBeg)*xWidth,(j-xBeg)*yWidth:(j+1-xBeg)*yWidth]=subimg
	cv2.imwrite(tmpDir+"test_"+numStr+"python.tif",img)
	shutil.move(tmpDir+"test_"+numStr+"python.tif",writePre+"test_"+numStr+"python.tif")
shutil.rmtree(tmpDir)
