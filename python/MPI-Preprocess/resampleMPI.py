from mpi4py import MPI
import cv2, numpy as np
import sys, os, string
comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()
#print size
#print rank
name = MPI.Get_processor_name()
#print name
if rank == 0:
	configFile = "./resampleInfo.ini"
	f=open(configFile,"r")
	lines = f.readlines()
	f.close()
	readPre=lines[0].replace('\n','')
	readPost=lines[1].replace('\n','')
	writePre=lines[2].replace('\n','')
	writePost=lines[3].replace('\n','')
	newSize = lines[4].replace('\n','')
	[newX,newY] = string.split(newSize,' ')
	newX = string.atoi(newX)
	newY = string.atoi(newY)
	#print newX,newY
	begNum=input("input begNum\n")
	endNum=input("input endNum\n")
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
	readPre=None
        readPost=None
        writePre=None
        writePost=None
	newX=None
	newY=None
	curIndex = comm.recv(source=0,tag=11)
	#print curIndex
	curBeg = curIndex[0]
	curEnd = curIndex[1]
readPre=comm.bcast(readPre,root=0)
readPost=comm.bcast(readPost,root=0)
writePre=comm.bcast(writePre,root=0)
writePost=comm.bcast(writePost,root=0)
newX=comm.bcast(newX,root=0)
newY=comm.bcast(newY,root=0)
#newImage = np.zeros((3,3),np.uint8)
#print index
#other process
#exit()
#print "i am : %d"%(rank)
for i in xrange(curBeg, curEnd + 1):
	numStr = "%05d"%(i)
	filename = readPre+numStr+readPost
	print name+" processing : " + filename
	origImg = cv2.imread(filename,cv2.CV_LOAD_IMAGE_UNCHANGED)
	#print "origImg size: "
	#print  origImg.shape
		
	#if newImage.shape[0] != newX or newImage.shape[1] != newY:
	#	newImage.resize(newX, newY)

	newImage = cv2.resize(origImg, (newX,newY))
	saveName = writePre+numStr+"_%d_%d_resample"%(newX,newY) + writePost
	print name+" save as:"+saveName
	#print imageList[j].shape
	cv2.imwrite(saveName,newImage)

