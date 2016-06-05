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
	src = '/lustre/share/Public/mostlsu/mpi/test/'  
	dst = '/lustre/share/Public/mostlsu/mpi/test/'
	readPre = ""
	readPost = ".tif"
	writePre = "crop_"
	writePost = ".tif"
	begNum = 5      # input("Please input begin num")
	endNum = 10     #  input("Please input end num")
	cropRange = [300,300,300,300]
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
	writePre = None
	writePost = None
	cropRange=None
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
writePre = comm.bcast(writePre,root=0)
writePost = comm.bcast(writePost,root=0)
cropRange = comm.bcast(cropRange,root=0)

if sA == []:
	print name+" is not working!"
	exit()     

x = cropRange[0]
y = cropRange[1]
w = cropRange[2]
h = cropRange[3]

for z in range(len(sA)):
	s = sA[z]
	numStr = "%05d"%(s)
	filename = src + readPre + numStr + readPost
	savedName = dst+writePre+numStr+"_%d_%d_%d_%d"%(cropRange[0],cropRange[1],cropRange[2],cropRange[3])+writePost
	print " processing : " + readPre + numStr + readPost
	origImg = cv2.imread(filename,cv2.CV_LOAD_IMAGE_UNCHANGED)
	tmpImg = origImg[y:y+h,x:x+w]
	cv2.imwrite(savedName,tmpImg)

