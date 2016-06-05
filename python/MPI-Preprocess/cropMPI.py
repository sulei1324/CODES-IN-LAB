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
	configFile = "./cropInfo.ini"
	f=open(configFile,"r")
	lines = f.readlines()
	f.close()
	readPre=lines[0].replace('\n','')
	readPost=lines[1].replace('\n','')
	writePre=lines[2].replace('\n','')
	writePost=lines[3].replace('\n','')
	cropRange=[]
	#print lines
	#read all range
	for i in xrange(4, len(lines)):
		numList = string.split(lines[i],' ') 
		cropRange.append([string.atoi(numList[0]), string.atoi(numList[1]), string.atoi(numList[2]),string.atoi(numList[3])])
	#print cropRange
	begNum=1000#input("input begNum\n")
	endNum=1050#input("input endNum\n")
	cropNum = len(cropRange)
	#print cropNum
	#size = 3
	index=np.zeros((size,2),np.int32)
	slice = int(max(np.ceil((endNum - begNum + 1)/np.float64(size)),1))
	#print slice
	for i in xrange(begNum, endNum + 1, slice):
		tmpBeg = i
		tmpEnd = min(endNum, i + slice-1)
		index[(i-begNum) / slice,:]=[tmpBeg,tmpEnd]
	print index	
	curBeg = index[0][0]
	curEnd = index[0][1]
	for i in xrange(1,size):
		comm.send(index[i],dest=i,tag=11)
else:
	readPre=None
        readPost=None
        writePre=None
        writePost=None
        cropRange=None
	curIndex = comm.recv(source=0,tag=11)
	#print curIndex
	curBeg = curIndex[0]
	curEnd = curIndex[1]
readPre=comm.bcast(readPre,root=0)
readPost=comm.bcast(readPost,root=0)
writePre=comm.bcast(writePre,root=0)
writePost=comm.bcast(writePost,root=0)
cropRange=comm.bcast(cropRange,root=0)
cropNum = len(cropRange)
exit()
imageList=[]
for i in xrange(cropNum):
	imageList.append(np.zeros((3,3),np.uint8))
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
	for j in xrange(0,cropNum):
		x = cropRange[j][0]
		y = cropRange[j][1]
		w = cropRange[j][2]
		h = cropRange[j][3]
		
		if imageList[j].shape[0] != w or imageList[0].shape[1] != h:
			imageList[j].resize(w, h)

		imageList[j] = origImg[x:x+w, y:y+h]
		print name + "save as " + writePre+numStr+"_%d_%d_crop"%(cropRange[j][0],cropRange[j][1]) + writePost
		#print imageList[j].shape
		cv2.imwrite(writePre+numStr+"_%d_%d_crop"%(cropRange[j][0],cropRange[j][1])+writePost,imageList[j])

