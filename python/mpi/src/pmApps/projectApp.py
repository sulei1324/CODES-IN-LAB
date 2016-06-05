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
	src = "/lustre/share/Public/mostlsu/mpi/test/"
	dst = "/lustre/share/Public/mostlsu/mpi/test/"
	readPre = ""
	readPost = ".tif"
	writePre = "pro_"
	wirtePost = ".tif"
	begNum = 10      # input("Please input begin num")
	endNum = 30      #  input("Please input end num")
	blockNum = 4   #   input("Please input blockNum")
	terminateFlag = None
	eA = flf.getAvailSerial(begNum, endNum, src, readPre, readPost)
	if eA == None:
		print "There is no file to dispose."
		terminateFlag = 1
	else:
		uA = aN.alloNum4pro(mpiSize, eA,blockNum)  
		
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
	wirtePost = None
	blockNum = None
	terminateFlag = None


terminateFlag = comm.bcast(terminateFlag,root=0)
if terminateFlag == 1:
	print "the end: ",rank
	exit()

if rank !=0:
	sA = comm.recv(source=0,tag=77)

src = comm.bcast(src,root=0)
dst = comm.bcast(dst,root=0)
readPre = comm.bcast(readPre,root=0)
readPost = comm.bcast(readPost,root=0)
writePre = comm.bcast(writePre,root=0)
wirtePost = comm.bcast(wirtePost,root=0)
blockNum = comm.bcast(blockNum,root=0)

if sA == []:
	print name+" is not working!"
	exit()     


for j in range(0,len(sA), blockNum):
	s = j
	e = j + blockNum - 1	
	if e > len(sA)-1:
		e = len(sA)-1
	print "process begin: %05d  end : %05d"%(sA[s], sA[e])
	sS = "%05d"%(sA[s])
	eS = "%05d"%(sA[e])
	for i in range(s, e+1):
		n = sA[i]
		numStr = "%05d"%(n)
		filename = src + readPre+numStr+readPost
		if i == s:
			img1 = cv2.imread(filename,cv2.CV_LOAD_IMAGE_UNCHANGED)
			img3 = numpy.zeros(img1.shape,numpy.uint8)
		else:
			img1 = cv2.imread(filename,cv2.CV_LOAD_IMAGE_UNCHANGED)
		img3 = numpy.maximum(img1,img3)
	cv2.imwrite(dst+writePre+sS+"-"+eS+"project.tif",img3)
