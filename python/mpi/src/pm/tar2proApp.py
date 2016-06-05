import string
import mpi4py
from mpi4py import MPI
import sys
import funLib as flib

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
mpiSize = comm.Get_size()
name = MPI.Get_processor_name()

if rank == 0:
    begNum = int(sys.argv[2])
    endNum = int(sys.argv[3])
    samNum = sys.argv[1]
    blockNum = int(sys.argv[4])
    srcRoot = "G:\\sulei\\workplace\\mpi\\src\\test\\rawdata\\"
    dstRoot = "G:\\sulei\\workplace\\mpi\\src\\test\\result\\"
    print begNum,endNum,samNum,rank
    tarPre = ''       # string
    tarPost = '.tar'      # string
    tarSrc = srcRoot + samNum + "\\"       # string
    tarDst = dstRoot + samNum + "\\" + "src\\"
    monSrc = tarDst
    monDst = dstRoot + samNum + "\\"  + "montage\\"
    proSrc = monDst
    proDst = dstRoot + samNum + "\\"  + "project\\"
    terminateFlag = None
#    flf.printLostFile(begNum, endNum, srcPath, readPre, readPost)
    eA = flib.getAvailSerial(begNum, endNum, tarSrc, tarPre, tarPost)
    if eA == None:
        print "There is no file to dispose."
        terminateFlag = 1
    else:
        uA = flib.alloNum4pro(mpiSize, eA,blockNum)  
       
        for i in range(len(uA)):
            if i == 0:
                sA = uA[i]
            else:
                comm.send(uA[i],dest=i,tag=77)
       
else:
    sA = None
    tarPre = None
    tarPost = None
    tarSrc = None
    tarDst = None
    monSrc = None
    monDst = None
    blockNum = None
    proSrc = None
    proDst = None
    terminateFlag = None
 
terminateFlag = comm.bcast(terminateFlag,root=0)
print rank,terminateFlag
if terminateFlag == 1:
    print "the end: ",rank
    exit()
 
if rank !=0:
    sA = comm.recv(source=0,tag=77)
     
print sA,rank    
tarPre = comm.bcast(tarPre,root=0)
tarPost = comm.bcast(tarPost,root=0)
tarSrc = comm.bcast(tarSrc,root=0)
tarDst = comm.bcast(tarDst,root=0)
monSrc = comm.bcast(monSrc,root=0)
monDst = comm.bcast(monDst,root=0)
blockNum = comm.bcast(blockNum,root=0)
proSrc = comm.bcast(proSrc,root=0)
proDst = comm.bcast(proDst,root=0)
  
if sA == []:
    print  "rank " + str(rank) + " in " + name +" is not working!"
    exit()     
   

# flib.autoTar(sA, tarSrc + tarPre, tarPost, tarDst)
# 
# flib.montage(sA,monSrc,monDst)

flib.project(sA, proSrc, proDst, blockNum)
