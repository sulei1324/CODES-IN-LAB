import string,os,shutil,time,math,cv2,cv,numpy
import findLostFile as flf
import allocateNum as aN
import mpi4py
from mpi4py import MPI

comm = MPI.COMM_WORLD
mpiSize = comm.Get_size()
rank = comm.Get_rank()
name = MPI.Get_processor_name()

if rank == 0:
	src = raw_input("Please input the source file address: \n")         # '/lustre/share/Public/mostlsu/mpi/test/'  
	dst = raw_input("Please input the destination file address: \n")    # '/lustre/share/Public/mostlsu/mpi/test/'
	readPre = raw_input("Please input the pre of the read image name: \n")
	readPost = raw_input("Please input the post of the read image name: \n")
	width = input("Please input the width of the read image: \n")
	height = input("Please input the height of the read  image: \n")
	xOffset = input("Please input the offset of the x: \n")
	yOffset = input("Please input the offset of the y: \n")
	begNum = input("Please input begin num: \n")
	endNum = input("Please input end num: \n")
	terminateFlag = None
	eA = flf.getAvailSerial(begNum, endNum, src, readPre, readPost)
	flf.printLostFile(begNum, endNum, src, readPre, readPost)
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
	width = None
	height = None
	xOffset = None
	yOffset = None
	terminateFlag = None

terminateFlag = comm.bcast(terminateFlag,root=0)
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
width = comm.bcast(width,root=0)
height = comm.bcast(height,root=0)
xOffset = comm.bcast(xOffset,root=0)
yOffset = comm.bcast(yOffset,root=0)

if sA == []:
	print "Process " + str(rank) + " in " + name + " is not working!"
	exit()     

for z in range(len(sA)):
	s = sA[z]
	numStr = "%05d"%(s)
	filename = src + readPre + numStr + readPost
	print " processing : " + readPre + numStr + readPost
	origImg = cv2.imread(filename,cv2.CV_LOAD_IMAGE_UNCHANGED)
	tmpImg = numpy.zeros((width, height))
	tmpImg[ : , xOffset : width] = origImg[ : , 0 : width - xOffset]
	cv2.imwrite(filename, tmpImg)


